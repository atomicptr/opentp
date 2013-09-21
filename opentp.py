#!/usr/bin/env python
# Copyright (C) Christopher Kaster 2013. All Rights Reserved.
from PIL import Image
from array import array
from copy import copy
from json import JSONEncoder

import xml.etree.ElementTree as ET
import os
import imghdr
import time


#### settings
texture_dir = "/Users/kasoki/Projects/opentp/textures"
atlas_dest = "/Users/kasoki/Projects/opentp/atlas"
atlas_name = "opentp_atlas"
atlas_output_format = "png"
atlas_data_format = "json"
atlas_size = (4048, 128)

supported_image_formats = ("png", "jpeg", "gif")

### other stuff
atlas_data = []

#### profiler things
be_quiet_about_line_timestamps_below = 0.001

execution_start_time = time.time()
line_times_list = []
atlas_times_list = []



def get_supported_images():
	""" returns a list of image file names which are in the "texture_dir" directory """
	images = []

	for file_name in os.listdir(texture_dir):
		path = os.path.join(texture_dir, file_name)
	
		if imghdr.what(path) in supported_image_formats:
			img = Image.open(path)
			
			# check if image is smaller than atlas
			if img.size[0] > atlas_size[0] or img.size[1] > atlas_size[1]:
				raise ValueError("Error: %s has a size of %sx%s! Image size must" +
					" be smaller than the atlas size (%sx%s)" % (img.filename, 
					img.size[0], img.size[1], atlas_size[0], atlas_size[1]))
			
			images.append(file_name)
	
	print("Found %s valid images." % (len(images)))
	
	return images

def compare_image_size(img_name_1, img_name_2):
	img1 = Image.open(os.path.join(texture_dir, img_name_1))
	img2 = Image.open(os.path.join(texture_dir, img_name_2))
	
	return (img1.size[0] * img1.size[1]) - (img2.size[0] * img2.size[1])

def get_atlas_data():
	data = None

	if atlas_data_format is "json":
		return JSONEncoder().encode(atlas_data), "json"
	elif atlas_data_format is "xml":
		root = ET.Element("texture-atlas")
		
		for data in atlas_data:
			e = ET.SubElement(root, "texture", {
				"atlas_file": data["atlas_file"],
				"name": data["name"]})
			e_pos = ET.SubElement(e, "position", {
				"x": str(data["position"]["x"]),
				"y": str(data["position"]["y"]),
				"width": str(data["position"]["width"]),
				"height": str(data["position"]["height"])})
				
		return ET.tostring(root, encoding='utf8', method='xml'), "xml"
	else:
		raise ValueError("Unknown Atlas data format: %s" % atlas_data_format)

def get_matrix(matrix, x, y):
	return matrix[atlas_size[0] * y + x]
		

def set_matrix(matrix, x, y, val):
	matrix[atlas_size[0] * y + x] = val

def image_fits(matrix, image_size, x, y):
	image_width = image_size[0]
	image_height = image_size[1]
	
	for local_y in range(image_height):
		for local_x in range(image_width):
			if get_matrix(matrix, x + local_x, y + local_y) is '1':
				return False
	return True

def paste_image_into_atlas_image(matrix, atlas_image, image, x, y):
	image_width = image.size[0]
	image_height = image.size[1]
	
	atlas_image.paste(image, (x, y))
	
	for local_y in range(image_height):
		for local_x in range(image_width):
			set_matrix(matrix, x + local_x, y + local_y, '1')

if __name__ == "__main__":
	supported_images = get_supported_images()
	
	# sort images by the amount of pixels they'd take (largest first)
	supported_images = sorted(supported_images, cmp=compare_image_size, reverse=True)

	atlas_counter = 0
	
	while len(supported_images) > 0:
		# copy supported_images (this array exists only for performance reasons)
		images = copy(supported_images)
	
		# create new image
		atlas_image = Image.new("RGBA", atlas_size)
		
		# create matrix for atlas_image
		matrix = array('c')
	
		for i in range((atlas_size[0] + 1) * (atlas_size[1] + 1)):
			matrix.append('0')
		
		atlas_time_stamp = time.time()
		
		# fill atlas image with textures
		for y in range(atlas_size[1]):
			start = time.time()
			for x in range(atlas_size[0]):
		
				if get_matrix(matrix, x, y) is '1':
					continue
		
				for img_name in images:
					img = Image.open(os.path.join(texture_dir, img_name))
				
					# remove images which wouldn't fit anymore
					if y + img.size[1] > atlas_size[1]:
						images.remove(img_name)
						continue
				
					# check if the image may fit 
					if x + img.size[0] > atlas_size[0]:
						continue
				
					if image_fits(matrix, img.size, x, y):
						print("%s: fits into: pos: {%s, %s} size: {%s, %s} (%s left)" % (img_name, 
							x, y, img.size[0], img.size[1], len(supported_images)))
				
						paste_image_into_atlas_image(matrix, atlas_image, img, x, y)
					
						# add data to atlas
						atlas_data.append({
							"atlas_file": "%s_%s.%s" % (atlas_name, atlas_counter, atlas_output_format),
							"name": img_name,
							"position": {
									"x": x,
									"y": y,
									"width": img.size[0],
									"height": img.size[1]
							}})
					
						# remove image from supported_images and copied array
						supported_images.remove(img_name)
						images.remove(img_name)
					
			time_for_last_line = time.time() - start
		
			line_times_list.append(time_for_last_line)
		
			if time_for_last_line > be_quiet_about_line_timestamps_below:
				print("Line %s took %s seconds." % (y, time_for_last_line))
				
	
		path = os.path.join(atlas_dest, "%s_%s.%s" % (atlas_name, atlas_counter, atlas_output_format))
		atlas_image.save(path, atlas_output_format)
		
		print("Atlas #%s took %s seconds" % (atlas_counter, (time.time() - atlas_time_stamp)))
		atlas_times_list.append(atlas_time_stamp)
		
		atlas_counter += 1
	
	# save atlas data to file
	data, extension = get_atlas_data()

	file = open(os.path.join(atlas_dest, "%s.%s" % (atlas_name, extension)), "w")
	
	file.write(data)
	
	file.close()
	
	### stats output
	print("")
	print("###" * 5)
	print("")
	print("Whole Atlas creation took %s seconds." % (time.time() - execution_start_time))
	print("Average Atlas creation took %s seconds." % (sum(atlas_times_list) / float(len(atlas_times_list))))
	print("Average time per line was %s seconds." % (sum(line_times_list) / float(len(line_times_list))))
