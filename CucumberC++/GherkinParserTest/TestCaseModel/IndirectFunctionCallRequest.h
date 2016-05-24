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

#include <list>

#if defined(WIN32) && (_MSC_VER < 1900)
    // _MSC_VER == 1900 (Visual Studio 2015, MSVC++ 14.0)
	#include <boost/function.hpp>
	#include <boost/bind.hpp>
	using namespace boost;
#else
	#include <functional>
	using namespace std::placeholders;
    using namespace std;
#endif

class ICallBackRequest
{
public:
    virtual ~ICallBackRequest(){}
    virtual void CallBack() = 0;
};

template<class R>
class CallBackRequest : public ICallBackRequest
{
public:
	CallBackRequest(function<R(void)> func) : CallBackFunction(func){ }
	virtual void CallBack() override
	  {
		  CallBackFunction();
	  }

private:
	function<R(void)> CallBackFunction;
};

template<class R, class A>
class CallBackRequest1 : public ICallBackRequest
{
public:
	CallBackRequest1(function<R(A)> func, A& arg) : CallBackFunction(func), m_Arg(arg){ }
	virtual void CallBack() override
	{
		CallBackFunction(m_Arg);
	}

private:
	function<R(A)> CallBackFunction;
    A m_Arg;	//注意： 由于实际参数可能不是变量，所以不应该使用引用
};

template<class R, class A1, class A2>
class CallBackRequest2 : public ICallBackRequest
{
public:
	CallBackRequest2(function<R(A1, A2)> func, A1& arg1, A2& arg2) : CallBackFunction(func), m_Arg1(arg1), m_Arg2(arg2){ }
	virtual void CallBack() override
	{
		CallBackFunction(m_Arg1, m_Arg2);
	}

private:
	function<R(A1, A2)> CallBackFunction;
	A1 m_Arg1;
	A2 m_Arg2;
};

template<class R, class A1, class A2, class A3>
class CallBackRequest3 : public ICallBackRequest
{
public:
	CallBackRequest3(function<R(A1, A2, A3)> func, A1& arg1, A2& arg2, A3& arg3) : CallBackFunction(func), m_Arg1(arg1), m_Arg2(arg2), m_Arg3(arg3){ }
	virtual void CallBack() override
	{
		CallBackFunction(m_Arg1, m_Arg2, m_Arg3);
	}

private:
	function<R(A1, A2, A3)> CallBackFunction;
	A1 m_Arg1;
	A2 m_Arg2;
	A3 m_Arg3;
};
