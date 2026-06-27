#ifndef HELPER_H
#define HELPER_H

#include <bits/stdc++.h>
using namespace std;

class Helper {
public:
    static vector<string> ReadFileLines(const string &path);
    static void WriteFileLines(const string &path, const vector<string> &lines, bool append = true);
    static vector<string> SplitString(const string &s, const string &delimiter = ",");
    static int ToInt(const string &str);
    static int ReadInt(int low, int high);
    static int ShowReadMenu(const vector<string> &choices);
};

#endif