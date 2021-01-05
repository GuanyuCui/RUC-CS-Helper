#ifndef OBJ4D_H
#define OBJ4D_H
#include "util.h"

// 4 维物体抽象类
class Object4D
{
    public:
        Object4D(MyVectorND<4> v, float m);
        virtual ~Object4D() = 0;
        // 纯虚函数
        virtual void move() = 0;
        virtual void draw() = 0;
        virtual bool collideWith(Object4D * obj) = 0;
    protected:
        // 质量
        float mass;
        // 速度
        MyVectorND<4> velocity;
        // 加速度
        // ...
};

// 演示无外力作用下 4 维超球的对心弹性碰撞
class Sphere4D : public Object4D
{
    public:
        // (x-x_0)^2 + (y-y_0)^2 + ... = radius ^ 2
        Sphere4D(MyVectorND<4> _center, float _radius, 
            MyVectorND<4> _velocity, float _mass, int color = GetColor(255, 0, 0));
        Sphere4D(const Sphere4D & obj);
        ~Sphere4D();
        void move();
        void draw();
        bool collideWith(Object4D * obj);
    private:
        // 球心
        MyVectorND<4> center;
        // 半径
        float radius;
        // 颜色
        int color;
};
#endif