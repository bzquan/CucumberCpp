#include <vector>
#include <sstream>
#include "StringCalculator.h"

void StringCalculator::Input(const string input)
{
    char delim = GetSeparator(input);
    vector<string> nums = Split(input, delim);
    m_Result = 0;
    for (string& str : nums)
    {
        if (IsAllDigit(str))
            m_Result += (int)stol(str);
        else
        {
            m_Result = -1;
            return;
        }
    }
}

char StringCalculator::GetSeparator(const string& input)
{
    if (IsSeprator(input, '+'))
        return '+';
    else if (IsSeprator(input, ','))
        return ',';
    else if (IsSeprator(input, ';'))
        return ';';
    else
        return '\0';
}

vector<string> StringCalculator::Split(const string &str, char delim)
{
    istringstream iss(str);
    string tmp;
    vector<string> res;
    while (getline(iss, tmp, delim))
        res.push_back(tmp);
    
    return res;
}

bool StringCalculator::IsSeprator(const string& input, char ch)
{
    return string::npos != input.find(ch);
}

bool StringCalculator::IsAllDigit(const string& str)
{
    if (str.length() == 0) return false;
    for (char ch : str)
    {
        bool is_digit = (ch >= '0') && (ch <= '9');
        bool is_space = (ch == ' ');
        if (!is_digit && !is_space) return false;
    }
    return true;
}
