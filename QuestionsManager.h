#ifndef QUESTIONSMANAGER_H
#define QUESTIONSMANAGER_H

#include <bits/stdc++.h>
#include "Question.h"
#include "User.h"

class QuestionsManager {
private:
    std::map<int, std::vector<int>> questionid_questionidsThead_to_map;
    std::map<int, Question> questionid_questionobject_map;
    int last_id;
    std::string file_path;

public:
    QuestionsManager(const std::string &path = "18_questions.txt");
    void LoadDatabase();
    void PrintUserToQuestions(User &user);
    void PrintUserFromQuestions(User &user);
    int ReadQuestionIdAny(User &user);
    int ReadQuestionIdThread(User &user);
    void AnswerQuestion(User &user);
    void DeleteQuestion(User &user);
    void AskQuestion(User &user, std::pair<int, int> to_user_pair);
    void ListFeed();
    void UpdateDatabase();
};

#endif
