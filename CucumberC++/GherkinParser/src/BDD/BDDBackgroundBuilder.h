#pragma once

#include <string>
#include "BDDUtil.h"
#include "BDDAbstrctScenarioBuilder.h"

namespace CucumberCpp
{
    class BDDBackgroundBuilder : public BDDAbstrctScenarioBuilder
    {
        std::wstring BuildScenarioImpl() override
        {
            std::wstring background;
            background
                .append(BDDUtil::INDENT + L"void FeatureBackground()\n")
                .append(BDDUtil::INDENT + L"{\n")
                .append(BuildSteps(BDDUtil::INDENT_DOUBLE))
                .append(BDDUtil::INDENT + L"}\n");

            return background;
        }
    };
}
