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
