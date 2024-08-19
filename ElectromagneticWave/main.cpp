#include "WaveViewer.h"
#include "FreeSpaceFDTD.h"

int main()
{
    FreeSpaceFDTD g(MODE::TRANSVERSE_ELECTRIC, 100, 100, 512, 512);
}