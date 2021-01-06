#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "common.h"
#include <QMainWindow>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    class View *graphicsView;

    class Game *game;

    class QSettings *settings;

    class StrobeAPI *strobe;

    class StrobeDialog *strobeDialog;

    qreal scaleFactor;

    int screenWidth, screenHeight;

    void resizeEvent(QResizeEvent *event) override;
    void moveEvent(QMoveEvent *event) override;

private:
    class QTimer *resizer;

    bool resized;

    void prepareManualViewportUpdate();

private slots:
    void resizeTriggered();

};


#endif // MAINWINDOW_H
