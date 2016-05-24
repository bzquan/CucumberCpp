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

#include "GherkinTable.h"
#include "FeatureStepModel.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace ::testing;

namespace bdd
{
	class FeatureTestModel : public testing::Test
	{
	public:
		void Given(wstring text) { DoStep(text); }
		void Given(wstring text, wstring docStringArg) { DoStep(text, docStringArg); }
		void Given(wstring text, GherkinTable tableArg) { DoStep(text, tableArg); }
		void Given(wstring text, GherkinRow tableRowArg) { DoStep(text, tableRowArg); }

		void When(wstring text) { DoStep(text); }
		void When(wstring text, wstring docStringArg) { DoStep(text, docStringArg); }
		void When(wstring text, GherkinTable tableArg) { DoStep(text, tableArg); }
		void When(wstring text, GherkinRow tableRowArg) { DoStep(text, tableRowArg); }

		void Then(wstring text) { DoStep(text); }
		void Then(wstring text, wstring docStringArg) { DoStep(text, docStringArg); }
		void Then(wstring text, GherkinTable tableArg) { DoStep(text, tableArg); }
		void Then(wstring text, GherkinRow tableRowArg) { DoStep(text, tableRowArg); }

		void And(wstring text) { DoStep(text); }
		void And(wstring text, wstring docStringArg) { DoStep(text, docStringArg); }
		void And(wstring text, GherkinTable tableArg) { DoStep(text, tableArg); }
		void And(wstring text, GherkinRow tableRowArg) { DoStep(text, tableRowArg); }

		void But(wstring text) { DoStep(text); }
		void But(wstring text, wstring docStringArg) { DoStep(text, docStringArg); }
		void But(wstring text, GherkinTable tableArg) { DoStep(text, tableArg); }
		void But(wstring text, GherkinRow tableRowArg) { DoStep(text, tableRowArg); }

		void Spec(const char* guid)
		{
			std::cout << guid << std::endl;
		}

	protected:
		virtual AbstractStepModel* GetStepModel() = 0;

	private:
		void DoStep(wstring text) { GetStepModel()->DoStep(text); }
		void DoStep(wstring text, wstring docStringArg) { GetStepModel()->DoStep(text, docStringArg); }
		void DoStep(wstring text, GherkinTable tableArg) { GetStepModel()->DoStep(text, tableArg); }
		void DoStep(wstring text, GherkinRow tableRowArg) { GetStepModel()->DoStep(text, tableRowArg); }
	};
}
