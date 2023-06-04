#ifndef START_H
#define START_H

#include <QWidget>
#include <QMap>
#include "user_info.h"

namespace Ui {
class Start;
}

static QMap<QString,UserInfo> usersInfo_map; // 所有用户信息

class Start : public QWidget
{
    Q_OBJECT

public:
    explicit Start(QWidget *parent = 0);
    ~Start();
    int user_num;
    QString cur; // user_name,user_key
    void init();

signals:
    void login(int x,int y);
    void regist(int x,int y);
    void register_success();
    void register_fail();
    void login_success(QString user);
    void login_fail(int x);
    void userbest(int diff,int score);
    void set_rank_board(const QMap<QString, UserInfo>& usersInfo);

private:
    Ui::Start *ui;

public slots:
    void updhis(int diff,int score);
    void loginbut();
    void quitbut();
    void registbut();
    void updusr(QString user,QString pswd);
    void check(QString user,QString pswd);
    void send_rank_board_data();
};

#endif // START_H
