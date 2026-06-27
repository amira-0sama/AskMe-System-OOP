#include "Helper.h"

vector<string> Helper::ReadFileLines(const string &path) {
    vector<string> lines;
    fstream file_handler(path.c_str());
    if (file_handler.fail()) {
        cout << "\n\nERROR: Can't open the file\n\n";
        return lines;
    }
    string line;
    while (getline(file_handler, line)) {
        if (line.empty()) continue;
        lines.push_back(line);
    }
    file_handler.close();
    return lines;
}

void Helper::WriteFileLines(const string &path, const vector<string> &lines, bool append) {
    auto status = ios::in | ios::out | ios::app;
    if (!append) status = ios::in | ios::out | ios::trunc;

    fstream file_handler(path.c_str(), status);
    if (file_handler.fail()) {
        cout << "\n\nERROR: Can't open the file\n\n";
        return;
    }
    for (const auto &line : lines)
        file_handler << line << "\n";
    file_handler.close();
}

vector<string> Helper::SplitString(const string &s, const string &delimiter) {
    vector<string> strs;
    string temp = s;
    size_t pos = 0;
    while ((pos = temp.find(delimiter)) != string::npos) {
        strs.push_back(temp.substr(0, pos));
        temp.erase(0, pos + delimiter.length());
    }
    strs.push_back(temp);
    return strs;
}

int Helper::ToInt(const string &str) {
    istringstream iss(str);
    int num;
    iss >> num;
    return num;
}

int Helper::ReadInt(int low, int high) {
    cout << "\nEnter number in range " << low << " - " << high << ": ";
    int value;
    cin >> value;
    if (value >= low && value <= high) return value;
    cout << "ERROR: invalid number...Try again\n";
    return ReadInt(low, high);
}

int Helper::ShowReadMenu(const vector<string> &choices) {
    cout << "\nMenu:\n";
    for (int i = 0; i < (int)choices.size(); i++)
        cout << "\t" << i + 1 << ": " << choices[i] << "\n";
    return ReadInt(1, choices.size());
}