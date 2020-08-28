#pragma once

#include <string>
#include <fstream>

namespace Insight {

	namespace MiniLogger {

		static void writeToLogFile(const std::string& message, const std::string& filename = std::string("TheKeyInsight.log")) {
			std::ofstream file(filename, std::ios::app);
			file << message;
			file.close();
		}

	}

}