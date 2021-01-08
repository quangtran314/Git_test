#include "mainwindow.h"

#include <QSettings>
#include <QTimer>
#include <QScreen>
#include <QtOpenGL>
#include <QString>
#include <QGraphicsView>

#include "game/game.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){

    graphicsView = new QGraphicsView(this);
    graphicsView->setFixedSize(GAME_DEFAULT_SCREENWIDTH, GAME_DEFAULT_SCREENHEIGHT);

    graphicsView->setFixedSize(GAME_DEFAULT_SCREENWIDTH, GAME_DEFAULT_SCREENHEIGHT);
    screenHeight = graphicsView->height();
    screenWidth = graphicsView->width();

    prepareManualViewportUpdate();
    
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setCentralWidget(graphicsView);
    adjustSize();

    game = new Game(graphicsView, screenHeight, screenWidth);
    resizer = new QTimer(this);
    connect(resizer, SIGNAL(timeout()), this, SLOT(resizeTriggered()));

}

MainWindow::~MainWindow()
{
    delete game;
}

void MainWindow::prepareManualViewportUpdate(){
    graphicsView->setViewportUpdateMode(QGraphicsView::NoViewportUpdate);

    QTimer *renderTimer = new QTimer(this);
    renderTimer->setInterval(0);

    connect(renderTimer, &QTimer::timeout, [this](){
        graphicsView->viewport()->update();
    });
    renderTimer->start();
}

void MainWindow::moveEvent(QMoveEvent *event){
    QMainWindow::moveEvent(event);
}

void MainWindow::resizeEvent(QResizeEvent *event){
    QMainWindow::resizeEvent(event);

    if(!resizer->isActive()){
        resizer->start(100);
    }
    resized = true;
}

void MainWindow::resizeTriggered(){
    if(!resized){
        delete game;

        int newHeight = height();
        int newWidth = width();

        graphicsView->setFixedSize(newWidth, newHeight);
        adjustSize();
        graphicsView->setMinimumSize(GAME_DEFAULT_SCREENWIDTH, GAME_DEFAULT_SCREENHEIGHT);
        game = new Game(graphicsView, newWidth, newHeight);
        resizer->stop();
    }

    resized = false;
}
