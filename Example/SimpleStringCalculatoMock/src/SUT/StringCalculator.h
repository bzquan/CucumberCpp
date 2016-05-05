#pragma once

#include <vector>
#include <string>

using namespace std;

class IDisplay;

class StringCalculator
{
public:
    StringCalculator(IDisplay& display) : m_display(display) {}
    void Input(const string input) { m_inputString = input; }
    void CalculateSum();

private:
    std::vector<string> Split(const string &str, char delim);
    char GetSeparator(const string& input);
    bool IsSeprator(const string& input, char ch);
    bool IsAllDigit(const string& str);

private:
    IDisplay& m_display;
    string    m_inputString;
};
