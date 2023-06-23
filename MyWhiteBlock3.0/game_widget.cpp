#include "game_widget.h"
#include "ui_game_widget.h"

#include <QPushButton>
#include <QAction>
#include <QTime>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QString>
#include <QDebug>
#include <QtDebug>
#include <QPainter>
#include <QLabel>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QDesktopWidget>
#include <QTimer>
#include <QTime>


game_widget::game_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::game_widget),
    layout(new QHBoxLayout)
{
    ui->setupUi(this);
    game_widget::setWindowTitle("Don't Tap The White Block");
    setWindowIcon(QIcon(":/new/prefix3/whiteblock.webp"));

    setFixedSize(800,1200);
    this->move((QApplication::desktop()->width()-this->width())/2,(QApplication::desktop()->height()-this->height())/2);
    connect(&timer, &QTimer::timeout, this, &game_widget::UpdataData);
    track_num = 4,difficulty = 1;

    layout->setAlignment(Qt::AlignBottom | Qt::AlignCenter);
    setLayout(layout);

    make_keyhint(track_num);
}

void game_widget::make_keyhint(int track_num__) {
    QString keyhint_str_4[4] = {"D", "F", "J", "K"};
    QString keyhint_str_6[6] = {"S", "D", "F", "J", "K", "L"};
    QString* keyhint_str = track_num__ == 4 ? keyhint_str_4 : keyhint_str_6;

    for (int i = 0; i < track_num; ++i) {
        QLabel* keyhint = new QLabel(keyhint_str[i]);
        keyhint->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

        QPalette palette = keyhint->palette();
        palette.setColor(QPalette::WindowText, Qt::white);  // Change to the desired color
        keyhint->setPalette(palette);

        // Set font size
        QFont font = keyhint->font();
        font.setPointSize(16);  // Change to the desired font size
        font.setBold(true);
        keyhint->setAlignment(Qt::AlignCenter);
        keyhint->setFont(font);

        layout->addWidget(keyhint);
        layout->setStretchFactor(keyhint, 1);
    }
}

void game_widget::Set(int track, int diff)
{
    this->track_num = track;
    this->difficulty = diff;

    QLayoutItem* item;
    while (item = layout->takeAt(0)) {
        if (QWidget* widget = item->widget()) {
            layout->removeWidget(widget);
            delete widget;
        }
        delete item;
    }

    make_keyhint(track);

}

void game_widget::SetBlockData(int width, int height)
{
    Bwidth = width;
    Bheight = height;
}

void game_widget::StartGame()
{
    timer.start();
    elapsedTimer.start();
    ui->label->setText(QString("得分：%1").arg(score));
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::white); // 设置字体颜色为白色
    ui->label->setPalette(palette);
    musicplayer->play();
    this->setFocus();
    int RefreshFrequency = 10;
    timer.setInterval(RefreshFrequency);
    failed = false;
    speed = 2;
    score = 0;
    QTime time = QTime::currentTime();
    qsrand(QTime(0,0,0,0).secsTo(time));
    QTimer::singleShot(5,this,[=](){
        SetBlockData(width()/track_num, height()/(track_num+1));
    });
}

void game_widget::refresh()
{
    timer.stop();
    bData.clear();
    failed = false;
    speed = 2;
    score = 0;
    this->myplaylist = new QMediaPlaylist;
    this->musicplayer = new QMediaPlayer;

    myplaylist->setPlaybackMode(QMediaPlaylist::Loop);
    myplaylist->addMedia(QUrl("qrc:/new/prefix2/canon.mp3"));
    musicplayer->setPlaylist(myplaylist);
    musicplayer->setVolume(100);
    musicplayer->setPlaybackRate(2);
    this->StartGame();
}

