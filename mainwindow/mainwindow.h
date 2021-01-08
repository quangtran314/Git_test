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
    class QGraphicsView *graphicsView;

    class Game *game;

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
