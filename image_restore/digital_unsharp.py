from PIL import Image
from PIL import ImageFilter

image = Image.open('noised.jpg')

img = image.filter(ImageFilter.UnsharpMask(radius = 9, percent = 150, threshold = 3))

img.save('sharpened_palace.jpg')

img.show()