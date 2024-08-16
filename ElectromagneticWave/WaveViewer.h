#pragma once
#include "SFML/Graphics.hpp"

class WaveViewer
{
private: /* window */
	sf::RenderWindow window;

private: /* config */
	unsigned int width = 512;
	unsigned int height = 512;

public: /* constructor */
	WaveViewer(unsigned int _width, unsigned int _height);
};