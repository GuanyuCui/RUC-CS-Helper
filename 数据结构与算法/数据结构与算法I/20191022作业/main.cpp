#include "calculator.h"

int main(int argc, char * argv[])
{
    Calculator<double> c;
    c.printLogo();
    c.printUsage();
    return 0;
}