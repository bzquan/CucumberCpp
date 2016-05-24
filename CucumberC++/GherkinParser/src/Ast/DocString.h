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
#include "StepArgument.h"
#include "IHasLocation.h"

namespace GherkinAst
{
    class DocString : public StepArgument, public IHasLocation
    {
    public:
        DocString(int lineNo, std::wstring contentType, std::wstring content) :
            IHasLocation(lineNo),
            m_ContentType(contentType),
            m_Content(content)
        {
        }

        StepArgument* copy() const override
        {
            return new DocString(*this);
        }

        std::wstring& ContentType() { return m_ContentType; }
        std::wstring& Content() { return m_Content; }

        void Visit(IVisitable& visitable) override
        {
            visitable.Accept(*this);
        }

    private:
        std::wstring m_ContentType;
        std::wstring m_Content;
    };
}