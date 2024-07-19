#include "Application.h"
#include "Graphics.h"

class ApolloApp : public Apollo::Application 
{
    public:
        ApolloApp(const char* name, int width, int height) : Apollo::Application(name, width, height) {}

        ~ApolloApp() { Application::~Application(); }

        void Update() override 
        {
            
        }

        void Draw() override 
        {
            Apollo::Graphics graphics(*this);

            graphics.Clear(Apollo::Color(12, 12, 24));
            
            graphics.DrawFillRectangle(5, graphics.m_height - 25, graphics.m_width - 10, 20, Apollo::Color(127, 127, 127));

            graphics.Present();
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