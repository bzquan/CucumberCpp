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
#include <memory>
#include "BDDFeatureBuilder.h"
#include "BDDStepImplBuilderManager.h"
#include "BDDASTVisitor.h"

namespace GherkinAst
{
    class Feature;
}

namespace CucumberCpp
{
    class BDDExecSpecGenerator
    {
    public:
        BDDExecSpecGenerator();
        void GenExecSpec(GherkinAst::Feature* pFeature);
        std::wstring StepHeaderFileName();
        std::wstring StepImplFileName();
        std::wstring StepModelTemplateHeaderFileName();
        std::wstring StepModelTemplateImplFileName();
        std::wstring FeatureFileName();
        std::wstring StepDefsHeader();
        std::wstring StepDefsImpl();
        std::wstring StepModelTemplateHeader();
        std::wstring StepModelTemplateImpl();
        std::wstring FeatureImpl();

    private:
        std::unique_ptr<BDDASTVisitor> m_BDDASTVisitor;
        std::unique_ptr<BDDFeatureBuilder> m_FeatureBuilder;
        std::unique_ptr<BDDStepImplBuilderManager> m_StepImplBuilderManager;
    };
}
