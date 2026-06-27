#ifndef QUESTION_H
#define QUESTION_H

#include <bits/stdc++.h>
#include "Helper.h"
using namespace std;

class Question {
private:
    int question_id;
    int parent_question_id;
    int from_user_id;
    int to_user_id;
    int is_anonymous_questions;
    string question_text;
    string answer_text;

public:
    Question();
    Question(const string &line);

    string ToString() const;
    void PrintToQuestion() const;
    void PrintFromQuestion() const;
    void PrintFeedQuestion() const;

    int GetQuestionId() const { return question_id; }
    int GetParentQuestionId() const { return parent_question_id; }
    int GetFromUserId() const { return from_user_id; }
    int GetToUserId() const { return to_user_id; }
    int GetIsAnonymousQuestions() const { return is_anonymous_questions; }
    const string& GetQuestionText() const { return question_text; }
    const string& GetAnswerText() const { return answer_text; }

    void SetQuestionId(int id) { question_id = id; }
    void SetParentQuestionId(int id) { parent_question_id = id; }
    void SetFromUserId(int id) { from_user_id = id; }
    void SetToUserId(int id) { to_user_id = id; }
    void SetIsAnonymousQuestions(int aq) { is_anonymous_questions = aq; }
    void SetQuestionText(const string &text) { question_text = text; }
    void SetAnswerText(const string &ans) { answer_text = ans; }
};

#endif
