#include "QuestionsManager.h"
using namespace std;

QuestionsManager::QuestionsManager(const string &path) {
    last_id = 0;
    file_path = path;
}

void QuestionsManager::LoadDatabase() {
    last_id = 0;
    questionid_questionidsThead_to_map.clear();
    questionid_questionobject_map.clear();

    vector<string> lines = Helper::ReadFileLines(file_path);
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

void QuestionsManager::PrintUserToQuestions(User &user) {
    cout << "\n";
    bool found = false;
    for (auto &pair : questionid_questionidsThead_to_map) {
        for (auto &question_id : pair.second) {
            Question &question = questionid_questionobject_map[question_id];
            if (question.GetToUserId() != user.GetUserId()) continue;
            question.PrintToQuestion();
            found = true;
        }
    }
    if (!found) cout << "No Questions";
    cout << "\n";
}

void QuestionsManager::PrintUserFromQuestions(User &user) {
    cout << "\n";
    bool found = false;
    for (auto &pair : questionid_questionidsThead_to_map) {
        for (auto &question_id : pair.second) {
            Question &question = questionid_questionobject_map[question_id];
            if (question.GetFromUserId() != user.GetUserId()) continue;
            question.PrintFromQuestion();
            found = true;
        }
    }
    if (!found) cout << "No Questions";
    cout << "\n";
}

int QuestionsManager::ReadQuestionIdAny(User &user) {
    while (true) {
        int question_id;
        cout << "Enter Question id or -1 to cancel: ";
        cin >> question_id;
        if (question_id == -1) return -1;
        if (!questionid_questionobject_map.count(question_id)) {
            cout << "\nERROR: No question with such ID. Try again\n\n";
            continue;
        }
        Question &question = questionid_questionobject_map[question_id];
        if (question.GetToUserId() != user.GetUserId()) {
            cout << "\nERROR: Invalid question ID. Try again\n\n";
            continue;
        }
        return question_id;
    }
}

int QuestionsManager::ReadQuestionIdThread(User &user) {
    while (true) {
        int question_id;
        cout << "For thread question: Enter Question id or -1 for new question: ";
        cin >> question_id;
        if (question_id == -1) return -1;
        if (!questionid_questionidsThead_to_map.count(question_id)) {
            cout << "No thread question with such ID. Try again\n";
            continue;
        }
        return question_id;
    }
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
    Helper::WriteFileLines(file_path, lines, false);
}
