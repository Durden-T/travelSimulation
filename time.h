#ifndef TIME_H
#define TIME_H



#include"common.h"
//ʱ�䣺��0��Ϊ���� ��1�� ��2�� ��3��......
//ʱ�� 0-23



class Time
{
	//����Ϊ��Ԫ����
	friend istream& operator>>(istream& is, Time& time);
	friend ostream& operator<<(ostream& os, const Time& time);
	friend bool operator>(const Time& lhs, const Time& rhs);
	friend bool operator<=(const Time& lhs, const Time& rhs);
	friend bool operator==(const Time& lhs, const Time& rhs);
	friend bool operator!=(const Time& lhs, const Time& rhs);
	friend bool operator<(const Time& lhs, const Time& rhs);


public:
	//Ĭ�ϳ�ʼ��Ϊ�����ʱ�䣬���ڲ���
	Time(unsigned int _day = INT_MAX, unsigned int _hour = INT_MAX, unsigned int _minute = INT_MAX) :day(_day), hour(_hour), minute(_minute) {}

	//���ʱ���Ƿ���Ч
	bool valid();

	//�ϲ������˳�/�ɻ���ʱ��ǰ������һ��
	Time& advanceTo(const Time& after);

	//ÿ�ε�������һСʱ
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