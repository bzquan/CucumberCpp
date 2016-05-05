#pragma once

#if (_MSC_VER < 1900)   // _MSC_VER == 1900 (Visual Studio 2015, MSVC++ 14.0)
#include <boost/function.hpp>
#include <boost/bind.hpp>
using namespace boost;

#else
#include <functional>
using namespace std::placeholders;

#endif

#include <map>
#include <exception>

#include "StringUtility.h"
#include "GherkinTable.h"
#include "FeatureStepArg.h"

namespace bdd
{
	template <typename T> class StepArgTypeClass;

	template <> class StepArgTypeClass<long>
	{
	public:
		static long GetArg(StepArg& arg) { return arg.longValue(); }
	};
	template <> class StepArgTypeClass<double>
	{
	public:
		static double GetArg(StepArg& arg) { return arg.doubleValue(); }
	};
	template <> class StepArgTypeClass<wstring>
	{
	public:
		static wstring GetArg(StepArg& arg) { return arg.wstrValue(); }
	};

	template<typename T>
	T GetArg(StepArg& arg)
	{
		return StepArgTypeClass<T>::GetArg(arg);
	}

	class StepFunction
	{
		friend class FeatureStepTest;
	public:
		virtual void Execute() = 0;

		virtual void SetArg(GherkinTable&) {}
		virtual void SetArg(GherkinRow&) {}
		virtual void SetArg(wstring docStringArg)
		{
			m_docStringArg = docStringArg;
		}

		void SetArgs(wsmatch &match)
		{
			m_args.clear();		// Clear previous arguments, which are arguments for a previous step.

			for (size_t i = 1; i < match.size(); i++)
			{
				m_args.push_back(StepArg(match[i]));
			}
		}

		StepArg Arg(size_t index)
		{
			if (index < m_args.size())
				return m_args[index];
			else
				return StepArg(L"");
		}

	protected:
		wstring m_docStringArg;

	private:
		vector<StepArg> m_args;
	};

	class StepFunctionNull : public StepFunction
	{
	public:
		void Execute() override
		{
			throw domain_error("Undefined step : " + m_stepText);
		}
		void StepText(wstring stepText)
		{
			m_stepText = StringUtility::wstring2string(stepText);
		}

	private:
		string m_stepText;
	};

	class StepFunctionTableParam : public StepFunction
	{
	public:
		StepFunctionTableParam(function<void(GherkinTable&)> step) :
			m_step(step) {}
		void Execute() override
		{
			m_step(m_table);
		}

		void SetArg(GherkinTable& table) override
		{
			m_table = table;
		}

	private:
		function<void(GherkinTable&)> m_step;
		GherkinTable m_table;
	};

	template<typename T>
	class StepFunctionTableParam1 : public StepFunction
	{
	public:
		StepFunctionTableParam1(function<void(GherkinTable&, T)> step) :
			m_step(step) {}

		void Execute() override
		{
			m_step(m_table, GetArg<T>(Arg(0)));
		}

		void SetArg(GherkinTable& table) override
		{
			m_table = table;
		}

	private:
		function<void(GherkinTable&, T)> m_step;
		GherkinTable m_table;
	};

	template<typename T1, typename T2>
	class StepFunctionTableParam2 : public StepFunction
	{
	public:
		StepFunctionTableParam2(function<void(GherkinTable&, T1, T2)> step) :
			m_step(step) {}
		void Execute() override
		{
			m_step(m_table, GetArg<T1>(Arg(0)), GetArg<T2>(Arg(1)));
		}

		void SetArg(GherkinTable& table) override
		{
			m_table = table;
		}

	private:
		function<void(GherkinTable&, T1, T2)> m_step;
		GherkinTable m_table;
	};

	class StepFunctionTableRowParam : public StepFunction
	{
	public:
		StepFunctionTableRowParam(function<void(GherkinRow&)> step) :
			m_step(step) {}
		void Execute() override
		{
			m_step(m_tableRow);
		}

		void SetArg(GherkinRow& row) override
		{
			m_tableRow = row;
		}

	private:
		function<void(GherkinRow&)> m_step;
		GherkinRow m_tableRow;
	};

	template<typename T>
	class StepFunctionTableRowParam1 : public StepFunction
	{
	public:
		StepFunctionTableRowParam1(function<void(GherkinRow&, T)> step) :
			m_step(step) {}
		void Execute() override
		{
			m_step(m_tableRow, GetArg<T>(Arg(0)));
		}

