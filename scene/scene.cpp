#include "scene.h"

#include <QTransform>
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsOpacityEffect>
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QPainter>
#include <QString>

#include "game/game.h"
#include "bird/bird.h"
#include "button/button.h"


Scene::Scene(Game *parent_game, const QRectF& rect) : QGraphicsScene(rect), game(parent_game)
{
    QPainter _painter;

    isClickAvailable[0] = true;
    isClickAvailable[1] = true;

    QPixmap background(IMG_BACKGROUND_DAY);
    background = background.scaled(game->getScreenWidth(), game->getScreenHeight());
    game->graphicsView->setBackgroundBrush(QBrush(background));

    game->graphicsView->setScene(this);
    game->graphicsView->setSceneRect(sceneRect());

    QPixmap pixmap_ground(IMG_GROUND_SEGMENT);
    PIXMAP_SCALE(pixmap_ground, game->getScaleFactor())
    groundImage = QImage(game->getScreenWidth() * 2, pixmap_ground.height(), QImage::Format_RGB32);
    groundImage.fill(0);
    groundPainter = new QPainter();
    groundPainter->begin(&groundImage);
    int _indicator = 0;
    int _counter = 0;
    for(; _counter < ((game->getScreenWidth() * 2) / pixmap_ground.width()); ++_counter)
    {
        groundPainter->drawPixmap(_indicator, 0, pixmap_ground.width(), pixmap_ground.height(), pixmap_ground);
        _indicator += pixmap_ground.width();
    }
    groundPainter->end();

    QImage buffer((_counter-1) * pixmap_ground.width(), pixmap_ground.height(), QImage::Format_RGB32);
    buffer = groundImage.copy(0,0,(_counter-1) * pixmap_ground.width(), pixmap_ground.height());
    groundImage = buffer.scaledToWidth(groundImage.width());
    ground = new QGraphicsPixmapItem(QPixmap::fromImage(groundImage));
    ground->setPos(0, game->getScreenHeight() - groundImage.height() + groundImage.height() / 7);

    QPixmap pixmap_play(IMG_BUTTON_PLAY);
    PIXMAP_SCALE(pixmap_play, game->getScaleFactor())
    item_button_play = new Button(game, pixmap_play, ButtonFuncs::play);
    item_button_play->setPos(game->getScreenWidth() / 2 - pixmap_play.width() * 1.2, ground->y() - pixmap_play.height());

    QPixmap pixmap_about(IMG_BUTTON_ABOUT);
    PIXMAP_SCALE(pixmap_about, game->getScaleFactor())
    item_button_about = new Button(game, pixmap_about, ButtonFuncs::about);
    item_button_about->setPos(game->getScreenWidth() - item_button_play->x() - pixmap_about.width(), item_button_play->y());

    QPixmap pixmap_gameInfo(IMG_GAMEINFO);
    PIXMAP_SCALE(pixmap_gameInfo, game->getScaleFactor())
    item_pixmap_gameInfo = new QGraphicsPixmapItem(pixmap_gameInfo);
    item_pixmap_gameInfo->setPos(game->getScreenWidth() / 2 - pixmap_gameInfo.width() / 2, game->getScreenHeight() / 2 - pixmap_gameInfo.height() / 3);
    item_pixmap_gameInfo->setVisible(false);

    scorePresentPlay = new QGraphicsTextItem();
    QFont mFont1("Consolas", 55, QFont::Bold);
    QString  htmlString1 =  QString::number(game->getScore());
    scorePresentPlay->setHtml(htmlString1);
    scorePresentPlay->setFont(mFont1);
    scorePresentPlay->setDefaultTextColor(Qt::red);
    scorePresentPlay->setPos(QPointF(game->getScreenWidth() / 2 - 10, game->getScreenHeight()/9));
    scorePresentPlay->setVisible(false);

    QPixmap pixmap_pipe_down(IMG_PIPE_DOWN);
    QPixmap pixmap_pipe_up(IMG_PIPE_UP);
    PIXMAP_SCALE(pixmap_pipe_down, game->getScaleFactor())
    PIXMAP_SCALE(pixmap_pipe_up, game->getScaleFactor())

    pipe[0][0] = new QGraphicsPixmapItem(pixmap_pipe_down);
    pipe[0][1] = new QGraphicsPixmapItem(pixmap_pipe_down);
    pipe[0][2] = new QGraphicsPixmapItem(pixmap_pipe_down);
    pipe[1][0] = new QGraphicsPixmapItem(pixmap_pipe_up);
    pipe[1][1] = new QGraphicsPixmapItem(pixmap_pipe_up);
    pipe[1][2] = new QGraphicsPixmapItem(pixmap_pipe_up);

    QPixmap pixmap_bird_raw(IMG_BIRD_YELLOW_UP);
    QPixmap pixmap_bird = pixmap_bird_raw;
    PIXMAP_SCALE(pixmap_bird, game->getScaleFactor())
    QPointF pos_bird(game->getScreenWidth() / 2 - pixmap_bird_raw.width() / 2, POS_Y_LOGO(game->getScreenHeight()) + pixmap_bird_raw.height() * 5);
    bird = new Bird(pos_bird, pixmap_bird, game->getScreenHeight() - ground->boundingRect().height(), game->getScreenWidth(), game->getScreenHeight(), game->getScaleFactor());

    button[0] = item_button_play;
    button[1] = item_button_about;
    button[2] = nullptr;

    addItem(pipe[0][0]);
    addItem(pipe[0][1]);
    addItem(pipe[0][2]);
    addItem(pipe[1][0]);
    addItem(pipe[1][1]);
    addItem(pipe[1][2]);

    addItem(item_pixmap_gameInfo);
    addItem(bird);
    addItem(ground);

    addItem(item_button_about);
    addItem(item_button_play);

    addItem(scorePresentPlay);
}

