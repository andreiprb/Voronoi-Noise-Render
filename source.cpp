#include "Renderer.h"

int main()
{
    srand(time(NULL));
    
    Renderer perlin_renderer(1280, 720);
    VoronoiNoise::Algorithm(perlin_renderer, 25, true, 'e', 'b');
    perlin_renderer.Run();

    return 0;
}