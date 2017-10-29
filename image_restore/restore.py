import numpy as np
import cv2
import os
import argparse
from PIL import Image, ImageFilter
from matplotlib import pyplot as plt

parser = argparse.ArgumentParser(description = "a basic denoiser which uses OpenCV")
parser.add_argument('--input', required = True, type = str, help = "path to the image to be denoised")
parser.add_argument('--output', required = True, type = str, help = 'name to be given to the output image')
parser.add_argument('--mode', required = True, type = str, help = "filter to be applied")
parser.add_argument('--mask', type = str, help = "mask to be applied")
args = parser.parse_args()


input_img = args.input

mode = args.mode
result = args.output

if mode == "denoise":

    img = cv2.imread(input_img)
    dst = cv2.fastNlMeansDenoisingColored(img,None,10,10,7,21)
    cv2.imwrite(result, dst)
    plt.subplot(121),plt.imshow(img)
    plt.subplot(122),plt.imshow(dst)
    plt.show()

elif mode == "unsharp":
    img = Image.open(input_img)
    img = img.filter(ImageFilter.UnsharpMask(radius = 9, percent = 150, threshold = 3))
    img.save(result)

elif mode == "inpaint":
    img = cv2.imread(input_img)
    mask = args.mask
    if not mask:
        raise ValueError("no mask provided. Provide a mask to be applied to the input image by specifying the --mask flag while running the program")
    mask = cv2.imread(mask, 0)
    dst = cv2.inpaint(img, mask, 3, cv2.INPAINT_TELEA)
    cv2.imwrite(result, dst)
