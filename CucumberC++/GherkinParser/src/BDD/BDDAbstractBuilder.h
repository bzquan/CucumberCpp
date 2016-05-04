#pragma once

#include <string>

namespace CucumberCpp
{
    class BDDAbstractBuilder
    {
    public:
        std::wstring FeatureTitle() { return m_FeatureTitle; }
        virtual void FeatureTitle(std::wstring title);

    private:
        std::wstring m_FeatureTitle;
    };
}
