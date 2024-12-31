#include <iostream>

#include "ApolloApp.h"

#if defined(WINDOWS) && !defined(_CONSOLE)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char* argv[])
#endif
{
    ApolloApp App("Apollo Music Player", 800, 600);
    App.Run();
}