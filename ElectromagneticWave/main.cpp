#include "WaveViewer.h"
#include "FreeSpaceFDTD.h"
#include "WaveguideFDTD.h"

int main()
{
    //FreeSpaceFDTD g(MODE::TRANSVERSE_ELECTRIC, 100, 100, 5.0E-7, 500, 500, 50, 50, 10);
    //g.render(1000, 1000);


    WaveguideFDTD x(MODE::TRANSVERSE_ELECTRIC, 200, 100, 5.0E-7, 1000, 500);
    x.render(2000, 1000);
}