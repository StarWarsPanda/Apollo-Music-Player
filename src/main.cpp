#include "Application.h"
#include "Graphics.h"

class ApolloApp : public Apollo::Application {
    public:
        ApolloApp(const char* name, int width, int height) : Apollo::Application(name, width, height) {}

        ~ApolloApp() { Application::~Application(); }

        void Update() override 
        {
        
        }

        void Draw() override {
            Apollo::Graphics graphics(*this);
            graphics.DrawText("Hello Apollo!", 10, 10, 200, 30);
        }
};

#ifdef WINDOWS
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char* argv[])
#endif
{
    ApolloApp App("Apollo Music Player", 800, 600);
    App.Run();
}