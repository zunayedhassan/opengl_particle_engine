#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector3.h"
#include "GLEngine.h"


class Particle
{
    public:
        Particle(int ID);

        void Update(long time);

    private:
        void Rotate(float angle, float &x, float &y);

    public:
        long lastTime;

        int id;

        Vector3 color;

        Vector3 position;
        Vector3 velocity;
        Vector3 acceleration;
        Vector3 rotation;

        float totalLife;
        float life;

        float alpha;
        float size;

        float bounciness;

        bool active;
};

#endif // PARTICLE_H
