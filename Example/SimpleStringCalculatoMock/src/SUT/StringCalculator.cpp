#include <vector>
#include <sstream>
#include "IDisplay.h"
#include "StringCalculator.h"

void StringCalculator::CalculateSum()
{
    char delim = GetSeparator(m_inputString);
    vector<string> nums = Split(m_inputString, delim);
    int sum = 0;
    for (string& str : nums)
    {
        if (IsAllDigit(str))
            sum += (int)stol(str);
        else
        {
            sum = -1;
            break;
        }
    }

    m_display.Sum(sum);
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

std::vector<std::string> StringCalculator::Split(const std::string &str, char delim)
{
    std::istringstream iss(str);
    std::string tmp;
    std::vector<string> splitted_str;
    while (getline(iss, tmp, delim))
        splitted_str.push_back(tmp);
    
    return splitted_str;
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
