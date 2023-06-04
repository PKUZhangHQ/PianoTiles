#ifndef USER_INFO_H
#define USER_INFO_H

#include<cstdint>
#include<fstream>
#include<iostream>
#include<QVector>
#include<QMap>
#include<QString>
#include<algorithm>

const int MAX_CSTR_LEN = 32;
const int MAX_HIST_LEN = 10;

#pragma pack(push, 1)
struct UserInfo;
struct UserInfoIO {
    char user_name[MAX_CSTR_LEN];
    char pswd[MAX_CSTR_LEN];
    int32_t score_num[3];
    int32_t scores[3][MAX_HIST_LEN]; // 0 easy, 1 med, 2 hard

    UserInfoIO(){};
    UserInfoIO(UserInfo& info__);
};

struct UserInfo {
    QString user_name;
    QString pswd;
    QVector<int32_t> scores[3];

    UserInfo(){};
    UserInfo(UserInfoIO& io_info__);
    UserInfo(QString& uname__, QString& pswd__);
};


#pragma pack(pop)

QMap<QString, UserInfo> read_user_info (const char* path__) ;

void dump_user_info (QMap<QString, UserInfo>& map_user__, const char* path__) ;

#endif // USER_INFO_H
