#pragma once

#include <string>
#include "DataTable.h"

namespace GherkinAst
{
    class TableRow;
}

namespace CucumberCpp
{
    class BDDGherkinTableBuilder
    {
    public:
        std::wstring Build(GherkinAst::DataTable& dataTable, int tableSeqNo = -1, std::wstring indent = L"");
        static std::wstring BuildTableVariable(GherkinAst::DataTable& dataTable, std::wstring& tableVariableName, std::wstring indent = L"");

    private:
        static std::wstring AppendGherkinTableDefinition(std::wstring& tableVariableName, std::wstring indent);
        static std::wstring AppendGherkinTableBody(GherkinAst::DataTable& dataTable, std::wstring indent);
        static std::wstring EndingOfRow(bool is_not_last_row);
    };
}
