#include "Emitter.h"

Emitter::Emitter()
{
    this->lastTime          = -1;

    this->texture           = NULL;

    this->emissionRate      = 30.0f;         // 30 particle per second
    this->emissionRadius    = 0.0f;

    this->life              = 2.0f;
    this->lifeRange         = 0.5f;

    this->size              = 5.0f;
    this->sizeRange         = 2.0f;

    this->saturation        = 1.0f;
    this->alpha             = 0.5f;

    this->spread            = 1.0f;

    this->gravity           = 0.0f;         // No gravity, so they will be going up
}

Emitter::~Emitter()
{
    for (list<Particle *>::iterator it = this->particles.begin(); it != this->particles.end(); it++)
    {
        delete (*it);
    }
}

void Emitter::Update(long time)
{
    if (this->texture == NULL)
    {
        return;
    }

    if (this->lastTime == -1)
    {
        this->lastTime = time;
    }

    int numberOfEmission = (int) (time - this->lastTime) / 1000.0f * this->emissionRate;

    for (int i = 0; i < numberOfEmission; i++)
    {
        addParticle();
    }

    if (numberOfEmission > 0)
    {
        this->lastTime = time;
    }

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(this->position.x, this->position.y, this->position.z);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->texture->texID);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);

    if (this->texture->getMode() == MODE_DARKEN)
    {
        glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_COLOR);

        glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB_EXT, GL_PREVIOUS_EXT);
        glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB_EXT, GL_SRC_ALPHA);
    }
    else if (this->texture->getMode() == MODE_NORMAL)
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB_EXT, GL_PREVIOUS_EXT);
        glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB_EXT, GL_SRC_COLOR);
    }

    for (list<Particle *>::iterator it = this->particles.begin(); it != this->particles.end(); it++)
    {
        Particle *particle = (*it);

        particle->acceleration.y = -this->gravity;
        particle->acceleration += this->wind;
        particle->alpha = this->alpha;
        particle->rotation = this->rotation;

        particle->Update(time);

        if (particle->active == false)
        {
            delete particle;

            list<Particle *>::iterator pTemp = it--;
            this->particles.erase(pTemp);
        }
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glMatrixMode(GL_MODELVIEW);

    glPopMatrix();
}

void Emitter::setTexture(Texture *tex)
{
    this->texture = tex;
}

void Emitter::addParticle()
{
    Particle *particle = new Particle((int) this->particles.size());

    float r = this->frand() * this->saturation + (1 - this->saturation);
    float g = this->frand() * this->saturation + (1 - this->saturation);
    float b = this->frand() * this->saturation + (1 - this->saturation);

    particle->color = Vector3(r, g, b);

    particle->life = frand(this->life - this->lifeRange, this->life + this->lifeRange);
    particle->totalLife = particle->life;

    particle->velocity = Vector3(frand(-spread, spread), frand(3, 20), frand(-spread, spread));
    particle->acceleration = Vector3(0.0f, -this->gravity, 0.0f);

    particle->size = frand(this->size - this->sizeRange, this->size + this->sizeRange);

    particle->position.x = frand(-this->emissionRadius, this->emissionRadius);
    particle->position.z = frand(-this->emissionRadius, this->emissionRadius);

    this->particles.push_back(particle);
}

float Emitter::frand(float start, float end)
{
    float num = (float) rand() / (float) RAND_MAX;

    return (start + (end - start) * num);
}
