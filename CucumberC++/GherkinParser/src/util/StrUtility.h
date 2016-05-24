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

