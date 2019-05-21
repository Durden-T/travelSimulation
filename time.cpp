#include"time.h"

istream& operator>>(istream& is, Time& time)
{
	return (is >> time.day >> time.hour >> time.minute);
}

ostream& operator<<(ostream& os, const Time& time)
{
	return (os << "��" << time.day << "��" << time.hour << "ʱ" << time.minute << "��");
}

bool operator<=(const Time& lhs, const Time& rhs)
{
	return !(lhs > rhs);
}

bool operator==(const Time& lhs, const Time& rhs)
{
	return lhs.day == rhs.day && lhs.hour == rhs.hour && lhs.minute == rhs.minute;
}

bool operator!=(const Time& lhs, const Time& rhs)
{
	return !(lhs == rhs);
}

bool operator>(const Time& lhs, const Time& rhs)
{
	if (lhs.day > rhs.day)
		return true;
	if (lhs.day < rhs.day)
		return false;
	if (lhs.hour > rhs.hour)
		return true;
	if (lhs.hour < rhs.hour)
		return false;
	if (lhs.minute > rhs.minute)
		return true;
	else
		return false;
}

bool operator<(const Time& lhs, const Time& rhs)
{
	return !(lhs > rhs) && !(lhs == rhs);
}

Time& Time::advanceTo(const Time& after)
{
	//��after��ʱ�䲻Ϊ0,˵������ʵ�е�ʱ����ǵ�ͼ��,��˵�ǰ��dayǰ��after.day��
	if (after.day)
		day += after.day;
	//afterΪ��ͼʱ�䣬��ǰʱ�䳬���˵�ͼʱ��(ֻ��hour,minute)
	else if (hour > after.hour || hour == after.hour && minute > after.minute)
	{
		//ת�Ƶ���һ��
		++day;
	}

	hour = after.hour;
	minute = after.minute;

	return *this;
}