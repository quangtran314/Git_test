#include "mainwindow.h"

#include <QSettings>
#include <QTimer>
#include <QScreen>
#include <QtOpenGL>
#include <QString>

#include "view/view.h"
#include "game/game.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){

    settings = new QSettings(QApplication::organizationName(), QApplication::applicationName(), this);
    qDebug("abc " + (settings->fileName()).toLatin1() + " def");

    graphicsView = new View(this);
    graphicsView->setFixedSize(settings->value(CONFIG_SCREENWIDTH, GAME_DEFAULT_SCREENWIDTH).toInt(), settings->value(CONFIG_SCREENHEIGHT, GAME_DEFAULT_SCREENHEIGHT).toInt());

    settings->beginGroup(CONFIG_GENERAL);
    if(settings->value(CONFIG_FULLSCREEN, 0).toBool())
    {
        screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
        screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
        QTimer::singleShot(500, this, SLOT(showFullScreen()));
    }
    else
    {
        graphicsView->setFixedSize(settings->value(CONFIG_SCREENWIDTH, GAME_DEFAULT_SCREENWIDTH).toInt(), settings->value(CONFIG_SCREENHEIGHT, GAME_DEFAULT_SCREENHEIGHT).toInt());
        screenHeight = graphicsView->height();
        screenWidth = graphicsView->width();
    }
    settings->endGroup();

    settings->beginGroup(CONFIG_GRAPHICS);

    bool gpuRender = settings->value(CONFIG_OPENGL, GAME_DEFAULT_OPENGL_ENABLED).toBool();
    if(gpuRender)
    {
        QOpenGLWidget *glWidget = new QOpenGLWidget(this);
        graphicsView->setViewport(glWidget);


        graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    }
    else
    {
        bool fpsCap = settings->value(CONFIG_FPSCAP, GAME_DEFAULT_FPSCAP).toBool();
        int _config_viewportupdate = settings->value(CONFIG_VIEWPORTUPDATE, GAME_DEFAULT_VIEWPORTUPDATE).toInt();

        if(fpsCap)
        {
            if(_config_viewportupdate == 0)
            {
                graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
            }
            else if(_config_viewportupdate == 1)
            {
                graphicsView->setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);
            }
            else
            {
                graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
            }
        }
        else
        {
            prepareManualViewportUpdate();
        }
    }

    if(settings->value(CONFIG_ANTIALIASING, GAME_DEFAULT_ANTIALIASING_ENABLED).toBool())
        graphicsView->setRenderHint(QPainter::Antialiasing);
    else
        graphicsView->setRenderHint(QPainter::Antialiasing, 0);
    if(settings->value(CONFIG_SMOOTHPIXMAPTRANSFORM, GAME_DEFAULT_SMOOTHPIXMAPTRANSFORM_ENABLED).toBool())
        graphicsView->setRenderHint(QPainter::SmoothPixmapTransform);
    else
        graphicsView->setRenderHint(QPainter::SmoothPixmapTransform, 0);
    if(settings->value(CONFIG_HQANTIALIASING, GAME_DEFAULT_HQANTIALIASING_ENABLED).toBool())
        graphicsView->setRenderHint(QPainter::HighQualityAntialiasing);
    else
        graphicsView->setRenderHint(QPainter::HighQualityAntialiasing, 0);

    settings->endGroup();

    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setCentralWidget(graphicsView);
    adjustSize();

    game = new Game(graphicsView, settings, screenHeight, screenWidth);
    resizer = new QTimer(this);
    connect(resizer, SIGNAL(timeout()), this, SLOT(resizeTriggered()));

}

MainWindow::~MainWindow()
{
    settings->setValue(CONFIG_SCREENWIDTH, width());
    settings->setValue(CONFIG_SCREENHEIGHT, height());
    settings->sync();

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
        game = new Game(graphicsView, settings, newWidth, newHeight);
        resizer->stop();
    }

    resized = false;
}
