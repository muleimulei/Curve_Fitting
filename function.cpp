#include "function.h"


double get1_1(double v)
{
    return 1;
}
double get1_2(double v)
{
    return v;
}


double get2_1(double v)
{
    return 1 / v;
}

GETVALUE BASEFUNC[2][3] =
{
    {get1_1, get1_2},
    {get2_1, get1_1, get1_2}
};
