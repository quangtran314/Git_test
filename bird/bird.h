#ifndef BIRD_H
#define BIRD_H

#include "common.h"
#include <QObject>
#include <QGraphicsPixmapItem>


class Bird : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(qreal y READ y WRITE setY)

public:
    Bird(const QPointF &pos, const QPixmap& pixmap, const qreal& groundStarPosY, int scrWidth, int scrHeight, qreal scaleF);

    enum BirdTypes{
        yellow,
        blue,
        red
    };

    void setRotation(qreal angle);
    void startOscillate();
    void stopOscillate();
    void rise();
    void setColor(BirdTypes type);
    void fall();

private:
    enum WingStates{
        up,
        middle,
        down
    };

    WingStates wingState;

    bool wingDirection;
    bool oscillateDirection;

    BirdTypes birdType;

    qreal currentRotation;

    class QTimer *birdDesigner;

    class QPropertyAnimation *yAnimator;
    class QPropertyAnimation *oscillator;
    class QPropertyAnimation *rotator;

protected:
    qreal groundYPos;
    qreal scaleFactor;

    void rotate(const qreal &end, const int &duration, const QEasingCurve &curve);

    int screenHeight, screenWidth;

private slots:
    void gravitation();
    void designBird();
    void oscillate();
};

#endif // BIRD_H
