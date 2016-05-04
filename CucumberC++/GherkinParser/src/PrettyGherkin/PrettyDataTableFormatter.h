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
