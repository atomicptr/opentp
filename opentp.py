#!/usr/bin/env python
from PIL import Image
import os
import imghdr
import time

texture_dir = "/Users/kasoki/Projects/opentp/textures"
atlas_dest = "/Users/kasoki/Projects/opentp/atlas"
atlas_name = "opentp_atlas"
atlas_output_format = "png"
atlas_size = (512, 512)

supported_image_formats = ("png", "jpeg", "gif")

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

class Rectangle:
	def __init__(self, x, y, width, height):
		self.x = x
		self.y = y
		self.width = width
		self.height = height
	
	def left(self):
		return self.x
		
	def right(self):
		return self.x + self.width
	
	def top(self):
		return self.y
		
	def bottom(self):
		return self.y + self.height
		
	def to_tuple(self):
		return (self.x, self.y, self.width, self.height)
		
	def fits_in(self, rect):
		if self.width <= rect.width and self.height <= rect.height:
			return True
		else:
			return False

class Node:
	counter = 0
	steps = 0
	def __init__(self, rect):
		self.children = [None, None]
		self.image_name = None
		self.rect = rect
		self.parent = None
		self.id = Node.counter
		Node.counter += 1
		
	def is_leaf(self):
		if self.children == [None, None]:
			return True
			
		return False
		
	def insert(self, image_name):
		Node.steps += 1
		
		img = Image.open(os.path.join(texture_dir, image_name))
		
		new_image_rect = Rectangle(self.rect.x, self.rect.y, img.size[0], 
					img.size[1])
		
		# does the new image fits into our rectangle?
		if not new_image_rect.fits_in(self.rect):
			return None
		
		if self.is_leaf():
			if not self.image_name:				
				new_empty_rect = Rectangle(new_image_rect.right(), self.rect.y, 
					self.rect.width - new_image_rect.width, 
					self.rect.height - new_image_rect.height)
				
				img_parent_node = Node(Rectangle(new_image_rect.x, new_image_rect.y, 
					self.rect.width, new_image_rect.height))
				
				img_parent_node.parent = self
				self.children[0] = img_parent_node
				
				img_uncle_node = Node(Rectangle(img_parent_node.rect.bottom(),
					self.rect.y,
					img_parent_node.rect.width,
					self.rect.height - img_parent_node.rect.height))
					
				img_uncle_node.parent = self
				self.children[1] = img_uncle_node
				
				img_parent_node.children[0] = Node(new_image_rect)
				img_parent_node.children[1] = Node(new_empty_rect)
				
				img_parent_node.children[0].parent = img_parent_node
				img_parent_node.children[1].parent = img_parent_node
				
				img_parent_node.children[0].image_name = image_name
				
				return img_parent_node.children[0]
			else:
				return None
		else:
			for child in self.children:
				child.insert(image_name)
				
def copy_into_picture(image, node):
	if node.image_name:
		tmp_img = Image.open(os.path.join(texture_dir, node.image_name))
		image.paste(tmp_img, (node.rect.x, node.rect.y))#node.rect.to_tuple())

	for child in node.children:
		if child:
			copy_into_picture(image, child)

if __name__ == "__main__":
	images = get_supported_images()
	
	im = Image.new("RGBA", atlas_size)
	
	root = Node(Rectangle(0, 0, atlas_size[0], atlas_size[1]))
	
	counter = 0
	image_len = len(images)
	
	sq_pixels = atlas_size[0] * atlas_size[1]
	
	images = images[0:35]
	
	for image_name in images:
		path = os.path.join(texture_dir, image_name)

		Node.steps = 0
		root.insert(image_name)
		counter += 1
		print("Took %s steps. %s/%s images" % (Node.steps, counter, image_len))
		
		img = Image.open(path)
		
		sq_pixels -= (img.size[0] * img.size[1])
		
		print("\t%s Square Pixels remaining" % sq_pixels)
		
	
	copy_into_picture(im, root)
	
	path = os.path.join(atlas_dest, "%s.%s" % (atlas_name, atlas_output_format))
	im.save(path, atlas_output_format)
