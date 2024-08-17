#pragma once
#include "SFML/Graphics.hpp"
#include "WaveField.h"

class WaveViewer
{
private: /* window */
	sf::RenderWindow window;

private: /* config */
	unsigned int width = 512;
	unsigned int height = 512;

private: /* derived */
	double scale = 1.0;

public: /* constructor */
	WaveViewer(unsigned int _width, unsigned int _height);

private: /* display */
	bool setColorScale(const WaveField& _field);
	double calcColorScale(double _rval) const;
	sf::Color calcColorGradient(double _nval) const;

public: /* public use */
	bool drawField(const WaveField& _field);
	bool display();
	
};