#include "shuangrenintroduce.h"

shuangrenintroduce::shuangrenintroduce(QWidget *parent) : QWidget(parent)
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

    playerone = 0;
    playertwo = 0;

    labelone = new QLabel(this);//玩家1
    labelone->setPixmap(QPixmap(":/img/player1zhunbei0.png"));
    labelone->move(this->width()*0.26, this->height()*0.4);
    shuomingtxt1 = new QLabel(this);
    shuomingtxt1->setText(" Player1\nPress  Q");
    shuomingtxt1->setFont(QFont ("Arial", 23));
    shuomingtxt1->move(this->width()*0.3, this->height()*0.55);

    labeltwo = new QLabel(this);//玩家2
    labeltwo->setPixmap(QPixmap(":/img/player2zhunbei0.png"));
    labeltwo->move(this->width()*0.56, this->height()*0.4);
    shuomingtxt2 = new QLabel(this);
    shuomingtxt2->setText(" Player2\nPress  M");
    shuomingtxt2->setFont(QFont ("Arial", 23));
    shuomingtxt2->move(this->width()*0.6, this->height()*0.55);

    timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(shanshuo()));
    timer->start(1000);

    connect(caidanbtn,SIGNAL(clicked()),this,SLOT(fanhui()));
    connect(shengyinbtn,SIGNAL(clicked()),this,SLOT(changemusic()));
}

void shuangrenintroduce::shanshuo()
{
    static int i = 1;
    char filename[50] = " ";
    sprintf(filename,":/img/player1zhunbei%d.png",i);
    if(!playerone)
    {
        labelone->setPixmap(QPixmap(filename));
    }

    if(!playertwo)
    {
        sprintf(filename,":/img/player2zhunbei%d.png",i);
        labeltwo->setPixmap(QPixmap(filename));
    }
    i++;
    i %=2;
}

void shuangrenintroduce::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Q)
    {
        if(music)
        {
            QSoundEffect *sound;
            if(playertwo == 1)
            {
                sound = new QSoundEffect(this);
                sound->setVolume((float)qitayinliang / 100);
                sound->setSource(QUrl::fromLocalFile(":/music/confirmation_002.wav"));
            }
            else
            {
                sound = new QSoundEffect(this);
                sound->setVolume((float)qitayinliang / 100);
                sound->setSource(QUrl::fromLocalFile(":/music/confirmation_001.wav"));
            }
            sound->play();
        }
        playerone = 1;
        labelone->setPixmap(QPixmap(":/img/player1prepared.png"));
        if(playertwo == 1)
        {
            emit shuangrenbegin();
            delete this;
        }
    }
    if(event->key() == Qt::Key_M)
    {
        if(music)
        {
            QSoundEffect *sound;
            if(playerone == 1)
            {
                sound = new QSoundEffect(this);
                sound->setVolume((float)qitayinliang / 100);
                sound->setSource(QUrl::fromLocalFile(":/music/confirmation_002.wav"));
            }
            else
            {
                sound = new QSoundEffect(this);
                sound->setVolume((float)qitayinliang / 100);
                sound->setSource(QUrl::fromLocalFile(":/music/confirmation_001.wav"));
            }
            sound->play();
        }
        playertwo = 1;
        labeltwo->setPixmap(QPixmap(":/img/player2prepared.png"));
        if(playerone == 1)
        {
            emit shuangrenbegin();
            delete this;
        }
    }
}

void shuangrenintroduce::fanhui()
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

void shuangrenintroduce::changemusic()
{
    emit mysignal();
    if(music) this->shengyinbtn->setStyleSheet("QPushButton{border-style:flat;border-image: url(:/img/shengyinbtn1.png);}");
    else this->shengyinbtn->setStyleSheet("QPushButton{border-style:flat;border-image: url(:/img/shengyinbtn0.png);}");
}
