﻿/* The MIT License (MIT)
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

namespace CucumberCpp
{
    class BDDStepBuilder;

    class BDDStepImplBuilderContext
    {
    public:
        static void Clear();
        static std::vector<BDDStepBuilder*>& StepBuilders();
        static std::wstring FeatureTitle();
        static void FeatureTitle(std::wstring title);

        static std::wstring StepImplClassName();
        static std::wstring StepHeaderFileName();
        static std::wstring StepImplementationFileName();
        static std::wstring StepModelTemplateHeaderFileName();
        static std::wstring StepModelTemplateImplFileName();
        static std::wstring FeatureTestModelName();
        static BDDStepBuilder* CreateNewStepBuilder(GherkinAst::Step& step);
        static std::vector<BDDStepBuilder*>& NonDuplicateStepBuilders();

    private:
        static void MakeNonDuplicateStepBuilders();
        static BDDStepBuilder* GetSameStepBuilder(BDDStepBuilder* pNewStepBuilder);
        static std::wstring ToIdentifier(const std::wstring& str);

    private:
        static std::vector<BDDStepBuilder*> s_StepBuilderList;
        static std::vector<BDDStepBuilder*> s_NonDuplicateStepBuilderList;
        static std::wstring s_FeatureTitle;
    };
}
