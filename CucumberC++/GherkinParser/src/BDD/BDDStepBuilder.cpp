#include <algorithm>
#include <regex>
#include "BDDUtil.h"
#include "StrUtility.h"
#include "BDDGherkinTableBuilder.h"
#include "BDDStepBuilder.h"

using namespace std;
using namespace GherkinAst;
using namespace CucumberCpp;

namespace
{
    wstring paramIndicator{ L"QQQQQQ" };
}

BDDStepBuilder::BDDStepBuilder(Step& step, wstring stepDefClassName) :
    m_pTableArg(nullptr),
    m_TableSeqNo(0),
    m_pDocStringArg(nullptr),
    m_DocStringSeqNo(0)
{
    m_StepKeyword = BDDUtil::RemoveAllWhiteSpaces(step.Keyword());
    m_StepText = step.Text();
    m_StepDefClassName = stepDefClassName;
}

void BDDStepBuilder::TableArg(GherkinAst::DataTable* pDataTable)
{
    m_pTableArg = pDataTable;
}

void BDDStepBuilder::DocStringArg(GherkinAst::DocString* pDocString)
{
    m_pDocStringArg = pDocString;
}

void BDDStepBuilder::AddStepComments(wstring newComment)
{
    if (find(m_StepComments.begin(), m_StepComments.end(), newComment) == m_StepComments.end())
    {
        m_StepComments.push_back(newComment);
    }
}

wstring BDDStepBuilder::BuildStepHeader()
{
    MakeStepFunction();
    wstring stepHeader;
    if (!BDDUtil::supportUnicode())
    {
        stepHeader
           .append(BDDUtil::INDENT_DOUBLE + L"// " + m_StepFunctionName)
           .append(BDDUtil::NEW_LINE);
    }
    stepHeader
        .append(BDDUtil::INDENT + L"void " + BDDUtil::to_ident(m_StepFunctionName) + L"(" + BuildStepFormalArg(true) + L");");

    return stepHeader;
}

wstring BDDStepBuilder::BuildStepImp()
{
    MakeStepFunction();
    wstring stepImp;
    if (!BDDUtil::supportUnicode())
    {
        stepImp
            .append(wstring(L"//-- ") + m_StepDefClassName + L"::" + m_StepFunctionName + L"(" + BuildStepFormalArg(false) + L")")
            .append(BDDUtil::NEW_LINE);
    }

    stepImp
        .append(wstring(L"void ") + BDDUtil::to_ident(m_StepDefClassName) + L"::" + BDDUtil::to_ident(m_StepFunctionName) + L"(" + BuildStepFormalArg(false) + L")")
        .append(BDDUtil::NEW_LINE)
        .append(L"{")
        .append(BDDUtil::NEW_LINE)
        .append(BDDUtil::INDENT + L"PendingStep(L\"" + m_StepFunctionName + L"\");")
        .append(BDDUtil::NEW_LINE)
        .append(L"}");

    return stepImp;
}

wstring BDDStepBuilder::BuildStepBind()
{
    MakeStepFunction();
    wstring bind;
    bind
        .append(BDDUtil::INDENT_DOUBLE)
        .append(MakeTypeTemplateArg())
        .append(L"(")
        .append(BDDUtil::NEW_LINE)
        .append(BDDUtil::INDENT_TRIPLE + L"L\"")
        .append(MakeStepRegex())
        .append(L"\",")
        .append(BDDUtil::NEW_LINE)
        .append(BDDUtil::INDENT_TRIPLE)
        .append(L"function < void(")
        .append(BuildStepFormalArg(true))
        .append(L") >")
        .append(BDDUtil::NEW_LINE)
        .append(BDDUtil::INDENT_TRIPLE)
        .append(L"(bind(&")
        .append(BDDUtil::to_ident(m_StepDefClassName) + L"::" + BDDUtil::to_ident(m_StepFunctionName))
        .append(L", this")
        .append(MakeArgPalceHoder())
        .append(L")));");

    return bind;
}

wstring BDDStepBuilder::MakeTypeTemplateArg()
{
    wstring typeTemplateArg = HasDocStringArg() ? L"StepDocString" : L"Step";
    if (HasTypeTemplateArg())
    {
        typeTemplateArg.append(L"<");
        wstring separator;
        for (BDDStepArg& stepArg : m_OrigArgList)
        {
            switch (stepArg.ArgType())
            {
            case BDDStepArgType::FloatArg:
            case BDDStepArgType::StringArg:
                typeTemplateArg.append(separator);
                typeTemplateArg.append(stepArg.StepParamTypeName());
                separator = L", ";
                break;
            default:
                // do nothing
                break;
            }
        }
        typeTemplateArg.append(L">");
    }

    return typeTemplateArg;
}

