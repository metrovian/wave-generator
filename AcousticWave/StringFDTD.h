#pragma once
#include "FDTD.h"

class StringFDTD : public FDTD
{
public: /* public use */
	bool solve(double _time) override;
};