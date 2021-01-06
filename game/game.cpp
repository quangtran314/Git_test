#include "game.h"

#include <QTimer>
#include <QImage>
#include <QPainter>
#include <QSettings>
#include <QEasingCurve>
#include <QTimer>

#include "mainwindow/mainwindow.h"
#include "view/view.h"
#include "bird/bird.h"
#include "button/button.h"
#include "scene/scene.h"
#include "physics/physics.h"

Game::Game(View *GraphicsView, QSettings *settings, int windowWidth, int windowHeight)
    : graphicsView(GraphicsView), screenWidth(windowWidth), screenHeight(windowHeight),  registry(settings)
{
    scoreRecord = 0;
    score = 0;

    gameFinished = 0;
    gameStarted = 0;
    gameActuallyStarted = 0;

    birdClosestPipe = 1;

    scaleFactor = GAME_DEFAULT_SCALEFACTOR;

    loadConfiguration();

    scene = new Scene(this, QRectF(0, 0, screenWidth, screenHeight));

    physics = new Physics(this, physicsTickRate, physicsComplexAnalysis, true, physicsSpeedFactor, physicsDisableCollisionDetection);
}

Game::~Game()
{
    delete physics;
    delete scene;
}

void Game::loadConfiguration()
{
    scaleFactor = registry->value(CONFIG_SCALEFACTOR, scaleFactor).toReal();

    scoreRecord = registry->value(CONFIG_SCORE_RECORD, 0).toInt();

    registry->beginGroup(CONFIG_PHYSICS);
    physicsTickRate = registry->value(CONFIG_PHYSICS_TICKRATE, PHYSICS_DEFAULT_TICKRATE).toInt();
    physicsComplexAnalysis = registry->value(CONFIG_PHYSICS_COMPLEXANALYSIS, PHYSICS_COMPLEXANALYSIS_ENABLED).toBool();
    physicsSpeedFactor = registry->value(CONFIG_PHYSICS_SPEEDFACTOR, PHYSICS_DEFAULT_SPEEDFACTOR).toReal();
    physicsDisableCollisionDetection = registry->value(CONFIG_PHYSICS_DISABLECOLLISIONDETECTION, PHYSICS_DEFAULT_DISABLECOLLISIONDETECTION).toBool();
    registry->endGroup();

}

int Game::getScore()
{
    return score;
}

int Game::getScoreRecord()
{
    return scoreRecord;
}

int Game::getScreenHeight()
{
    return screenHeight;
}

int Game::getScreenWidth()
{
    return screenWidth;
}

qreal Game::getScaleFactor()
{
    return scaleFactor;
}

void Game::clickEvent()
{
    if(gameActuallyStarted)
    {
        if(!isGameStarted())
        {
            scene->bird->stopOscillate();

            scene->fadeGroup(GROUP_NEWROUND, false, 100);

            if(physics)
                physics->switchOnlyGroundMove();

            gameStarted = true;
        }
        else
        {
        }

        if(scene->isGroupVisible(GROUP_NEWROUND))
            scene->fadeGroup(GROUP_NEWROUND, false, 5);

        scene->bird->rise();

        return;
    }
}

void Game::prepareNewRound()
{
    scene->flash(Qt::black, 500, QEasingCurve::Linear);

    QTimer::singleShot(550, [this]() {

             int random1 = Physics::randInt(0, 2);
             int random2 = Physics::randInt(0, 1);

             if(random1 == 0)
                 scene->bird->setColor(Bird::BirdTypes::yellow);
             else if(random1 == 1)
                 scene->bird->setColor(Bird::BirdTypes::blue);
             else // == 2
                 scene->bird->setColor(Bird::BirdTypes::red);

             if(random2 == 0)
             {
                  graphicsView->setBackgroundBrush(QBrush(QPixmap(IMG_BACKGROUND_DAY).scaled(screenWidth,screenHeight)));
             }
             else // == 1
             {
                  graphicsView->setBackgroundBrush(QBrush(QPixmap(IMG_BACKGROUND_NIGHT).scaled(screenWidth,screenHeight)));
             }

             scene->fadeGroup(GROUP_NEWROUND, true, 1, GROUP_ROUNDEND);


             delete physics;
             physics = new Physics(this, physicsTickRate, physicsComplexAnalysis, false, physicsSpeedFactor, physicsDisableCollisionDetection);

             score = -1;
             updateScore();

             gameStarted = false;

             scene->bird->setPos(scene->bird->boundingRect().width() * 2.75, POS_Y_LOGO(screenHeight) + QPixmap(IMG_BIRD_YELLOW_UP).height() * 5);

             prepareFirstGame();

             scene->bird->setRotation(0);

             physics->start();
             physics->switchOnlyGroundMove();
    });
}

void Game::prepareFirstGame()
{
    scene->bird->startOscillate();

    gameFinished = false;
    gameActuallyStarted = true;
}


void Game::gameOver()
{
    physics->stop();

    if(score > scoreRecord)
    {
        registry->setValue(CONFIG_SCORE_RECORD, score);
        scoreRecord = score;
    }

    scene->gameOver(score, scoreRecord);

    gameFinished = true;
    gameActuallyStarted = false;
    birdClosestPipe = 1;
}

bool Game::isGameFinished()
{
    return gameFinished;
}

bool Game::isGameStarted()
{
    return gameStarted;
}

bool Game::isGameActuallyStarted()
{
    return gameActuallyStarted;
}

void Game::updateScore()
{
    ++score;

    scene->updateScore(score);
}
