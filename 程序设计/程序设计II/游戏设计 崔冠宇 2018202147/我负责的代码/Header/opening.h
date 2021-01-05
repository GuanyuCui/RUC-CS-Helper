#ifndef OPENING_H
#define OPENING_H

#include "../Header/tools.h"
#include "../Header/dec3D.h"

//标题选项
class TitleChoice
{
    public:
        //构造函数
        TitleChoice(int x, int y, int fimg, int bimg);
        ~TitleChoice();
        //绘制
        void draw();
        //设置焦点
        void setFocus(bool flag);
    private:
        //是否是焦点所在
        bool isFocus;
        //坐标
        int x;
        int y;
        //图片(前景背景)
        Pic frontImg;
        Pic backImg;
};

const int decNum = 30;
class Opening
{
    public:
        //构造函数
        Opening(int backPic, int decPic0, int decPic1, KeyBoard & kbd);
        ~Opening();
        void addChoice(TitleChoice * newChoice);
        //绘制
        void draw();
        //根据输入操作(true: 成功, false: 失败)
        bool operate();
        void setFocus(unsigned int newFocus);
        unsigned int getFocus();
        unsigned int getChoiceNum();
    private:
        //背景图片
        int backImg;
        //装饰图片
        int decPic0;
        int decPic1;
        //选项容器
        std::vector <TitleChoice * > choices;
        //焦点所在
        unsigned int focus;
        unsigned int choiceNum;
        //操纵的键盘
        KeyBoard & kbd;
        std::array <Dec3D*, decNum> decs;
};

#endif