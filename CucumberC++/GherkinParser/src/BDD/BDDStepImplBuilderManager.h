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

#include <string>
#include "BDDAbstractBuilder.h"
#include "BDDStepBuilder.h"

namespace GherkinAst
{
    class Step;
    class DocString;
    class DataTable;
}

namespace CucumberCpp
{
    class BDDStepBuilder;
    class BDDStepImplHeaderBuilder;
    class BDDStepImplCppBuilder;
    class BDDStepModelTemplateBuilder;

    class BDDStepImplBuilderManager : public BDDAbstractBuilder
    {
    public:
        BDDStepImplBuilderManager() = default;
        void FeatureTitle(std::wstring title) override;
        BDDStepBuilder* NewStep(GherkinAst::Step& step);
        void AddArg(GherkinAst::DataTable* pDataTable);
        void AddArg(GherkinAst::DocString* pDocString);
        std::wstring BuildStepImplHeader();
        std::wstring BuildStepImplCpp();
        std::wstring BuildTestModelHeader();
        std::wstring BuildTestModelImplementation();

    private:
        BDDStepBuilder* m_pCurrentStep = nullptr;
    };
}
