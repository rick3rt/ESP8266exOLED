#!/usr/bin/env python3
# pip install pillow to get the PIL module

import sys
from PIL import Image, ImageChops
import numpy as np
import os


screen_width = 128
screen_height = 64


def main(fn, id, threshold, file=None, ext=".jpg"):
    if file:
        f = open(os.path.join('../include/data_img', file + ".h"), "w")
        printto = f
        # and also save thumbnail of jpg
    else:
        printto = sys.stdout
    image = Image.open(os.path.join('img', fn + ext))
    image = rotate_image(image)
    image = resize_image(image, 200, 200)
    image = threshold_image(image, threshold)
    image = trim_image(image)
    image = resize_image(image, screen_width, screen_height)
    print(image.size, end='\t')

    print("\n"
          "#define {id}_width  {w}\n"
          "#define {id}_height {h}\n"
          "\n"
          "const uint8_t PROGMEM {id}_data[] = {{\n"
          .format(id=id, w=image.width, h=image.height), end='', file=printto)
    for y in range(0, image.height):
        for x in range(0, (image.width + 7) // 8 * 8):
            if x == 0:
                print("  ", end='', file=printto)
            if x % 8 == 0:
                print("B", end='', file=printto)

            bit = '1'
            if x < image.width and image.getpixel((x, y)) != 0:
                bit = '0'
            print(bit, end='', file=printto)

            if x % 8 == 7:
                print(",", end='', file=printto)
        print(file=printto)
    print("};", file=printto)
    if file:
        f.close()
        image.save(os.path.join('img_out', file + ".jpg"), "JPEG")


def resize_image(image, w, h):
    image.thumbnail((w, h), Image.ANTIALIAS)
    # image.thumbnail((screen_height, screen_width), Image.NEAREST)
    return image


def threshold_image(image, threshold):
    image = image.convert('L')  # create grayscale
    # image = image.convert('1')  # create binary image

    def fnth(x):
        return 255 if x > threshold else 0
    image = image.point(fnth, mode='1')
    return image


def rotate_image(image):
    w, h = image.size
    if h > w:
        image = image.rotate(90, expand=True)
    return image


def trim_image(im):
    bg = Image.new(im.mode, im.size, im.getpixel((0, 0)))
    diff = ImageChops.difference(im, bg)
    diff = ImageChops.add(diff, diff, 2.0, -100)
    bbox = diff.getbbox()
    if bbox:
        print('trimming!', end='\t')
        return im.crop(bbox)
    else:
        return im


def show_image(image):
    image.show()


if __name__ == '__main__':

    # get all files in dir
    onlyfiles = [f for f in os.listdir('img') if os.path.isfile(os.path.join('img', f))]
    for fn in onlyfiles:
        temp = os.path.splitext(fn)
        fn = temp[0]
        ext = temp[1]
        print("Saving {fname}".format(fname=fn), end='\t')
        main(fn, fn, 150, file=fn, ext=ext)
        print()

    # main(fn, id, 150, file=id)
