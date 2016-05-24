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