void game_widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //painter.fillRect(rect(),Qt::white);
    QPixmap pixmap = QPixmap(":/new/prefix1/backphoto.jpeg").scaled(this->size());
    painter.drawPixmap(this->rect(),pixmap);

    painter.setBrush(Qt::black);

    painter.setPen(Qt::black);
    if(track_num==4)
    {
//        qDebug() << "4 track width = " << width();
        painter.drawLine(QPointF(width()/4,0),QPointF(width()/4,height()));
        painter.drawLine(QPointF(2*width()/4,0),QPointF(2*width()/4,height()));
        painter.drawLine(QPointF(3*width()/4,0),QPointF(3*width()/4,height()));

        QPen originalPen = painter.pen();
        QPen pen(Qt::white);
        pen.setWidth(2); // 设置线条宽度为2
        painter.setPen(pen);
        painter.drawLine(QPointF(0, height()/4*3), QPointF(width(), height()/4*3)); // perfect line
        painter.setPen(originalPen);
    }

    else if(track_num==6)
    {
//        qDebug() << "6 track width = " << width();
        painter.drawLine(QPointF(width()/6,0),QPointF(width()/6,height()));
        painter.drawLine(QPointF(2*width()/6,0),QPointF(2*width()/6,height()));
        painter.drawLine(QPointF(3*width()/6,0),QPointF(3*width()/6,height()));
        painter.drawLine(QPointF(4*width()/6,0),QPointF(4*width()/6,height()));
        painter.drawLine(QPointF(5*width()/6,0),QPointF(5*width()/6,height()));

        QPen originalPen = painter.pen();
        QPen pen(Qt::white);
        pen.setWidth(2); // 设置线条宽度为2
        painter.setPen(pen);
        painter.drawLine(QPointF(0, height()/6*5), QPointF(width(), height()/6*5)); // perfect line
        painter.setPen(originalPen);

        QString keyhint_str[6] = {"S", "D", "F", "J", "K", "L"};
        QHBoxLayout *layout = new QHBoxLayout;
        layout->setAlignment(Qt::AlignBottom | Qt::AlignCenter);
        for (int i = 0; i < track_num; ++i) {
            QLabel* keyhint = new QLabel(keyhint_str[i]);

            QPalette palette = keyhint->palette();
            palette.setColor(QPalette::WindowText, Qt::white);  // Change to the desired color
            keyhint->setPalette(palette);

            // Set font size
            QFont font = keyhint->font();
            font.setPointSize(10);  // Change to the desired font size
            font.setBold(true);
            keyhint->setFont(font);
            keyhint->setAlignment(Qt::AlignCenter);

            layout->addWidget(keyhint);
            layout->setStretchFactor(keyhint, 1);
        }
        setLayout(layout);
    }


    // show time
    qint64 elapsedTime = elapsedTimer.elapsed();
    qint64 seconds = elapsedTime/1000;
    qint64 minutes = seconds/60;
    seconds = seconds%60;

    QString timeText = QString("时间: %1:%2")
                           .arg(minutes, 2, 10, QLatin1Char('0'))
                           .arg(seconds, 2, 10, QLatin1Char('0'));

    ui->timeLabel->setText(timeText);
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::white); // 设置字体颜色为白色

    ui->timeLabel->setPalette(palette);



    if(failed)
    {
        //failure signal
        //QPen pen(QColor(255,0,0));
        //pen.setWidth(5);
        //painter.setPen(pen);
        //painter.drawText(QRect(300,550,200,100),"Game Over");
        int w = 420;
        int h = 220;
        QFont f;
        f.setPixelSize(72);

        painter.setFont(f);
        painter.drawText((width()-w)/2,(height()-h)/2,w,h,Qt::AlignCenter,"Game Over!");
    }

    else
    {
        BlockData * d = bData.get_pos();
        while(d)
        {
            switch (d->type) {
            case BlockType::BONUS: painter.setBrush(Qt::darkBlue); break;
            case BlockType::DEATH: painter.setBrush(Qt::darkRed); break;
            case BlockType::NORMAL: painter.setBrush(Qt::black); break;
            }

            painter.drawRect(d->x,d->y,d->width,d->height);
            d = d->next;
            painter.setBrush(Qt::black);
        }
    }
}

