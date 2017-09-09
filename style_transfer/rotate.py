from PIL import Image

image = Image.open('output9.jpg')
img = image.rotate(90)
img.save('rotated.jpg')

img.show()