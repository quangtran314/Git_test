#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

#include "common.h"

class View : public QGraphicsView
{
    Q_OBJECT

private:
    class QElapsedTimer *fpsTimer;
    int frameCount;
    int tick;

protected:
    void paintEvent(class QPaintEvent *event) override;

public:
    View(QWidget* parent);
    ~View();

    float fps();

};

#endif // VIEW_H
