#include "Application.h"

#ifdef WINDOWS
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char* argv[])
#endif
{
	Application App = Application("Apollo Music Player", 800, 600);
	App.Run();
	App.~Application();
}