import numpy as np
import cv2
from matplotlib import pyplot as plt
img = cv2.imread('imgs/noise.jpg')
dst = cv2.fastNlMeansDenoisingColored(img,None,10,10,7,21)
cv2.imwrite('noised.jpg', dst)
plt.subplot(121),plt.imshow(img)
plt.subplot(122),plt.imshow(dst)
plt.show()
