#include "gamewidget.h"

int Bluebullet::cnt = 0;
int Greenbullet::cnt = 0;

GameWidget::GameWidget(QWidget *parent)
    : QWidget(nullptr)
{
    this->parent = parent;
    initialize();
    this->setFixedSize(1280, 720);
    this->setWindowTitle("坦克动荡魔改版——gw说的对不队");
    this->setWindowIcon(QIcon(":/img/tubiao.png"));
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(QImage(":/img/background_sand.png")));
    this->setPalette(palette);
    layout = new QVBoxLayout(this);
    this->Btank = new QLabel(this);
    this->Btank->setPixmap(QPixmap(":/img/BtankIcon.png").scaled(QSize(70, 140), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    this->Gtank = new QLabel(this);
    this->Gtank->setPixmap(QPixmap(":/img/GtankIcon.png").scaled(QSize(70, 140), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    view = new GameView(this);
    connect(view,&GameView::nextloop,this,&GameWidget::nextmap);
    view->setFocusPolicy(Qt::NoFocus);
    view->setStyleSheet("background: transparent;border:0px");


    this->Btankscore = new QLabel(this);
    this->Btankscore->setText(QString("# ") + QString::number(bluescore));
    this->Btankscore->setTextFormat(Qt::MarkdownText);

    this->Gtankscore = new QLabel(this);
    this->Gtankscore->setText(QString("# ") + QString::number(greenscore));
    this->Gtankscore->setTextFormat(Qt::MarkdownText);

    this->shengyinbtn=new QPushButton(this);//设置声音按钮
    QPixmap shengy(":/img/shengyinbtn1.png");
    shengy.scaled(shengy.size() * 0.5);
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

    this->hlayout = new QHBoxLayout(this);

    this->hlayout->addWidget(Btank);
    this->hlayout->addSpacing(30);
    this->hlayout->addWidget(Btankscore);
    this->hlayout->addSpacing(300);
    this->hlayout->addWidget(Gtank);
    this->hlayout->addSpacing(30);
    this->hlayout->addWidget(Gtankscore);


    layout->addWidget(view);
    layout->addLayout(hlayout);
    hlayout->setAlignment(Qt::AlignHCenter);
    layout->setAlignment(Qt::AlignCenter);
    view->show();

    connect(caidanbtn,SIGNAL(clicked()),this,SLOT(fanhui()));
    connect(shengyinbtn,SIGNAL(clicked()),this,SLOT(changemusic()));

}

GameWidget::~GameWidget()
{
}

void GameWidget::nextmap(void)
{
    delete Gtank;
    delete Btank;
    delete Gtankscore;
    delete Btankscore;
    initialize();
    this->Btank = new QLabel(this);
    this->Btank->setPixmap(QPixmap(":/img/BtankIcon.png").scaled(QSize(70, 140), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    this->Gtank = new QLabel(this);
    this->Gtank->setPixmap(QPixmap(":/img/GtankIcon.png").scaled(QSize(70, 140), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    view = new GameView(this);
    connect(view,&GameView::nextloop,this,&GameWidget::nextmap);
    view->setFocusPolicy(Qt::NoFocus);
    view->setStyleSheet("background: transparent;border:0px");

    this->Btankscore = new QLabel(this);
    this->Btankscore->setText(QString("# ") + QString::number(bluescore));
    this->Btankscore->setTextFormat(Qt::MarkdownText);

    this->Gtankscore = new QLabel(this);
    this->Gtankscore->setText(QString("# ") + QString::number(greenscore));
    this->Gtankscore->setTextFormat(Qt::MarkdownText);


    this->hlayout = new QHBoxLayout(this);
    this->hlayout->addWidget(Btank);
    this->hlayout->addSpacing(30);
    this->hlayout->addWidget(Btankscore);
    this->hlayout->addSpacing(300);
    this->hlayout->addWidget(Gtank);
    this->hlayout->addSpacing(30);
    this->hlayout->addWidget(Gtankscore);


    layout->addWidget(view);
    layout->addLayout(hlayout);
    hlayout->setAlignment(Qt::AlignHCenter);
    layout->setAlignment(Qt::AlignCenter);
    view->show();

}

void GameWidget::fanhui()
{
    if(music)
    {
        QSoundEffect *sound = new QSoundEffect();
        sound->setVolume((float)qitayinliang / 100);
        sound->setSource(QUrl::fromLocalFile(":/music/select_005.wav"));
        sound->play();
    }
    this->parent->show();
    greenscore = 0;
    bluescore = 0;
    view->scene->tank_b->sound->stop();
    view->scene->tank_g->sound->stop();
    delete view->scene;
    delete view;
    delete this;
}

void GameWidget::changemusic()
{
    emit mysignal();
    if(!music)
    {
        view->scene->tank_b->sound->stop();
        view->scene->tank_g->sound->stop();
    }
    if(music) this->shengyinbtn->setStyleSheet("QPushButton{border-style:flat;border-image: url(:/img/shengyinbtn1.png);}");
    else this->shengyinbtn->setStyleSheet("QPushButton{border-style:flat;border-image: url(:/img/shengyinbtn0.png);}");
}
