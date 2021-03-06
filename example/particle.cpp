#include <RGame.h>
#include <RPlane.h>
#include <RWindow.h>
#include <RRenderSys.h>
#include <deque>
#include <cstdlib>

using namespace Redopera;

std::deque<std::pair<RPlane, RPoint2F>> particles;
std::unique_ptr<RPlane> init;
std::unique_ptr<RRenderSys> renderer;

int WIDTH = 480, HEIGHT = 480;
float gravity = 1.f;

void start()
{
    init = std::make_unique<RPlane>();
    init->setTexture(RTexture::createWhiteTex());
    init->setModel(RRectF(WIDTH / 2.f, 0.f, 4.f, 4.f));

    renderer = std::make_unique<RRenderSys>();
    renderer->setViewMove();
    renderer->setViewport(0, WIDTH, 0, HEIGHT);
}

void finish()
{
    particles.clear();
    init.reset();
    renderer.reset();
}

void update()
{
    float RANGE = static_cast<float>(RAND_MAX) / 8.f;
    if(rand() % 2 == 0)
        particles.emplace_back(*init, RPoint2F(std::rand() / RANGE - 4.f, 30.f));

    for(auto it = particles.begin(); it != particles.end();)
    {
        it->second.ry() -= gravity;
        it->first.move(it->second);

        if(it->second.y() < -60.f)
            it = particles.erase(it);
        else
        {
            renderer->render(it->first.texture(), it->first.model());
            ++it;
        }
    }
}

int main()
{
    RGame game;
    RWindow::Format format;
    format.debug = false;
    RWindow window(WIDTH, HEIGHT, "Particle", format);

    window.show();
    start();
    window.exec([]{
        update();
        return 0;
    });
    finish();

    return 0;
}
