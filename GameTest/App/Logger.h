#pragma once

#include <vector>
#include <string>
#include "app.h"
#include "../math/Color.h"

class LogMessage
{
public:
	Color3F		m_color;
	std::string m_message;

	LogMessage(const std::string& message, Color3F color) : m_message(message), m_color(color)
	{

	}
	virtual void display(float x, float y)
	{
		App::Print(x, y, m_message.c_str(), m_color.r, m_color.g, m_color.b);
	}
};

template<typename T>
class LogData : public LogMessage
{
public:
	T m_value;

	LogData(const std::string& message, T value, Color3F color) : LogMessage(message, color), m_value(value)
	{

	}
	void display(float x, float y) override
	{
		App::Print(x, y, (m_message + ": " + std::to_string(m_value)).c_str(), m_color.r, m_color.g, m_color.b);
	}
};

class Logger
{
private:
	int	x, y;
	std::vector<LogMessage*>	m_data;
	int							m_totalLines = 0;
	int							m_verticalPadding = 0;
public:
	Logger(int _x = 0, int _y = 0, int vertical_padding = 0)
	{
		x = _x;
		y = _y;
		m_verticalPadding = vertical_padding;
	}
	~Logger()
	{
		for (int i = 0; i < m_totalLines; i++)
		{
			delete m_data[i];
		}
	}

	inline void setPadding(int p)
	{
		m_verticalPadding = p;
	}

	inline void clear()
	{
		m_data.clear();
		m_totalLines = 0;
	}

	LogMessage* addMessage(const std::string& message = "", Color3F color = Color3F(1))
	{
		LogMessage* L = new LogMessage(message, color);
		m_data.push_back(L);
		m_totalLines++;
		return L;
	}

	template<typename T>
	LogData<T>* addDataMessage(const std::string& message, T value, Color3F color = Color3F(1))
	{
		LogData<T>* L = new LogData<T>(message, value, color);
		m_data.push_back(L);
		m_totalLines++;
		return L;
	}

	void displayText() const
	{
		for (int i = 0; i < m_totalLines; i++)
		{
			m_data[i]->display(x, y + i * (15 + m_verticalPadding));
		}
	}

};