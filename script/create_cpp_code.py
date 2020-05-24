import os

# list files in data_out folder
FOLDER = 'data_out'
FILE_NAME = "draw_images"
files = [os.path.splitext(f)[0] for f in os.listdir(FOLDER) if os.path.isfile(
    os.path.join(FOLDER, f)) and os.path.splitext(f)[1] == ".h"]

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
    header_file += "#include \"data\\{hfile}.h\"\n".format(hfile=f)

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
header_file += "#define NUM_POINTERS {num}\n\n".format(num=len(files))
source_file += "mysize (*FunctionPointers[])(int, int) = {\n"
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

# print("====================")
# print(source_file)
# print("====================")

# endif in header
header_file += "\n#endif\n"


# write to file
f_header = open(FILE_NAME + ".h", "w")
f_source = open(FILE_NAME + ".cpp", "w")
print(source_file, file=f_source)
print(header_file, file=f_header)
