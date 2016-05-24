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
#include <vector>
#include <exception>

#include "StringUtility.h"

using namespace std;

namespace bdd
{
	class GherkinColumn
	{
	public:
		GherkinColumn() : m_Value(L"") {}
		GherkinColumn(wstring str) : m_Value(str) {}

		int intValue() { return StringUtility::stoi(m_Value); }
		long longValue() { return StringUtility::stol(m_Value); }
		double doubleValue() { return StringUtility::stod(m_Value); }
		wstring wstrValue() { return m_Value; }
		NString NStrValue() { return StringUtility::wstring2NString(m_Value); }
		string strValue() { return StringUtility::wstring2string(m_Value); }
		bool boolValue() { return (m_Value == L"true") || (m_Value == L"TRUE"); }

		bool operator==(const GherkinColumn& column) const;
		bool operator!=(const GherkinColumn& column) const;

	private:
		wstring m_Value;
	};

    class GherkinTable;

	class GherkinRow
	{
	public:
		GherkinRow() : m_pTable(nullptr){}
		GherkinRow(wstring row_value) : m_pTable(nullptr) { InitializeColumns(row_value); }
        GherkinRow(GherkinTable* pTable, wstring row_value) : m_pTable(pTable) { InitializeColumns(row_value); }
        int ColumnCount() const { return m_Columns.size(); }
        GherkinColumn& operator[](int index);
        GherkinColumn& operator[](wstring col_name);

        std::vector<GherkinColumn>::iterator begin() { return m_Columns.begin(); }
        std::vector<GherkinColumn>::iterator end() { return m_Columns.end(); }

		bool operator==(const GherkinRow& row) const;
		bool operator!=(const GherkinRow& row) const;

        void SetTable(GherkinTable* pTable) { m_pTable = pTable; }

    private:
        void InitializeColumns(wstring& row_value);

	private:
		vector<GherkinColumn> m_Columns;
        GherkinTable* m_pTable;
	};

	class GherkinTable
	{
	public:
        GherkinTable() {}
        GherkinTable(wstring table);
        GherkinTable(const GherkinTable& table);
        GherkinTable& operator=(const GherkinTable& table);

        vector<wstring> ColumnNames() { return m_ColumNames; }

        GherkinTable& AddRow(wstring row);
        vector<GherkinRow>& Rows() { return m_Rows; }
        GherkinRow& operator[](int index);

        int RowCount() const { return m_Rows.size(); }
        int ColIndexFromName(wstring col_name);

		std::vector<GherkinRow>::iterator begin() { return m_Rows.begin(); }
		std::vector<GherkinRow>::iterator end() { return m_Rows.end(); }

		bool operator==(const GherkinTable& table) const;

    private:
        void Copy(const GherkinTable& table);
    
    private:
		vector<GherkinRow> m_Rows;
        vector<wstring>    m_ColumNames;
	};
}

using namespace bdd;	// for compatibility with previous version
