#pragma once

#include <vector>
#include "Location.h"
#include "TableRow.h"
#include "PrettyTableCell.h"

class PrettyGherkin;

class PrettyTableRow
{
public:
    PrettyTableRow(GherkinAst::TableRow& row);

    GherkinAst::Location& Location() { return m_TableRow.Location(); }
    std::vector<PrettyTableCell>& Cells() { return m_Cells; }
    void FormatOriginalRow(PrettyGherkin& prettyGherkin, std::vector<int> preferedCellsWidth);
    void FormatTrimmedRow(std::vector<int> preferedCellsWidth);

private:
    GherkinAst::TableRow& m_TableRow;
    std::vector<PrettyTableCell> m_Cells;
};
