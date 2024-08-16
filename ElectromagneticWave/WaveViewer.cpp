#include "WaveViewer.h"

WaveViewer::WaveViewer(unsigned int _width, unsigned int _height)
{
	width = _width;
	height = _height;

	window.create(sf::VideoMode(_width, _height), "Wave Generator Viewer Test");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.display();
	}

}
