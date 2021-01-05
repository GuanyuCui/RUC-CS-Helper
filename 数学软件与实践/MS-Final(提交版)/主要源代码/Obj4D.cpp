#include "util.h"
#include "Obj4D.h"

extern float nowW;

Object4D::Object4D(MyVectorND<4> v, float m)
        : velocity(v), mass(m) {}
Object4D::~Object4D(){}

Sphere4D::Sphere4D(MyVectorND<4> _center, float _radius, 
            MyVectorND<4> _velocity, float _mass, int _color)
    : Object4D(_velocity, _mass), center(_center), radius(_radius), color(_color){}

Sphere4D::Sphere4D(const Sphere4D & obj)
: Object4D(obj.velocity, obj.mass), center(obj.center), radius(obj.radius), color(obj.color){}

Sphere4D::~Sphere4D(){}

void Sphere4D::move()
{
    // 每帧增加
    center = center + (1 / FPS) * velocity;
}

// 摄像机默认认为是 w = 0
void Sphere4D::draw()
{
    if(radius * radius - (nowW - center[3]) * (nowW - center[3]) >= 0)
    {
        DrawSphere3D(
            VGet(center[0], center[1], center[2]),
            std::sqrt(radius * radius - (nowW - center[3]) * (nowW - center[3])),
            32,
            color,
            GetColor(255, 255, 255),
            TRUE
            );
    }
    else
    {}
}

bool Sphere4D::collideWith(Object4D * another)
{
    if(typeid(*another) == typeid(Sphere4D))
    {
        Sphere4D * obj = dynamic_cast<Sphere4D *>(another);
        // 连心线
        MyVectorND<4> centerVec(obj -> center - center);

        if(centerVec.norm() > radius + obj -> radius)
        {
            return false;
        }

        //速度分解
        // v1_//
        MyVectorND<4> v1_parallel( (velocity * centerVec / centerVec.norm()) * (1 / centerVec.norm() * centerVec) );
        // v1_vertical
        MyVectorND<4> v1_vertical(velocity - v1_parallel);
        // v2_//
        MyVectorND<4> v2_parallel( (obj -> velocity * centerVec / centerVec.norm()) * (1 / centerVec.norm() * centerVec) );
        // v2_vertical
        MyVectorND<4> v2_vertical(obj -> velocity - v2_parallel);

        // 碰撞公式
        MyVectorND<4> v1_parallel_new = (1 / (mass + obj -> mass)) * ( (mass - obj -> mass) * v1_parallel + 2 * obj -> mass * v2_parallel );
        MyVectorND<4> v2_parallel_new = (1 / (mass + obj -> mass)) * ( 2 * mass * v1_parallel + (obj -> mass - mass) * v2_parallel );

        // 速度合成
        velocity = v1_parallel_new + v1_vertical;
        obj -> velocity = v2_parallel_new + v2_vertical;
        return true;
    }
    else
    {
        return false;
    }
}