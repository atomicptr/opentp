#!/usr/bin/env python
from PIL import Image
import os
import imghdr
import time
from array import array

texture_dir = "/Users/kasoki/Projects/opentp/textures"
atlas_dest = "/Users/kasoki/Projects/opentp/atlas"
atlas_name = "opentp_atlas"
atlas_output_format = "png"
atlas_size = (512, 512)

supported_image_formats = ("png", "jpeg", "gif")

be_quiet_about_line_timestamps_below = 0.001

execution_start_time = time.time()
line_times_list = []

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

def get_matrix(matrix, x, y):
	return matrix[atlas_size[0] * y + x]
		

def set_matrix(matrix, x, y, val):
	matrix[atlas_size[0] * y + x] = val

def image_fits(matrix, image_size, x, y):
	image_width = image_size[0]
	image_height = image_size[1]
	
	for local_y in range(image_height):
		for local_x in range(image_width):
			if get_matrix(matrix, x + local_x, y + local_y) is not '0':
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
	images = get_supported_images()
	
	# sort images by the amount of pixels they'd take (largest first)
	images = sorted(images, cmp=compare_image_size, reverse=True)
	
	# create matrix for atlas_image
	matrix = array('c')
	
	for i in range((atlas_size[0] + 1) * (atlas_size[1] + 1)):
		matrix.append('0')

	# create new image
	atlas_image = Image.new("RGBA", atlas_size)
	
	# fill atlas image with textures
	for y in range(atlas_size[1]):
		start = time.time()
		for x in range(atlas_size[0]):
		
			if(get_matrix(matrix, x, y) is not '0'):
				continue
		
			for img_name in images:
				img = Image.open(os.path.join(texture_dir, img_name))
				
				# check if the image may fit 
				if x + img.size[0] > atlas_size[0] or y + img.size[1] > atlas_size[1]:
					continue
				
				if image_fits(matrix, img.size, x, y):
					print("%s: fits into: pos: {%s, %s} size: {%s, %s}" % (img_name, 
						x, y, img.size[0], img.size[1]))
				
					paste_image_into_atlas_image(matrix, atlas_image, img, x, y)
					
					# remove image from array
					images.remove(img_name)
					
		time_for_last_line = time.time() - start
		
		line_times_list.append(time_for_last_line)
		
		if time_for_last_line > be_quiet_about_line_timestamps_below:
			print("Line %s took %s seconds." % (y, time_for_last_line))
				
	
	path = os.path.join(atlas_dest, "%s.%s" % (atlas_name, atlas_output_format))
	atlas_image.save(path, atlas_output_format)
	
	print("Atlas creation took %s seconds." % (time.time() - execution_start_time))
	print("Average time per line was %s seconds." % (sum(line_times_list) / float(len(line_times_list))))
