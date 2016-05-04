#include "BDDUtil.h"
#include "BDDAbstractBuilder.h"

using namespace CucumberCpp;

void BDDAbstractBuilder::FeatureTitle(std::wstring title)
{
    m_FeatureTitle = BDDUtil::MakeIdentifier(title);
}
