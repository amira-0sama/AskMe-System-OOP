#ifndef HELPER_H
#define HELPER_H

#include <bits/stdc++.h>

class Helper {
public:
    static std::vector<std::string> ReadFileLines(const std::string &path);
    static void WriteFileLines(const std::string &path, const std::vector<std::string> &lines, bool append = true);
    static std::vector<std::string> SplitString(const std::string &s, const std::string &delimiter = ",");
    static int ToInt(const std::string &str);
    static int ReadInt(int low, int high);
    static int ShowReadMenu(const std::vector<std::string> &choices);
};

#endif
