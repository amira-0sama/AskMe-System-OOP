#include "UsersManager.h"

UsersManager::UsersManager() {
    last_id = 0;
}

void UsersManager::LoadDatabase() {
    last_id = 0;
    userame_userobject_map.clear();
    vector<string> lines = Helper::ReadFileLines("18_users.txt");
    for (auto &line : lines) {
        User user(line);
        userame_userobject_map[user.GetUserName()] = user;
        last_id = max(last_id, user.GetUserId());
    }
}

void UsersManager::AccessSystem() {
    int choice = Helper::ShowReadMenu({"Login", "Sign Up"});
    if (choice == 1) DoLogin();
    else DoSignUp();
}

void UsersManager::DoLogin() {
    LoadDatabase();
    while (true) {
        string user_name;
        string password;
        cout << "Enter user name & password: ";
        cin >> user_name >> password;
        if (!userame_userobject_map.count(user_name)) {
            cout << "\nInvalid user name or password. Try again\n\n";
            continue;
        }
        User user_exist = userame_userobject_map[user_name];
        if (password != user_exist.GetPassword()) {
            cout << "\nInvalid user name or password. Try again\n\n";
            continue;
        }
        current_user = user_exist;
        break;
    }
}

void UsersManager::DoSignUp() {
    string user_name;
    while (true) {
        cout << "Enter user name. (No spaces): ";
        cin >> user_name;
        if (userame_userobject_map.count(user_name))
            cout << "Already used. Try again\n";
        else
            break;
    }
    current_user.SetUserName(user_name);
    string password, name, email;
    int allow_anonymous_questions;
    cout << "Enter password: "; cin >> password;
    cout << "Enter name: "; cin >> name;
    cout << "Enter email: "; cin >> email;
    cout << "Allow anonymous questions? (0 or 1): "; cin >> allow_anonymous_questions;

    current_user.SetPassword(password);
    current_user.SetName(name);
    current_user.SetEmail(email);
    current_user.SetAllowAnonymousQuestions(allow_anonymous_questions);
    current_user.SetUserId(++last_id);

    userame_userobject_map[current_user.GetUserName()] = current_user;
    UpdateDatabase(current_user);
}

void UsersManager::ListUsersNamesIds() {
    for (auto &pair : userame_userobject_map)
        cout << "ID: " << pair.second.GetUserId() << "\t\tName: " << pair.second.GetName() << "\n";
}

pair<int, int> UsersManager::ReadUserId() {
    int user_id;
    cout << "Enter User id or -1 to cancel: ";
    cin >> user_id;
    if (user_id == -1) return make_pair(-1, -1);
    for (auto &pair : userame_userobject_map) {
        if (pair.second.GetUserId() == user_id)
            return make_pair(user_id, pair.second.GetAllowAnonymousQuestions());
    }
    cout << "Invalid User ID. Try again\n";
    return ReadUserId();
}

void UsersManager::UpdateDatabase(const User &user) {
    vector<string> lines;
    lines.push_back(user.ToString());
    Helper::WriteFileLines("18_users.txt", lines);
}