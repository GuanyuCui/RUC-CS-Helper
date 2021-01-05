#ifndef UTIL_H
#define UTIL_H

#include "DxLib.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <string>
#include <array>
#include <vector>

//屏幕长宽
const int SCREEN_X = 960;
const int SCREEN_Y = 720;

//帧率
const float FPS = 60.0f;

//
template <size_t N>
class MyVectorND
{
    public:
        //构造
        MyVectorND()
        {
            for(size_t i = 0; i < N; i++)
            {
                v[i] = 0.0f;
            }
        }
        MyVectorND(const MyVectorND<N> & u)
        : v(u.v){} 

        MyVectorND(const std::array<float, N> & u)
        : v(u){} 

        // 赋值
        MyVectorND<N> & operator = (MyVectorND<N> u)
        {
            v = u.v;
            return *this;
        }

        //加法
        MyVectorND<N> operator + (MyVectorND<N> vec)
        {
            MyVectorND<N> ret(v);
            for(size_t i = 0; i < N; i++)
            {
                ret.v[i] += vec.v[i];
            }
            return ret;
        }
        //减法
        MyVectorND<N> operator - (MyVectorND<N> vec)
        {
            MyVectorND<N> ret(v);
            for(size_t i = 0; i < N; i++)
            {
                ret.v[i] -= vec.v[i];
            }
            return ret;
        }
        // 数乘
        MyVectorND<N> operator * (float a)
        {
            std::array<float, N> ret(v);
            for(size_t i = 0; i < N; i++)
            {
                ret.v[i] *= a;
            }
            return ret;
        }
        //点乘
        float operator * (MyVectorND<N> u)
        {
            float ret = 0.0f;
            for(size_t i = 0; i < N; i++)
            {
                ret += v[i] * u.v[i];
            }
            return ret;
        }

        float operator [] (size_t i)
        {
            return v[i];
        }

        float norm()
        {
            float ret = 0;
            for(size_t i = 0; i < N; i++)
            {
                ret += (v[i]) * (v[i]);
            }
            return std::sqrt(ret);
        }

        std::array<float, N> to_array()
        {
            return v;
        }
    private:
        std::array<float, N> v;
};

template <size_t N>
MyVectorND<N> operator * (float a, MyVectorND<N> vec)
{
    std::array<float, N> arr(vec.to_array());
    for(size_t i = 0; i < N; i++)
    {
        arr[i] *= a;
    }
    return MyVectorND<N>(arr);
}

class Sound
{
    public:
        Sound(const char * fileName, int playType);
        ~Sound();
        void play();
        void stop();
    private:
        bool isPlaying;
        int soundHandle;
        int playType;
};

#endif