#ifndef USER_H
#define USER_H

#include <bits/stdc++.h>
#include "Helper.h"

class User {
private:
    int user_id;
    std::string user_name;
    std::string password;
    std::string name;
    std::string email;
    int allow_anonymous_questions;

public:

    User();
    User(const std::string &line);

    std::string ToString() const;
    void Print() const;

    int GetUserId() const { return user_id; }
    const std::string& GetUserName() const { return user_name; }
    const std::string& GetPassword() const { return password; }
    const std::string& GetName() const { return name; }
    const std::string& GetEmail() const { return email; }
    int GetAllowAnonymousQuestions() const { return allow_anonymous_questions; }

    void SetUserId(int id) { user_id = id; }
    void SetUserName(const std::string &uname) { user_name = uname; }
    void SetPassword(const std::string &pass) { password = pass; }
    void SetName(const std::string &n) { name = n; }
    void SetEmail(const std::string &e) { email = e; }
    void SetAllowAnonymousQuestions(int allow) { allow_anonymous_questions = allow; }
};

#endif
