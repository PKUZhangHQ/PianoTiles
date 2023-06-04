#include"user_info.h"
#include<cstdint>
#include<fstream>
#include<iostream>
#include<QVector>
#include<QMap>
#include<QString>
#include<algorithm>


#pragma pack(push, 1)


UserInfoIO::UserInfoIO(UserInfo& info__) {
    strcpy(user_name, info__.user_name.toStdString().c_str());
    strcpy(pswd, info__.pswd.toStdString().c_str());
    for (int i = 0; i < 3; ++i) {
        score_num[i] = info__.scores[i].size();
        std::copy(info__.scores[i].begin(), info__.scores[i].end(), scores[i]);
    }
}

UserInfo::UserInfo(UserInfoIO& io_info__):
    user_name(io_info__.user_name),
    pswd(io_info__.pswd){
    for (int i = 0; i < 3; ++i) {
        scores[i].resize(io_info__.score_num[i]);
        std::copy(io_info__.scores[i], io_info__.scores[i] + io_info__.score_num[i], scores[i].begin());
    }
}
UserInfo::UserInfo(QString& uname__, QString& pswd__): user_name(uname__), pswd(pswd__) {}



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
        for (auto uit = map_user__.begin(); uit != map_user__.end(); ++uit) {
            UserInfoIO curr_info_io(uit.value());
            fout.write((char*)&curr_info_io, sizeof(UserInfoIO));
        }
    }
    fout.close();
}

