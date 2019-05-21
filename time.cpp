#include"time.h"

istream& operator>>(istream& is, Time& time)
{
	return (is >> time.day >> time.hour >> time.minute);
}

ostream& operator<<(ostream& os, const Time& time)
{
	return (os << "第" << time.day << "天" << time.hour << "时" << time.minute << "分");
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
	//若after的时间不为0,说明是现实中的时间而非地图中,因此当前的day前进after.day天
	if (after.day)
		day += after.day;
	//after为地图时间，当前时间超过了地图时间(只看hour,minute)
	else if (hour > after.hour || hour == after.hour && minute > after.minute)
	{
		//转移到下一天
		++day;
	}

	hour = after.hour;
	minute = after.minute;

	return *this;
}