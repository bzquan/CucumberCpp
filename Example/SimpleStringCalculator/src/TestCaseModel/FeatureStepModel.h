#pragma once

#include "FeatureStepFunction.h"

namespace bdd
{
	class AbstractStepModel
	{
	public:
		virtual ~AbstractStepModel()
		{
			for (map<wstring, StepFunction*>::iterator& iter = m_stepMap.begin(); iter != m_stepMap.end(); ++iter)
			{
				delete iter->second;
			}
		}

		// add steps to step dictionary
		void Step(wstring text, function<void(GherkinTable&)> step)
		{
			AddStep(text, new StepFunctionTableParam(step));
		}

		template<typename T>
		void Step(wstring text, function<void(GherkinTable&, T)> step)
		{
			AddStep(text, new StepFunctionTableParam1<T>(step));
		}

		template<typename T1, typename T2>
		void Step(wstring text, function<void(GherkinTable&, T1, T2)> step)
		{
			AddStep(text, new StepFunctionTableParam2<T1, T2>(step));
		}

		void Step(wstring text, function<void(GherkinRow&)> step)
		{
			AddStep(text, new StepFunctionTableRowParam(step));
		}

		template<typename T>
		void Step(wstring text, function<void(GherkinRow&, T)> step)
		{
			AddStep(text, new StepFunctionTableRowParam1<T>(step));
		}

		template<typename T1, typename T2>
		void Step(wstring text, function<void(GherkinRow&, T1, T2)> step)
		{
			AddStep(text, new StepFunctionTableRowParam2<T1, T2>(step));
		}

		void StepDocString(wstring text, function<void(wstring)> step)
		{
			AddStep(text, new StepFunctionDocString(step));
		}

		template<typename T>
		void StepDocString(wstring text, function<void(wstring, T)> step)
		{
			AddStep(text, new StepFunctionDocString1<T>(step));
		}

		template<typename T1, typename T2>
		void StepDocString(wstring text, function<void(wstring, T1, T2)> step)
		{
			AddStep(text, new StepFunctionDocString2<T1, T2>(step));
		}

		void Step(wstring text, function<void()> step)
		{
			AddStep(text, new StepFunction0(step));
		}

		template<typename T>
		void Step(wstring text, function<void(T)> step)
		{
			AddStep(text, new StepFunction1<T>(step));
		}

		template<typename T1, typename T2>
		void Step(wstring text, function<void(T1, T2)> step)
		{
			AddStep(text, new StepFunction2<T1, T2>(step));
		}

		template<typename T1, typename T2, typename T3>
		void Step(wstring text, function<void(T1, T2, T3)> step)
		{
			AddStep(text, new StepFunction3<T1, T2, T3>(step));
		}

		template<typename T1, typename T2, typename T3, typename T4>
		void Step(wstring text, function<void(T1, T2, T3, T4)> step)
		{
			AddStep(text, new StepFunction4<T1, T2, T3, T4>(step));
		}

		template<typename T1, typename T2, typename T3, typename T4, typename T5>
		void Step(wstring text, function<void(T1, T2, T3, T4, T5)> step)
		{
			AddStep(text, new <T1, T2, T3, T4, T5>StepFunction5(step));
		}

		template<typename T1, typename T2>
		void StepGen(wstring text, function<void(T1, T2)> step)
		{
			AddStep(text, new StepFunctionGen2<T1, T2>(step));
		}

		// Find matched step function by using regex and execute the step function
		void DoStep(wstring text)
		{
			StepFunction* pStep = GetMatchedStep(text);
			pStep->Execute();
		}

		void DoStep(wstring text, wstring docStringArg)
		{
			StepFunction* pStep = GetMatchedStep(text);
			pStep->SetArg(docStringArg);
			pStep->Execute();
		}

		void DoStep(wstring text, GherkinTable tableArg)
		{
			StepFunction* pStep = GetMatchedStep(text);
			pStep->SetArg(tableArg);
			pStep->Execute();
		}

		void DoStep(wstring text, GherkinRow tableRowArg)
		{
			StepFunction* pStep = GetMatchedStep(text);
			pStep->SetArg(tableRowArg);
			pStep->Execute();
		}

		virtual void RegisterSteps() = 0;

	protected:
		void PendingStep(wstring text)
		{
			throw domain_error("Pending step : " + StringUtility::wstring2string(text));
		}

	private:
		void AddStep(wstring text, StepFunction* pStep)
		{
			pair<map<wstring, StepFunction*>::iterator, bool> ret = m_stepMap.insert(pair<wstring, StepFunction*>(text, pStep));
			if (!ret.second)
			{
				delete pStep;
				throw invalid_argument("Step has been defined already : " + StringUtility::wstring2string(text));
			}
		}

		StepFunction* GetMatchedStep(wstring text)
		{
			for (map<wstring, StepFunction*>::iterator& iter = m_stepMap.begin(); iter != m_stepMap.end(); ++iter)
			{
				wstring pattern = iter->first;
				wregex exp(pattern);
				wsmatch match;
				if (regex_match(text, match, exp))
				{
					StepFunction* pStep = iter->second;
					pStep->SetArgs(match);
					return pStep;
				}
			}

			m_nullStepFunction.StepText(text);
			return &m_nullStepFunction;
		}

	private:
		map<wstring, StepFunction*> m_stepMap;
		StepFunctionNull m_nullStepFunction;
	};
}

