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

#include <string>
#include <vector>

class PrettyTableRow;
class PrettyTableCell;

class PrettyTableRowFormatter
{
public:
    PrettyTableRowFormatter(PrettyTableRow& context) : m_Context(context){}
    virtual ~PrettyTableRowFormatter(){}

    std::wstring Format(std::vector<int> preferedCellsWidth);

private:
    std::wstring FormatRow(std::vector<int> preferedCellsWidth);

protected:
    virtual std::wstring GetIndent() = 0;
    virtual std::wstring GetCellValue(PrettyTableCell& cell, int preferedWidth) = 0;

private:
    PrettyTableRow& m_Context;
};

class PrettyTableRowFormatter4GoogleTest : public PrettyTableRowFormatter
{
public:
    PrettyTableRowFormatter4GoogleTest(PrettyTableRow& context)
        : PrettyTableRowFormatter(context)
    {
    }

protected:
    std::wstring GetIndent() override { return L""; }
    std::wstring GetCellValue(PrettyTableCell& cell, int preferedWidth) override;
};

class PrettyTableRowFormatter4Feature : public PrettyTableRowFormatter
{
public:
    PrettyTableRowFormatter4Feature(PrettyTableRow& context)
        : PrettyTableRowFormatter(context)
    {
    }

protected:
    std::wstring GetIndent() override;
    std::wstring GetCellValue(PrettyTableCell& cell, int preferedWidth) override;
};
