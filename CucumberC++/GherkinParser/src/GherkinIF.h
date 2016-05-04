#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "GherkinErrorMsg.h"

struct ExecutableSpecFileNames
{
    std::wstring StepHeaderFileName;
    std::wstring StepImplFileName;
    std::wstring StepModelTemplateHeaderFileName;
    std::wstring StepModelTemplateImplFileName;
    std::wstring FeatureFileName;
};

struct ExecutableSpec : public ExecutableSpecFileNames
{
    std::wstring StepDefsHeader;
    std::wstring StepDefsImpl;
    std::wstring StepModelTemplateHeader;
    std::wstring StepModelTemplateImpl;
    std::wstring FeatureImpl;
};

class GherkinParser;

class GherkinIF
{
public:
    GherkinIF() = default;

    // formattedGherkin will be set empty if no changes from original
    bool prettyGherkin(std::wstring original, std::wstring& formattedGherkin);
    // formattedGherkin will be set if no error
    bool prettyGherkin(std::wistream& is, std::wstring& formattedGherkin);
    std::vector<GherkinErrorMsg> errorMsgs() { return m_ErrorMsgs; }
    std::vector<int> errorLines();

    bool GenExecSpec(std::wistream& is, ExecutableSpec& output);
    bool GenExecSpec(std::wstring original, std::wstring& formattedGherkin, std::wstring target_dir, ExecutableSpecFileNames& output);

private:
    bool prettyGherkin(GherkinParser& parser, std::wstring original, std::wstring& formattedGherkin);
    bool prettyGherkin(GherkinParser& parser, std::wistream& is, std::wstring& formattedGherkin);
    void trimGherkin(std::wstring& original);
    void appendCR_if_not_exist(std::wstring& str);

private:
    std::vector<GherkinErrorMsg> m_ErrorMsgs;
};
