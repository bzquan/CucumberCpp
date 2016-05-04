#include "IndirectFunctionCaller.h"

IndirectFunctionCaller* IndirectFunctionCaller::s_pInstance = NULL;

IndirectFunctionCaller* IndirectFunctionCaller::Instance()
{
	if (s_pInstance == NULL)
	{
		s_pInstance = new IndirectFunctionCaller();
	}

	return s_pInstance;
}

IndirectFunctionCaller::~IndirectFunctionCaller()
{
	s_pInstance = NULL;
}

void IndirectFunctionCaller::Clear()
{
	m_CallBackRequestList.clear();
}

void IndirectFunctionCaller::DoCallBacks()
{
	while (!m_CallBackRequestList.empty())
	{
		ICallBackRequest* pCallBackRequest = NextCallBackRequest();

		pCallBackRequest->CallBack();
		delete pCallBackRequest;
	}
}

ICallBackRequest* IndirectFunctionCaller::NextCallBackRequest()
{
	ICallBackRequest* pCallBackRequest = m_CallBackRequestList.front();
	m_CallBackRequestList.pop_front();

	return pCallBackRequest;
}
