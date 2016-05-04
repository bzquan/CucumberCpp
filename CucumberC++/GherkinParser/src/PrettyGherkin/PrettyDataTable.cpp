#include "PrettyGherkin.h"
#include "PrettyDataTableFormatter.h"
#include "PrettyDataTable.h"

using namespace GherkinAst;

void PrettyDataTable::CreatePrettyRows(DataTable& baseTable)
{
    for (TableRow& row : baseTable.Rows())
    {
        m_Rows.push_back(PrettyTableRow(row));
    }
}

void PrettyDataTable::Format(PrettyGherkin& prettyGherkin)
{
    PrettyDataTableFormatter4Feature formatter(*this);
    formatter.Format(prettyGherkin);

    FormatTrimmedTable(prettyGherkin);
}

void PrettyDataTable::FormatTrimmedTable(PrettyGherkin& prettyGherkin)
{
    PrettyDataTableFormatter4GoogleTest formatter(*this);
    formatter.Format(prettyGherkin);
}
