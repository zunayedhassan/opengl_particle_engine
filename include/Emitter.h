#ifndef EMITTER_H
#define EMITTER_H

#include "GLEngine.h"
#include "Particle.h"
#include "Vector3.h"


class Emitter
{
    public:
        Emitter();
        ~Emitter();

        void Update(long time);
        void setTexture(Texture *tex);

    protected:
        void addParticle();

        float frand(float start = 0.0f, float end = 1.0f);

    public:
        list<Particle *> particles;

        Texture *texture;

        long lastTime;

        // Attributes
        float emissionRate;
        float emissionRadius;

        float life;
        float lifeRange;

        float size;
        float sizeRange;

        float saturation;
        float alpha;

        float spread;

        float gravity;

        Vector3 position;
        Vector3 wind;
        Vector3 rotation;
};

#endif // EMITTER_H
