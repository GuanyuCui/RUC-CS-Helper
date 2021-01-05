#ifndef TOOLS_H
#define TOOLS_H

#include "DxLib.h"
#include <cmath>
#include <ctime>
#include <cstdio>
#include <algorithm>
#include <tuple>
#include <array>
#include <map>
#include <vector>
#include <string>

//屏幕长宽
const int SCREEN_X = 1024;
const int SCREEN_Y = 768;

const double PI = 3.14159265359;

//Counter 类型是ull
typedef unsigned long long Counter;

class Sound
{
    public:
        Sound(const char * fileName, int playType);
        Sound(int soundHandle, int playType);
        ~Sound();
        void play();
        void stop();
		int getHandle();
        bool getPlayingState();
    private:
        bool isPlaying;
        int soundHandle;
        int playType;
};

enum KeyState
{
    PRESS, HOLD, RELEASE, NOTPRESS
};
class KeyBoard
{
    public:
        KeyBoard();
        KeyState getState(int key);
    private:
        std::array <KeyState, 256> states;
};

//类模板
template <typename T>
class MyVector2D
{
    public:
        MyVector2D(T x, T y): x(x), y(y){}
        //获取分量
        T getX() const {return x;}
        T getY() const {return y;}
        //向量加减
        MyVector2D<T> & operator + (const MyVector2D<T> & vec)
        {
            x += vec.x;
            y += vec.y;
            return this;
        }
        MyVector2D<T> & operator - (const MyVector2D<T> & vec)
        {
            x -= vec.x;
            y -= vec.y;
            return this;
        }
    private:
        T x;
        T y;
};
//类模板
//辅助用数工具
template <typename T>
class RangedNum
{
    public:
        RangedNum(T _min, T _max, T _step, T _initData)
        :_min(_min), _max(_max), _step(_step), _data(_initData){}
        const T& getData() const { return _data; }
        virtual void operator++(int)
        {
            if(_data < _max - _step)
            {
                _data += _step;
            }
            else _data = _max;
        }
        virtual void operator--(int)
        {
            if(_data > _min + _step)
            {
                _data -= _step;
            }
            else _data = _min;
        }
    protected:
        //最小值
        T _min;
        //最大值
        T _max;
        //步长
        T _step;
        //实际数据
        T _data;
};
template class RangedNum<int>;
//来回变动的数据
template <typename T1>
class FloatNum : public RangedNum<T1>
{
    public:
        FloatNum(T1 _min, T1 _max, T1 _step, T1 _initData)
        :RangedNum<T1>(_min, _max, _step, _initData), isIncreasing(true){}
        void operator ++(int)
        {
            if(isIncreasing)
            {
                _data += _step;
                if(_data > _max)
                {
                    isIncreasing = false;
                    _data = _max - _step;
                }
            }
            else
            {
                _data -= _step;
                if(_data < _min)
                {
                    isIncreasing = true;
                    _data = _min + _step;
                }
            }
        }
    private:
        bool isIncreasing;
        void operator --(int){};
};
template FloatNum<int>;
//基类
class Pic
{
    public:
        Pic(float x, float y, int imgHandle, bool isBrt = false, unsigned int brtStep = 0, unsigned int initBrt = 255);
        virtual ~Pic();
        virtual void draw();
        virtual bool getShowState() const ;
    protected:
        float x;
        float y;
        int imgHandle;
        bool isBrt;
        FloatNum<int> brt;
        bool isShow;
};
//继承
class MovingPic : public Pic
{
    public:
        MovingPic(float x, float y, int showX1, int showY1, int showX2, int showY2, int imgHandle, float vx, float vy, bool isBrt = false, unsigned int brtStep = 0, unsigned int initBrt = 255);
        ~MovingPic();
        virtual void draw();
        virtual bool getShowState() const ;
    private:
        //图片消失的坐标
        int showX1;
        int showY1;
        int showX2;
        int showY2;
        
        MyVector2D<float> velocity;
};

#endif