import os

# list files in data_out folder
FOLDER = 'data_img'
FOLDER_ANIM = 'data_anim'
FILE_NAME = "draw_images"
USE_ANIMATION = True

files = [os.path.splitext(f)[0] for f in os.listdir("../include/" + FOLDER) if os.path.isfile(
    os.path.join("../include/" + FOLDER, f)) and os.path.splitext(f)[1] == ".h"]

files_anim = [os.path.splitext(f)[0] for f in os.listdir('../include/' + FOLDER_ANIM) if os.path.isfile(
    os.path.join('../include/' + FOLDER_ANIM, f)) and os.path.splitext(f)[1] == ".h"]


# Define {t}, corresponds to tab (spaces or \t)
mytab = "    "

# init empty strings to contain file contents
header_file = "// this file is auto generated. Do not change, changes will be undone on update.\n\n"
source_file = "// this file is auto generated. Do not change, changes will be undone on update.\n\n"

# add include statements
header_file += "#ifndef {fname}_H\n".format(fname=FILE_NAME.upper())
header_file += "#define {fname}_H\n\n".format(fname=FILE_NAME.upper())
header_file += "#include <Arduino.h>\n"
header_file += "#include \"displayFunctions.h\"\n"
header_file += "// Include all data, contains size definitions and data\n"

source_file += "#include \"{fn}.h\"".format(fn=FILE_NAME)

# include all headers
for f in files:
    header_file += "#include \"{data_folder}\\{hfile}.h\"\n".format(data_folder=FOLDER, hfile=f)

source_file += "\n\n// All functions to display the bitmaps\n"
header_file += "\n\n// All functions to display the bitmaps\n"

# write body of function and source per header
for f in files:
    header_file += "void display_{img}();\n".format(img=f)
    source_file += ("void display_{img}()\n"
                    "{{\n"
                    "{t}display.clearDisplay();\n"
                    "{t}display.drawBitmap((128 - {img}_width) / 2, (64 - {img}_height) / 2, {img}_data, {img}_width, {img}_height, 1);\n"
                    "{t}display.display();\n"
                    "}}\n\n"
                    .format(img=f, t=mytab))

header_file += "\n\n"
source_file += "\n\n"

source_file += "// Functions to draw the bitmaps at x,y\n"
header_file += "// Functions to draw the bitmaps at x,y\n"

# write body of function and source per header
for f in files:
    header_file += "mysize draw_{img}(int x, int y);\n".format(img=f)
    source_file += ("mysize draw_{img}(int x, int y)\n"
                    "{{\n"
                    "{t}display.drawBitmap(x, y, {img}_data, {img}_width, {img}_height, 1);\n"
                    "{t}return mysize{{{img}_width, {img}_height}};\n"
                    "}}\n\n"
                    .format(img=f, t=mytab))

header_file += "\n\n"
source_file += "\n\n"

# // array with pointers to all functions
# mysize (*FunctionPointers[])(int, int) = {
#     draw_pink_pant,
#     draw_rain,
#     draw_rowing,
#     draw_samsung,
#     draw_shock,
# };
header_file += "#define NUM_IMG_POINTERS {num}\n\n".format(num=len(files))
source_file += "mysize (*ImgDrawPointers[])(int, int) = {\n"
for f in files:
    source_file += "{t}draw_{img},\n".format(img=f, t=mytab)
source_file += "};\n\n"

# write function that draws all images
header_file += "void display_all_images(int delay_ms);\n"
source_file += "void display_all_images(int delay_ms)\n{\n"
for f in files:
    # source_file += ("{t}display.clearDisplay();\n"
    #                 "{t}draw_{img}();\n"
    #                 "{t}display.display();\n"
    #                 "{t}delay(delay_ms);\n\n"
    #                 .format(img=f, t=mytab))
    source_file += ("{t}display_{img}();\n"  # draw_{img} already has display.clearDisplay() and display.display()
                    "{t}delay(delay_ms);\n\n"
                    .format(img=f, t=mytab))
source_file += "}\n"

# and stuff for animations

