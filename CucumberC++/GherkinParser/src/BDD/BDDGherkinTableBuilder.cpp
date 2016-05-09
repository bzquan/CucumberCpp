#include "BDDUtil.h"
#include "TableRow.h"
#include "BDDGherkinTableBuilder.h"

using namespace std;
using namespace GherkinAst;
using namespace CucumberCpp;

wstring BDDGherkinTableBuilder::Build(DataTable& dataTable, int tableSeqNo, wstring indent)
{
    std::wstring strTableSeqNo;
    if (tableSeqNo >= 0)
    {
        strTableSeqNo = std::to_wstring(tableSeqNo);
    }

    std::wstring tableVariableName = wstring(L"table") + strTableSeqNo;
    return BuildTableVariable(dataTable, tableVariableName, indent);
}

std::wstring BDDGherkinTableBuilder::BuildTableVariable(DataTable& dataTable, std::wstring& tableVariableName, std::wstring indent)
{
    std::wstring tableDefinition;
    tableDefinition
        .append(AppendGherkinTableDefinition(tableVariableName, indent))
        .append(AppendGherkinTableBody(dataTable, indent));

    return tableDefinition;
}

std::wstring BDDGherkinTableBuilder::AppendGherkinTableDefinition(std::wstring& tableVariableName, std::wstring indent)
{
    std::wstring tableDef;
    tableDef
        .append(indent + L"GherkinTable " + tableVariableName + L" = GherkinTable(")
        .append(BDDUtil::NEW_LINE);

    return tableDef;
}

std::wstring BDDGherkinTableBuilder::AppendGherkinTableBody(DataTable& dataTable, std::wstring indent)
{
    std::wstring tableBody;
    vector<TableRow>& rows = dataTable.Rows();

    int ROW_COUNT = rows.size();
    for (int index = 0; index < ROW_COUNT; index++)
    {
        bool is_not_last_row = (index < ROW_COUNT - 1);
        tableBody
            .append(BDDUtil::INDENT_DOUBLE)
            .append(indent + L"L\"")
            .append(rows[index].TrimmedFormattedText)
            .append(EndingOfRow(is_not_last_row));
    }

    return tableBody;
}

wstring BDDGherkinTableBuilder::EndingOfRow(bool is_not_last_row)
{
    wstring ending_row;
    if (is_not_last_row) ending_row.append(L"\\n");
    ending_row.append(L"\"");

    if (!is_not_last_row) ending_row.append(L");");

    ending_row.append(BDDUtil::NEW_LINE);

    return ending_row;
}