bool BDDStepBuilder::HasTypeTemplateArg()
{
    for (BDDStepArg& stepArg : m_OrigArgList)
    {
        switch (stepArg.ArgType())
        {
        case BDDStepArgType::FloatArg:
        case BDDStepArgType::StringArg:
            return true;
        default:
            // do nothing
            break;
        }
    }

    return false;
}

bool BDDStepBuilder::HasAttribute(std::wstring attr)
{
    std::size_t found = m_StepText.find(attr);
    return (found!=std::wstring::npos);
}

wstring BDDStepBuilder::BuildStepForScenario(const wstring& indent)
{
    MakeStepFunction();

    wstring stepOfScenario;
    BuildTableArg(indent, stepOfScenario);
    BuildDocStringArg(indent, stepOfScenario);
    BuildStepStatement(indent, stepOfScenario);

    return stepOfScenario;
}

void BDDStepBuilder::BuildTableArg(const wstring& indent, wstring& stepOfScenario)
{
    if (m_pTableArg != nullptr)
    {
        BDDGherkinTableBuilder tableBuilder;
        stepOfScenario
            .append(BDDUtil::NEW_LINE)
            .append(tableBuilder.Build(*m_pTableArg, m_TableSeqNo, indent));
    }
}

void BDDStepBuilder::BuildDocStringArg(const wstring& indent, wstring& stepOfScenario)
{
    if (m_pDocStringArg != nullptr)
    {
        wstring varDef = indent + wstring(L"std::wstring ") + DocStringRealArgName() + L" = ";
        wstring indentAfterVar;
        indentAfterVar.append(varDef.length(), L' ');

        stepOfScenario
            .append(BDDUtil::NEW_LINE)
            .append(varDef)
            .append(BuildDocString(indentAfterVar));
    }
}

wstring BDDStepBuilder::BuildDocString(const wstring& indent)
{
    wstring docString;
    wstring docStringContent = m_pDocStringArg->Content();
    StrUtility::ReplaceAll(docStringContent, L"\"", L"\\\"");

    vector<wstring> docStringLines = StrUtility::Split(docStringContent, L'\n');
    for (size_t i = 0; i < docStringLines.size(); i++)
    {
        if (i > 0) docString.append(indent);

        docString.append(wstring(L"L\"") + docStringLines[i]);
        if (i < docStringLines.size() - 1)
        {
            docString
                .append(L"\\n\"")
                .append(BDDUtil::NEW_LINE);
        }
    }
    docString
      .append(L"\";")
      .append(BDDUtil::NEW_LINE);

    return docString;
}

void BDDStepBuilder::BuildStepStatement(const wstring& indent, wstring& stepOfScenario)
{
    wstring stepTextByEscapingQuotaion = m_StepText;
    StrUtility::ReplaceAll(stepTextByEscapingQuotaion, L"\"", L"\\\"");

    stepOfScenario
        .append(indent + m_StepKeyword + L"(L\"" + stepTextByEscapingQuotaion + L"\"")
        .append(BuildStepRealArg())
        .append(L");");
}

wstring BDDStepBuilder::MakeArgPalceHoder()
{
    int index = 1;
    wstring placeHolder;
    for (size_t i = 0; i < m_AdjustdArgList.size(); i++)
    {
        placeHolder
            .append(wstring(L", _") + std::to_wstring(index));
        index++;
    }

    return placeHolder;
}

wstring BDDStepBuilder::MakeStepRegex()
{
    wstring preEscapedText = PreEscapeSpecialCharacters(m_StepText);
    wregex  stepRegex{ BDDUtil::StepPattern };
    wstring stepRegexText = std::regex_replace(preEscapedText, stepRegex, paramIndicator);
    for (BDDStepArg& stepArg : m_OrigArgList)
    {
        switch (stepArg.ArgType())
        {
        case BDDStepArgType::TableColumnArg:
        case BDDStepArgType::FloatArg:
        case BDDStepArgType::StringArg:
            StrUtility::ReplaceFirst(stepRegexText, paramIndicator, stepArg.RegexPattern());
            break;
        default:
            // do nothing
            break;
        }
    }

    return PostEscapeSpecialCharacters(stepRegexText);
}

wstring BDDStepBuilder::BuildStepFormalArg(bool useTypeNameOnly)
{
    wstring args;
    for (BDDStepArg& stepArg : m_AdjustdArgList)
    {
        wstring separator = (args.length() > 0) ? L", " : L"";
        if (useTypeNameOnly)
            args.append(separator + stepArg.StepParamTypeName());
        else
            args.append(separator + stepArg.StepParam());
    }

    return args;
}

