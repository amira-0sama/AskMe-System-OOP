#ifndef USERSMANAGER_H
#define USERSMANAGER_H

#include <bits/stdc++.h>
#include "User.h"
#include "Helper.h"

class UsersManager {
private:
    std::map<std::string, User> userame_userobject_map;
    User current_user;
    int last_id;
    std::string file_path;

public:
    UsersManager(const std::string &path = "18_users.txt");
    void LoadDatabase();
    void AccessSystem();
    void DoLogin();
    void DoSignUp();
    void ListUsersNamesIds();
    std::pair<int, int> ReadUserId();
    void UpdateDatabase(const User &user);
    User& GetCurrentUser() { return current_user; }
};

#endif
