#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "AbstractTestModel.h"

class Pretty_Gherkin_TestModel : public AbstractTestModel
{
public:
    void SetUp();
    void TearDown();
    void VerifyExpectations() override;

    void GivenGherkin(wstring& docStr);
    void MakePrettyGherkin();
    void ExpectNewGUIDCreated();
    void ExpectFormattedGherkin(wstring& docStr);

private:
    wstring TakeoutLeadingDelimiter(wstring& docStr);
    void RemoveAllGUIDsFromFormattedGherkin();

private:
    wstring m_OriginGherkin;
    wstring m_FormattedGherkin;
};
