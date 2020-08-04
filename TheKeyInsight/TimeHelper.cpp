#include "TimeHelper.hpp"

namespace Insight {

	DateTime::DateTime()
	{
		auto _now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		
		std::tm* info = std::localtime(&_now);
		_day = info->tm_mday;
		_month = info->tm_mon + 1;
		_year = 1900 + info->tm_year;
		_h = info->tm_hour;
		_m = info->tm_min;
		_s = info->tm_sec;
	}

	DateTime::DateTime(int day, int month, int year, int h, int m, int s) :
		_day(day), _month(month), _year(year), _h(h), _m(m), _s(s)
	{
	}

	DateTime::DateTime(int day, int month, int year) :_day(day), _month(month),
		_year(year), _h(0), _m(0), _s(0)
	{
	}


	DateTime DateTime::now() const
	{
		return DateTime();
	}

	std::string DateTime::getDate() const
	{
		std::ostringstream date_op;
		date_op << std::string((_day < 10) ? " " : "") << _day
			<< std::string((_month < 10) ? ".0" : ".")
			<< _month << "." << _year;
		return date_op.str();
	}

	std::string DateTime::getTime(const std::string& sep = std::string(":")) const
	{
		std::ostringstream time_op;
		time_op << std::string((_h < 10) ? "0" : "") << _h << sep
				<< std::string((_m < 10) ? "0" : "") << _m << sep
				<< std::string((_s < 10) ? "0" : "") << _s;
		return time_op.str();
	}

	std::string DateTime::getDateTime(const std::string& sep = std::string(":")) const
	{
		return getDate() + " " + getTime(sep);
	}
}