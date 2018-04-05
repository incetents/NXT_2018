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

#define MaxSimpleLoggerMessages 128

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
	u_int m_totalMessages = 0;
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
	void Print(std::string message, Color3F color = Color::WHITE)
	{
		assert(m_totalMessages != 256);

		m_messages[m_totalMessages++] = SimpleMessage(message, color);
	}
	void Draw()
	{
		for (u_int i = 0; i < m_totalMessages; i++)
		{
			App::Print(m_InitialX, m_InitialY + m_verticalSpacing * i, m_messages[i].m_text.c_str(), m_messages[i].m_color);
		}
		m_totalMessages = 0;
	}

} &SimpleLogger = Singleton<class SimpleLogger>::instanceRef;