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
