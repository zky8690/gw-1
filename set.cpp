#include "set.h"

set::set(QWidget *parent)
    : QWidget(parent)
{
    this->parent = parent;

    this->resize(977, 632);//设置窗口大小
    this->setWindowTitle("tank");//设置窗口标题
    this->setWindowIcon(QIcon(":/img/tubiao"));//设置窗口图标
    this->setAutoFillBackground(true);

    QPalette palette;//调色板
    QBrush mainwindows(QPixmap(":/img/gameintroduce.png").scaled(this->size()));
    palette.setBrush(QPalette::Window,mainwindows);
    this->setPalette(palette);

    label = new QLabel(this);//设置标题
    label->setPixmap(QPixmap(":/img/biaoti.png"));
    label->move(this->width()*0.33, this->height()*0.8);

    this->shengyinbtn=new QPushButton(this);//设置声音按钮
    QPixmap shengy(":/img/shengyinbtn1.png");
    this->shengyinbtn->setFixedSize(shengy.size());
    if(music) this->shengyinbtn->setStyleSheet("QPushButton{border-style:flat;border-image: url(:/img/shengyinbtn1.png);}");
    else this->shengyinbtn->setStyleSheet("QPushButton{border-style:flat;border-image: url(:/img/shengyinbtn0.png);}");
    shengyinbtn->move(20,this->height()*0.94);

    this->caidanbtn =new QPushButton(this);//设置菜单
    QPixmap caid(":/img/caidanbtn.png");
    this->caidanbtn->setFixedSize(caid.size());
    this->caidanbtn->setStyleSheet("QPushButton{border-style:flat;border-image: url(:/img/caidanbtn.png);}");
    caidanbtn->move(this->width() - 130,this->height()*0.93 + 4);
    caidantxt = new QLabel(this);
    caidantxt->setText("菜单");
    caidantxt->setFont(QFont ("Arial", 20));
    caidantxt->move(this->width()-80,this->height()*0.94);

    sliderone = new QSlider(this);
    sliderone->move(this->width() * 2 / 5,this->height() / 3);
    sliderone->setFixedHeight(150);
    sliderone->setMaximum(100);
    sliderone->setMinimum(0);
    sliderone->setValue(bgmyinliang);

    slidertwo = new QSlider(this);
    slidertwo->move(this->width() * 3 / 5,this->height() / 3);
    slidertwo->setFixedHeight(150);
    slidertwo->setMaximum(100);
    slidertwo->setMinimum(0);
    slidertwo->setValue(qitayinliang);

    bgmtxt = new QLabel(this);
    bgmtxt->setText("bgm声音大小");
    bgmtxt->setFont(QFont ("Arial", 15));
    bgmtxt->move(this->width() * 2 / 5 - 40,this->height() * 2 / 3 - 50);

    qitatxt = new QLabel(this);
    qitatxt->setText("其他声音大小");
    qitatxt->setFont(QFont ("Arial", 15));
    qitatxt->move(this->width() * 3 / 5 - 40,this->height() * 2 / 3 - 50);

    connect(caidanbtn,SIGNAL(clicked()),this,SLOT(fanhui()));
    connect(shengyinbtn,SIGNAL(clicked()),this,SLOT(changemusic()));
    connect(sliderone,SIGNAL(valueChanged(int)),SLOT(changebgm()));
    connect(slidertwo,SIGNAL(valueChanged(int)),SLOT(changeqita()));
    connect(slidertwo,SIGNAL(sliderReleased()),SLOT(buleng()));
}


void set::fanhui()
{
    if(music)
    {
        QSoundEffect *sound = new QSoundEffect();
        sound->setVolume((float)qitayinliang / 100);
        sound->setSource(QUrl::fromLocalFile(":/music/select_005.wav"));
        sound->play();
    }
    delete this;
}

void set::changemusic()
{
    emit mysignal();
    if(music) this->shengyinbtn->setStyleSheet("QPushButton{border-style:flat;border-image: url(:/img/shengyinbtn1.png);}");
    else this->shengyinbtn->setStyleSheet("QPushButton{border-style:flat;border-image: url(:/img/shengyinbtn0.png);}");
}

void set::changeqita()
{
    qitayinliang = slidertwo->value();
}

void set::changebgm()
{
    bgmyinliang = sliderone->value();
    bgm->setVolume((float)bgmyinliang / 100);
}

void set::buleng()
{
    if(music)
    {
        QSoundEffect *sound = new QSoundEffect();
        sound->setVolume((float)qitayinliang / 100);
        sound->setSource(QUrl::fromLocalFile(":/music/drop_004.wav"));
        sound->play();
    }
}
