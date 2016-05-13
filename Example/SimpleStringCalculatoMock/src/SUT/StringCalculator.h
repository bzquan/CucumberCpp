#pragma once

#include <vector>
#include <string>

class IDisplay;

class StringCalculator
{
public:
    StringCalculator(IDisplay* pDisplay = nullptr) : m_pDisplay(pDisplay) {}
    void Input(const std::string input) { m_inputString = input; }
    int CalculateSum();

private:
    std::vector<std::string> Split(const std::string &str, char delim);
    int CalculateSum(std::vector<std::string>& nums);
    char GetSeparator(const std::string& input);
    bool IsSeprator(const std::string& input, char ch);
    bool IsAllDigit(const std::string& str);
    void InformResult(int sum);

private:
    IDisplay*    m_pDisplay;
    std::string  m_inputString;
};
