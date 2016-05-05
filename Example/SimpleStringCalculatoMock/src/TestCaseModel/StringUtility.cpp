#include <string>
#include <vector>
#include <clocale>
#include <locale>
#include <algorithm>
#include <sstream>

#include "StringUtility.h"

using namespace std;

void StringUtility::Split(vector<wstring>& tokens, const wstring& wstr)
{
    int start = 0;
    int end = 0;
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
    const wchar_t* WHITE_SPACES = L" \t";

    wstring result;
    wstring::size_type left = wstr.find_first_not_of(WHITE_SPACES);
    if (left != wstring::npos)
    {
        wstring::size_type right = wstr.find_last_not_of(WHITE_SPACES);
        result = wstr.substr(left, right - left + 1);
    }

    return FilterQuotations(result);
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
	if (wstr.length() == 0) return std::string();

	const std::locale locale("");
	typedef std::codecvt<wchar_t, char, std::mbstate_t> converter_type;
	const converter_type& converter = std::use_facet<converter_type>(locale);
	std::vector<char> to(wstr.length() * converter.max_length());
	std::mbstate_t state;
	const wchar_t* from_next;
	char* to_next;
	const converter_type::result result = converter.out(state, wstr.data(), wstr.data() + wstr.length(), from_next, &to[0], &to[0] + to.size(), to_next);
	if (result == converter_type::ok || result == converter_type::noconv)
	{
		std::string(&to[0], to_next);
		return std::string(&to[0], to_next);
	}

	return std::string();
}

// It only works for ASCII only wstring
std::string StringUtility::wstring2string2(const wstring& wstr)
{
	if (wstr.length() == 0) return "";

	size_t length = wstr.size();
	size_t convLength;
	const size_t mem_size = sizeof(char)* length * 2 + 1; // enough memory to have a string
	char *c = (char*)malloc(mem_size);
	wcstombs_s(&convLength, c, mem_size, wstr.c_str(), length * 2);

	string resultStr(c);
	free(c);

	return resultStr;
}

wstring StringUtility::string2wstring(const string& str)
{
    size_t length = str.size();
    size_t convLength;
    wchar_t *wc = (wchar_t*)malloc(sizeof(wchar_t)* (length + 2));
    mbstowcs_s(&convLength, wc, length + 1, str.c_str(), _TRUNCATE);

    wstring resultStr(wc);
    free(wc);

    return resultStr;
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
	return (int)stol(wstr);
}

int StringUtility::stoi(const string& str)
{
    return (int)stol(str);
}

long StringUtility::stol(const wstring& wstr)
{
    string str = wstring2string(wstr);
	RemoveAllComma(str);
    if (!IsNumber(str))
    {
        return LONG_MAX;
    }

    return stol(str);
}

long StringUtility::stol(const string& str)
{
    char* error = NULL;
    long value = strtol(str.c_str(), &error, 10);
    if (*error == '\0')
        return value;
    else
        return LONG_MAX;
}

double StringUtility::stod(const wstring& wstr)
{
    string str = wstring2string(wstr);
	RemoveAllComma(str);
	if (!IsNumber(str))
    {
        return HUGE_VAL;
    }

    char* error = NULL;
    double value = strtod(str.c_str(), &error);
    if (*error == '\0')
        return value;
    else
        return HUGE_VAL;
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


wstring StringUtility::RemoveAllChar(const wstring& str, char ch)
{
	wstring workStr = str;
	workStr.erase(std::remove(workStr.begin(), workStr.end(), ch), workStr.end());

	return workStr;
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
