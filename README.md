# Voronoi Noise Render

C++ SFML Voronoi Noise Render

Call voronoi function: VoronoiNoise::Algorithm(renderer, number_of_seeds, gridded_spread, distance_mode, mode)

gridded_spread is a boolean parameter, which spreads the seeds evenly when true, and randomly when false.

distance_mode is a character with the modes: 'm' - manhattan distance, 'e' - euclidian distance(the one we are used to)

Modes: 'g' - grayscale(clouds), 'c' - cellular(red), 'p' - patches, 'b' - biomes(similar to patches but from a defined color vector), 's' - shell(turtle shell, use only with gridded spread and euclidian distance)

SFML instalation guide, from Zipped: https://www.youtube.com/watch?v=VWWSc2nqrEA&t=1s
