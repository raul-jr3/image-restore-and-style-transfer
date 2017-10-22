import numpy as np
import cv2
import os
import argparse
from matplotlib import pyplot as plt

parser = argparse.ArgumentParser(description = "a basic denoiser which uses OpenCV")
parser.add_argument('--input', required = True, type = str, help = "path to the image to be denoised")
parser.add_argument('--output', required = True, type = str, help = 'name to be given to the output image')
args = parser.parse_args()


input_img = args.input
img = cv2.imread(input_img)

dst = cv2.fastNlMeansDenoisingColored(img,None,10,10,7,21)

result = args.output

cv2.imwrite(result, dst)
plt.subplot(121),plt.imshow(img)
plt.subplot(122),plt.imshow(dst)
plt.show()
