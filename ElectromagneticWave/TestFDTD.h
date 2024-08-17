#pragma once
#include "FDTD.h"

class TestFDTD : public FDTD
{
	// FDTD을(를) 통해 상속됨
	bool solve() override;
};