#ifndef SCENE_H
#define SCENE_H

#include "common.h"

#include <QGraphicsScene>
#include <QPropertyAnimation>
class Button;

class Scene : public QGraphicsScene
{
    Q_OBJECT

private:
    QImage groundImage;

    bool isClickAvailable[2];

    class QPainter *groundPainter;

protected:
    class Game *game;


    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;


public:
    Scene(class Game *parent_game, const QRectF& rect);
    ~Scene();


    Button *button[5];
    Button *item_button_play;
    Button *item_button_about;

    QGraphicsItem *item_pixmap_gameInfo;

    class QGraphicsTextItem *scorePresentPlay;

    QGraphicsPixmapItem *pipe[2][3];
    QGraphicsPixmapItem *ground;

    class Bird *bird;

    void gameOver(int score, int scoreRecord);
    void updateGround();
    void updateScore();
};

#endif // SCENE_H
