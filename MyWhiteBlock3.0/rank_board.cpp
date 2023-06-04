#include<algorithm>
#include<functional>
#include<QFile>
#include "rank_board.h"
#include "ui_rank_board.h"
#include "user_info.h"
#include <QMap>
#include <QVector>

QVector<std::pair<int, QString> > records[3];

/*
rank_board的逻辑:
    QObject::connect(G, &Gamehall::gotoRank, S, &Start::send_rank_board_data); // 进入排行榜,调用start信息
    QObject::connect(S, &Start::set_rank_board, rkbd, &rank_board::init); // 通过start信息设置排行榜

Gameball触发gotoRank,调用Start的send_rank_board_data
S::send_rank_board_data中emit set_rank_board发送users_Info数据, 同时传递和触发rank_board::init
rkbd::init初始化records[3], 把所有现有的users_Info记录下来

CombBox触发的是diff_show(int diff),其中records rank_board的头文件的全局变量
user_info.h包含在这个文件了, 所以应该也可以调用users_info
*/

rank_board::rank_board(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rank_board)
{
    ui->setupUi(this);

    QStringList diffList;
    diffList<<"(简单)"<<"(普通)"<<"(困难)";
    ui->diffBox->addItems(diffList);
    ui->diffBox->setCurrentIndex(0);
    connect(ui->diffBox,SIGNAL(currentIndexChanged(int)),this,SLOT(rank_board::diff_show(int))); // 不太对好像

    connect(ui->back_btn, &QPushButton::clicked, this, rank_board::terminate);
}

rank_board::~rank_board()
{
    delete ui;
}

void rank_board::init(const QMap<QString, UserInfo>& usersInfo)
{
    records[0].clear();records[1].clear();records[2].clear();
    for(auto user:usersInfo){
        for(int diff=0;diff<3;++diff){
            for(auto score:user.scores[diff]){
                records[diff].push_back(std::make_pair(score,user.user_name));
            }
        }
    }
    for(int diff=0;diff<3;++diff){
        std::sort(records[diff].begin(),records[diff].end(),std::greater<std::pair<int,QString>());
    }

    // select diff 的函数 显示默认为简单
    diff_show(0);
    // 选择窗口
}

void rank_board::diff_show(int diff)
{
    QVector<std::pair<int, QString>> record = records[diff];
    int last_score = __INT_MAX__, placement = 0;
    for (int i = 0; i < ui->gridLayout->rowCount(); ++i) {
        QLabel *placement_label, *name_label, *score_label;
        placement_label = dynamic_cast<QLabel*>(ui->gridLayout->itemAtPosition(i, 0)->widget());
        name_label = dynamic_cast<QLabel*>(ui->gridLayout->itemAtPosition(i, 1)->widget());
        score_label = dynamic_cast<QLabel*>(ui->gridLayout->itemAtPosition(i, 2)->widget());
        if (i >= record.size()) {
            ++placement;
            placement_label->setText(QString("No. ") + QString::number(placement));
            name_label->setText(QString("虚位以待"));
            score_label->setText(QString(" "));
        }
        else {
            auto curr_record = record[i];
            if (curr_record.first < last_score) {
                ++placement;
                last_score = curr_record.first;
            }
            placement_label->setText(QString("No. ") + QString::number(placement));
            name_label->setText(QString(curr_record.second));
            score_label->setText(QString::number(curr_record.first));
        }
    }
    this->resize(800, 800);
    //this->move((QApplication::desktop()->width()-this->width())/2,(QApplication::desktop()->height()-this->height())/2);
    this->show();
}

void rank_board::terminate() {
    this->close();
}
