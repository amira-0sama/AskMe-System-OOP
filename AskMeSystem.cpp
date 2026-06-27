#include "AskMeSystem.h"

void AskMeSystem::LoadDatabase(bool fill_user_questions) {
    users_manager.LoadDatabase();
    questions_manager.LoadDatabase();
    if (fill_user_questions)
        questions_manager.FillUserQuestions(users_manager.GetCurrentUser());
}

void AskMeSystem::run() {
    LoadDatabase();
    users_manager.AccessSystem();
    questions_manager.FillUserQuestions(users_manager.GetCurrentUser());

    vector<string> menu = {
        "Print Questions To Me", "Print Questions From Me",
        "Answer Question", "Delete Question", "Ask Question",
        "List System Users", "Feed", "Logout"
    };

    while (true) {
        int choice = Helper::ShowReadMenu(menu);
        LoadDatabase(true);

        if (choice == 1) questions_manager.PrintUserToQuestions(users_manager.GetCurrentUser());
        else if (choice == 2) questions_manager.PrintUserFromQuestions(users_manager.GetCurrentUser());
        else if (choice == 3) {
            questions_manager.AnswerQuestion(users_manager.GetCurrentUser());
            questions_manager.UpdateDatabase();
        } else if (choice == 4) {
            questions_manager.DeleteQuestion(users_manager.GetCurrentUser());
            questions_manager.FillUserQuestions(users_manager.GetCurrentUser());
            questions_manager.UpdateDatabase();
        } else if (choice == 5) {
            pair<int, int> to_user_pair = users_manager.ReadUserId();
            if (to_user_pair.first != -1) {
                questions_manager.AskQuestion(users_manager.GetCurrentUser(), to_user_pair);
                questions_manager.UpdateDatabase();
            }
        } else if (choice == 6) users_manager.ListUsersNamesIds();
        else if (choice == 7) questions_manager.ListFeed();
        else break;
    }
    run();
}