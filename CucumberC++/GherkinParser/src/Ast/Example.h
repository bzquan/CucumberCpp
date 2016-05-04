#pragma once

#include <vector>
#include "IHasLocation.h"
#include "IHasDescription.h"
#include "IHasRows.h"
#include "DataTable.h"
#include "IVisit.h"

namespace GherkinAst
{
    class Example : public IHasLocation, public IHasDescription, public IVisit
    {
    public:
        Example(int lineNo, std::wstring* pTitle, GherkinAst::DataTable* pTable);
        ~Example();

        DataTable& ExampleTable() { return *m_pExampleTable; }
        void Visit(IVisitable& visitable) override;

    private:
        DataTable* m_pExampleTable;
    };
}
