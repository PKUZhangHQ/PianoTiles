#ifndef RANK_BOARD_H
#define RANK_BOARD_H

#include <QDialog>

namespace Ui {
class rank_board;
}

class rank_board : public QDialog
{
    Q_OBJECT

public:
    explicit rank_board(QWidget *parent = nullptr);
    ~rank_board();

private:
    Ui::rank_board *ui;

public slots:
    void init();
    void terminate();
};

#endif // RANK_BOARD_H
