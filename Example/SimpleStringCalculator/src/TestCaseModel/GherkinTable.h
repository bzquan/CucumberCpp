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

	protected:
        void InitializeColumns(wstring& row_value);

	private:
		vector<GherkinColumn> m_Columns;
        GherkinTable* m_pTable;
	};

	class GherkinTable
	{
	public:
        void SetColumnNames(wstring col_names);
        vector<wstring> ColumnNames() { return m_ColumNames; }
        int ColIndexFromName(wstring col_name);

		int RowCount() const { return m_Rows.size(); }

        GherkinTable& AddRow(wstring row);
        GherkinRow& operator[](int index);

		std::vector<GherkinRow>::iterator begin() { return m_Rows.begin(); }
		std::vector<GherkinRow>::iterator end() { return m_Rows.end(); }

		bool operator==(const GherkinTable& table) const;

	private:
		vector<GherkinRow> m_Rows;
        vector<wstring>    m_ColumNames;
	};
}

using namespace bdd;	// for compatibility with previous version
