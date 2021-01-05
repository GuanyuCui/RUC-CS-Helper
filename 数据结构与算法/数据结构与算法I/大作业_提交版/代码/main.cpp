#include "solution.h"
int main(int argc, char * argv[])
{
    //解决方案
    Solution s;
    //打印Logo
    s.printLogo();
    //加载数据
    if(!s.loadData())
    {
        return 0;
    }
    //主界面建立
    s.printUsage();
    //主过程——用户操作
    s.mainProc();
    return 0;
}