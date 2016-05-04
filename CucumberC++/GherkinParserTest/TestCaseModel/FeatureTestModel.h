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
