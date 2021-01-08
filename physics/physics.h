#ifndef PHYSICS_H
#define PHYSICS_H

#include <QPropertyAnimation>

#include "common.h"

class Physics
{
public:
    Physics(class Game *parent_game, int tickRate = 5, bool isOnlyGround = 0, qreal speedFactor = 1.0, bool isCollisionDetectionDisabled = 0);
    virtual ~Physics();

    void start();
    void stop();
    void switchOnlyGroundMove();

    bool isOnlyGround();

    static int randInt(int low, int high);

    typedef struct{
        qreal x;
        qreal y;
        qreal width;
        qreal height;
    }rectangle;

private:
    int pipeCriticX;

    qreal speedfactor;

    void moveGround();
    void movePipes();

    bool collisionDetectionDisabled;
    bool pipeMarkers[4];
    bool markers[3];

    rectangle birdRect;
    rectangle _itemPipe;

    class QTimer *physicsTimer;

    class QTransform *_transform;

protected:
    class Game *game;

    class Bird *bird;

    bool complexAnalysis;
    bool onlyGround;

    int updateInterval;

    virtual bool collisionCheck();
};

#endif // PHYSICS_H
