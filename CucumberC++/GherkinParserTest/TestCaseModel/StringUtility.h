#pragma once

#include <string>
#include <map>
#include <list>
#include <vector>
#include <math.h>

#include "GeneralMacro.h"
//#include "NString.h"

class StringUtility
{
public:
    static void Split(std::vector<std::wstring>& tokens, const std::wstring& wstr);
    static std::wstring Trim(const std::wstring& str);

    static std::string wstring2string(const std::wstring& wstr);
    static std::wstring string2wstring(const std::string& str);
    static NString wstring2NString(const std::wstring& wstr);

	static bool IsDigit(char ch);
    static bool IsNumber(const std::string& str);
    static int stoi(const std::wstring& wstr);
    static long stol(const std::wstring& wstr);
    static double stod(const std::wstring& wstr);

    static std::wstring RemoveAllChar(const std::wstring& str, char ch);
    static std::string RemoveAllChar(const std::string& str, char ch);
    static std::string int2hex(int value);
    static int convertToBinary(const std::wstring& str, char* buffer, size_t buffer_size);

private:
    static int stoi(const std::string& str);
    static long stol(const std::string& str);

private:
    static std::wstring FilterQuotations(const std::wstring& wstr);
    static std::wstring RemoveAllComma(const std::wstring& wstr){ return RemoveAllChar(wstr, ','); }
    static std::string RemoveAllComma(const std::string& str){ return RemoveAllChar(str, ','); }
    static void RemoveAllCharDirectly(std::string& str, char ch);
    static bool IsValidStartOfNumber(const std::string& str);
    static char char2octet(wchar_t ch);
};

