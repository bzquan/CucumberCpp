#pragma once

#include <vector>
#include <mutex>
#include <condition_variable>
#include "AbstractNotificationTrace.h"

class NotificationTrace : public AbstractNotificationTrace
{
public:
    NotificationTrace() {}

    void Append(std::string notification_msg) override;
    void WaitNotification(std::string expected_msg, std::chrono::milliseconds wait_time) override;

private:
    bool Match(std::string expected_msg);

private:
	std::vector<std::string> m_Trace;
	std::mutex m_Mutex;
	std::condition_variable m_Condition;
};

