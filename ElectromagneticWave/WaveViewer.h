#pragma once
#include "SFML/Graphics.hpp"
#include "FDTD.h"

class WaveViewer
{
private: /* window */
	sf::RenderWindow window;
	sf::RectangleShape slider;
	sf::CircleShape knob;

private: /* config */
	unsigned int width = 512;
	unsigned int height = 512;
	
private: /* derived */
	double scale = 0.0;
	float kpos = 0.0;
	float minpos = 0.0;
	float maxpos = 0.0;
	float box = 0.0;
	float boy = 0.0;
	float rad = 0.0;
	size_t time = 0;

public: /* constructor */
	WaveViewer(unsigned int _width, unsigned int _height);

private: /* event */
	bool onMoveSliderKnob(const DataFDTD& _data);

private: /* display */
	bool draw(const DataFDTD& _data);
	bool drawField(const WaveField& _field);
	bool drawSlider();
	bool setColorScale(const WaveField& _field);
	double calcColorScale(double _rval) const;
	sf::Color calcColorGradient(double _nval) const;

public: /* public use */
	bool display(const DataFDTD& _data);
};