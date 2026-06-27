#include "Question.h"

Question::Question() {
    question_id = parent_question_id = from_user_id = to_user_id = -1;
    is_anonymous_questions = 1;
}

Question::Question(const string &line) {
    vector<string> substrs = Helper::SplitString(line);
    assert(substrs.size() == 7);
    question_id = Helper::ToInt(substrs[0]);
    parent_question_id = Helper::ToInt(substrs[1]);
    from_user_id = Helper::ToInt(substrs[2]);
    to_user_id = Helper::ToInt(substrs[3]);
    is_anonymous_questions = Helper::ToInt(substrs[4]);
    question_text = substrs[5];
    answer_text = substrs[6];
}

string Question::ToString() const {
    ostringstream oss;
    oss << question_id << "," << parent_question_id << "," << from_user_id << "," 
        << to_user_id << "," << is_anonymous_questions << "," << question_text << "," << answer_text;
    return oss.str();
}

void Question::PrintToQuestion() const {
    string prefix = (parent_question_id != -1) ? "\tThread: " : "";
    cout << prefix << "Question Id (" << question_id << ")";
    if (!is_anonymous_questions) cout << " from user id(" << from_user_id << ")";
    cout << "\t Question: " << question_text << "\n";
    if (!answer_text.empty()) cout << prefix << "\tAnswer: " << answer_text << "\n";
    cout << "\n";
}

void Question::PrintFromQuestion() const {
    cout << "Question Id (" << question_id << ")";
    if (!is_anonymous_questions) cout << " !AQ";
    cout << " to user id(" << to_user_id << ")";
    cout << "\t Question: " << question_text;
    if (!answer_text.empty()) cout << "\tAnswer: " << answer_text << "\n";
    else cout << "\tNOT Answered YET\n";
}

void Question::PrintFeedQuestion() const {
    if (parent_question_id != -1) cout << "Thread Parent Question ID (" << parent_question_id << ") ";
    cout << "Question Id (" << question_id << ")";
    if (!is_anonymous_questions) cout << " from user id(" << from_user_id << ")";
    cout << " To user id(" << to_user_id << ")\t Question: " << question_text << "\n";
    if (!answer_text.empty()) cout << "\tAnswer: " << answer_text << "\n";
}