from PIL import Image

image = Image.open('plain.png')
img = image.resize((5, 5))
img.rotate(180)
img.save('plained.png')

img.show()
