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

#include <string>
#include <algorithm>    // std::max
#include "PrettyTableCell.h"

using namespace std;
using namespace GherkinAst;

wstring PrettyTableCell::TrimmedValue(int preferedWidth)
{
    wstring trmmedCell{ m_Cell.TrimmedValue() };

    int noOfSpaceToPad = std::max(preferedWidth - m_TrimmedValueWidth, 0);
    trmmedCell.append(noOfSpaceToPad, L' ');

    return trmmedCell;
}

wstring PrettyTableCell::OriginalValue(int preferedWidth)
{
    wstring trmmedCell{ m_Cell.Value() };

    int noOfSpaceToPad = std::max(preferedWidth - m_OriginalValueWidth, 0);
    trmmedCell.append(noOfSpaceToPad, L' ');

    return trmmedCell;
}

int PrettyTableCell::GetCellWidth(wstring& value)
{
    const int ONE_CHARACTER = 1;
    const int TWO_CHARACTER = 2;
    int width = 0;
    for (wchar_t ch : value)
    {
        bool isASCII = (ch <= L'\u007F');
        width += isASCII ? ONE_CHARACTER : TWO_CHARACTER;
    }

    return width;
}
