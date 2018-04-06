#pragma once

#include "app.h"
#include "../Utility/Singleton.h"

#include <string>
#include <vector>
#include <assert.h>
#include "../Math/Color.h"

#define SLogPrint(t, c) SimpleLogger.Print(t, c)
#define SLogDraw SimpleLogger.Draw()
#define SLogStart(x, y) SimpleLogger.SetInitialPosition(x, y)
#define SLogSpacing(x) SimpleLogger.SetVerticalSpacing(x)

#define MaxSimpleLoggerMessages 48

struct SimpleMessage
{
	SimpleMessage(std::string t = "", Color3F c = Color3F(1, 1, 1))
	{
		m_text = t;
		m_color = c;
	}
	Color3F		m_color;
	std::string m_text;
};

static class SimpleLogger : Singleton<class SimpleLogger>
{
private:
	int m_InitialX = 0;
	int m_InitialY = 0;
	int m_verticalSpacing = 10;
	SimpleMessage* m_messages = new SimpleMessage[MaxSimpleLoggerMessages];
	SimpleMessage* m_errorsTemp = new SimpleMessage[MaxSimpleLoggerMessages];
	SimpleMessage* m_errorsStatic = new SimpleMessage[MaxSimpleLoggerMessages];
	u_int m_totalMessages = 0;
	u_int m_totalErrorTemp = 0;
	u_int m_totalErrorStatic = 0;
public:
	void SetVerticalSpacing(int v)
	{
		m_verticalSpacing = v;
	}
	void SetInitialPosition(int x, int y)
	{
		m_InitialX = x;
		m_InitialY = y;
	}
	void Print(std::string message, Color3F color = Color3F::WHITE())
	{
		if (m_totalMessages >= MaxSimpleLoggerMessages)
			return;

		m_messages[m_totalMessages++] = SimpleMessage(message, color);
	}
	// Error temp gets cleared at the end of the frame like normal messages
	void ErrorTemp(std::string message)
	{
		if (m_totalErrorTemp >= MaxSimpleLoggerMessages)
			return;

		m_errorsTemp[m_totalErrorTemp++] = SimpleMessage(message);
	}
	// Static error never gets cleared
	void ErrorStatic(std::string message)
	{
		if (m_totalErrorStatic >= MaxSimpleLoggerMessages)
			return;

		m_errorsStatic[m_totalErrorStatic++] = SimpleMessage(message);
	}

	// Manually clear errors from screen
	inline void ClearAllErrors()
	{
		m_totalErrorStatic = 0;
	}

	void Draw()
	{
		// Item count
		int TotalLogs = 0;
		// Draw Errors
		for (u_int i = 0; i < m_totalErrorTemp; i++)
		{
			App::Print(m_InitialX, m_InitialY + m_verticalSpacing * TotalLogs, m_errorsTemp[i].m_text.c_str(), Color3F::RED());
			TotalLogs++;
		}
		for (u_int i = 0; i < m_totalErrorStatic; i++)
		{
			App::Print(m_InitialX, m_InitialY + m_verticalSpacing * TotalLogs, m_errorsStatic[i].m_text.c_str(), Color3F::RED());
			TotalLogs++;
		}
		// Draw Messages
		for (u_int i = 0; i < m_totalMessages; i++)
		{
			App::Print(m_InitialX, m_InitialY + m_verticalSpacing * TotalLogs, m_messages[i].m_text.c_str(), m_messages[i].m_color);
			TotalLogs++;
		}
		// Clear temp errors and messages
		m_totalErrorTemp = 0;
		m_totalMessages = 0;
	}

} &SimpleLogger = Singleton<class SimpleLogger>::instanceRef;