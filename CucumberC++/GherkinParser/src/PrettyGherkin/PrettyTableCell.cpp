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
