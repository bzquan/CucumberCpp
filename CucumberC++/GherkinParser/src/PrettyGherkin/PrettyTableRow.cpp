#include "PrettyGherkin.h"
#include "PrettyTableRowFormatter.h"
#include "PrettyTableRow.h"

using namespace std;
using namespace GherkinAst;

PrettyTableRow::PrettyTableRow(TableRow& row) : m_TableRow(row)
{
    for (TableCell& cell : row.Cells())
    {
        m_Cells.push_back(PrettyTableCell(cell));
    }
}

void PrettyTableRow::FormatOriginalRow(PrettyGherkin& prettyGherkin, std::vector<int> preferedCellsWidth)
{
    PrettyTableRowFormatter4Feature rowFormatter(*this);
    wstring formattedRow = rowFormatter.Format(preferedCellsWidth);
    prettyGherkin.append(formattedRow);

    m_TableRow.OriginalFormattedText = formattedRow;
}

void PrettyTableRow::FormatTrimmedRow(std::vector<int> preferedCellsWidth)
{
    PrettyTableRowFormatter4GoogleTest rowFormatter(*this);
    m_TableRow.TrimmedFormattedText = rowFormatter.Format(preferedCellsWidth);
}
