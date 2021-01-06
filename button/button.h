#ifndef BUTTON_H
#define BUTTON_H

#include "common.h"

#include <QGraphicsPixmapItem>
#include <QPixmap>

class Game;

class ButtonFuncs{
private:
    ButtonFuncs(){}

public:
    static void about(Game *game_instance);
    static void play(Game *game_instance);
};

class Button : public QGraphicsPixmapItem
{
    typedef void (*Function) (Game *game_instance);

private:
    QPixmap Pixmap;

protected:
    Function buttonFunction;
    Game *game;

public:
    Button(Game *parent_game, const QPixmap& pixmap, Function function)
        : QGraphicsPixmapItem(pixmap), Pixmap(pixmap), buttonFunction(function), game(parent_game){}

    virtual void invoke(Game *parent_game = nullptr);
};

#endif // BUTTON_H
