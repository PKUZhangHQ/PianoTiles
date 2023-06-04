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

