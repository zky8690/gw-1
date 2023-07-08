#ifndef SET_H
#define SET_H

#include <QWidget>
#include <QBitmap>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QKeyEvent>
#include <QSoundEffect>
#include <QSlider>
extern bool music;
extern int bgmyinliang;
extern int qitayinliang;
extern QSoundEffect* bgm;

class set : public QWidget
{
    Q_OBJECT
public:
    explicit set(QWidget *parent = nullptr);

private:
    QLabel* label;
    QLabel* caidantxt;
    QPushButton* caidanbtn;
    QWidget* parent;
    QPushButton* shengyinbtn;
    QSlider* sliderone;
    QSlider* slidertwo;
    QLabel* bgmtxt;
    QLabel* qitatxt;

signals:
    void mysignal();
private slots:
    void fanhui();
    void changemusic();
    void changebgm();
    void changeqita();
    void buleng();
};

#endif // SET_H
