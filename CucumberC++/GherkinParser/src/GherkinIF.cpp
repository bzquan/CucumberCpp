#include <sstream>
#include <exception>
#include "GherkinParser.h"
#include "PrettyGherkin.h"
#include "BDDExecSpecGenerator.h"
#include "StrUtility.h"
#include "BDDUtil.h"
#include "GherkinIF.h"

bool GherkinIF::prettyGherkin(std::wstring original, std::wstring& formattedGherkin)
{
    GherkinParser parser;
    return prettyGherkin(parser, original, formattedGherkin);
}

bool GherkinIF::prettyGherkin(std::wistream& is, std::wstring& formattedGherkin)
{
    GherkinParser parser;
    return prettyGherkin(parser, is, formattedGherkin);
}

bool GherkinIF::prettyGherkin(GherkinParser& parser, std::wstring original, std::wstring& formattedGherkin)
{
    trimGherkin(original);
    std::wistringstream is(original);
    bool result = prettyGherkin(parser, is, formattedGherkin);
    if (result)
    {
        appendCR_if_not_exist(formattedGherkin);
        // set formattedGherkin empty if the is no change
        if (original == formattedGherkin)
        {
            formattedGherkin = wstring();
        }
    }

    return result;
}

void GherkinIF::trimGherkin(std::wstring& original)
{
    StrUtility::Trim2(original);
    StrUtility::ReplaceAll(original, L"\r", L"");
    appendCR_if_not_exist(original);
}

void GherkinIF::appendCR_if_not_exist(std::wstring& str)
{
    const size_t len = str.length();
    if ((len > 0) && (str[len - 1] != CucumberCpp::BDDUtil::NEW_LINE_CHAR))
        str.append(CucumberCpp::BDDUtil::NEW_LINE); // append CR at the end if not exist
}

bool GherkinIF::prettyGherkin(GherkinParser& parser, std::wistream& is, std::wstring& formattedGherkin)
{
    if (parser.parse(is))
    {
        PrettyGherkin prettyGherkin(parser.Feature());
        formattedGherkin.append(prettyGherkin.Format());
        return true;
    }
    else
    {
        m_ErrorMsgs = parser.errorMsgs();
        return false;
    }
}

std::vector<int> GherkinIF::errorLines()
{
    std::vector<int> errorLines;
    for (GherkinErrorMsg& error : m_ErrorMsgs)
    {
        errorLines.push_back(error.lineNo());
    }
    return errorLines;
}

bool GherkinIF::GenExecSpec(std::wistream& is, ExecutableSpec& output)
{
    GherkinParser parser;
    if (!parser.parse(is))
    {
        m_ErrorMsgs = parser.errorMsgs();
        return false;
    }

    CucumberCpp::BDDExecSpecGenerator execSpecGenerator;
    execSpecGenerator.GenExecSpec(parser.Feature());

    output.FeatureImpl = execSpecGenerator.FeatureImpl();
    output.FeatureFileName = execSpecGenerator.FeatureFileName();

    output.StepDefsHeader = execSpecGenerator.StepDefsHeader();
    output.StepHeaderFileName = execSpecGenerator.StepHeaderFileName();

    output.StepDefsImpl = execSpecGenerator.StepDefsImpl();
    output.StepImplFileName = execSpecGenerator.StepImplFileName();

    output.StepModelTemplateHeader = execSpecGenerator.StepModelTemplateHeader();
    output.StepModelTemplateHeaderFileName = execSpecGenerator.StepModelTemplateHeaderFileName();

    output.StepModelTemplateImpl = execSpecGenerator.StepModelTemplateImpl();
    output.StepModelTemplateImplFileName = execSpecGenerator.StepModelTemplateImplFileName();

    return true;
}

bool GherkinIF::GenExecSpec(std::wstring original, std::wstring& formattedGherkin, std::wstring target_dir, ExecutableSpecFileNames& output)
{
    GherkinParser parser;

    bool res = prettyGherkin(parser, original, formattedGherkin);
    if (!res) return false;

    CucumberCpp::BDDExecSpecGenerator gen;
    gen.GenExecSpec(parser.Feature());

    try
    {
        // output files
        CucumberCpp::BDDUtil::WriteFileAsUTF8WithBOM(target_dir + gen.StepHeaderFileName(), gen.StepDefsHeader());
        CucumberCpp::BDDUtil::WriteFileAsUTF8WithBOM(target_dir + gen.StepImplFileName(), gen.StepDefsImpl());
        CucumberCpp::BDDUtil::WriteFileAsUTF8WithBOM(target_dir + gen.StepModelTemplateHeaderFileName(), gen.StepModelTemplateHeader());
        CucumberCpp::BDDUtil::WriteFileAsUTF8WithBOM(target_dir + gen.StepModelTemplateImplFileName(), gen.StepModelTemplateImpl());
        CucumberCpp::BDDUtil::WriteFileAsUTF8WithBOM(target_dir + gen.FeatureFileName(), gen.FeatureImpl());

        //////// set resulting filenames
        output.StepHeaderFileName = target_dir + gen.StepHeaderFileName();
        output.StepImplFileName = target_dir + gen.StepImplFileName();
        output.StepModelTemplateHeaderFileName = target_dir + gen.StepModelTemplateHeaderFileName();
        output.StepModelTemplateImplFileName = target_dir + gen.StepModelTemplateImplFileName();
        output.FeatureFileName = target_dir + gen.FeatureFileName();

        return true;
    }
    catch (CucumberCpp::BadFileException& ex)
    {
        m_ErrorMsgs.push_back(GherkinErrorMsg(0, ex.ErrorMsg()));
        return false;
    }
}

