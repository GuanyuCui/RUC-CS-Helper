#include "calculator.h"

int main(int argc, char * argv[])
{
    Calculator<int> c;
    c.printLogo();
    c.printUsage();
    return 0;
}