wstring BDDStepBuilder::BuildStepRealArg()
{
    wstring args;
    for (BDDStepArg& stepArg : m_AdjustdArgList)
    {
        switch (stepArg.ArgType())
        {
        case BDDStepArgType::TableArg:
            args.append(wstring(L", table") + std::to_wstring(m_TableSeqNo));
            break;
        case BDDStepArgType::TableColumnArg:
            args.append(L", param");
            break;
        case BDDStepArgType::DocStringArg:
            args.append(wstring(L", ") + DocStringRealArgName());
            break;
        default:
            // do nothing
            break;
        }
    }

    return args;
}

wstring BDDStepBuilder::DocStringRealArgName()
{
    return wstring(L"docString") + std::to_wstring(m_DocStringSeqNo);
}

void BDDStepBuilder::MakeAdjustedArgList()
{
    m_AdjustdArgList.clear();
    if (m_pTableArg != nullptr)
    {
        m_AdjustdArgList.push_back(BDDStepArg(BDDStepArg::TableArg));
    }

    auto isTableColumnArg = [](BDDStepArg& stepArg) { return stepArg.ArgType() == BDDStepArgType::TableColumnArg; };
    vector<BDDStepArg>::iterator it = std::find_if(m_OrigArgList.begin(), m_OrigArgList.end(), isTableColumnArg);
    if (it != m_OrigArgList.end())
    {
        m_AdjustdArgList.push_back(*it);
    }

    for (BDDStepArg& stepArg : m_OrigArgList)
    {
        if ((stepArg.ArgType() != BDDStepArgType::TableArg) && (stepArg.ArgType() != BDDStepArgType::TableColumnArg))
        {
            m_AdjustdArgList.push_back(stepArg);
        }
    }
}

void BDDStepBuilder::MakeStepFunction()
{
    if (m_StepFunctionName.length() == 0)
    {
        MakeStepArgList();
        MakeAdjustedArgList();
        MakeStepFunctionName();
    }
}

void BDDStepBuilder::MakeStepFunctionName()
{
    wregex  stepRegex{ BDDUtil::StepPattern };
    wstring stepRegexText = std::regex_replace(m_StepText, stepRegex, paramIndicator);
    for (BDDStepArg& stepArg : m_OrigArgList)
    {
        StrUtility::ReplaceFirst(stepRegexText, paramIndicator, stepArg.StepFunctionPlaceHolder());
    }

    m_StepFunctionName = BDDUtil::MakeIdentifier(stepRegexText);
}

void BDDStepBuilder::MakeStepArgList()
{
    if (m_OrigArgList.size() > 0) return;  // step argument list has been created


    if (m_pDocStringArg != nullptr)
    {
        m_OrigArgList.push_back(BDDStepArg(BDDStepArg::DocStringArg));
    }

    int numArg = 1;
    int strArg = 1;

    wregex  stepRegex{ BDDUtil::StepPattern };
    wsmatch match;
    wstring text(m_StepText);
    while (std::regex_search(text, match, stepRegex)) {
        BDDStepArg arg(match[0]);
        if (arg.ArgType() == BDDStepArgType::FloatArg)
        {
            arg.ArgIndex = numArg++;
        }
        else if (arg.ArgType() == BDDStepArgType::StringArg)
        {
            arg.ArgIndex = strArg++;
        }
        m_OrigArgList.push_back(arg);

        text = match.suffix().str();
    }
}

wstring BDDStepBuilder::PreEscapeSpecialCharacters(const wstring& text)
{
    wstring result_text(text);
    StrUtility::ReplaceAll(result_text, L"{", L"\\{");
    StrUtility::ReplaceAll(result_text, L"}", L"\\}");
    StrUtility::ReplaceAll(result_text, L"(", L"\\(");
    StrUtility::ReplaceAll(result_text, L")", L"\\)");
    StrUtility::ReplaceAll(result_text, L"[", L"\\[");
    StrUtility::ReplaceAll(result_text, L"]", L"\\]");

    return result_text;
}

wstring BDDStepBuilder::PostEscapeSpecialCharacters(const wstring& text)
{
    wstring result_text(text);
    StrUtility::ReplaceAll(result_text, L"\\{", L"\\\\{");
    StrUtility::ReplaceAll(result_text, L"\\}", L"\\\\}");
    StrUtility::ReplaceAll(result_text, L"\\(", L"\\\\(");
    StrUtility::ReplaceAll(result_text, L"\\)", L"\\\\)");
    StrUtility::ReplaceAll(result_text, L"\\[", L"\\\\[");
    StrUtility::ReplaceAll(result_text, L"\\]", L"\\\\]");

    return result_text;
}
