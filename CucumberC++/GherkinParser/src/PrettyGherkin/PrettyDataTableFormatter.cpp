#include <algorithm>
#include "Definitions.h"
#include "PrettyGherkin.h"
#include "PrettyDataTableFormatter.h"

using namespace std;
using namespace GherkinAst;

void PrettyDataTableFormatter::Format(PrettyGherkin& prettyGherkin)
{
    vector<int> preferedCellsWidth = CalculatePreferedCellsWidth();
    FormatTableRows(prettyGherkin, preferedCellsWidth);
}

void PrettyDataTableFormatter::FormatTableRows(PrettyGherkin& prettyGherkin, std::vector<int>& preferedCellsWidth)
{
    for (PrettyTableRow& tableRow : m_Rows)
    {
        prettyGherkin.AppendOriginalComment(tableRow.Location().Line());
        FormatTableRow(tableRow, prettyGherkin, preferedCellsWidth);
    }
}

vector<int> PrettyDataTableFormatter::CalculatePreferedCellsWidth()
{
    vector<int> preferedCellsWidth;
    if (m_Rows.size() == 0) return preferedCellsWidth;

    for (size_t column = 0; column < m_Rows[0].Cells().size(); column++)
    {
        preferedCellsWidth.push_back(CalculatePreferedCellWidth(column));
    }

    return preferedCellsWidth;
}

int PrettyDataTableFormatter::CalculatePreferedCellWidth(int column)
{
    int preferedCellsWidth = 0;
    for (size_t i = 0; i < m_Rows.size(); i++)
    {
        PrettyTableCell& cell = m_Rows[i].Cells()[column];
        preferedCellsWidth = std::max(GetCellValueWidth(cell), preferedCellsWidth);
    }

    return preferedCellsWidth;
}

void PrettyDataTableFormatter4GoogleTest::FormatTableRow(PrettyTableRow& tableRow, PrettyGherkin& /*prettyGherkin*/, std::vector<int>& preferedCellsWidth)
{
    tableRow.FormatTrimmedRow(preferedCellsWidth);
}

void PrettyDataTableFormatter4Feature::FormatTableRow(PrettyTableRow& tableRow, PrettyGherkin& prettyGherkin, std::vector<int>& preferedCellsWidth)
{
    tableRow.FormatOriginalRow(prettyGherkin, preferedCellsWidth);
    prettyGherkin.appendLine();
}
