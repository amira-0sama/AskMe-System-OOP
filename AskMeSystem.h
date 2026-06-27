#ifndef ASKMESYSTEM_H
#define ASKMESYSTEM_H

#include "UsersManager.h"
#include "QuestionsManager.h"

class AskMeSystem {
private:
    UsersManager users_manager;
    QuestionsManager questions_manager;

public:
    void LoadDatabase(bool fill_user_questions = false);
    void run();
};

#endif
