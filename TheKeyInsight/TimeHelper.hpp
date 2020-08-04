#pragma once

#include <chrono>
#include <ctime>
#include <string>
#include <sstream>

namespace Insight {

	class DateTime
	{
	private:
		int _day, _month, _year, _h, _m, _s;
	public:
		DateTime();
		DateTime(int day, int month, int year, int h, int m, int s);
		DateTime(int day, int month, int year);
		DateTime now() const;
		std::string getDate() const;
		std::string getTime(const std::string& sep) const;
		std::string getDateTime(const std::string& sep) const;
		~DateTime() = default;
	};

}