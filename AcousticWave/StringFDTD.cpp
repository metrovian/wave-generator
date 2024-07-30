#include "StringFDTD.h"

StringFDTD::StringFDTD(double _length, double _period, unsigned long long _numx, unsigned long long _numt, double _tension, double _density)
{
    setBasicCondition(sqrt(_tension / _density), _length, _period, _numx, _numt);
}

StringFDTD::StringFDTD(double _length, double _period, unsigned long long _numx, unsigned long long _numt, double _tension, double _density, double _decay)
{
    decay = _decay;
    setBasicCondition(sqrt(_tension / _density), _length, _period, _numx, _numt);
}

bool StringFDTD::solve()
{
    return false;
}
