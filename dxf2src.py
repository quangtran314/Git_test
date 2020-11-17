import ezdxf
from ezdxf.addons.dxf2code import entities_to_code

NAME = "dim_test"
DXF_FILE = r"D:\Work\Programming Stuffs\CNPM\Finals\Files\{}.dxf".format(NAME)
SOURCE_CODE_FILE = r"D:\Work\Programming Stuffs\CNPM\Finals\Files\{}.py".format(NAME)

doc = ezdxf.readfile(DXF_FILE)
msp = doc.modelspace()

source = entities_to_code(msp)

print('writing ' + SOURCE_CODE_FILE)
with open(SOURCE_CODE_FILE, mode='wt') as f:
    f.write(source.import_str())
    f.write('\n\n')
    f.write(source.code_str())
    f.write('\n')

print('done.')
