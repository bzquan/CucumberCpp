#pragma once

#include <string>

using namespace std;

class StringCalculator
{
public:
    StringCalculator() : m_Result(-1) {}
    void Input(const string input);
    int Result() { return m_Result; }

private:
    vector<string> Split(const string &str, char delim);
    char GetSeparator(const string& input);
    bool IsSeprator(const string& input, char ch);
    bool IsAllDigit(const string& str);

private:
    int m_Result;
};
