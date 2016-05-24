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
#include <map>
#include <list>

#include "IndirectFunctionCaller.h"

using namespace std;

class ITestAction
{
public:
    virtual ~ITestAction(){}
    virtual void Excecute() = 0;
};

template <class T>
class ActionTemplate : public ITestAction
{
	typedef void(T::*ActionFunctor)();
public:
	ActionTemplate(T* pContext, ActionFunctor expectedActionFunctor) :
	  m_pContext(pContext),
	  m_ExpectedActionFunctor(expectedActionFunctor){}

	  virtual void Excecute()
	  {
		  (m_pContext->*m_ExpectedActionFunctor)();
	  }

protected:
	T* m_pContext;
	ActionFunctor	m_ExpectedActionFunctor;
};

class ActionWithFunc : public ITestAction
{
public:
    ActionWithFunc(std::function<void(void)> action) :
        m_ActionFunctor(action) {}

    virtual void Excecute()
    {
        m_ActionFunctor();
    }

protected:
    std::function<void(void)>  m_ActionFunctor;
};

class AbstractTestModel
{
public:
	AbstractTestModel()
	{
		s_DSLModelList.push_back(this);
	}
	virtual ~AbstractTestModel()
	{
		s_DSLModelList.remove(this);
	}

	void AddAction(ITestAction* pAction)
	{
		s_ActionList.push_back(pAction);
	}

	void AddExpectation(ITestAction* pAction)
	{
		s_ExpectationList.push_back(pAction);
	}

	void Execute()
	{
		Execute(s_ExpectationList);
		Execute(s_ActionList);
		IndirectFunctionCaller::Instance()->DoCallBacks();
		VerifyExpectationsOfAllModels();
		Clear();
	}

protected:
	virtual void VerifyExpectations() = 0;

private:
	void Execute(list<ITestAction*> &commands)
	{
		for ( list<ITestAction*>::iterator it = commands.begin(); it != commands.end(); ++it )
		{
			(*it)->Excecute();
		}
	}

	void VerifyExpectationsOfAllModels()
	{
		for ( list<AbstractTestModel*>::iterator it = s_DSLModelList.begin(); it != s_DSLModelList.end(); ++it )
		{
			(*it)->VerifyExpectations();
		}
	}

	void Clear()
	{
		Clear(s_ActionList);
		Clear(s_ExpectationList);
		IndirectFunctionCaller::Instance()->Clear();
	}

	void Clear(list<ITestAction*> &commands)
	{
		for ( list<ITestAction*>::iterator it = commands.begin(); it != commands.end(); ++it )
		{
			delete *it;
		}
		commands.clear();
	}

protected:
	static list<AbstractTestModel*>	s_DSLModelList;
	static list<ITestAction*>	s_ActionList;
	static list<ITestAction*>	s_ExpectationList;
};