Scene::~Scene()
{
    delete bird;
    delete groundPainter;
}

void Scene::gameOver(int score, int scoreRecord)
{
    item_button_play->setPos(game->getScreenWidth() / 2 - item_button_play->boundingRect().width() / 2, game->getScreenHeight()/2 + 120);
    item_button_play->show();
}

void Scene::updateGround()
{
    if(ground->x() <= -(ground->boundingRect().width() / 2))
    {
        groundPainter->begin(&groundImage);
        groundPainter->drawPixmap(groundImage.width(), 0, groundImage.width() / 2, groundImage.height(), QPixmap::fromImage(groundImage.copy(0, 0, groundImage.width() / 2, groundImage.height())));
        groundPainter->drawPixmap(0, 0, ground->boundingRect().width() / 2, ground->boundingRect().height(), QPixmap::fromImage(groundImage.copy(groundImage.width() / 2, 0, groundImage.width() / 2, groundImage.height())));
        groundPainter->end();
        ground->setPixmap(QPixmap::fromImage(groundImage));
        ground->setPos(0, ground->y());
    }
}

void Scene::updateScore()
{
    QString  htmlString1 =  QString::number(game->getScore());
    scorePresentPlay->setHtml(htmlString1);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if((!isClickAvailable[0] || !isClickAvailable[1]) && !(game->isGameActuallyStarted()))
    {
        event->accept();
        return;
    }

    QPointF pos = event->scenePos();

    for(unsigned int k = 0; k < ARRAY_SIZE(button); ++k)
    {
        QApplication::processEvents();
        if (button[k] == nullptr)
            break;
        if(itemAt(pos, game->graphicsView->transform()) == button[k])
        {
            button[k]->invoke();
            return;
        }
    }

    game->clickEvent();
    event->accept();
}

void Scene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    mousePressEvent(event);
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if((!isClickAvailable[0] || !isClickAvailable[1]) && !(game->isGameActuallyStarted()))
    {
        event->accept();
        return;
    }
    game->clickEvent();
    event->accept();
}
