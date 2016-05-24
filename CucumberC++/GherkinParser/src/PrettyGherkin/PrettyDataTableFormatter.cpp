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
