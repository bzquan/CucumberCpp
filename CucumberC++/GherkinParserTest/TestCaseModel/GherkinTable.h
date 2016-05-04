#pragma once

#include <string>
#include <vector>

#include "StringUtility.h"

using namespace std;

namespace bdd
{
	class GherkinColumn
	{
	public:
		GherkinColumn() : value(L"") {}
		GherkinColumn(wstring str) : value(str) {}

		int intValue() { return StringUtility::stoi(value); }
		long longValue() { return StringUtility::stol(value); }
		double doubleValue() { return StringUtility::stod(value); }
		wstring wstrValue() { return value; }
		NString NStrValue() { return StringUtility::wstring2NString(value); }
		string strValue() { return StringUtility::wstring2string(value); }
		bool boolValue() { return (value == L"true") || (value == L"TRUE"); }

		bool operator==(const GherkinColumn& column) const;
		bool operator!=(const GherkinColumn& column) const;

	private:
		wstring value;
	};

	class GherkinRow
	{
	public:
		GherkinRow() {}
		GherkinRow(wstring row_value) { InitializeColumns(row_value); }
		int ColumnCount() const { return columns.size(); }
		GherkinColumn& operator[](int index) { return (index < ColumnCount()) ? columns[index] : nullColumn; }

        std::vector<GherkinColumn>::iterator begin()
        {
            return columns.begin();
        }

        std::vector<GherkinColumn>::iterator end()
        {
            return columns.end();
        }

		bool operator==(const GherkinRow& row) const;
		bool operator!=(const GherkinRow& row) const;

	protected:
		void InitializeColumns(wstring& row_value)
		{
			vector<wstring> tokens;
			StringUtility::Split(tokens, row_value);
			for (vector<wstring>::iterator it = tokens.begin(); it != tokens.end(); it++)
			{
				columns.push_back(GherkinColumn(*it));
			}
		}

	private:
		vector<GherkinColumn> columns;
		static GherkinColumn nullColumn;
	};

	class GherkinTable
	{
	public:
		int RowCount() const { return rows.size(); }

		GherkinTable& AddRow(wstring row)
		{
			rows.push_back(GherkinRow(row));
			return *this;
		}

		GherkinRow& operator[](int index)
		{
			if (index < RowCount())
			{
				return rows[index];
			}
			else
			{
				return nullRow;
			}
		}

		std::vector<GherkinRow>::iterator begin()
		{
			return rows.begin();
		}

		std::vector<GherkinRow>::iterator end()
		{
			return rows.end();
		}

		bool operator==(const GherkinTable& table) const;

	private:
		vector<GherkinRow> rows;
		static GherkinRow nullRow;
	};
}

using namespace bdd;	// for compatibility with previous version
