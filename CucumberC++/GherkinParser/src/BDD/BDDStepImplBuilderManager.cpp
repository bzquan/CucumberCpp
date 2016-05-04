#include "BDDStepImplBuilderContext.h"
#include "BDDStepImplHeaderBuilder.h"
#include "BDDStepImplCppBuilder.h"
#include "BDDTestModelBuilder.h"
#include "BDDStepImplBuilderManager.h"

using namespace std;
using namespace GherkinAst;
using namespace CucumberCpp;

void BDDStepImplBuilderManager::FeatureTitle(wstring title)
{
    BDDAbstractBuilder::FeatureTitle(title);
    BDDStepImplBuilderContext::FeatureTitle(title);
}

BDDStepBuilder* BDDStepImplBuilderManager::NewStep(Step& step)
{
    m_pCurrentStep = BDDStepImplBuilderContext::CreateNewStepBuilder(step);
    return m_pCurrentStep;
}

void BDDStepImplBuilderManager::AddArg(DataTable* pDdataTable)
{
    if (m_pCurrentStep != nullptr)
    {
        m_pCurrentStep->TableArg(pDdataTable);
    }
}

void BDDStepImplBuilderManager::AddArg(DocString* pDocString)
{
    if (m_pCurrentStep != nullptr)
    {
        m_pCurrentStep->DocStringArg(pDocString);
    }
}

wstring BDDStepImplBuilderManager::BuildStepImplHeader()
{
    return BDDStepImplHeaderBuilder::BuildStepImplHeader();
}

wstring BDDStepImplBuilderManager::BuildStepImplCpp()
{
    return BDDStepImplCppBuilder::BuildStepImplCpp();
}

wstring BDDStepImplBuilderManager::BuildTestModelHeader()
{
    return BDDStepModelTemplateBuilder::BuildTestModelHeader();
}

wstring BDDStepImplBuilderManager::BuildTestModelImplementation()
{
    return BDDStepModelTemplateBuilder::BuildTestModelImplementation();
}
