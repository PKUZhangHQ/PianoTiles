#include "start.h"
#include "ui_start.h"
#include "user_info.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDesktopWidget>
#include <QIcon>
#include <QVector>
#include <algorithm>



Start::Start(QWidget *parent):
    QWidget(parent),
    ui(new Ui::Start)
{
    qDebug() << "Hello";
    ui->setupUi(this);
    this->resize(600,800);
    setWindowIcon(QIcon(":/new/prefix3/whiteblock.webp"));
    this->user_num = 0;
    this->move((QApplication::desktop()->width()-this->width())/2,(QApplication::desktop()->height()-this->height())/2);

    this->ui->login->setShortcut(Qt::Key_Return);
    QObject::connect(this->ui->login, &QPushButton::clicked,this,&Start::loginbut);
    this->ui->exit->setShortcut(Qt::Key_Escape);
    QObject::connect(this->ui->exit, &QPushButton::clicked,this,&Start::quitbut);
    this->ui->register_2->setShortcut(Qt::Key_Space);
    QObject::connect(this->ui->register_2, &QPushButton::clicked,this,&Start::registbut);

//    this->setAttribute(Qt::WA_DeleteOnClose);
}

Start::~Start(){
    dump_user_info(usersInfo_map, "user_data");
    qDebug() << "Save All Users Info! End Program";
    delete ui;
}

void Start::init()
{
    // 这里读信息 拿到UsersInfo_map
    usersInfo_map = read_user_info("user_data");
    qDebug() << "Read All Users Info!";
    this->user_num = usersInfo_map.size(); // 这个貌似没用
    this->show();
}

void Start::loginbut()
{
    emit login(this->geometry().x(), this->geometry().y());
}

void Start::registbut()
{
    emit regist(this->geometry().x(),this->geometry().y());
}

void Start::quitbut()
{
    QMessageBox::StandardButton result = QMessageBox::question(this,"Warning","确定退出游戏?");
    if(result==QMessageBox::Yes)
        this->close();
}
void Start::updhis(int diff, int score)
{
    //这里要改了，运行时scores已经改成vector了
    QVector<int32_t>& curr_score_record = usersInfo_map[this->cur].scores[diff];
    curr_score_record.push_back(score);
    std::sort(curr_score_record.begin(),curr_score_record.end(),std::greater<int32_t>()); // 从大到小排
    if (curr_score_record.size() > MAX_HIST_LEN) {curr_score_record.removeLast();}

    usersInfo_map[this->cur].scores[diff] = curr_score_record;
    emit userbest(diff, curr_score_record.first()); // 这个要改
}

void Start::updusr(QString user, QString pswd)
{
    if(usersInfo_map.find(user)!=usersInfo_map.end())
        emit(register_fail());
    else{
        emit(register_success());
        this->user_num++;
        UserInfo newUser(user,pswd);
        usersInfo_map[user] = newUser;
    }
}

void Start::check(QString user, QString pswd)
{
    if(usersInfo_map.find(user)!=usersInfo_map.end()){
        if(usersInfo_map[user].pswd!=pswd)
            emit(login_fail(0)); // 密码错误
        else{
            emit(login_success(user));
            this->cur = user,this->close();
        }
    }
    else emit(login_fail(1)); // 用户名重复
}

void Start::send_rank_board_data(){
    qDebug() << "send rkbd data called" << endl;
    emit(set_rank_board(usersInfo_map));
}
