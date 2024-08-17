#pragma once
#include "FDTD.h"

class TestFDTD : public FDTD
{
	bool solve() override;

public:
	void test();
};