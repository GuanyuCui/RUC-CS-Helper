#ifndef ENDING_H
#define ENDING_H

#include "../Header/tools.h"

class Ending
{
    public:
        Ending(int backPic,const Counter & ctr);
        ~Ending();
        void addPic(Counter showTime, Pic * newPic);
        void draw();
    private:
        int backPic;
        //图片出现时间的Vector
        std::vector<Counter> showTimes;
        //多态
        std::vector<Pic *> pics;
        //计时器引用
        const Counter & ctr;
};
#endif