#ifndef GAME_H
#define GAME_H

#include "common.h"


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
    class QSettings *registry;

    class Physics *physics;

public:
    Game(class View *GraphicsView, class QSettings *settings, int windowWidth, int windowHeight);
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
    class View *graphicsView;
};

#endif // GAME_H
