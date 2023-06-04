#include<algorithm>
#include<functional>
#include<QFile>
#include "rank_board.h"
#include "ui_rank_board.h"
#include "user_info.h"
#include <QMap>
#include <QVector>

rank_board::rank_board(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rank_board)
{
    ui->setupUi(this);
    connect(ui->back_btn, &QPushButton::clicked, this, rank_board::terminate);
}

rank_board::~rank_board()
{
    delete ui;
}

void rank_board::init(const QMap<QString, UserInfo>& usersInfo)
{
    QVector<std::pair<int, QString> > records[3];
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
    diff_show(records[0],0);
    // 选择窗口
}

void rank_board::diff_show(const QVector<std::pair<int,QString>>& record,int diff)
{
    int last_score = __INT_MAX__, placement = 0;
    for (int i = 0; i < ui->gridLayout->rowCount(); ++i) {
        QLabel *placement_label, *name_label, *score_label;
        placement_label = dynamic_cast<QLabel*>(ui->gridLayout->itemAtPosition(i, 0)->widget());
        name_label = dynamic_cast<QLabel*>(ui->gridLayout->itemAtPosition(i, 1)->widget());
        score_label = dynamic_cast<QLabel*>(ui->gridLayout->itemAtPosition(i, 2)->widget());
        if (i >= records.size()) {
            ++placement;
            placement_label->setText(QString("No. ") + QString::number(placement));
            name_label->setText(QString("虚位以待"));
            score_label->setText(QString(" "));
        }
        else {
            auto curr_record = records[i];
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
