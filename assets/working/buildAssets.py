# Export map tiles to custom tilemap binary format
# Also copy image assets to resources
#
# Format: 
# Name                  type            bytes
# map width             ushort          2
# map height            ushort          2
# tile width            ushort          2
# tile height           ushort          2
# texture width         ushort          2
# texture height        ushort          2
# layer tiles           ushort          width*height*2

import os, struct, shutil
import xml.etree.ElementTree as ET

inFile = "map.tmx"
outFile = "../resources/map"

def writeFile():
    pass

def exportMap():
    root = ET.parse(inFile).getroot()
    layer = root.find("layer")
    tileset = root.find("tileset")
    
    if layer is not None and tileset is not None:
        out = open(outFile, "wb")
        
        #write map width/heoght
        out.write(struct.pack("HH", int(layer.attrib["width"]), int(layer.attrib["height"])))

        #write tile width and height
        out.write(struct.pack("HH", int(tileset.attrib["tilewidth"]), int(tileset.attrib["tileheight"])))
        
        #write texture image width and height
        image = tileset.find("image");
        out.write(struct.pack("HH", int(image.attrib["width"]), int(image.attrib["height"])))
        
        #write tiles
        data = layer.find("data")
        lines = filter(len, data.text.split('\n')) #filter empty elements, split by '\n'
        for line in lines:
            tiles = filter(len, line.split(',')) #filter empty elements, split by ','
            for tile in tiles:
                out.write(struct.pack("H", int(tile)))
        
        out.close()

def copyAssets():
    #copy image map tiles
    shutil.copyfile("tiles.png", "../resources/tiles.png")

print("Exporting map")
exportMap()
copyAssets()
print("Done.")
