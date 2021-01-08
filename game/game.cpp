#include "game.h"

#include <QTimer>
#include <QImage>
#include <QPainter>
#include <QSettings>
#include <QEasingCurve>
#include <QTimer>
#include <QGraphicsView>

#include "mainwindow/mainwindow.h"
#include "bird/bird.h"
#include "button/button.h"
#include "scene/scene.h"
#include "physics/physics.h"

Game::Game(QGraphicsView *GraphicsView, int windowWidth, int windowHeight)
    : graphicsView(GraphicsView), screenWidth(windowWidth), screenHeight(windowHeight)
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

    physics = new Physics(this, physicsTickRate, true, physicsSpeedFactor, physicsDisableCollisionDetection);
}

Game::~Game(){
    delete physics;
    delete scene;
}

void Game::loadConfiguration(){
    scaleFactor = scaleFactor;

    scoreRecord = 0;

    physicsTickRate = PHYSICS_DEFAULT_TICKRATE;
    physicsComplexAnalysis = PHYSICS_COMPLEXANALYSIS_ENABLED;
    physicsSpeedFactor = PHYSICS_DEFAULT_SPEEDFACTOR;
    physicsDisableCollisionDetection = PHYSICS_DEFAULT_DISABLECOLLISIONDETECTION;

}

int Game::getScore(){
    return score;
}

int Game::getScoreRecord(){
    return scoreRecord;
}

int Game::getScreenHeight(){
    return screenHeight;
}

int Game::getScreenWidth(){
    return screenWidth;
}

qreal Game::getScaleFactor(){
    return scaleFactor;
}

void Game::clickEvent(){
    if(gameActuallyStarted){
        if(!isGameStarted()){
            scene->bird->stopOscillate();


            if(physics)
                physics->switchOnlyGroundMove();

            gameStarted = true;
        }
        else{
        }

        scene->bird->rise();
        scene->item_pixmap_gameInfo->setVisible(false);
        scene->scorePresentPlay->setVisible(true);

        return;
    }
}

void Game::prepareNewRound(){
    scene->scorePresentPlay->setVisible(false);
    scene->item_pixmap_gameInfo->show();

    QTimer::singleShot(550, [this]() {

         int random1 = Physics::randInt(0, 2);
         int random2 = Physics::randInt(0, 1);

         if(random1 == 0)
             scene->bird->setColor(Bird::BirdTypes::yellow);
         else if(random1 == 1)
             scene->bird->setColor(Bird::BirdTypes::blue);
         else // == 2
             scene->bird->setColor(Bird::BirdTypes::red);

         if(random2 == 0){
              graphicsView->setBackgroundBrush(QBrush(QPixmap(IMG_BACKGROUND_DAY).scaled(screenWidth,screenHeight)));
         }
         else // == 1
         {
              graphicsView->setBackgroundBrush(QBrush(QPixmap(IMG_BACKGROUND_NIGHT).scaled(screenWidth,screenHeight)));
         }



         delete physics;
         physics = new Physics(this, physicsTickRate, false, physicsSpeedFactor, physicsDisableCollisionDetection);

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

void Game::prepareFirstGame(){
    scene->bird->startOscillate();
    scene->item_button_about->hide();
    scene->item_button_play->hide();
    scene->item_pixmap_gameInfo->setVisible(true);

    gameFinished = false;
    gameActuallyStarted = true;
}


void Game::gameOver(){
    physics->stop();

    if(score > scoreRecord){
        scoreRecord = score;
    }

    scene->gameOver(score, scoreRecord);

    gameFinished = true;
    gameActuallyStarted = false;
    birdClosestPipe = 1;
}

bool Game::isGameFinished(){
    return gameFinished;
}

bool Game::isGameStarted(){
    return gameStarted;
}

bool Game::isGameActuallyStarted(){
    return gameActuallyStarted;
}

void Game::updateScore(){
    ++score;

    scene->updateScore();
}
