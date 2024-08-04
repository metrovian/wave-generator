#pragma once
#include "FDTD.h"

class PipeFDTD : public FDTD
{
protected: /* virtual */
	bool solve() override;
};