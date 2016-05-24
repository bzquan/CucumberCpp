/* The MIT License (MIT)
 * 
 * Copyright (c) 2016 Bingzhe Quan
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <string>
#include <vector>
#include <clocale>
#include <locale>
#include <algorithm>
#include <sstream>
#include <codecvt>

#include "guid.h"
#include "StrUtility.h"

using namespace std;

namespace
{
    constexpr auto WHITE_SPACES = L" \t";
}

vector<wstring> StrUtility::Split(const wstring& wstr, wchar_t delim)
{
    std::vector<std::wstring> tokens;
    std::wstringstream ss(wstr);
    std::wstring item;
    while (std::getline(ss, item, delim)) {
        tokens.push_back(item);
    }

    return tokens;
}

wstring StrUtility::Trim(const wstring& wstr)
{
    if (wstr.length() == 0) return wstring();

    const wchar_t* WHITE_SPACES = L" \t";
    wstring::size_type left = wstr.find_first_not_of(WHITE_SPACES);
    wstring::size_type right = wstr.find_last_not_of(WHITE_SPACES);
    if (left != wstring::npos)
    {
        return wstr.substr(left, right - left + 1);
    }
    else
    {
        return wstring();
    }
}

void StrUtility::Trim2(wstring& wstr)
{
    wstring::size_type left = wstr.find_first_not_of(WHITE_SPACES);
    if (left != wstring::npos)
    {
        wstr.erase(0, left);
    }
    wstring::size_type right = wstr.find_last_not_of(WHITE_SPACES);
    if (right != wstring::npos)
    {
        wstr.erase(right + 1, wstr.length() - right);
    }
}

wstring StrUtility::TrimEnd(const wstring& wstr)
{
    wstring result;
    wstring::size_type left = wstr.find_first_not_of(WHITE_SPACES);
    if (left != wstring::npos)
    {
        wstring::size_type right = wstr.find_last_not_of(WHITE_SPACES);
        return wstr.substr(0, right + 1);
    }

    return result;
}

wstring StrUtility::string2wstring(const string& str)
{
    typedef std::codecvt_utf8<wchar_t> convert_type;
    std::wstring_convert<convert_type, wchar_t> cvt;

    return cvt.from_bytes(str);
}

string StrUtility::wstring2string (const wstring& wstr)
{
    typedef std::codecvt_utf8<wchar_t> convert_type;
    std::wstring_convert<convert_type, wchar_t> cvt;

    return cvt.to_bytes(wstr);
}

void StrUtility::ReplaceAll(std::wstring& text, std::wstring from, std::wstring to)
{
    size_t start_pos = 0;
    while ((start_pos = text.find(from, start_pos)) != std::wstring::npos) {
        text.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

void StrUtility::ReplaceFirst(std::wstring& text, std::wstring from, std::wstring to)
{
    size_t start_pos = 0;
    if ((start_pos = text.find(from, start_pos)) != std::wstring::npos) {
        text.replace(start_pos, from.length(), to);
    }
}

wstring StrUtility::NewGuid()
{
    GuidGenerator generator;
    Guid guid = generator.newGuid();

    stringstream ss;
    ss << guid;
    return string2wstring(ss.str());
}

bool StrUtility::startWith(wstring& wstr, wstring prefix)
{
    const size_t prefix_len = prefix.length();
    if (wstr.length() < prefix_len) return false;
    if (prefix_len == 0) return true;

    return wstr.substr(0, prefix_len) == prefix;
}
