#include "widget.h"
#include "ui_widget.h"
#include "shuangrenintroduce.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(977,632);//设置窗口大小
    this->setWindowTitle("tank");//设置窗口标题
    this->setWindowIcon(QIcon(":/img/tubiao.png"));//设置窗口图标

    QPalette palette;//调色板
    QBrush mainwindows(QPixmap(":/img/mainwindows1.png").scaled(QSize(this->size()), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    palette.setBrush(QPalette::Window,mainwindows);
    this->setPalette(palette);

    this->shuangrenbtn=new QPushButton(this);//设置双人按钮
    shuangrenbtn->setFocusPolicy(Qt::NoFocus);
    QPixmap shuangr(":/img/shuangrenbtn.png");
    this->shuangrenbtn->setFixedSize(shuangr.size());
    this->shuangrenbtn->setMask(shuangr.mask());
    this->shuangrenbtn->setStyleSheet("QPushButton{border-style:flat;border-image: url(:/img/shuangrenbtn.png);}");
    shuangrenbtn->move(this->width()*0.35,this->height()*0.45);

    this->helpbtn=new QPushButton(this);//设置帮助按钮
    helpbtn->setFocusPolicy(Qt::NoFocus);
    QPixmap help(":/img/helpbtn.png");
    this->helpbtn->setFixedSize(help.size());
    this->helpbtn->setMask(help.mask());
    this->helpbtn->setStyleSheet("QPushButton{border-style:flat;border-image: url(:/img/helpbtn.png);}");
    helpbtn->move(this->width()*0.23,this->height()*0.61);

    this->shezhibtn =new QPushButton(this);//设置设置按钮
    shezhibtn->setFocusPolicy(Qt::NoFocus);
    QPixmap shezhi(":/img/shezhibtn.png");
    this->shezhibtn->setFixedSize(shezhi.size());
    this->shezhibtn->setMask(shezhi.mask());
    this->shezhibtn->setStyleSheet("QPushButton{border-style:flat;border-image: url(:/img/shezhibtn.png);}");
    shezhibtn->move(this->width()*0.53,this->height()*0.60);

    this->shengyinbtn=new QPushButton(this);//设置声音按钮
    shengyinbtn->setFocusPolicy(Qt::NoFocus);
    QPixmap shengy(":/img/shengyinbtn1.png");
    shengy.scaled(shengy.size() * 0.5);
    this->shengyinbtn->setFixedSize(shengy.size());
    if(music) this->shengyinbtn->setStyleSheet("QPushButton{border-style:flat;border-image: url(:/img/shengyinbtn1.png);}");
    else this->shengyinbtn->setStyleSheet("QPushButton{border-style:flat;border-image: url(:/img/shengyinbtn0.png);}");
    shengyinbtn->move(20,this->height()*0.94);

    label = new QLabel(this);//设置标题
    QPixmap biaoti(":/img/biaoti.png");
    biaoti.scaled(biaoti.size() * 0.5);
    label->setPixmap(biaoti);
    label->move(this->width()*0.33, this->height()*0.8);

    tuichubtn = new QPushButton(this);//设置退出按钮
    tuichubtn->setFocusPolicy(Qt::NoFocus);
    QPixmap tuic(":/img/tuichubtn.png");
    tuic.scaled(tuic.size() * 0.5);
    this->tuichubtn->setFixedSize(tuic.size());
    tuichubtn->setStyleSheet("QPushButton{border-style:flat;border-image: url(:/img/tuichubtn.png);}");
    tuichubtn->move(this->width() - 50,this->height() *0.94);

    connect(shuangrenbtn,SIGNAL(clicked()),this,SLOT(shuangrenbtnclicked()));
    connect(shengyinbtn,SIGNAL(clicked()),this,SLOT(changemusic()));
    connect(tuichubtn,SIGNAL(clicked()),this,SLOT(closegame()));
    connect(shezhibtn,SIGNAL(clicked()),this,SLOT(shezhi()));
    connect(helpbtn,SIGNAL(clicked()),this,SLOT(help()));

    bgm = new QSoundEffect(this);//背景乐
    if(music) bgm->setSource(QUrl::fromLocalFile(":/music/background.wav"));
    else bgm->setSource(QUrl::fromLocalFile(":/music/silence.wav"));
    bgm->setLoopCount(QSoundEffect::Infinite);
    bgm->play();

    shuangrenbtn->installEventFilter(this);
    shezhibtn->installEventFilter(this);
    helpbtn->installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::shuangrenbtnclicked()
{
    if(music)
    {
        QSoundEffect *sound = new QSoundEffect(this);
        sound->setVolume((float)qitayinliang / 100);
        sound->setSource(QUrl::fromLocalFile(":/music/select_005.wav"));
        sound->play();
    }
    shuangrenw = new shuangrenintroduce(this);

    connect(shuangrenw,&shuangrenintroduce::mysignal,this,&Widget::changemusic);
    connect(shuangrenw,&shuangrenintroduce::shuangrenbegin,this,&Widget::shuangrenbegin);

    shuangrenw->show();

}

void Widget::shezhi()
{
    setw = new set(this);
    connect(setw,&set::mysignal,this,&Widget::changemusic);
    setw->show();
}

void Widget::changemusic()
{
    music = !music;
    if(music) this->shengyinbtn->setStyleSheet("QPushButton{border-style:flat;border-image: url(:/img/shengyinbtn1.png);}");
    else this->shengyinbtn->setStyleSheet("QPushButton{border-style:flat;border-image: url(:/img/shengyinbtn0.png);}");
    if(music == 0) {
        bgm->stop();
        bgm->setSource(QUrl::fromLocalFile(":/music/silence.wav"));
        bgm->setLoopCount(QSoundEffect::Infinite);
        bgm->play();
    }
    else {
        bgm->stop();
        bgm->setSource(QUrl::fromLocalFile(":/music/background.wav"));
        bgm->setLoopCount(QSoundEffect::Infinite);
        bgm->play();
    }
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if(shuangrenw)
    {
        shuangrenw->keyPressEvent(event);
    }
}


void Widget::shuangrenbegin()
{
    shuangrenw = NULL;
    QTime reachTime = QTime::currentTime().addMSecs(1000);
    while(QTime::currentTime() < reachTime){
        QApplication::processEvents(QEventLoop::AllEvents,100);
    }
    this->hide();
    gamewidget = new GameWidget(this);
    connect(gamewidget,&GameWidget::mysignal,this,&Widget::changemusic);
    gamewidget->show();
}



bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == shuangrenbtn)
    {
        if(event->type() == QEvent::HoverEnter)
        {
            if(music)
            {
                QSoundEffect *sound = new QSoundEffect(this);
                sound->setVolume((float)qitayinliang / 100);
                sound->setSource(QUrl::fromLocalFile(":/music/drop_004.wav"));
                sound->play();
            }
        }
        if(event->type()==QEvent::HoverMove)
        {
            QPixmap shuangr(":/img/shuangrenbtnhover.png");
            this->shuangrenbtn->setFixedSize(shuangr.size());
            this->shuangrenbtn->setMask(shuangr.mask());
            shuangrenbtn->setStyleSheet("QPushButton{border-style:flat;border-image: url(:/img/shuangrenbtnhover.png);}");
        }
        if(event->type()==QEvent::HoverLeave || event->type() == QEvent::MouseButtonPress)
        {
            QPixmap shuangr(":/img/shuangrenbtn.png");
            this->shuangrenbtn->setFixedSize(shuangr.size());
            this->shuangrenbtn->setMask(shuangr.mask());
            shuangrenbtn->setStyleSheet("QPushButton{border-style:flat;border-image: url(:/img/shuangrenbtn.png);}");
        }
    }
    if(watched == shezhibtn)
    {
        if(event->type() == QEvent::HoverEnter)
        {
            if(music)
            {
                QSoundEffect *sound = new QSoundEffect(this);
                sound->setVolume((float)qitayinliang / 100);
                sound->setSource(QUrl::fromLocalFile(":/music/drop_004.wav"));
                sound->play();
            }
        }
        if(event->type()==QEvent::HoverMove)
        {
            QPixmap shezhi(":/img/shezhibtnhover.png");
            this->shezhibtn->setFixedSize(shezhi.size());
            this->shezhibtn->setMask(shezhi.mask());
            shezhibtn->setStyleSheet("QPushButton{border-style:flat;border-image: url(:/img/shezhibtnhover.png);}");
        }
        if(event->type()==QEvent::HoverLeave || event->type() == QEvent::MouseButtonPress)
        {
            QPixmap shezhi(":/img/shezhibtn.png");
            this->shezhibtn->setFixedSize(shezhi.size());
            this->shezhibtn->setMask(shezhi.mask());
            shezhibtn->setStyleSheet("QPushButton{border-style:flat;border-image: url(:/img/shezhibtn.png);}");
        }
    }
    if(watched == helpbtn)
    {
        if(event->type() == QEvent::HoverEnter)
        {
            if(music)
            {
                QSoundEffect *sound = new QSoundEffect(this);
                sound->setVolume((float)qitayinliang / 100);
                sound->setSource(QUrl::fromLocalFile(":/music/drop_004.wav"));
                sound->play();
            }
        }
        if(event->type()==QEvent::HoverMove)
        {
            QPixmap help(":/img/helpbtnhover.png");
            this->helpbtn->setFixedSize(help.size());
            this->helpbtn->setMask(help.mask());
            helpbtn->setStyleSheet("QPushButton{border-style:flat;border-image: url(:/img/helpbtnhover.png);}");
        }
        if(event->type()==QEvent::HoverLeave || event->type() == QEvent::MouseButtonPress)
        {
            QPixmap help(":/img/helpbtn.png");
            this->helpbtn->setFixedSize(help.size());
            this->helpbtn->setMask(help.mask());
            helpbtn->setStyleSheet("QPushButton{border-style:flat;border-image: url(:/img/helpbtn.png);}");
        }
    }
    return false;
}

void Widget::help()
{
    QDialog* p = new QDialog;
    QPixmap help(":/img/help.png");
    p->setFixedSize(help.size());
    p->setStyleSheet("QDialog{background-image: url(:/img/help.png)}");
    p->exec();
}

void Widget::closegame()
{
    if(QMessageBox::question(this,"提示","确定退出？") == QMessageBox::Yes)
        this->close();
}
