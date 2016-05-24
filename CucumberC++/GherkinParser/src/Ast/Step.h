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
#include "Definitions.h"
#include "StepArgument.h"
#include "IHasLocation.h"
#include "IVisit.h"

namespace GherkinAst
{
    class Step : public IHasLocation, public IVisit
    {
    public:
        Step(StepKind stepKind, int lineNo, std::wstring* pText, GherkinAst::StepArgument* pStepArgument);
        ~Step();

        Step(const Step& other);
        Step& operator=(const Step& other);

        std::wstring Keyword();
        std::wstring& Text() { return m_Text; }

        GherkinAst::StepArgument* StepArgument() const
        {
            return m_pStepArgument;
        }

        bool IsAndOrButKeyWord();
        bool HasColumnIndexParam();
        void Visit(IVisitable& visitable) override;

    private:
        StepKind      m_Keyword;
        std::wstring  m_Text;
        GherkinAst::StepArgument*  m_pStepArgument;
    };
}