		void SetArg(GherkinRow& row) override
		{
			m_tableRow = row;
		}

	private:
		function<void(GherkinRow&, T)> m_step;
		GherkinRow m_tableRow;
	};

	template<typename T1, typename T2>
	class StepFunctionTableRowParam2 : public StepFunction
	{
	public:
		StepFunctionTableRowParam2(function<void(GherkinRow&, T1, T2)> step) :
			m_step(step) {}
		void Execute() override
		{
			m_step(m_tableRow, GetArg<T1>(Arg(0)), GetArg<T2>(Arg(1)));
		}

		void SetArg(GherkinRow& row) override
		{
			m_tableRow = row;
		}

	private:
		function<void(GherkinRow&, T1, T2)> m_step;
		GherkinRow m_tableRow;
	};


	class StepFunctionDocString : public StepFunction
	{
	public:
		StepFunctionDocString(function<void(wstring)> step) :
			m_step(step) {}

		void Execute() override
		{
			m_step(m_docStringArg);
		}

	private:
		function<void(wstring)> m_step;
	};

	template<typename T>
	class StepFunctionDocString1 : public StepFunction
	{
	public:
		StepFunctionDocString1(function<void(wstring, T)> step) :
			m_step(step) {}
		void Execute() override
		{
			m_step(m_docStringArg, GetArg<T>(Arg(0)));
		}

	private:
		function<void(wstring, T)> m_step;
	};

	template<typename T1, typename T2>
	class StepFunctionDocString2 : public StepFunction
	{
	public:
		StepFunctionDocString2(function<void(wstring, T1, T2)> step) :
			m_step(step) {}
		void Execute() override
		{
			m_step(m_docStringArg, GetArg<T1>(Arg(0)), GetArg<T2>(Arg(1)));
		}

	private:
		function<void(wstring, T1, StepArg)> m_step;
	};

	class StepFunction0 : public StepFunction
	{
	public:
		StepFunction0(function<void()> step) :
			m_step(step) {}
		void Execute() override
		{
			m_step();
		}

	private:
		function<void()> m_step;
	};

	template<typename T>
	class StepFunction1 : public StepFunction
	{
	public:
		StepFunction1(function<void(T)> step) :
			m_step(step) {}
		void Execute() override
		{
			m_step(GetArg<T>(Arg(0)));
		}

	private:
		function<void(T)> m_step;
	};

	template<typename T1, typename T2>
	class StepFunction2 : public StepFunction
	{
	public:
		StepFunction2(function<void(T1, T2)> step) :
			m_step(step) {}
		void Execute() override
		{
			m_step(GetArg<T1>(Arg(0)), GetArg<T2>(Arg(1)));
		}

	private:
		function<void(T1, T2)> m_step;
	};

	template<typename T1, typename T2, typename T3>
	class StepFunction3 : public StepFunction
	{
	public:
		StepFunction3(function<void(T1, T2, T3)> step) :
			m_step(step) {}
		void Execute() override
		{
			m_step(GetArg<T1>(Arg(0)), GetArg<T2>(Arg(1)), GetArg<T3>(Arg(2)));
		}

	private:
		function<void(T1, T2, T3)> m_step;
	};

	template<typename T1, typename T2, typename T3, typename T4>
	class StepFunction4 : public StepFunction
	{
	public:
		StepFunction4(function<void(T1, T2, T3, T4)> step) :
			m_step(step) {}
		void Execute() override
		{
			m_step(GetArg<T1>(Arg(0)), GetArg<T2>(Arg(1)), GetArg<T3>(Arg(2)), GetArg<T4>(Arg(3)));
		}

	private:
		function<void(T1, T2, T3, T4)> m_step;
	};

	template<typename T1, typename T2, typename T3, typename T4, typename T5>
	class StepFunction5 : public StepFunction
	{
	public:
		StepFunction5(function<void(T1, T2, T3, T4, T5)> step) :
			m_step(step) {}
		void Execute() override
		{
			m_step(GetArg<T1>(Arg(0)), GetArg<T2>(Arg(1)), GetArg<T3>(Arg(2)), GetArg<T4>(Arg(3)), GetArg<T5>(Arg(4)));
		}

	private:
		function<void(T1, T2, T3, T4, T5)> m_step;
	};
}
