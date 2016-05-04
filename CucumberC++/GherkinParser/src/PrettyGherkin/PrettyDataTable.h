#pragma once

#include <vector>
#include "DataTable.h"
#include "PrettyTableRow.h"

class PrettyGherkin;

class PrettyDataTable
{
public:
    PrettyDataTable(GherkinAst::DataTable& baseTable)
    {
        CreatePrettyRows(baseTable);
    }

    std::vector<PrettyTableRow>& Rows() { return m_Rows; }
    void Format(PrettyGherkin& prettyGherkin);
    void FormatTrimmedTable(PrettyGherkin& prettyGherkin);

private:
    void CreatePrettyRows(GherkinAst::DataTable& baseTable);

private:
    std::vector<PrettyTableRow> m_Rows;
};

