#include <vector>
#include <sstream>
#include "IDisplay.h"
#include "StringCalculator.h"

int StringCalculator::CalculateSum()
{
    char delim = GetSeparator(m_inputString);
    std::vector<std::string> nums = Split(m_inputString, delim);
    int sum = CalculateSum(nums);
    InformResult(sum);

    return sum;
}

void StringCalculator::InformResult(int sum)
{
    if (m_pDisplay != nullptr) m_pDisplay->Sum(sum);
}

char StringCalculator::GetSeparator(const std::string& input)
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
    std::stringstream iss(str);
    std::string tmp;
    std::vector<std::string> splitted_str;
    while (getline(iss, tmp, delim))
        splitted_str.push_back(tmp);
    
    return splitted_str;
}

int StringCalculator::CalculateSum(std::vector<std::string>& nums)
{
    int sum = 0;
    for (std::string& str : nums)
    {
        if (IsAllDigit(str))
            sum += std::stoi(str);
        else
        {
            sum = 0;
            break;
        }
    }

    return sum;
}

bool StringCalculator::IsSeprator(const std::string& input, char ch)
{
    return std::string::npos != input.find(ch);
}

bool StringCalculator::IsAllDigit(const std::string& str)
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
