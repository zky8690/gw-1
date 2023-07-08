#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QSize>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <QDebug>
#include "gameview.h"
#include "MyConstants.h"
#include <QRandomGenerator>
#include <QVBoxLayout>
#include <QPalette>
#include <QBrush>
#include <QLabel>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QPushButton>


using namespace std;


class GameWidget : public QWidget
{
    Q_OBJECT

public:
    GameWidget(QWidget *parent = nullptr);
    ~GameWidget();

private:
    GameView * view;
    QVBoxLayout *layout;
    QHBoxLayout *hlayout;
    QLabel *Gtank, *Btank, *Gtankscore, *Btankscore;
    QPushButton* shengyinbtn;
    QPushButton* caidanbtn;
    QLabel* caidantxt;
    QWidget* parent;
public slots:
    void nextmap(void);
    void fanhui();
    void changemusic();
signals:
    void mysignal();
};
#endif // GAMEWIDGET_H
