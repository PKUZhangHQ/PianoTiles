#ifndef USER_INFO_H
#define USER_INFO_H

#include<cstdint>
#include<fstream>
#include<iostream>
#include<vector>

const int MAX_CSTR_LEN = 32;
const int MAX_HIST_LEN = 10;

#pragma pack(push, 1)

struct UserInfo {
    char user_name[MAX_CSTR_LEN];
    char pswd[MAX_CSTR_LEN];
    int32_t score_num[3];
    int32_t scores[3][MAX_HIST_LEN]; // 0 easy, 1 med, 2 hard
//    int32_t easy_score[MAX_HIST_LEN];
//    int32_t med_score[MAX_HIST_LEN];
//    int32_t hard_score[MAX_HIST_LEN];
};


#pragma pack(pop)

vector<UserInfo> read_user_info (const char* path__) {
    vector<UserInfo> ret;
    ifstream fin;
    fin.open(path__, ios::in | ios::binary);
    if (fin) {
        UserInfo curr_info;
        while (fin.read((char*)&curr_info, sizeof(UserInfo))) {
            ret.push_back(curr_info);
        }
    }
    fin.close();
    return ret;
}

void dump_user_info (vector<UserInfo>& vec_user__, const char* path__) {
    ofstream fout;
    fout.open(path__, ios::out | ios::binary);
    if (fout) {
        for (auto uinfo: vec_user__){
            fout.write((char*)&uinfo, sizeof(UserInfo));
        }
    }
    fout.close();
}

void register_user_info (UserInfo& user__, const char* path__) {
    ofstream fout;
    fout.open(path__, ios::app | ios::binary);
    if (fout) {
        fout.write((char*)&user__, sizeof(UserInfo));
    }
    fout.close();
}


#endif // USER_INFO_H
