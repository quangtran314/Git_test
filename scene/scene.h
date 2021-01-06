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
    QPixmap pixmap_bigZero;
    QPixmap pixmap_smallZero;

    QImage image_mainScore;
    QImage image_endScore;
    QImage groundImage;

    bool flashStatus;
    bool isClickAvailable[2];

    class QGraphicsOpacityEffect *opacityEffect;
    class QGraphicsOpacityEffect **opacityEffectGroup[2];

    class QPropertyAnimation *opacityAnim;
    class QPropertyAnimation **opacityAnimGroup[2];

    class QPainter *groundPainter;

protected:
    class Game *game;

    Button *button[32];
    Button *item_button_play;
    Button *item_button_about;

    QGraphicsPixmapItem *item_pixmap_gameOver;
    QGraphicsPixmapItem *item_pixmap_scoreBoard;
    QGraphicsPixmapItem *item_pixmap_endScore;
    QGraphicsPixmapItem *item_pixmap_endScoreRecord;
    QGraphicsPixmapItem *item_pixmap_info;
    QGraphicsPixmapItem *item_pixmap_logo;
    QGraphicsPixmapItem *item_pixmap_gameReady;
    QGraphicsPixmapItem *item_pixmap_gameInfo;
    QGraphicsPixmapItem *item_pixmap_score;
    QGraphicsPixmapItem *item_pixmap_flash;

    QPixmap makeMainScore(int score);
    QPixmap makeEndingScore(int score, int *pos);

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;


public:
    Scene(class Game *parent_game, const QRectF& rect);
    ~Scene();

    QGraphicsPixmapItem *pipe[2][3];
    QGraphicsPixmapItem *ground;

    QGraphicsItem *group_item[8][GROUP_MAX_ITEM_COUNT];

    class Bird *bird;

    void flash(const QColor& color, int duration, const QEasingCurve& curve);
    void fadeGroup(int groupIndex, bool show, int duration, int group2Index = -1);
    void gameOver(int score, int scoreRecord);
    void updateGround();
    void updateScore(int score);
    bool isGroupVisible(int groupIndex);
};

#endif // SCENE_H
