#include "AskMeSystem.h"
using namespace std;

void AskMeSystem::LoadDatabase() {
    users_manager.LoadDatabase();
    questions_manager.LoadDatabase();
}

void AskMeSystem::run() {
    vector<string> menu = {
        "Print Questions To Me", "Print Questions From Me",
        "Answer Question", "Delete Question", "Ask Question",
        "List System Users", "Feed", "Logout"
    };

    while (true) {
        LoadDatabase();
        users_manager.AccessSystem();

        bool logged_in = true;
        while (logged_in) {
            int choice = Helper::ShowReadMenu(menu);

            if (choice == 1) questions_manager.PrintUserToQuestions(users_manager.GetCurrentUser());
            else if (choice == 2) questions_manager.PrintUserFromQuestions(users_manager.GetCurrentUser());
            else if (choice == 3) {
                questions_manager.AnswerQuestion(users_manager.GetCurrentUser());
                questions_manager.UpdateDatabase();
            } else if (choice == 4) {
                questions_manager.DeleteQuestion(users_manager.GetCurrentUser());
                questions_manager.UpdateDatabase();
            } else if (choice == 5) {
                pair<int, int> to_user_pair = users_manager.ReadUserId();
                if (to_user_pair.first != -1) {
                    questions_manager.AskQuestion(users_manager.GetCurrentUser(), to_user_pair);
                    questions_manager.UpdateDatabase();
                }
            } else if (choice == 6) users_manager.ListUsersNamesIds();
            else if (choice == 7) questions_manager.ListFeed();
            else logged_in = false;
        }
    }
}
