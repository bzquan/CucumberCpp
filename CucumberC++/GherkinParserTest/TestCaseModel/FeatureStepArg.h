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

#if defined(WIN32) && (_MSC_VER < 1900)
    // _MSC_VER == 1900 (Visual Studio 2015, MSVC++ 14.0)
	#include <boost/regex.hpp>
#else
	#include <regex>
#endif

#include <string>
#include "StringUtility.h"

using namespace std;

namespace bdd
{
	enum StepArgType { StrType, LongType, DoubleType, UnknownType };

	class StepArg
	{
	public:
		StepArg(wstring value) : m_value(value)
		{
			Type = DeduceArgType(value);
			m_value = TrimArg(Type, value);
		}

		StepArgType Type;
		wstring wstrValue()
		{
			return m_value;
		}
		string strValue()
		{
			return StringUtility::wstring2string(m_value);
		}
		int intValue()
		{
            return StringUtility::stoi(m_value);
		}
		long longValue()
		{
			return StringUtility::stol(m_value);
		}
		double doubleValue()
		{
			return StringUtility::stod(m_value);
		}
		bool operator==(const StepArg& other) const
		{
			return ((Type == other.Type) && (m_value == other.m_value));
		}

	private:
		StepArgType DeduceArgType(wstring& arg)
		{
			if (arg[0] == L'\"')
			{
				return StrType;
			}
			else
			{
				return DeduceNumType(arg);
			}
		}

		StepArgType DeduceNumType(wstring &arg)
		{
			//		const wstring NumberRegex = L"([-+]?\\d[\\d,]*)";
			const wstring NumberRegex = L"([-+]?\\d[\\d,]*\\.?\\d*)";

			wregex exp(NumberRegex);
			wsmatch match;
			if (regex_match(arg, match, exp) && (match.size() == 2))
			{
				return (arg.find_first_of(L'.') == string::npos) ? LongType : DoubleType;
			}
			else
			{
				return UnknownType;
			}
		}

		wstring TrimArg(StepArgType argType, wstring& origArg)
		{
			if (argType == StrType)
				return RemoveQuotationMarks(origArg);
			else
				return origArg;
		}

		wstring RemoveQuotationMarks(wstring &origArg)
		{
			// remove double quotation marks from string argument
			wstring arg;
			for (size_t i = 1; i < origArg.size() - 1; i++)
			{
				arg.append(1, origArg[i]);
			}
			return arg;
		}

	private:
		wstring m_value;
	};
}

