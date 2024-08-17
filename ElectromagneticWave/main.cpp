#include "WaveViewer.h"

int main()
{
    WaveViewer s(1512, 512);
    WaveField k(MODE::TRANSVERSE_ELECTRIC, 10, 10, 10, 10);
    s.display(k);

    std::cout << "test" << std::endl;

    while (1)
    {

    }
    return 0;
}