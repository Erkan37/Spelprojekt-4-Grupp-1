import os, sys
from wand.image import Image
import wand
import math 
  
def Log2(x): 
    return (math.log10(x) / 
            math.log10(2)); 
  
def isPowerOfTwo(n): 
    return (math.ceil(Log2(n)) == math.floor(Log2(n))); 

remove = False
json = False
pngs = True
for i in range(1, len(sys.argv)):
    if sys.argv[i] == '-r':
        remove = True
    elif sys.argv[i] == '--json':
        json = True
    elif sys.argv[i] == '--json-only':
        json = True
        pngs = False
    elif sys.argv[i] == '--po2':
        json = False
        pngs = False

print("DDS Converter:")

fileList = []

def Search(dir):
    for root, dirs, files in os.walk(dir):
        for name in files:
            if (name.endswith('.png') and pngs) or ((name.endswith('.json')) and json) or (name.endswith('.dds')):
                path = root + '/' + name
                if name.endswith('.dds'):
                    with Image(filename = path) as img:
                        if (not isPowerOfTwo(img.size[0]) or not isPowerOfTwo(img.size[1])):
                            print(path + ' is not power of two! (' + str(img.size[0]) + ', ' + str(img.size[1]) + ')')
                else:
                    fileList.append(path)
                    print("Found: " + path + ".")

print("Searching...")
Search(os.getcwd() + "/")

confirm = raw_input("Confirm? [y/n]")

if confirm == "y":
    print("\nConverting...")

    for i in range(0, len(fileList)):
        if fileList[i].endswith(".png"):
            with Image(filename = fileList[i]) as img:
                img.format = 'dds'
                img.compression = 'no'
                img.save(filename = fileList[i].replace('png', 'dds'))
                print("Converted " + fileList[i] + ' from PNG to DDS.')
            if remove:
                os.remove(fileList[i])
                print("Removed " + fileList[i] + ".")
        elif fileList[i].endswith(".json"):
            f = open(fileList[i], "rt")
            data = f.read()
            data = data.replace('.png', '.dds')
            f.close()
            f = open(fileList[i], "wt")
            f.write(data)
            f.close()
            print("Converted " + fileList[i] + ".")