if USE_ANIMATION:
    header_file += "\n\n// include animation data\n\n"
    for f in files_anim:
        header_file += "#include \"{data_folder}\\{hfile}.h\"\n".format(
            data_folder=FOLDER_ANIM, hfile=f)

    header_file += "\n\n"
    source_file += "\n\n"

    for f in (f for f in files_anim if "blink" in f):
        header_file += "void animate_{img}();\n".format(img=f)

        source_file += ("void animate_{img}()\n"
                        "{{\n"
                        "{t}int num_iter = 0;\n"
                        "{t}int num_loops = 5;\n"
                        "{t}\n"
                        "{t}while (num_iter < num_loops)\n"
                        "{t}{{\n"
                        "{t}{t}num_iter++;\n"
                        "{t}{t}for (int i = 0; i < {img}_frames; i++)\n"
                        "{t}{t}{{\n"
                        "{t}{t}{t}display.clearDisplay();\n"
                        "{t}{t}{t}display.drawBitmap((128 - {img}_width) / 2, (64 - {img}_height) / 2, {img}_data[i], {img}_width, {img}_height, 1);\n"
                        "{t}{t}{t}display.display();\n"
                        "{t}{t}{t}if (i == 0)\n"
                        "{t}{t}{t}{t}delay(3000);\n"
                        "{t}{t}{t}else\n"
                        "{t}{t}{t}{t}delay(50);\n"
                        "{t}{t}}}\n"
                        "{t}}}\n"
                        "}}\n".format(img=f, t=mytab))

    for f in (f for f in files_anim if "stick" in f):
        header_file += "void animate_{img}();\n".format(img=f)

        source_file += ("void animate_{img}()\n"
                        "{{\n"
                        "{t}int num_iter = 0;\n"
                        "{t}int num_loops = 1;\n"
                        "{t}if ({img}_frames < 20)\n"
                        "{t}{t}num_loops = 5;\n"
                        "{t}{t}\n"
                        "{t}while (num_iter < num_loops)\n"
                        "{t}{{\n"
                        "{t}{t}num_iter++;\n"
                        "{t}{t}for (int i = 0; i < {img}_frames; i++)\n"
                        "{t}{t}{{\n"
                        "{t}{t}{t}display.clearDisplay();\n"
                        "{t}{t}{t}display.drawBitmap((128 - {img}_width) / 2, (64 - {img}_height) / 2, {img}_data[i], {img}_width, {img}_height, 1);\n"
                        "{t}{t}{t}display.display();\n"
                        "{t}{t}{t}delay(50);\n"
                        "{t}{t}}}\n"
                        "{t}}}\n"
                        "}}\n".format(img=f, t=mytab))

    num_stick = 0
    num_blink = 0
    source_file += "\nvoid (*BlinkDrawPointers[])() = {\n"
    for f in (f for f in files_anim if "blink" in f):
        source_file += "{t}animate_{img},\n".format(img=f, t=mytab)
        num_blink += 1
    source_file += "};\n\n"

    source_file += "\nvoid (*StickDrawPointers[])() = {\n"
    for f in (f for f in files_anim if "stick" in f):
        source_file += "{t}animate_{img},\n".format(img=f, t=mytab)
        num_stick += 1

    source_file += "};\n\n"

    header_file += "#define NUM_BLINK_POINTERS {num}\n\n".format(num=num_blink)
    header_file += "#define NUM_STICK_POINTERS {num}\n\n".format(num=num_stick)


# void animate_blink5()
# {
#     for (int i = 0; i < blink5_frames; i++)
#     {
#         display.clearDisplay();
#         display.drawBitmap((128 - blink5_width) / 2, (64 - blink5_height) / 2, blink5_data[i], blink5_width, blink5_height, 1);
#         display.display();
#         if (i == 0)
#         {
#             delay(5000);
#         }
#         else
#         {
#             delay(10);
#         }
#     }
# }


# endif in header
header_file += "\n#endif\n"


# write to file
f_header = open("../include/" + FILE_NAME + ".h", "w")
f_source = open("../src/" + FILE_NAME + ".cpp", "w")
print(source_file, file=f_source)
print(header_file, file=f_header)

print("source and header files written!")
