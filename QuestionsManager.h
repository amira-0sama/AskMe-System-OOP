#ifndef QUESTIONSMANAGER_H
#define QUESTIONSMANAGER_H

#include <bits/stdc++.h>
#include "Question.h"
#include "User.h"
using namespace std;

class QuestionsManager {
private:
    map<int, vector<int>> questionid_questionidsThead_to_map;
    map<int, Question> questionid_questionobject_map;
    int last_id;

public:
    QuestionsManager();
    void LoadDatabase();
    void FillUserQuestions(User &user);
    void PrintUserToQuestions(User &user);
    void PrintUserFromQuestions(User &user);
    int ReadQuestionIdAny(User &user);
    int ReadQuestionIdThread(User &user);
    void AnswerQuestion(User &user);
    void DeleteQuestion(User &user);
    void AskQuestion(User &user, pair<int, int> to_user_pair);
    void ListFeed();
    void UpdateDatabase();
};

#endif
