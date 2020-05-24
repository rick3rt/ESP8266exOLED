#!/usr/bin/env python3
# pip install pillow to get the PIL module

import sys
from PIL import Image
import numpy as np
import os


screen_width = 128
screen_height = 64


def main(fn, id, threshold, file=None):
    if file:
        f = open(os.path.join('data_out', file + ".h"), "w")
        printto = f
        # and also save thumbnail of jpg
    else:
        printto = sys.stdout
    image = Image.open(fn)
    image = resize_image(image)
    image = threshold_image(image, threshold)

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

            bit = '0'
            if x < image.width and image.getpixel((x, y)) != 0:
                bit = '1'
            print(bit, end='', file=printto)

            if x % 8 == 7:
                print(",", end='', file=printto)
        print(file=printto)
    print("};", file=printto)
    if file:
        f.close()
        image.save(os.path.join('img_out', file + ".jpg"), "JPEG")


def resize_image(image):
    image.thumbnail((screen_width, screen_height), Image.ANTIALIAS)
    # image.thumbnail((screen_height, screen_width), Image.NEAREST)
    return image


def threshold_image(image, threshold):
    image = image.convert('L')  # create grayscale
    # image = image.convert('1')  # create binary image

    def fnth(x):
        return 255 if x > threshold else 0
    image = image.point(fnth, mode='1')
    return image


def show_image(image):
    image.show()


if __name__ == '__main__':
    if len(sys.argv) < 3:
        print("Usage: {} <imagefile> <id>\n".format(sys.argv[0]), file=sys.stderr)
        sys.exit(1)
    fn = sys.argv[1]
    id = sys.argv[2]

    main(fn, id, 150, file=id)

    im = Image.open(fn)
    im = resize_image(im)
    im = threshold_image(im, 150)
    show_image(im)
