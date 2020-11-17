import sys
import ezdxf
import tkinter
def print_line(e):
    print("Line on layer: %s\n" % e.dxf.layer)
    print("Start point: %s\n" % e.dxf.start)
    print("End point: %s\n" % e.dxf.end)

def print_ellipse(e):
    print("Ellipse on layer: %s\n" % e.dxf.layer)
    print("Center?: %s\n" % e.dxf.center)
    print("Major axis?: %s\n" % e.dxf.major_axis)
    print("minor axis(maybe): %s\n" % e.minor_axis)
    print("Ratio??: %s\n" % e.dxf.ratio)

def print_arc(e):
    print("Arc on layer: %s\n" % e.dxf.layer)
    print("Center?: %s\n" % e.dxf.center)
    print("Radius?: %s\n" % e.dxf.radius)
    print("Start angle?: %s\n" % e.dxf.start_angle)
    print("End angle?: %s\n" % e.dxf.end_angle)
    print("Start point?: %s\n" % e.start_point)
    print("End point?: %s\n" % e.end_point)
try:
    # doc = ezdxf.readfile("pythondrawing.dxf")
    doc = ezdxf.readfile("Drawing1.dxf")
except IOError:
    print("Not a DXF file")
    sys.exit(1)
except ezdxf.DXFStructureError:
    print("Invalid or corrupted DXF file.")
    sys.exit(2)

msp = doc.modelspace()
# for e in msp.query('LINE'):
#     print_line(e)

# i = 0
# for e in msp.query('ELLIPSE'):
#     i = i + 1
#     print(i)
#     print_ellipse(e)

for e in msp.query('ARC'):
    print_arc(e)