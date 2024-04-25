#include "VoronoiNoise.h"

float VoronoiNoise::euclidianDistance(const int& x, const int& y, const pixel2& center)
{
    return std::sqrt(std::pow(x - center.x, 2) + std::pow(y - center.y, 2));
}

float VoronoiNoise::manhattanDistance(const int& x, const int& y, const pixel2& center)
{
    return std::abs(x - center.x) + std::abs(y - center.y);
}

color VoronoiNoise::obtainColor(const std::pair<float, color>* distances, char aspect_index3, char aspect)
{
    if (aspect == 'p' || aspect == 'b')
        return { distances[0].second.r, distances[0].second.g, distances[0].second.b, 255};

    int value_cap;
    if (aspect == 's')
        value_cap = distances[1].first - distances[0].first;

    else
        value_cap = 255 - distances[0].first;

    if (value_cap > 255)
        value_cap = 255;

    if (value_cap < 0)
        value_cap = 0;

    unsigned char cl = value_cap;

    switch (aspect) {
    case 's':
        return { cl, cl, 0, 255 };
    case 'c':
        return { cl, 0, (unsigned char)((255 - cl) / 2), 255 };
    case 'g':
    default:
        return { cl, cl, cl, 255 };
    }
}

color VoronoiNoise::generateColor(char aspect)
{
    if (aspect == 'b')
        return { ColorVectors::s_biome_colors[rand() % ColorVectors::s_biome_colors.size()] };

    return { (unsigned char)(rand() % 256),(unsigned char)(rand() % 256),
            (unsigned char)(rand() % 256), 255 };
}

void VoronoiNoise::Algorithm(Renderer& r, const int& aspect_index1, const bool& aspect_index2, const char& aspect_index3, char aspect = 'g')
{
    if (aspect != 'g' && aspect != 'c' && aspect != 's' && aspect != 'b' && aspect != 'p')
        aspect = 'g';

    std::pair<pixel2, color>* centers = new std::pair<pixel2, color>[aspect_index1];
    std::pair<float, color>* distances = new std::pair<float, color>[aspect_index1];
    int grid_size = std::sqrt(aspect_index1);

    for (int i = 0; i < aspect_index1; i++)
    {
        if (aspect_index2)
            centers[i].first = { rand() % (r.m_window_width / grid_size) + (i % grid_size) * (r.m_window_width / grid_size),
                            rand() % (r.m_window_height / grid_size) + (i / grid_size) * (r.m_window_height / grid_size)};

        else
            centers[i].first = { rand() % r.m_window_width, rand() % r.m_window_height };

        centers[i].second = VoronoiNoise::generateColor(aspect);
    }

    for (int x = 0; x < r.m_window_width; x++)
    {
        for (int y = 0; y < r.m_window_height; y++)
        {  
            for (int i = 0; i < aspect_index1; i++)
            {
                distances[i].first = aspect_index3 == 'm' ? VoronoiNoise::manhattanDistance(x, y, centers[i].first) :
                                                            VoronoiNoise::euclidianDistance(x, y, centers[i].first);
                distances[i].second = centers[i].second;
            }

            std::sort(distances, distances + aspect_index1, [](const std::pair<float, color>& a, const std::pair<float, color>& b)
                {
                    return a.first < b.first;
                });

            color Col = VoronoiNoise::obtainColor(distances, aspect_index3, aspect);
            int index = (y * r.m_window_width + x) * 4;

            r.m_pixels[index] = Col.r;
            r.m_pixels[index + 1] = Col.g;
            r.m_pixels[index + 2] = Col.b;
            r.m_pixels[index + 3] = Col.a;
        }
    }

    delete[] distances;
    delete[] centers;
}
