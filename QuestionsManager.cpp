#include "QuestionsManager.h"

QuestionsManager::QuestionsManager() {
    last_id = 0;
}

void QuestionsManager::LoadDatabase() {
    last_id = 0;
    questionid_questionidsThead_to_map.clear();
    questionid_questionobject_map.clear();

    vector<string> lines = Helper::ReadFileLines("18_questions.txt");
    for (auto &line : lines) {
        Question question(line);
        last_id = max(last_id, question.GetQuestionId());
        questionid_questionobject_map[question.GetQuestionId()] = question;

        if (question.GetParentQuestionId() == -1)
            questionid_questionidsThead_to_map[question.GetQuestionId()].push_back(question.GetQuestionId());
        else
            questionid_questionidsThead_to_map[question.GetParentQuestionId()].push_back(question.GetQuestionId());
    }
}

void QuestionsManager::FillUserQuestions(User &user) {
    user.questions_id_from_me.clear();
    user.questionid_questionidsThead_to_map.clear();

    for (auto &pair : questionid_questionidsThead_to_map) {
        for (auto &question_id : pair.second) {
            Question &question = questionid_questionobject_map[question_id];
            if (question.GetFromUserId() == user.GetUserId())
                user.questions_id_from_me.push_back(question.GetQuestionId());

            if (question.GetToUserId() == user.GetUserId()) {
                if (question.GetParentQuestionId() == -1)
                    user.questionid_questionidsThead_to_map[question.GetQuestionId()].push_back(question.GetQuestionId());
                else
                    user.questionid_questionidsThead_to_map[question.GetParentQuestionId()].push_back(question.GetQuestionId());
            }
        }
    }
}

void QuestionsManager::PrintUserToQuestions(User &user) {
    cout << "\n";
    if (user.questionid_questionidsThead_to_map.empty()) cout << "No Questions";
    for (auto &pair : user.questionid_questionidsThead_to_map) {
        for (auto &question_id : pair.second)
            questionid_questionobject_map[question_id].PrintToQuestion();
    }
    cout << "\n";
}

void QuestionsManager::PrintUserFromQuestions(User &user) {
    cout << "\n";
    if (user.questions_id_from_me.empty()) cout << "No Questions";
    for (auto &question_id : user.questions_id_from_me)
        questionid_questionobject_map[question_id].PrintFromQuestion();
    cout << "\n";
}

int QuestionsManager::ReadQuestionIdAny(User &user) {
    int question_id;
    cout << "Enter Question id or -1 to cancel: ";
    cin >> question_id;
    if (question_id == -1) return -1;

    if (!questionid_questionobject_map.count(question_id)) {
        cout << "\nERROR: No question with such ID. Try again\n\n";
        return ReadQuestionIdAny(user);
    }
    Question &question = questionid_questionobject_map[question_id];
    if (question.GetToUserId() != user.GetUserId()) {
        cout << "\nERROR: Invalid question ID. Try again\n\n";
        return ReadQuestionIdAny(user);
    }
    return question_id;
}

int QuestionsManager::ReadQuestionIdThread(User &user) {
    int question_id;
    cout << "For thread question: Enter Question id or -1 for new question: ";
    cin >> question_id;
    if (question_id == -1) return -1;

    if (!questionid_questionidsThead_to_map.count(question_id)) {
        cout << "No thread question with such ID. Try again\n";
        return ReadQuestionIdThread(user);
    }
    return question_id;
}

void QuestionsManager::AnswerQuestion(User &user) {
    int question_id = ReadQuestionIdAny(user);
    if (question_id == -1) return;

    Question &question = questionid_questionobject_map[question_id];
    question.PrintToQuestion();

    if (!question.GetAnswerText().empty())
        cout << "\nWarning: Already answered. Answer will be updated\n";

    string answer;
    cout << "Enter answer: ";
    getline(cin, answer);
    getline(cin, answer);
    question.SetAnswerText(answer);
}

void QuestionsManager::DeleteQuestion(User &user) {
    int question_id = ReadQuestionIdAny(user);
    if (question_id == -1) return;

    vector<int> ids_to_remove;
    if (questionid_questionidsThead_to_map.count(question_id)) {
        ids_to_remove = questionid_questionidsThead_to_map[question_id];
        questionid_questionidsThead_to_map.erase(question_id);
    } else {
        ids_to_remove.push_back(question_id);
        for (auto &pair : questionid_questionidsThead_to_map) {
            vector<int> &vec = pair.second;
            for (int i = 0; i < (int)vec.size(); i++) {
                if (vec[i] == question_id) {
                    vec.erase(vec.begin() + i);
                    break;
                }
            }
        }
    }
    for (auto id : ids_to_remove) questionid_questionobject_map.erase(id);
}

void QuestionsManager::AskQuestion(User &user, pair<int, int> to_user_pair) {
    Question question;
    if (!to_user_pair.second) {
        cout << "Note: Anonymous questions are not allowed for this user\n";
        question.SetIsAnonymousQuestions(0);
    } else {
        int anonymous;
        cout << "Is anonymous questions?: (0 or 1): ";
        cin >> anonymous;
        question.SetIsAnonymousQuestions(anonymous);
    }

    question.SetParentQuestionId(ReadQuestionIdThread(user));
    string question_text;
    cout << "Enter question text: ";
    getline(cin, question_text);
    getline(cin, question_text);
    question.SetQuestionText(question_text);

    question.SetFromUserId(user.GetUserId());
    question.SetToUserId(to_user_pair.first);
    question.SetQuestionId(++last_id);

    questionid_questionobject_map[question.GetQuestionId()] = question;

    if (question.GetParentQuestionId() == -1)
        questionid_questionidsThead_to_map[question.GetQuestionId()].push_back(question.GetQuestionId());
    else
        questionid_questionidsThead_to_map[question.GetParentQuestionId()].push_back(question.GetQuestionId());
}

void QuestionsManager::ListFeed() {
    for (auto &pair : questionid_questionobject_map) {
        Question &question = pair.second;
        if (question.GetAnswerText().empty()) continue;
        question.PrintFeedQuestion();
    }
}

void QuestionsManager::UpdateDatabase() {
    vector<string> lines;
    for (auto &pair : questionid_questionobject_map)
        lines.push_back(pair.second.ToString());
    Helper::WriteFileLines("18_questions.txt", lines, false);
}