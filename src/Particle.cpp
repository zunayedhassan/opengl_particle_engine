#include "Particle.h"

Particle::Particle(int ID)
{
    this->id = ID;

    this->totalLife  = 1.0f;
    this->life       = 1.0f;

    this->alpha      = 1.0f;
    this->size       = 1.0f;

    this->bounciness = 0.9f;

    this->active     = true;

    this->lastTime   = -1;
}

void Particle::Update(long time)
{
    if (!active)
    {
        return;
    }

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    if (this->lastTime == -1)
    {
        this->lastTime = time;
    }

    float change = (float) (time - this->lastTime) / 1000.0f;

    this->velocity += this->acceleration * change;
    this->position += this->velocity * change;

    float x = this->position.x;
    float y = this->position.y;
    float z = this->position.z;

    // Rotation around X
    this->Rotate(this->rotation.x * time / 1000.0f, y, z);

    // Rotation around Y
    this->Rotate(this->rotation.y * time / 1000.0f, x, z);

    // Rotation around Z
    this->Rotate(this->rotation.z * time / 1000.0f, x, y);

    if (this->position.y < 0.0f)
    {
        this->velocity.y = this->velocity.y * -this->bounciness;
        this->position.y = 0.0f;
    }

    const float fadeTime = 0.2f;

    if ((this->totalLife - this->life) < fadeTime)
    {
        glColor4f(this->color.x, this->color.y, this->color.z, (this->totalLife - this->life) / fadeTime * this->alpha);
    }
    else if (this->life < 1.0f)
    {
        glColor4f(this->color.x, this->color.y, this->color.z, this->life * this->alpha);
    }
    else
    {
        glColor4f(this->color.x, this->color.y, this->color.z, this->alpha);
    }

    glTranslatef(x, y, z);

    float modelView[16];

    glGetFloatv(GL_MODELVIEW_MATRIX, modelView);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (i == j)
            {
                modelView[i * 4 + j] = 1.0f;
            }
            else
            {
                modelView[i * 4 + j] = 0.0f;
            }
        }
    }

    glLoadMatrixf(modelView);

    if (this->id % 5 == 0)
    {
        glRotatef(this->life *  100.0f, 0, 0, 1);
    }
    else
    {
        glRotatef(this->life * -100.0f, 0, 0, 1);
    }


    glBegin(GL_TRIANGLE_STRIP);

        glTexCoord2f(1, 1);
        glVertex3f( this->size,  this->size, 0);

        glTexCoord2f(0, 1);
        glVertex3f(-this->size,  this->size, 0);

        glTexCoord2f(1, 0);
        glVertex3f(this->size,  -this->size, 0);

        glTexCoord2f(0, 0);
        glVertex3f(-this->size, -this->size, 0);

    glEnd();

    this->life -= change;

    if (this->life <= 0.0f)
    {
        this->active = false;
    }

    this->lastTime = time;

    glPopMatrix();
}

void Particle::Rotate(float angle, float &x, float &y)
{
    float finalX = x * cos(angle) - y * sin(angle);
    float finalY = y * cos(angle) + x * sin(angle);

    x = finalX;
    y = finalY;
}
