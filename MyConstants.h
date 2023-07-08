#ifndef MYCONSTANTS_H
#define MYCONSTANTS_H

#include <fstream>
#include <QString>
#include <string>
#include <QRandomGenerator>
#include <QDebug>
#include <QFile>
using namespace std;

extern int bluescore,greenscore;
extern QString Filename;
extern int n, m;
extern double unit;
extern int dx[4], dy[4];
extern bool music;
extern int qitayinliang;
extern int bgmyinliang;

static void initialize(void) {
    int i = QRandomGenerator::global()->bounded(1,10);
    Filename = ":/layout/map";
    Filename.push_back(QChar(i + '0'));
    Filename += ".txt";
    QFile f(Filename);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << ("打开文件失败");
    }
    QTextStream txtInput(&f);

    txtInput >> n >> m;
    txtInput >> unit;
    f.close();
}

const qreal fps = 33;



#endif // MYCONSTANTS_H
