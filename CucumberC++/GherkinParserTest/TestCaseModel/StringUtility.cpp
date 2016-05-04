#include <string>
#include <vector>
#include <clocale>
#include <locale>
#include <algorithm>
#include <sstream>
#include <codecvt>
#include <climits>
#include "StringUtility.h"

using namespace std;

void StringUtility::Split(vector<wstring>& tokens, const wstring& wstr)
{
    wstring::size_type start = 0;
    wstring::size_type end = 0;
    while ((end = wstr.find(L'|', start)) != string::npos) {
        if (start < end)
        {
            wstring column = wstr.substr(start, end - start);
            tokens.push_back(Trim(column));
        }
        start = end + 1;
    }
}

wstring StringUtility::Trim(const wstring& wstr)
{
    if (wstr.length() == 0) return wstring();

    const wchar_t* WHITE_SPACES = L" \t";
    wstring::size_type left = wstr.find_first_not_of(WHITE_SPACES);
    wstring::size_type right = wstr.find_last_not_of(WHITE_SPACES);
    if (left != wstring::npos)
    {
        wstring result = wstr.substr(left, right - left + 1);
        return FilterQuotations(result);
    }
    else
    {
        return wstring();
    }
}

wstring StringUtility::FilterQuotations(const wstring& wstr)
{
	wstring ws = wstr;
    wstring::size_type left_quotaion = ws.find_first_of(L'"');
    wstring::size_type right_quotaion = ws.find_last_of(L'"');
    wstring::size_type length = ws.length();
    if ((length > 2) && (left_quotaion == 0) && (right_quotaion == length-1))
    {
        return ws.substr(left_quotaion + 1, right_quotaion - 1);
    }
    else
    {
        return ws;
    }
}

string StringUtility::wstring2string(const wstring& wstr)
{
    typedef std::codecvt_utf8<wchar_t> convert_type;
    std::wstring_convert<convert_type, wchar_t> cvt;

    return cvt.to_bytes(wstr);
}

wstring StringUtility::string2wstring(const string& str)
{
    typedef std::codecvt_utf8<wchar_t> convert_type;
    std::wstring_convert<convert_type, wchar_t> cvt;

    return cvt.from_bytes(str);
}

NString StringUtility::wstring2NString(const wstring& wstr)
{
	return NString(wstr.c_str());
}

bool StringUtility::IsNumber(const string& str)
{
    if (!IsValidStartOfNumber(str))
    {
        return false;
    }

    string::const_iterator it = str.begin();
    it++;   // skip the first character because it is valid beginning of a number
    while (it != str.end() && (IsDigit(*it) || (*it == '.'))) ++it;
    return !str.empty() && it == str.end();
}

bool StringUtility::IsDigit(char ch)
{
	return (ch >= '0') && (ch <= '9');
}

bool StringUtility::IsValidStartOfNumber(const string& str)
{
    if (str.length() == 0)
    {
        return false;
    }

    char ch = str[0];
    return (ch == '-') || (ch == '+') || IsDigit(ch);
}

int StringUtility::stoi(const wstring& wstr)
{
    wstring text = RemoveAllComma(wstr);

    try
    {
        return std::stoi(text);
    }
    catch(...)
    {
        return INT_MAX;
    }
}

int StringUtility::stoi(const string& str)
{
    string text = RemoveAllComma(str);
    try
    {
        return std::stoi(text);
    }
    catch(...)
    {
        return INT_MAX;
    }
}

long StringUtility::stol(const wstring& wstr)
{
    wstring text = RemoveAllComma(wstr);
    try
    {
        return std::stol(text);
    }
    catch(...)
    {
        return LONG_MAX;
    }
}

long StringUtility::stol(const string& str)
{
    string text = RemoveAllComma(str);
    try
    {
        return std::stol(text);
    }
    catch(...)
    {
        return LONG_MAX;
    }
}

double StringUtility::stod(const wstring& wstr)
{
    wstring text = RemoveAllComma(wstr);
    try
    {
        return std::stod(text);
    }
    catch(...)
    {
        return HUGE_VAL;
    }
}

wstring StringUtility::RemoveAllChar(const wstring& str, char ch)
{
    wstring workStr = str;
    workStr.erase(std::remove(workStr.begin(), workStr.end(), ch), workStr.end());

    return workStr;
}

string StringUtility::RemoveAllChar(const string& str, char ch)
{
	// std::string - erase : Erases the sequence of characters in the range [first,last).
	// std::remove : Transforms the range [first,last) into a range with all the elements
	//               that compare equal to val removed, and returns an iterator to the new end of that range.

    string workStr = str;
    RemoveAllCharDirectly(workStr, ch);

    return workStr;
}

void StringUtility::RemoveAllCharDirectly(string& str, char ch)
{
    // std::string - erase : Erases the sequence of characters in the range [first,last).
    // std::remove : Transforms the range [first,last) into a range with all the elements
    //               that compare equal to val removed, and returns an iterator to the new end of that range.

    str.erase(std::remove(str.begin(), str.end(), ch), str.end());
}

string StringUtility::int2hex(int value)
{
    std::stringstream stream;
    stream << std::hex << value;
    std::string result(stream.str());

    return result;
}

char StringUtility::char2octet(wchar_t ch)
{
    if ((ch >= L'0') && (ch <= L'9'))
    {
        return (char)(ch - L'0');
    }
    else if ((ch >= L'A') && (ch <= L'F'))
    {
        return (char)(10 + (ch - L'A'));
    }
    else if ((ch >= L'a') && (ch <= L'f'))
    {
        return (char)(10 + (ch - L'a'));
    }
    else
    {
        return 0xF;
    }
}

int StringUtility::convertToBinary(const wstring& str, char* buffer, size_t buffer_size)
{
    if (NULL == buffer) return -1;

    // 長さは2以上の偶数
    const size_t len = str.length();
    if ((len < 2) || (len % 2 != 0)) return -1;

    const size_t octet_length = len / 2;
    if (buffer_size < octet_length) return -1;

    for (size_t i = 0; (i < octet_length) && (i < buffer_size); i++)
    {
        buffer[i] = char2octet(str[i * 2]) * 0x10 + char2octet(str[i * 2 + 1]);
    }

    return octet_length;
}
