from PIL import Image, ImageFilter

image = Image.open('out.jpg')

image = image.filter(ImageFilter.SHARPEN)

image.save('sharp_rahul.jpg')

image.show()