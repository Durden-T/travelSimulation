#ifndef TIME_H
#define TIME_H



#include"common.h"
//时间：第0天为当天 第1天 第2天 第3天......
//时间 0-23



class Time
{
	//定义为友元函数
	friend istream& operator>>(istream& is, Time& time);
	friend ostream& operator<<(ostream& os, const Time& time);
	friend bool operator>(const Time& lhs, const Time& rhs);
	friend bool operator<=(const Time& lhs, const Time& rhs);
	friend bool operator==(const Time& lhs, const Time& rhs);
	friend bool operator!=(const Time& lhs, const Time& rhs);
	friend bool operator<(const Time& lhs, const Time& rhs);


public:
	//默认初始化为无穷大时间，便于测试
	Time(unsigned int _day = INT_MAX, unsigned int _hour = INT_MAX, unsigned int _minute = INT_MAX) :day(_day), hour(_hour), minute(_minute) {}

	//检测时间是否有效
	bool valid();

	//赶不上这趟车/飞机，时间前进到下一天
	Time& advanceTo(const Time& after);

	//每次调用增加一小时
	inline void addOneHour();

private:
	unsigned int day, hour, minute;
};

inline bool Time::valid()
{
	return hour < 24 && minute < 60;
}

inline void Time::addOneHour()
{
	if (++hour > 23)
	{
		hour = 0;
		++day;
	}
}
#endif