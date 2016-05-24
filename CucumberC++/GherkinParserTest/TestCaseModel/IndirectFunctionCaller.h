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
#include "IndirectFunctionCallRequest.h"

class IndirectFunctionCaller
{
public:
    static IndirectFunctionCaller* Instance();

	virtual ~IndirectFunctionCaller();
	void Clear();
	void DoCallBacks();

	template<class R>
    void RegisterCallBack(function<R(void)> func);

	template<class R, class A1>
	void RegisterCallBack(function<R(A1)> func, A1& arg1);

	template<class R, class A1, class A2>
	void RegisterCallBack(function<R(A1, A2)> func, A1& arg1, A2& arg2);

	template<class R, class A1, class A2, class A3>
	void RegisterCallBack(function<R(A1, A2, A3)> func, A1& arg1, A2& arg2, A3& arg3);

private:
    IndirectFunctionCaller(){}
	ICallBackRequest* NextCallBackRequest();

private:
    static IndirectFunctionCaller* s_pInstance;

private:
	std::list<ICallBackRequest*> m_CallBackRequestList;
};

//////////////////

template<class R>
void IndirectFunctionCaller::RegisterCallBack(function<R(void)> func)
{
	m_CallBackRequestList.push_back( new CallBackRequest<R>(func) );
}

template<class R, class A1>
void IndirectFunctionCaller::RegisterCallBack(function<R(A1)> func, A1& arg1)
{
	m_CallBackRequestList.push_back(new CallBackRequest1<R, A1>(func, arg1));
}

template<class R, class A1, class A2>
void IndirectFunctionCaller::RegisterCallBack(function<R(A1, A2)> func, A1& arg1, A2& arg2)
{
	m_CallBackRequestList.push_back(new CallBackRequest2<R, A1, A2>(func, arg1, arg2));
}

template<class R, class A1, class A2, class A3>
void IndirectFunctionCaller::RegisterCallBack(function<R(A1, A2, A3)> func, A1& arg1, A2& arg2, A3& arg3)
{
	m_CallBackRequestList.push_back(new CallBackRequest3<R, A1, A2, A3>(func, arg1, arg2, arg3));
}
