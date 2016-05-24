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
#include "TableCell.h"
#include "Location.h"

class PrettyTableCell
{
public:
    PrettyTableCell(GherkinAst::TableCell& cell) : m_Cell(cell)
    {
        m_TrimmedValueWidth = GetCellWidth(cell.TrimmedValue());
        m_OriginalValueWidth = GetCellWidth(cell.Value());
    }

    std::wstring TrimmedValue(int preferedWidth);
    int TrimmedValueWidth() { return m_TrimmedValueWidth; }

    std::wstring OriginalValue(int preferedWidth);
    int OriginalValueWidth() { return m_OriginalValueWidth; }

private:
    static int GetCellWidth(std::wstring& value);

private:
    GherkinAst::TableCell& m_Cell;
    int m_TrimmedValueWidth  = 0;
    int m_OriginalValueWidth = 0;
};

