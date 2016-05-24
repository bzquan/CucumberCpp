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

#include <algorithm>
#include <iostream>
#include "NotificationTrace.h"

using namespace std;

void NotificationTrace::Append(std::string notification_msg)
{
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_Trace.push_back(notification_msg);
    m_Condition.notify_all();
}

void NotificationTrace::WaitNotification(std::string expected_msg, std::chrono::milliseconds wait_time)
{
    auto wait_until = std::chrono::system_clock::now() + wait_time;
    unique_lock<std::mutex> lock(m_Mutex);

    if (!m_Condition.wait_until(lock, wait_until, [this, expected_msg] { return Match(expected_msg); }))
    {
        throw domain_error("Time out in WaitNotification!");
    }
}

bool NotificationTrace::Match(std::string expected_msg)
{
    return find(m_Trace.begin(), m_Trace.end(), expected_msg) != m_Trace.end();
}
