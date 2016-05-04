#include "Feature.h"
#include "BDDStepImplBuilderContext.h"
#include "BDDExecSpecGenerator.h"

using namespace std;
using namespace GherkinAst;
using namespace CucumberCpp;

BDDExecSpecGenerator::BDDExecSpecGenerator()
{
    m_FeatureBuilder = std::make_unique<BDDFeatureBuilder>();
    m_StepImplBuilderManager = std::make_unique<BDDStepImplBuilderManager>();
    m_BDDASTVisitor = std::make_unique<BDDASTVisitor>(*m_FeatureBuilder.get(), *m_StepImplBuilderManager.get());
}

void BDDExecSpecGenerator::GenExecSpec(Feature* pFeature)
{
    BDDStepImplBuilderContext::Clear();
    if ((pFeature != nullptr) && (m_BDDASTVisitor != nullptr))
    {
        BDDASTVisitor* pVisitor = m_BDDASTVisitor.get();
        pFeature->Visit(*pVisitor);
    }
}

wstring BDDExecSpecGenerator::StepHeaderFileName()
{
    return BDDStepImplBuilderContext::StepHeaderFileName();
}

wstring BDDExecSpecGenerator::StepImplFileName()
{
    return BDDStepImplBuilderContext::StepImplementationFileName();
}

wstring BDDExecSpecGenerator::StepModelTemplateHeaderFileName()
{
    return BDDStepImplBuilderContext::StepModelTemplateHeaderFileName();
}

wstring BDDExecSpecGenerator::StepModelTemplateImplFileName()
{
    return BDDStepImplBuilderContext::StepModelTemplateImplFileName();
}

wstring BDDExecSpecGenerator::FeatureFileName()
{
    return m_FeatureBuilder->FeatureFileName();
}

wstring BDDExecSpecGenerator::StepDefsHeader()
{
    return m_StepImplBuilderManager->BuildStepImplHeader();
}

wstring BDDExecSpecGenerator::StepDefsImpl()
{
    return m_StepImplBuilderManager->BuildStepImplCpp();
}

wstring BDDExecSpecGenerator::StepModelTemplateHeader()
{
    return m_StepImplBuilderManager->BuildTestModelHeader();
}
wstring BDDExecSpecGenerator::StepModelTemplateImpl()
{
    return m_StepImplBuilderManager->BuildTestModelImplementation();
}

wstring BDDExecSpecGenerator::FeatureImpl()
{
    m_FeatureBuilder->StepHeaderFileName(StepHeaderFileName());
    m_FeatureBuilder->StepClassName(BDDStepImplBuilderContext::StepImplClassName());
    return m_FeatureBuilder->Build();
}
