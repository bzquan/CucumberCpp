#pragma once

#include <string>
#include <map>
#include <list>
#include <vector>
#include <math.h>
#include <locale>

using namespace std;

class StrUtility
{
public:
    static vector<wstring> Split(const wstring& wstr, wchar_t delim);
    static wstring Trim(const wstring& wstr);
    static void Trim2(wstring& wstr);
    static wstring TrimEnd(const wstring& wstr);
    static wstring string2wstring(const string& str);
    static string wstring2string (const wstring& str);
    static void ReplaceAll(std::wstring& text, std::wstring from, std::wstring to);
    static void ReplaceFirst(std::wstring& text, std::wstring from, std::wstring to);
    static wstring NewGuid();
    static bool startWith(std::wstring& wstr, std::wstring prefix);
};

