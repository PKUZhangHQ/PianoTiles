#ifndef RANK_BOARD_H
#define RANK_BOARD_H

#include <QDialog>
#include <QVector>
#include "user_info.h"

namespace Ui {
class rank_board;
}

class rank_board : public QDialog
{
    Q_OBJECT

public:
    explicit rank_board(QWidget *parent = nullptr);
    void diff_show(const QVector<std::pair<int,QString>>& records,int diff);
    ~rank_board();

private:
    Ui::rank_board *ui;

public slots:
    void init(const QMap<QString, UserInfo>& usersInfo);
    void terminate();
};

#endif // RANK_BOARD_H
