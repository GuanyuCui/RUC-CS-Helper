#include "../Header/opening.h"

//-----------------------class TitleChoice----------------------
TitleChoice::TitleChoice(int x, int y, int fimg, int bimg): x(x), y(y), frontImg(float(x), float(y), fimg, true, 17, 0), backImg(float(x), float(y), bimg), isFocus(false){}
TitleChoice::~TitleChoice()
{
    //DeleteGraph(frontImg);
    //DeleteGraph(backImg);
}

void TitleChoice::setFocus(bool flag)
{
    isFocus = flag;
}

void TitleChoice::draw()
{
    //两种情况, 一种是焦点（前景+背景图片）, 另一种不是焦点（仅背景）
    backImg.draw();
    if(isFocus)
    {
        frontImg.draw();
    }
}

Opening::Opening(int backImg, int decPic0, int decPic1, KeyBoard & kbd)
:backImg(backImg), decPic0(decPic0), decPic1(decPic1), focus(0), choiceNum(0), kbd(kbd)
{
    for (int i = 0; i < decNum; i++)
	{
        decs.at(i) = new Dec3D(decPic0, decPic1, 35);
	}
}

Opening::~Opening()
{
    unsigned int size = unsigned int(choices.size());
    //从内存删除图片
    for(unsigned int i = 0; i < size; i++)
    {
        delete choices.at(i);
    }
}

void Opening::addChoice(TitleChoice * newChoice)
{
    choices.push_back(newChoice);
    choiceNum++;
	if (choices.size() > 0)
	{
		choices.at(0)->setFocus(true);
	}
}

void Opening::draw()
{
    //绘制背景图片
    DrawGraph(0, 0, backImg, TRUE);
    for(int i = 0; i < decNum; i++)
    {
        decs.at(i) -> draw();
    }
    //遍历绘制标题选项
    unsigned int choiceNum = unsigned int(choices.size());
    for(unsigned int i = 0; i < choiceNum; i++)
    {
        choices.at(i) -> draw();
    }
}

bool Opening::operate()
{
    //当上键或左键被按下
    if(kbd.getState(KEY_INPUT_UP) == PRESS || kbd.getState(KEY_INPUT_LEFT) == PRESS)
    {
        choices.at(focus) -> setFocus(false);
        if(focus == 0)
        {
            focus += unsigned int(choices.size()); //Attention!
        }
        focus--;
        choices.at(focus) -> setFocus(true);
        return true;
    }
    //当下键或右键被按下
    else if(kbd.getState(KEY_INPUT_DOWN) == PRESS || kbd.getState(KEY_INPUT_RIGHT) == PRESS)
    {
        choices.at(focus) -> setFocus(false);
        if(focus == unsigned int(choices.size() - 1)) //Attention!
        {
            focus -= unsigned int(choices.size()); //Attention!
        }
        focus++;
        choices.at(focus) -> setFocus(true);
        return true;
    }
    return false;
}
void Opening::setFocus(unsigned int newFocus)
{
    choices.at(focus) -> setFocus(false);
    focus = newFocus;
    choices.at(focus) -> setFocus(true); 
}
unsigned int Opening::getFocus()
{
    return focus;
}
unsigned int Opening::getChoiceNum()
{
    return choiceNum;
}