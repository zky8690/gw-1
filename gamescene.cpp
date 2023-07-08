#include "gamescene.h"

bool check(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m) return false;
    return true;
}

GameScene::GameScene()
{
    QFile f(Filename);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << ("打开文件失败");
    }
    QTextStream txtInput(&f);
    int blank; txtInput >> blank >> blank >> blank;
    QString s[50];
    for (int i = 0; i < n; ++ i) txtInput >> s[i];
    f.close();

    for (int i = 0; i < n; ++ i) qDebug() << s[i];

    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            if (s[i][j] == '#') {
                QPointF pos(j * unit + unit / 2, i * unit + unit / 2);
                Wall *w = new Wall(this, pos, QSize(unit +2, unit+2));
                for (int k = 0; k < 4; ++ k) {
                    int tx = i + dx[k], ty = j + dy[k];
                    if (check(tx, ty) && s[tx][ty] == '.') {
                        w->canBeTouched[k] = true;
                    }
                }
            }
        }
    }
    while(true)
    {
        int x = QRandomGenerator::global()->bounded(0,n);
        int y = QRandomGenerator::global()->bounded(0,m);
        if (s[x][y] != '#')
        {
            QPointF pos(y * unit + unit / 2,x * unit + unit / 2);
            tank_b = new Bluetank(this,pos,QSize(unit,unit) * 2 / 3);
            s[x][y] = 'B';
            break;
        }
    }
    while(true)
    {
        int x = QRandomGenerator::global()->bounded(0,n);
        int y = QRandomGenerator::global()->bounded(0,m);
        if (s[x][y] == '.')
        {
            QPointF pos(y * unit + unit / 2,x * unit + unit / 2);
            tank_g = new Greentank(this,pos,QSize(unit,unit) * 2 / 3);
            break;
        }
    }
    timer = new QTimer(this);
    timer->start(1000 / fps);
    Endtimer = new QTimer(this);
    Endtimer->setSingleShot(true);
    connect(tank_g, &Tank::ImDead,this,&GameScene::Prepare_to_dieg);
    connect(tank_b, &Tank::ImDead,this,&GameScene::Prepare_to_dieb);
    connect(Endtimer,&QTimer::timeout,this,&GameScene::Destroy);
    connect(timer, SIGNAL(timeout()), this, SLOT(advance()));
}


void GameScene::keyPressEvent(QKeyEvent *event) {
    if (event -> key() == Qt::Key_Up) {
        tank_g->KeyPressed[0] = true;
    }
    if (event->key() == Qt::Key_Down) {
        tank_g->KeyPressed[1] = true;
    }
    if (event->key() == Qt::Key_Left) {
        tank_g->KeyPressed[2] = true;
    }
    if (event->key() == Qt::Key_Right) {
        tank_g->KeyPressed[3] = true;
    }
    if (event->key() == Qt::Key_M) {
        tank_g->KeyPressed[4] = true;
    }
    if (event->key() == Qt::Key_E) {
        tank_b->KeyPressed[0] = true;
    }
    if (event->key() == Qt::Key_D) {
        tank_b->KeyPressed[1] = true;
    }
    if (event->key() == Qt::Key_S) {
        tank_b->KeyPressed[2] = true;
    }
    if (event->key() == Qt::Key_F) {
        tank_b->KeyPressed[3] = true;
    }
    if (event->key() == Qt::Key_Q) {
        tank_b->KeyPressed[4] = true;
    }
}

void GameScene::keyReleaseEvent(QKeyEvent *event) {
    if (event -> key() == Qt::Key_Up) {
        tank_g->KeyPressed[0] = false;
    }
    if (event->key() == Qt::Key_Down) {
        tank_g->KeyPressed[1] = false;
    }
    if (event->key() == Qt::Key_Left) {
        tank_g->KeyPressed[2] = false;
    }
    if (event->key() == Qt::Key_Right) {
        tank_g->KeyPressed[3] = false;
    }
    if (event->key() == Qt::Key_M) {
        tank_g->KeyPressed[4] = false;
    }
    if (event->key() == Qt::Key_E) {
        tank_b->KeyPressed[0] = false;
    }
    if (event->key() == Qt::Key_D) {
        tank_b->KeyPressed[1] = false;
    }
    if (event->key() == Qt::Key_S) {
        tank_b->KeyPressed[2] = false;
    }
    if (event->key() == Qt::Key_F) {
        tank_b->KeyPressed[3] = false;
    }
    if (event->key() == Qt::Key_Q) {
        tank_b->KeyPressed[4] = false;
    }
}

void GameScene::Prepare_to_dieg(void)
{
    if (Endtimer->isActive() == false)
    {
        // qDebug()<<"green";
        Endtimer->start(4000);
    }
}

void GameScene::Prepare_to_dieb(void)
{
    if (Endtimer->isActive() == false)
    {
//        <<"blue";
        Endtimer->start(4000);
    }
}
void GameScene::Destroy(void){
    // qDebug()<<Endtimer->remainingTime();
    if (tank_b->isDying == 0 && tank_g->isDying > 0)
    {
        bluescore++;
    }
    if (tank_g->isDying == 0 && tank_b->isDying > 0)
    {
        greenscore++;
    }
    this->clear();
    emit EndGame();
    delete this;
}
