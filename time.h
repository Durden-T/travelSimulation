#ifndef TIME_H
#define TIME_H



#include"common.h"
//ʱ�䣺��0��Ϊ���� �ڶ��� �ڶ��� ������......
//ʱ�� 0-23 time unsigned int
class Time
{
	friend istream& operator>>(istream& is, Time& time);
	friend ostream& operator<<(ostream& os, const Time& time);
	friend bool operator>(const Time& lhs, const Time& rhs);
	friend bool operator<=(const Time& lhs, const Time& rhs);
	friend bool operator==(const Time& lhs, const Time& rhs);
	friend bool operator!=(const Time& lhs, const Time& rhs);
	friend bool operator<(const Time& lhs, const Time& rhs);


public:
	//Ĭ�ϳ�ʼ��Ϊ�����ʱ�䣬�������ط��Ĳ���
	Time(unsigned int _day = INT_MAX, unsigned int _hour = INT_MAX, unsigned int _minute = INT_MAX) :day(_day), hour(_hour), minute(_minute) {}

	//���ʱ���Ƿ���Ч
	bool valid();

	//�ϲ������˳�/�ɻ���ʱ��ǰ������һ��
	Time& advanceTo(const Time& after);

	//��ÿ�ε�������һСʱ
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