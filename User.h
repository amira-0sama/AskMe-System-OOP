#ifndef USER_H
#define USER_H

#include <bits/stdc++.h>
#include "Helper.h"
using namespace std;

class User {
private:
    int user_id;
    string user_name;
    string password;
    string name;
    string email;
    int allow_anonymous_questions;

public:
    vector<int> questions_id_from_me;
    map<int, vector<int>> questionid_questionidsThead_to_map;

    User();
    User(const string &line);

    string ToString() const;
    void Print() const;

    int GetUserId() const { return user_id; }
    const string& GetUserName() const { return user_name; }
    const string& GetPassword() const { return password; }
    const string& GetName() const { return name; }
    const string& GetEmail() const { return email; }
    int GetAllowAnonymousQuestions() const { return allow_anonymous_questions; }

    void SetUserId(int id) { user_id = id; }
    void SetUserName(const string &uname) { user_name = uname; }
    void SetPassword(const string &pass) { password = pass; }
    void SetName(const string &n) { name = n; }
    void SetEmail(const string &e) { email = e; }
    void SetAllowAnonymousQuestions(int allow) { allow_anonymous_questions = allow; }
};

#endif
