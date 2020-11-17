import ezdxf

# create a new file with official DXF version
doc = ezdxf.new('AC1032')
msp = doc.modelspace()

# create a square with polylines
points = [(4, 0), (8, 0), (8, 4), (4, 4), (4, 0)]
msp.add_lwpolyline(points)

# create an ellipse
msp.add_ellipse((15, 2), (-4, 0), 0.5)

# create an arc
msp.add_arc((12, 2.5), 8.3815, 17.4, 162.6, True)

doc.saveas('pythondrawing.dxf')