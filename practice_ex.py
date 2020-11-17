import ezdxf

def test(fmt):
    doc = ezdxf.new('R2018', setup=('linetypes', 'styles'))
    msp = doc.modelspace()
    ezdxf.setup_dimstyle(doc, fmt)

    # Big rect
    rect1 = ([
        (150, 100),
        (800, 100),
        (800, 650),
        (150, 650),
        (150, 100),
    ])

    msp.add_lwpolyline(rect1)

    # Small rect
    rect2 = ([
        (1000, 100),
        (1030, 100),
        (1030, 650),
        (1000, 650),
        (1000, 100),
    ])

    msp.add_lwpolyline(rect2)

    dimh1 = msp.add_linear_dim(
        base=(150, 710), p1=(150, 710), p2=(800, 710),
        dimstyle=fmt,
        override={
        'dimtad':0,
        'dimclrd':1,
        }
    )
    dimh1.set_arrows(blk="")
    dimh1.render()

    dimv1 = msp.add_linear_dim(
        base=(100, 750), p1=(100, 100), p2=(100, 650), angle=90,
        dimstyle=fmt,
        override={
        'dimtad':0,
        'dimclrd':1,
        }
    )
    dimv1.set_arrows(blk="")
    dimv1.render()

    dimv2 = msp.add_linear_dim(
        base=(950, 750), p1=(950, 100), p2=(950, 650), angle=90,
        dimstyle=fmt,
        override={
        'dimtad':0,
        'dimclrd':1,
        }
    )
    dimv2.set_arrows(blk="")
    dimv2.render()

    doc.saveas('practice_ex.dxf')

test('EZ_CM_100_H25_CM')