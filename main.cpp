#include "widget.h"

#include <QApplication>
#include "MyConstants.h"
#include <QSoundEffect>

int n, m, bluescore, greenscore;
double unit;
QString Filename;
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
bool music = 0;
int bgmyinliang = 50;
int qitayinliang = 50;
QSoundEffect* bgm;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
