#ifndef GAMEINTRODUCE_H
#define GAMEINTRODUCE_H

#include <QWidget>
#include <QBitmap>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QKeyEvent>
#include <QSoundEffect>

extern bool music;
extern int qitayinliang;
extern int bgmyinliang;

class shuangrenintroduce : public QWidget
{
    Q_OBJECT
public:
    explicit shuangrenintroduce(QWidget *parent = nullptr);

private:
    bool playerone;
    bool playertwo;

    QLabel* label;
    QLabel* labelone;
    QLabel* labeltwo;
    QLabel* caidantxt;
    QTimer* timer;
    QPushButton* caidanbtn;
    QWidget* parent;
    QPushButton* shengyinbtn;
    QLabel* shuomingtxt1;
    QLabel* shuomingtxt2;
signals:
    void mysignal();
    void shuangrenbegin();
private slots:
    void shanshuo();
    void fanhui();
    void changemusic();

public:
    void keyPressEvent(QKeyEvent *event);
};

#endif // GAMEINTRODUCE_H
