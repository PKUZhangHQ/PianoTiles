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

QMap<QString, UserInfo> read_user_info (const char* path__) {
    QMap<QString, UserInfo> ret;
    std::ifstream fin;
    fin.open(path__, std::ios::in | std::ios::binary);
    if (fin) {
        UserInfoIO curr_info_io;
        while (fin.read((char*)&curr_info_io, sizeof(UserInfoIO))) {
            UserInfo curr_info(curr_info_io);
            ret[curr_info.user_name] = curr_info;
        }
    }
    fin.close();
    return ret;
}

void dump_user_info (QMap<QString, UserInfo>& map_user__, const char* path__) {
    std::ofstream fout;
    fout.open(path__, std::ios::out | std::ios::binary);
    if (fout) {
        for (auto uit = map_user__.begin(); uit != map_user__.end(); ++uit){
            UserInfoIO curr_info_io(uit->second);
            fout.write((char*)&curr_info_io, sizeof(UserInfoIO));
        }
    }
    fout.close();
}

#endif // USER_INFO_H
