#include "Definitions.h"
#include "PrettyTableRow.h"
#include "PrettyTableCell.h"
#include "PrettyGherkinDef.h"
#include "PrettyTableRowFormatter.h"

using namespace std;
using namespace GherkinAst;

wstring PrettyTableRowFormatter::Format(std::vector<int> preferedCellsWidth)
{
    wstring formattingText{ GetIndent() };
    formattingText.append(FormatRow(preferedCellsWidth));

    return formattingText;
}

wstring PrettyTableRowFormatter::FormatRow(std::vector<int> preferedCellsWidth)
{
    wstring rowBuilder;
    int index = 0;
    for (PrettyTableCell& tableCell : m_Context.Cells())
    {
        rowBuilder
            .append(CELLL_SEPARATOR)
            .append(GetCellValue(tableCell, preferedCellsWidth[index]));
        index++;
    }
    rowBuilder.append(CELLL_SEPARATOR);

    return rowBuilder;
}

wstring PrettyTableRowFormatter4GoogleTest::GetCellValue(PrettyTableCell& cell, int preferedWidth)
{
    return cell.TrimmedValue(preferedWidth);
}

wstring PrettyTableRowFormatter4Feature::GetIndent()
{
    return STEPARG_INDENT;
}

wstring PrettyTableRowFormatter4Feature::GetCellValue(PrettyTableCell& cell, int preferedWidth)
{
    return cell.OriginalValue(preferedWidth);
}
