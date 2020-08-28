#pragma once

#include <string>
#include <cstdlib>
#include <fstream>
#include <windows.h>
#include "Base64Encrypter.hpp"
#include "TimeHelper.hpp"

namespace Insight {

	namespace IO
	{
		template <class T>
		std::string writeEncryptedLog(const T& t)
		{
			DateTime dt;
			system("mkdir EncryptedLogs");
			std::string path = "EncryptedLogs\\";
			std::string name = dt.getDateTime("_") + ".log";
			try
			{
				std::ofstream file(path+name);
				if (!file) return "";
				std::ostringstream s;

				s << "[" << dt.getDateTime(":") << "]" << std::endl << t << std::endl;

				std::string data = Base64::EncryptB64(s.str());

				file << data;
				if (!file)
					return "";
				file.close();
				return name;
			}
			catch (...)
			{
				return "";
			}
		}

	}

}
