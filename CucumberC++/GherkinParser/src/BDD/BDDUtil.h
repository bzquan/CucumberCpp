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
#include <exception>

namespace CucumberCpp
{
    class BadFileException : public std::exception
    {
    public:
        BadFileException(const std::wstring& filePath) :
            m_msg(L"Bad file:\n")
        {
            m_msg.append(filePath);
        }

        const std::wstring& ErrorMsg() const { return m_msg; }

    private:
        std::wstring m_msg;
    };

    class BDDUtil
    {
    public:
        static std::wstring INDENT;
        static std::wstring INDENT_DOUBLE;
        static std::wstring INDENT_DOUBLE_PLUS;
        static std::wstring INDENT_TRIPLE;
        static std::wstring INDENT_TABLE_HEADER;
        static std::wstring ParameterClassName;
        
        static std::wstring FloatRegex;
        static std::wstring StringRegex;
        static std::wstring RowParamRegex;
        static std::wstring StepPattern;

        static std::wstring NEW_LINE;
        static wchar_t      NEW_LINE_CHAR;
        static std::wstring TEST_METHOD_BODY;

    public:
        static std::wstring ReplaceWhiteSpaceWithUnderBar(const std::wstring& str);
        static std::wstring RemoveAllWhiteSpaces(const std::wstring& str);
        static std::wstring TrimWhiteSpaces(const std::wstring& str);
        static std::wstring MakeIdentifier(const std::wstring& str);
        static std::wstring ToTitleCase(const std::wstring& str);
        static std::wstring ToLowerCaseWithUnderBar(const std::wstring& str);
        static std::wstring ToCPPwstringLiteral(const std::wstring& str);
        static void WriteFileAsUTF8WithBOM(std::wstring filepath, std::wstring contents);
        static std::wstring to_ident(std::wstring name);
        static std::wstring to_symbol(std::wstring ident);
        static bool supportUnicode() { return s_supportUnicode; }
        static void supportUnicode(bool flag) { s_supportUnicode = flag; }

    private:
        static std::wstring to_wstring(wchar_t ch);
        static void WriteFileAsUTF8WithBOMWin32(std::wstring filepath, std::wstring contents);
        static void WriteFileAsUTF8WithBOMQt(std::wstring filepath, std::wstring contents);

    private:
        static bool  s_supportUnicode;
    };
}
