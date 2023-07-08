#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QBitmap>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "shuangrenintroduce.h"
#include <QSoundEffect>
#include <QDialog>
#include <QTime>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "gamewidget.h"
#include "set.h"
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    GameWidget *gamewidget;


private:
    QPushButton* shuangrenbtn;
    QPushButton* shengyinbtn;
    QLabel* label;
    shuangrenintroduce* shuangrenw =NULL;
    set* setw = NULL;
    Ui::Widget *ui;
    QPushButton* tuichubtn;
    QPushButton* shezhibtn;
    QPushButton* helpbtn;

public slots:
    void shuangrenbtnclicked();
    void changemusic();
    void shuangrenbegin();
    void closegame();
    void help();
    void shezhi();
public:
    void keyPressEvent(QKeyEvent *event);
    bool eventFilter(QObject* , QEvent*);
};
#endif // WIDGET_H
