#include "User.h"

User::User() {
    user_id = allow_anonymous_questions = -1;
}

User::User(const string &line) {
    vector<string> substrs = Helper::SplitString(line);
    assert(substrs.size() == 6);
    user_id = Helper::ToInt(substrs[0]);
    user_name = substrs[1];
    password = substrs[2];
    name = substrs[3];
    email = substrs[4];
    allow_anonymous_questions = Helper::ToInt(substrs[5]);
}

string User::ToString() const {
    ostringstream oss;
    oss << user_id << "," << user_name << "," << password << "," << name << "," << email << "," << allow_anonymous_questions;
    return oss.str();
}

void User::Print() const {
    cout << "User " << user_id << ", " << user_name << " " << password << ", " << name << ", " << email << "\n";
}