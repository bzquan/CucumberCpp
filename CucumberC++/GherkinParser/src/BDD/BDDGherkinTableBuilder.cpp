/* The MIT License (MIT)
 * 
 * Copyright (c) 2016 Bingzhe Quan
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
        .append(indent + L"GherkinTable " + tableVariableName + L"(")
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
