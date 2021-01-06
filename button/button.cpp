#include "button.h"

#include <QMessageBox>
#include <QString>

#include "game/game.h"
#include "scene/scene.h"

void ButtonFuncs::about(Game *game_instance){
    QWidget *gameQObject = dynamic_cast<QWidget *>(game_instance);
    QMessageBox::about(gameQObject, "About...", QString("Flappy Bird Qt by fuzun\nVersion: v%1\n\ngithub.com/fuzun/Flappy-Bird-Qt").arg(QCoreApplication::applicationVersion()));
}

void ButtonFuncs::play(Game *game_instance){

    if(!game_instance->isGameFinished()){
        game_instance->prepareFirstGame();
        game_instance->scene->fadeGroup(GROUP_FIRSTSCREEN, false, 500, GROUP_GAMEPLAY);
    } else {
        game_instance->prepareNewRound();
    }
}

void Button::invoke(Game *parent_game){
    buttonFunction(game);
}
