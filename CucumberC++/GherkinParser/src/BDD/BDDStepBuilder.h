/* The MIT License (MIT)
 * 
 * Copyright (c) 2016 Bingzhe Quan
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <vector>
#include <string>
#include "Step.h"
#include "DataTable.h"
#include "DocString.h"
#include "BDDStepArg.h"

namespace CucumberCpp
{
    class BDDStepArg;

    class BDDStepBuilder
    {
    public:
        BDDStepBuilder() = default;
        BDDStepBuilder(GherkinAst::Step& step, std::wstring stepDefClassName);

        std::wstring StepKeyword() { return m_StepKeyword; }
        std::wstring StepText() { return m_StepText; }

        void TableSeqNo(int no) { m_TableSeqNo =no; }
        GherkinAst::DataTable* TableArg() { return m_pTableArg; }
        void TableArg(GherkinAst::DataTable* pDataTable);

        GherkinAst::DocString* DocStringArg() { return m_pDocStringArg; }
        void DocStringArg(GherkinAst::DocString* pDocString);
        void DocStringSeqNo(int no) { m_DocStringSeqNo = no; }

        void AddStepComments(std::wstring newComment);
        std::vector<std::wstring>& StepComments() { return m_StepComments; }

        std::wstring BuildStepHeader();
        std::wstring BuildStepImp();
        std::wstring BuildStepBind();
        std::wstring BuildStepForScenario(const std::wstring& indent);
        bool HasAttribute(std::wstring attr);

    private:
        std::wstring MakeTypeTemplateArg();
        bool HasDocStringArg() { return m_pDocStringArg != nullptr; }
        bool HasTypeTemplateArg();
        void BuildTableArg(const std::wstring& indent, std::wstring& stepOfScenario);
        void BuildDocStringArg(const std::wstring& indent, std::wstring& stepOfScenario);
        std::wstring BuildDocString(const std::wstring& indent);
        void BuildStepStatement(const std::wstring& indent, std::wstring& stepOfScenario);
        std::wstring MakeArgPalceHoder();
        std::wstring MakeStepRegex();
        std::wstring BuildStepFormalArg(bool useTypeNameOnly);
        std::wstring BuildStepRealArg();
        std::wstring DocStringRealArgName();
        void MakeAdjustedArgList();
        void MakeStepFunction();
        void MakeStepFunctionName();
        void MakeStepArgList();
        std::wstring PreEscapeSpecialCharacters(const std::wstring& text);
        std::wstring PostEscapeSpecialCharacters(const std::wstring& text);

    private:
        std::vector<BDDStepArg> m_OrigArgList;
        std::vector<BDDStepArg> m_AdjustdArgList;
        std::vector<std::wstring> m_StepComments;
        std::wstring m_StepText;
        std::wstring m_StepKeyword;
        int m_TableSeqNo     = 0;
        int m_DocStringSeqNo = 0;
        GherkinAst::DataTable* m_pTableArg      = nullptr;
        GherkinAst::DocString* m_pDocStringArg  = nullptr;
        std::wstring m_StepDefClassName;
        std::wstring m_StepFunctionName;
    };
}
