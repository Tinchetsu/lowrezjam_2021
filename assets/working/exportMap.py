# Export map tiles to binary format
# Format: 
# Name                  type        bytes
# Number of layers      ushort      2
# layer chunk                       (layer chunk) * (num of layers)
#
# Layer chunk:
# layer width           ushort      2
# layer height          ushort      2
# layer tiles           ushort      width*height*2

import os, struct, shutil
import xml.etree.ElementTree as ET

inFile = "map.tmx"
outFile = "../resources/map"

def writeFile():
    pass

def export():
    root = ET.parse(inFile).getroot()
    layers = root.findall("layer")
    out = open(outFile, "wb")
    
    #write number of layers
    out.write(struct.pack("H", len(layers)))
    
    #write layer chunks
    for layer in layers:
        out.write(struct.pack("HH", int(layer.attrib["width"]), int(layer.attrib["height"])))
        data = layer.find("data")
        lines = filter(len, data.text.split('\n')) #filter empty elements
        for line in lines:
            tiles = filter(len, line.split(','))
            for tile in tiles:
                out.write(struct.pack("H", int(tile)))
    out.close()

    #copy image map tiles
    shutil.copyfile("tiles.png", "../resources/tiles.png")

print("Exporting map")
export()
print("Done.")