void game_widget::keyPressEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat()) return;

    this->grabKeyboard();

    BlockData* TapKeyboard = nullptr;
    if(track_num == 4)
    {
        switch(event->key())
        {
        case Qt::Key_D: TapKeyboard = bData.remove(Bwidth-1);break;
        case Qt::Key_F: TapKeyboard = bData.remove(2*(Bwidth-1)); break;
        case Qt::Key_J: TapKeyboard = bData.remove(3*(Bwidth-1)); break;
        case Qt::Key_K: TapKeyboard = bData.remove(4*(Bwidth-1)); break;
        default:break;
        }

        if(TapKeyboard && TapKeyboard->type != BlockType::DEATH)
        {
            switch (TapKeyboard->type) {
            case BlockType::NORMAL: ++score; break;
            case BlockType::BONUS: score += 3; break;
            }
            // in perfect line, score double
            if(TapKeyboard->y>height()/4*2&&TapKeyboard->y<height()/4*3){
                switch (TapKeyboard->type) {
                case BlockType::NORMAL: ++score; break;
                case BlockType::BONUS: score += 3; break;
                }
            }
            ui->label->setText(QString("得分：%1").arg(score));
            QPalette palette;
            palette.setColor(QPalette::WindowText, Qt::white); // 设置字体颜色为白色

            ui->label->setPalette(palette);


            //easy
            if(difficulty==0)
            {
                if(!(score%15)) ++speed;
                if(score%22 == 0) --speed;
            }

            //medium
            if(difficulty==1)
            {
                if(!(score%10)) ++speed;
            }

            //diffcult
            if(difficulty==2)
            {
                if(!(score%5)) ++speed;
            }
        }

        else
        {
            failed = true;
            this->releaseKeyboard();
            emit gameover(this->geometry().x(),this->geometry().y(),this->difficulty,this->score);
            this->musicplayer->stop();
            timer.stop();
        }
    }

    else if(track_num == 6)
    {
        switch(event->key())
        {
        case Qt::Key_S: TapKeyboard = bData.remove(Bwidth-1);break;
        case Qt::Key_D: TapKeyboard = bData.remove(2*(Bwidth-1)); break;
        case Qt::Key_F: TapKeyboard = bData.remove(3*(Bwidth-1)); break;
        case Qt::Key_J: TapKeyboard = bData.remove(4*(Bwidth-1)); break;
        case Qt::Key_K: TapKeyboard = bData.remove(5*(Bwidth-1)); break;
        case Qt::Key_L: TapKeyboard = bData.remove(6*(Bwidth-1)); break;
        default:break;
        }
        if(TapKeyboard && TapKeyboard->type != BlockType::DEATH)
        {
            switch (TapKeyboard->type) {
            case BlockType::NORMAL: ++score; break;
            case BlockType::BONUS: score += 3; break;
            }
            // in perfect line, score double
            if(TapKeyboard->y>height()/6*4&&TapKeyboard->y<height()/6*5){
                switch (TapKeyboard->type) {
                case BlockType::NORMAL: ++score; break;
                case BlockType::BONUS: score += 3; break;
                }
            }
            ui->label->setText(QString::number(score));
            if(!(score%20)) ++speed;
            if(score%66 == 0) --speed;
        }
        else
        {
            failed = true;
            this->releaseKeyboard();
            this->musicplayer->stop();
            emit gameover(this->geometry().x(),this->geometry().y(),this->difficulty,this->score);
            timer.stop();
        }
    }
    delete TapKeyboard;
}

void game_widget::mousePressEvent(QMouseEvent *event)
{
    QPoint point = event->pos();
    BlockData* rm_block = bData.remove(point.x(),point.y());
    if(rm_block && rm_block->type != BlockType::DEATH)
    {
        switch (rm_block->type) {
        case BlockType::NORMAL: ++score; break;
        case BlockType::BONUS: score += 3; break;
        }
        //刷新速度
        ui->label->setText(QString::number(score));

        //easy
        if(difficulty==0)
        {
            if(!(score%15)) ++speed;
            if(score%22 == 0) --speed;
        }

        //medium
        if(difficulty==1)
        {
            if(!(score%10)) ++speed;
        }

        //diffcult
        if(difficulty==2)
        {
            if(!(score%5)) ++speed;
        }
    }

    else
    {
        //failure
        failed = true;
        this->releaseKeyboard();
        this->musicplayer->stop();
        emit gameover(this->geometry().x(),this->geometry().y(),this->difficulty,this->score);
        timer.stop();
        //        QPainter mouse_painter(this);
        //        int w = 400;
        //        int h = 220;
        //        QFont f;
        //        f.setPixelSize(72);
        //        mouse_painter.setFont(f);
        //        mouse_painter.drawText((width()-w)/2,(height()-h)/2,w,h,Qt::AlignCenter,"Game Over!");
    }
    delete rm_block;
}

void game_widget::UpdataData()
{
    // 生成块
    static int _speed = Bheight;

    if(_speed >= Bheight)
    {

        BlockData *d = new BlockData;
        int x = qrand() % track_num;
        // decide the block type randomly
        int type_lot = qrand() % 100;

        BlockType::type btp;
        if (type_lot <= 75)
            btp = BlockType::NORMAL;
        else if (type_lot <= 100)
            btp = BlockType::BONUS;
        else
            btp = BlockType::DEATH;

        bData.init(&d,x*Bwidth,-Bheight,Bwidth,Bheight, btp);
        bData.insert(d);
        _speed = 0;

    }
    bData.updata(speed);
    if(!bData.judge(height()))
    {
        failed = true;
        this->releaseKeyboard();
        this->musicplayer->stop();
        emit gameover(this->geometry().x(),this->geometry().y(),this->difficulty,this->score);
        timer.stop();
    }
    _speed += speed;
    update();
}

game_widget::~game_widget()
{
    delete ui;
}
