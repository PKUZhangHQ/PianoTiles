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
    int32_t easy_score[MAX_HIST_LEN];
    int32_t med_score[MAX_HIST_LEN];
    int32_t hard_score[MAX_HIST_LEN];
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

#endif // USER_INFO_H
