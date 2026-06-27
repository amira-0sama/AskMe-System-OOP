#ifndef USERSMANAGER_H
#define USERSMANAGER_H

#include <bits/stdc++.h>
#include "User.h"
#include "Helper.h"
using namespace std;

class UsersManager {
private:
    map<string, User> userame_userobject_map;
    User current_user;
    int last_id;

public:
    UsersManager();
    void LoadDatabase();
    void AccessSystem();
    void DoLogin();
    void DoSignUp();
    void ListUsersNamesIds();
    pair<int, int> ReadUserId();
    void UpdateDatabase(const User &user);
    User& GetCurrentUser() { return current_user; }
};

#endif
