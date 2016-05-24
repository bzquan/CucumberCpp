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

#include "GeneralMacro.h"
//#include "NString.h"

using namespace std;

class StringUtility
{
public:
    static void Split(vector<wstring>& tokens, const wstring& wstr);
    static vector<string> Split(const string &str, char delimiter);
    static vector<wstring> Split(const wstring &str, wchar_t delimiter);

    static wstring Trim(const wstring& str);

    static string wstring2string(const wstring& wstr);
	static string wstring2string2(const wstring& wstr);
	static wstring string2wstring(const string& str);
	static NString wstring2NString(const wstring& wstr);

	static bool IsDigit(char ch);
	static bool IsNumber(const string& str);
    static int stoi(const wstring& wstr);
    static int stoi(const string& str);
    static long stol(const wstring& wstr);
    static long stol(const string& str);
    static double stod(const wstring& wstr);

    static wstring RemoveAllChar(const wstring& str, wchar_t ch);
    static string RemoveAllChar(const string& str, char ch);
    static string int2hex(int value);
    static int convertToBinary(const wstring& str, char* buffer, size_t buffer_size);

private:
    static wstring FilterQuotations(const wstring& wstr);
    static string RemoveAllComma(const string& str){ return RemoveAllChar(str, ','); }
    static wstring RemoveAllComma(const wstring& str){ return RemoveAllChar(str, L','); }
    static void RemoveAllCharDirectly(string& str, char ch);
    static void RemoveAllCharDirectly(wstring& str, wchar_t ch);
    static bool IsValidStartOfNumber(const string& str);
    static char char2octet(wchar_t ch);
};

