#pragma once

// Forward declaration
namespace ShiryuTeam { class Application; }
namespace ShiryuTeam { Application* CreateApplication(int argc, char** argv); }

bool g_ApplicationRunning = true;

namespace ShiryuTeam {

	int Main(int argc, char** argv)
	{
		while (g_ApplicationRunning)
		{
			Application* app = CreateApplication(argc, argv);
			app->Run();
			delete app;
		}

		return 0;
	}

}

#if defined(WL_PLATFORM_WINDOWS) && !defined(WL_HEADLESS) && defined(WL_DIST)

#include <Windows.h>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	return ShiryuTeam::Main(__argc, __argv);
}

#else

int main(int argc, char** argv)
{
	return ShiryuTeam::Main(argc, argv);
}

#endif // defined(WL_PLATFORM_WINDOWS) && defined(WL_DIST)