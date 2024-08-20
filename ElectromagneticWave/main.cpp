#include "WaveViewer.h"
#include "FreeSpaceFDTD.h"

int main()
{
    FreeSpaceFDTD g(MODE::TRANSVERSE_MAGNETIC, 100, 100, 1.0E-7, 512, 512);
    g.render(1000, 1000);
}