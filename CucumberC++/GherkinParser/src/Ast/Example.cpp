#include "DataTable.h"
#include "IVisitable.h"
#include "Example.h"

using namespace GherkinAst;

Example::Example(int lineNo, std::wstring* pTitle, GherkinAst::DataTable* pTable) :
    IHasLocation(lineNo),
    IHasDescription(L"Examples", pTitle, nullptr),
    m_pExampleTable(pTable)
{
}

Example::~Example()
{
    delete m_pExampleTable;
}

void Example::Visit(IVisitable& visitable)
{
    visitable.Accept(*this);
}
