#!/usr/bin/env python
from PIL import Image
import os
import imghdr

texture_dir = "/Users/kasoki/Projects/opentp/textures"
atlas_dest = "/Users/kasoki/Projects/opentp/atlas"
atlas_name = "opentp_atlas"
atlas_output_format = "png"
atlas_size = (512, 512)

supported_image_formats = ("png", "jpg", "gif")

def get_supported_images():
	""" returns a list of image file names which are in the "texture_dir" directory """
	images = []

	for file_name in os.listdir(texture_dir):
		if imghdr.what(os.path.join(texture_dir, file_name)) in supported_image_formats:
			images.append(file_name)
			
	return images


if __name__ == "__main__":
	images = get_supported_images()
	
	im = Image.new("RGBA", atlas_size)
	
	i = 0
	j = 0
	
	for file in images:
		path = os.path.join(texture_dir, file)
		
		tmp_img = Image.open(path)
		
		im.paste(tmp_img, (i, j))
		
		i += 1
		
		if not i < 512:
			i = 0
			j += 1
	
	path = os.path.join(atlas_dest, "%s.%s" % (atlas_name, atlas_output_format))
	im.save(path, atlas_output_format)
