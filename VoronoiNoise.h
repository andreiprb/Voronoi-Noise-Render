#pragma once

#include <math.h>

#include "color_vectors.h"
#include "Renderer.h"

class Renderer;

class VoronoiNoise
{
    static float euclidianDistance(const int& x, const int& y, const pixel2& center);
    static float manhattanDistance(const int& x, const int& y, const pixel2& center);
    static color obtainColor(const std::pair<float, color>* distances, char aspect_index3, char aspect);
    static color generateColor(char aspect);
public:
    static void Algorithm(Renderer& r, const int& aspect_index1, const bool& aspect_index2, const char& aspect_index3, char aspect);
};