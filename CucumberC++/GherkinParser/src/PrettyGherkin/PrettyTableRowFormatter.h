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
