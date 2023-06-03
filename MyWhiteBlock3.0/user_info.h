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

struct UserInfoIO {
    char user_name[MAX_CSTR_LEN];
    char pswd[MAX_CSTR_LEN];
    int32_t score_num[3];
    int32_t scores[3][MAX_HIST_LEN]; // 0 easy, 1 med, 2 hard

    UserInfoIO(UserInfo& info__) {
        strcpy(user_name, info__.user_name.toStdString().c_str());
        strcpy(pswd, info__.pswd.toStdString().c_str());
        for (int i = 0; i < 3; ++i) {
            score_num[i] = info__.scores[i].size();
            std::copy(info__.scores[i].begin(), info__.scores[i].end(), scores[i]);
        }
    }
};

struct UserInfo {
    QString user_name;
    QString pswd;
    QVector<int32_t> scores[3];

    UserInfo(UserInfoIO& io_info__):
        user_name(io_info__.user_name),
        pswd(io_info__.pswd){
        for (int i = 0; i < 3; ++i) {
            scores[i].resize(io_info__.score_num[i]);
            std::copy(io_info__.scores[i], io_info__.scores[i] + io_info__.score_num[i], scores[i].begin());
        }
    }
    UserInfo(QString& uname__, QString& pswd__): user_name(uname__), pswd(pswd__) {}
};


#pragma pack(pop)

QMap<QString, UserInfo> read_user_info (const char* path__) {
    QMap<QString, UserInfo> ret;
    std::ifstream fin;
    fin.open(path__, std::ios::in | std::ios::binary);
    if (fin) {
        UserInfoIO curr_info_IO;
        while (fin.read((char*)&curr_info_IO, sizeof(UserInfoIO))) {
            UserInfo curr_info(curr_info_IO);
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
            fout.write((char*)&uinfo, sizeof(UserInfoIO));
        }
    }
    fout.close();
}

//void register_user_info (UserInfo& user__, const char* path__) {
//    ofstream fout;
//    fout.open(path__, ios::app | ios::binary);
//    if (fout) {
//        fout.write((char*)&user__, sizeof(UserInfo));
//    }
//    fout.close();
//}


#endif // USER_INFO_H
