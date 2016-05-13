#include "GherkinTable.h"

bool GherkinColumn::operator==(const GherkinColumn& column) const
{
	return m_Value == column.m_Value;
}

bool GherkinColumn::operator!=(const GherkinColumn& column) const
{
	bool result = *this == column;
	return !result;
}

bool GherkinRow::operator==(const GherkinRow& row) const
{
	if (this->ColumnCount() != row.ColumnCount())
	{
		return false;
	}

	for (size_t i = 0; i < this->ColumnCount(); i++ )
	{
		GherkinRow& other_row = const_cast<GherkinRow&>(row);
		if ( m_Columns[i] != other_row[i] )
		{
			return false;
		}
	}

	return true;
}

bool GherkinRow::operator!=(const GherkinRow& row) const
{
	bool result = *this == row;
	return !result;
}

GherkinColumn& GherkinRow::operator[](int index)
{
    if ( (index >= 0) && (index < static_cast<int>(ColumnCount())) )
    {
        return m_Columns[index];
    }
    else
    {
        std::string msg("Out of range in GherkinRow: ");
        msg.append(std::to_string(index));
        throw exception(msg.c_str());
    }
}

GherkinColumn& GherkinRow::operator[](wstring col_name)
{
    if (m_pTable == nullptr) throw exception("No table set to GherkinRow.");

    int index = m_pTable->ColIndexFromName(col_name);
    return (*this)[index];
}

void GherkinRow::InitializeColumns(wstring& row_value)
{
    vector<wstring> tokens;
    StringUtility::Split(tokens, row_value);
    for (vector<wstring>::iterator it = tokens.begin(); it != tokens.end(); it++)
    {
        m_Columns.push_back(GherkinColumn(*it));
    }
}

GherkinTable::GherkinTable(const wstring table)
{
    vector<wstring> rows = StringUtility::Split(table, L'\n');
    if (rows.size() == 0) return;

    StringUtility::Split(m_ColumNames, rows[0]);

    for (size_t i = 1; i < rows.size(); i++)
    {
        AddRow(rows[i]);
    }
}

int GherkinTable::ColIndexFromName(wstring col_name)
{
    int index = 0;
    for (wstring& name : m_ColumNames)
    {
        if (name == col_name) return index;
        index++;
    }

    return -1;
}

GherkinTable& GherkinTable::AddRow(wstring row)
{
    m_Rows.push_back(GherkinRow(this, row));
    return *this;
}

bool GherkinTable::operator==(const GherkinTable& table) const
{
	if (this->RowCount() != table.RowCount())
	{
		return false;
	}

	for (size_t i = 0; i < this->RowCount(); i++ )
	{
		GherkinTable& other_table = const_cast<GherkinTable&>(table);
		if ( m_Rows[i] != other_table[i] )
		{
			return false;
		}
	}

	return true;
}

GherkinRow& GherkinTable::operator[](int index)
{
    if (index < static_cast<int>(RowCount()))
    {
        return m_Rows[index];
    }
    else
    {
        std::string msg("Out of range in GherkinTable: ");
        msg.append(std::to_string(index));
        throw exception(msg.c_str());
    }
}
