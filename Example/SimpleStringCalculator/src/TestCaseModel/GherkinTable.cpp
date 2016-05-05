#include "GherkinTable.h"

GherkinColumn GherkinRow::nullColumn;
GherkinRow GherkinTable::nullRow;

bool GherkinColumn::operator==(const GherkinColumn& column) const
{
	return value == column.value;
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

	for (int i = 0; i < this->ColumnCount(); i++ )
	{
		GherkinRow& other_row = const_cast<GherkinRow&>(row);
		if ( columns[i] != other_row[i] )
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

bool GherkinTable::operator==(const GherkinTable& table) const
{
	if (this->RowCount() != table.RowCount())
	{
		return false;
	}

	for (int i = 0; i < this->RowCount(); i++ )
	{
		GherkinTable& other_table = const_cast<GherkinTable&>(table);
		if ( rows[i] != other_table[i] )
		{
			return false;
		}
	}

	return true;
}
