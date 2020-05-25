#!/usr/bin/env python3
# pip install pillow to get the PIL module

# TODO: include things as delays between frames, invert on or off. depends on image

from PIL import Image, ImageChops, GifImagePlugin
import numpy as np
import math
import os


screen_width = 128
screen_height = 64


def write_data_file(images, filename):
    f = open(os.path.join('../include/data_anim', filename + ".h"), "w")
    printto = f

    image = images[0]
    im_width = image.width
    im_height = image.height
    im_num_bytes = math.ceil(im_width / 8) * im_height
    im_num_frames = len(images)

    # header info:
    print("\n"
          "#define {id}_width  {w}\n"
          "#define {id}_height {h}\n"
          "#define {id}_bytes {num_bytes}\n"
          "#define {id}_frames {num_frames}\n"
          "\n"
          "const uint8_t PROGMEM {id}_data[{id}_frames][{id}_bytes] = {{\n"
          .format(id=filename, w=im_width, h=im_height, num_bytes=im_num_bytes, num_frames=im_num_frames), end='', file=printto)

    for image in frames:
        print("{", file=printto)
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
        print("},", file=printto)
    print("};", file=printto)
    f.close()


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


def get_bbox(im):
    bg = Image.new(im.mode, im.size, im.getpixel((0, 0)))
    diff = ImageChops.difference(im, bg)
    diff = ImageChops.add(diff, diff, 2.0, -100)
    return diff.getbbox()


def show_image(image):
    image.show()


def save_image(im, filename):
    im.save(os.path.join('anim_out', filename + ".jpg"), "JPEG")


def save_gif(frames, filename):
    out = os.path.join('anim_out', filename + ".gif")
    # frames[0] = frames[0].convert('P')
    frames[0].save(out, format="GIF", save_all=True, append_images=frames)


if __name__ == '__main__':

    # get all files in dir
    onlyfiles = [f for f in os.listdir('anim') if
                 os.path.isfile(os.path.join('anim', f)) and f[0] != '_']

    for fn in onlyfiles:
        fn_no_ext = os.path.splitext(fn)[0]
        im = Image.open('anim/' + fn)
        # im = threshold_image(im, 150)
        nframes = im.n_frames
        # print("{fn}\t number of frames:{nf}".format(fn=fn, nf=nframes))
        fskip = round(nframes / 20)
        fskip = max(1, fskip)
        # print(fskip)
        frame_range = range(nframes)
        if "blink" in fn_no_ext:
            frame_range_sel = range(0, nframes, fskip)
        else:
            frame_range_sel = range(nframes)
        # print(len(frame_range_sel))
        # first get bbox
        bbox_array = np.zeros((nframes, 4))
        for i in frame_range:
            im.seek(i)
            frame = Image.new('L', im.size)
            frame.paste(im, (0, 0), im.convert('L'))
            # BBOX: left, upper, right, and lower
            bbox_array[i, :] = get_bbox(frame)
        # get min of left and upper, max of right and lower
        bbox_im = np.concatenate((np.nanmin(bbox_array[:, 0:2], axis=0),
                                  np.nanmax(bbox_array[:, 2:4], axis=0)), axis=0)
        bbox_im = tuple(bbox_im)

        # crop frames to bbox, thumbnail, convert to black/white
        frames = []
        for i in frame_range:
            im.seek(i)
            frame = Image.new('L', im.size)
            frame.paste(im, (0, 0), im.convert('L'))
            frame = threshold_image(frame, 100)
            frame = frame.crop(bbox_im)
            frame = resize_image(frame, screen_width, screen_height)
            if i in frame_range_sel:
                # save_image(frame, fn_no_ext + "_{:03d}".format(i))
                frames.append(frame)

        # now create header file
        write_data_file(frames, fn_no_ext)
        for i in range(len(frames)):
            frames[i] = frames[i].convert('P')
        save_gif(frames, "anim_" + fn_no_ext)

        print("saved jpgs and gifs and headers for {}!".format(fn))

# for fn in onlyfiles:
#     temp = os.path.splitext(fn)
#     fn = temp[0]
#     ext = temp[1]
#     print("Saving {fname}".format(fname=fn), end='\t')
#     main(fn, fn, 150, file=fn, ext=ext)
#     print()
# main(fn, id, 150, file=id)
