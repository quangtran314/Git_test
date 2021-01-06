#include "view.h"

#include <QElapsedTimer>
#include <QPaintEvent>

View::View(QWidget *parent) : QGraphicsView(parent)
{
    frameCount = 0;
    tick = 0;

    fpsTimer = new QElapsedTimer();
    fpsTimer->start();

}

View::~View(){
    delete fpsTimer;
}

void View::paintEvent(QPaintEvent *event){
    ++frameCount;

    QGraphicsView::paintEvent(event);
}

float View::fps(){
    float elapsedTime = (float)(fpsTimer->elapsed());
    int _frameCount = frameCount;

    if(elapsedTime >= 1000.0){
        fpsTimer->restart();
        frameCount = 0;
    }

    return (1000.0f * _frameCount / elapsedTime);
}
