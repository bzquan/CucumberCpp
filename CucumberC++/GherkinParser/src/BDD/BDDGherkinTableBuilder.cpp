#include "BDDUtil.h"
#include "TableRow.h"
#include "BDDGherkinTableBuilder.h"

using namespace std;
using namespace GherkinAst;
using namespace CucumberCpp;

wstring BDDGherkinTableBuilder::Build(DataTable& dataTable, int tableSeqNo, wstring indent)
{
    m_tableBuilder.clear();
    if (tableSeqNo >= 0)
    {
        m_tableSeqNo = std::to_wstring(tableSeqNo);
    }

    m_indent = indent;
    AppendGherkinTableDefinition();
    AppendGherkinTableBody(dataTable);

    return m_tableBuilder;
}

void BDDGherkinTableBuilder::AppendGherkinTableDefinition()
{
    m_tableBuilder
        .append(m_indent + L"GherkinTable table" + m_tableSeqNo + L";")
        .append(BDDUtil::NEW_LINE);
}

void BDDGherkinTableBuilder::AppendGherkinTableBody(DataTable& dataTable)
{
    AppendTableVariable();
    AppendGherkinTableHeader(dataTable.Rows()[0]);
    AppendGherkinTableRows(dataTable);
}

void BDDGherkinTableBuilder::AppendTableVariable()
{
    m_tableBuilder
        .append(m_indent + L"table" + m_tableSeqNo)
        .append(BDDUtil::NEW_LINE);
}

void BDDGherkinTableBuilder::AppendGherkinTableHeader(TableRow& row)
{
    m_tableBuilder
        .append(m_indent + L"//")
        .append(BDDUtil::INDENT_TRIPLE)
        .append(row.TrimmedFormattedText)
        .append(BDDUtil::NEW_LINE);
}

void BDDGherkinTableBuilder::AppendGherkinTableRows(DataTable& dataTable)
{
    vector<TableRow>& rows = dataTable.Rows();

    int ROW_COUNT = rows.size();
    for (int index = 1; index < ROW_COUNT; index++)
    {
        bool is_last_row = (index == ROW_COUNT - 1);
        m_tableBuilder
            .append(BDDUtil::INDENT)
            .append(m_indent + L".AddRow(L\"")
            .append(rows[index].TrimmedFormattedText)
            .append(EndingOfRow(is_last_row))
            .append(BDDUtil::NEW_LINE);
    }
}

wstring BDDGherkinTableBuilder::EndingOfRow(bool is_last_row)
{
    wstring ending_row(L"\")");
    if (is_last_row) ending_row.append(L";");

    return ending_row;
}
