#include "../Header/ending.h"

Ending::Ending(int backPic, const Counter & ctr)
:backPic(backPic), ctr(ctr){}

Ending::~Ending()
{

}

void Ending::addPic(Counter showTime, Pic * newPic)
{
    showTimes.push_back(showTime);
    pics.push_back(newPic);
}

void Ending::draw()
{
    DrawGraph(0, 0, backPic, TRUE);
    for(unsigned int i = 0; i < pics.size(); i++)
    {
        Pic * tmp = pics.at(i);
        if(ctr >= showTimes.at(i) && tmp -> getShowState())
        {
            tmp -> draw();
        }
        /*
        else if(!(tmp -> getShowState()))
        {
            showTimes.erase(showTimes.begin() + i);
            pics.erase(pics.begin() + i);
            delete tmp;
        }
        */
    }
}