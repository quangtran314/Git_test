#ifndef GAME_H
#define GAME_H

#include "common.h"
#include <QGraphicsView>


class Game
{

private:
    bool gameFinished, gameStarted;
    bool gameActuallyStarted;
    bool physicsComplexAnalysis;
    bool physicsDisableCollisionDetection;

    int score, scoreRecord;
    int screenHeight, screenWidth;
    int physicsTickRate;

    qreal physicsSpeedFactor;
    qreal scaleFactor;

    void loadConfiguration();

protected:

    class Physics *physics;

public:
    Game(class QGraphicsView *GraphicsView, int windowWidth, int windowHeight);
    virtual ~Game();

    void clickEvent();
    void updateScore();
    void gameOver();
    void prepareFirstGame();
    void prepareNewRound();

    bool isGameFinished();
    bool isGameStarted();
    bool isGameActuallyStarted();

    int getScore();
    int getScoreRecord();
    int getScreenWidth();
    int getScreenHeight();

    int birdClosestPipe;

    qreal getScaleFactor();

    class Scene *scene;
    class QGraphicsView *graphicsView;
};

#endif // GAME_H
