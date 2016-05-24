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

#pragma once

#include <vector>
#include <string>
#include <vector>
#include "PrettyTableCell.h"
#include "PrettyTableRow.h"
#include "PrettyDataTable.h"

class PrettyGherkin;

class PrettyDataTableFormatter
{
private:
    std::vector<PrettyTableRow>& m_Rows;

public:
    PrettyDataTableFormatter(PrettyDataTable& context) : m_Rows(context.Rows())
    {
    }

    std::vector<PrettyTableRow>& Rows() { return m_Rows; }
    void Format(PrettyGherkin& prettyGherkin);

protected:
    virtual void FormatTableRow(PrettyTableRow& row, PrettyGherkin& prettyGherkin, std::vector<int>& preferedCellsWidth) = 0;
    virtual int GetCellValueWidth(PrettyTableCell& cell) = 0;

private:
    void FormatTableRows(PrettyGherkin& prettyGherkin, std::vector<int>& preferedCellsWidth);
    std::vector<int> CalculatePreferedCellsWidth();
    int CalculatePreferedCellWidth(int column);
};

class PrettyDataTableFormatter4GoogleTest : public PrettyDataTableFormatter
{
public:
    PrettyDataTableFormatter4GoogleTest(PrettyDataTable& context)
        : PrettyDataTableFormatter(context)
    {
    }

protected:
    void FormatTableRow(PrettyTableRow& tableRow, PrettyGherkin& prettyGherkin, std::vector<int>& preferedCellsWidth) override;
    int GetCellValueWidth(PrettyTableCell& cell) override { return cell.TrimmedValueWidth(); }
};

class PrettyDataTableFormatter4Feature : public PrettyDataTableFormatter
{
public:
    PrettyDataTableFormatter4Feature(PrettyDataTable& context)
        : PrettyDataTableFormatter(context)
    {
    }

protected:
    void FormatTableRow(PrettyTableRow& tableRow, PrettyGherkin& prettyGherkin, std::vector<int>& preferedCellsWidth) override;
    int GetCellValueWidth(PrettyTableCell& cell) override { return cell.OriginalValueWidth(); }
};
