#include "WaveViewer.h"

WaveViewer::WaveViewer(unsigned int _width, unsigned int _height)
{
	width = _width;
	height = _height;
}

bool WaveViewer::drawField(const WaveField& _field)
{
	sf::Vector2u size = window.getSize();

	unsigned long long rows = _field.getNX();
	unsigned long long cols = _field.getNY();

	if (rows <= 0) return false;
	if (cols <= 0) return false;

	//setColorScale(_field);

	float cx = (float)size.x / (float)rows;
	float cy = (float)size.y / (float)cols;

	sf::RectangleShape cell(sf::Vector2f(cx, cy));

	for (unsigned long long i = 0; i < rows; ++i)
	{
		for (unsigned long long j = 0; j < cols; ++j)
		{
			cell.setPosition((float)i * cx, (float)j * cy);
			cell.setFillColor(calcColorGradient(calcColorScale(_field.getField(i, j).z())));

			window.draw(cell);
		}
	}

	return true;
}

bool WaveViewer::setColorScale(const WaveField& _field)
{
	scale = 0.0;

	unsigned long long rows = _field.getNX();
	unsigned long long cols = _field.getNY();

	for (unsigned long long i = 0; i < rows; ++i)
	{
		for (unsigned long long j = 0; j < cols; ++j)
		{
			if (scale < fabs(_field.getField(i, j).z()))
			{
				scale = fabs(_field.getField(i, j).z());
			}
		}
	}

	return true;
}

double WaveViewer::calcColorScale(double _rval) const
{
	if (scale > 0)
	{
		return _rval / scale;
	}

	else
	{
		return 0.0;
	}
}

sf::Color WaveViewer::calcColorGradient(double _nval) const
{
	return sf::Color((sf::Uint8)(255.0 * _nval), 0, (sf::Uint8)(255.0 * (1.0 - _nval)));
}

bool WaveViewer::display(const WaveField& _field)
{
	auto func = [&]()
	{
		window.create(sf::VideoMode(width, height), "Electromagnetic Field Distribution Viewer");

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}

				if (event.type == sf::Event::Resized)
				{
					sf::FloatRect visa(0, 0, event.size.width, event.size.height);
					window.setView(sf::View(visa));
				}
			}

			drawField(_field);
			window.display();
		}
	};

	std::thread trd = std::thread(func);
	trd.detach();

	return true;
}
