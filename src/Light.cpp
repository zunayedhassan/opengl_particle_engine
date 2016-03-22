#include "Light.h"

GLint           Light::numLights        = 0;
vector<GLint>    Light::availableLights;
vector<Light *> Light::lights;

Light::Light(LIGHT_TYPE light_type)
{
    Light::lights.push_back(this);

    if (Light::availableLights.size() > 0)
    {
        Light::lightNum = Light::availableLights[0];

        Light::availableLights.erase(Light::availableLights.begin());

        this->Visible(true);

        this->setLightType(light_type);

        this->setAmbient (0, 0, 0, 1);
        this->setDiffuse (1, 1, 1, 1);
        this->setSpecular(1, 1, 1, 1);

        this->updateLight();
    }
    else
    {
        this->lightNum = 0;

        this->Visible(false);
    }
}

Light::~Light()
{
    if (this->lightNum != 0)
    {
        Light::availableLights.push_back(this->lightNum);
    }

    for (vector<Light *>::iterator currentLight = Light::lights.begin(); currentLight != Light::lights.end(); currentLight++)
    {
        if ((*currentLight) == this)
        {
            Light::lights.erase(currentLight);
        }
    }
}

GLvoid Light::Visible(bool value)
{

}

GLvoid Light::setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    this->ambient[0] = r;
    this->ambient[1] = g;
    this->ambient[2] = b;
    this->ambient[3] = a;

    glLightfv(this->lightNum, GL_AMBIENT, this->ambient);
}

GLvoid Light::setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    this->diffuse[0] = r;
    this->diffuse[1] = g;
    this->diffuse[2] = b;
    this->diffuse[3] = a;

    glLightfv(this->lightNum, GL_DIFFUSE, this->diffuse);
}

GLvoid Light::setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    this->specular[0] = r;
    this->specular[1] = g;
    this->specular[2] = b;
    this->specular[3] = a;

    glLightfv(this->lightNum, GL_SPECULAR, this->specular);
}

GLvoid Light::setLightType(LIGHT_TYPE type)
{
    this->lightType = type;

    if (this->lightType == LIGHT_SPOT)
    {
        this->position[3] = 1.0f;
    }
    else if (this->lightType == LIGHT_POINT)
    {
        this->position[3] = 1.0f;

        this->setCutoff(180.0f);
    }
    else if (this->lightType == LIGHT_DIRECTIONAL)
    {
        this->position[3] = 0.0f;
    }

    this->updateLight();
}

GLvoid Light::setPosition(GLfloat x, GLfloat y, GLfloat z)
{
    this->position[0] = x;
    this->position[1] = y;
    this->position[2] = z;

    glLightfv(this->lightNum, GL_POSITION, this->position);
}

// Set spot light specific member function
GLvoid Light::setSpotDirection(GLfloat x, GLfloat y, GLfloat z)
{
    this->spotDirection[0] = x;
    this->spotDirection[1] = y;
    this->spotDirection[2] = z;

    glLightfv(this->lightNum, GL_SPOT_DIRECTION, this->spotDirection);
}

GLvoid Light::setCutoff(GLfloat value)
{
    this->cutoff = value;

    glLightf(this->lightNum, GL_SPOT_CUTOFF, this->cutoff);
}

GLvoid Light::setExponent(GLfloat value)
{
    this->exponent = value;

    glLightf(this->lightNum, GL_SPOT_EXPONENT, this->exponent);
}

GLvoid Light::setAttenuation(GLfloat constant, GLfloat linear, GLfloat quadratic)
{
    glLightf(this->lightNum, GL_CONSTANT_ATTENUATION,  constant );
    glLightf(this->lightNum, GL_LINEAR_ATTENUATION,    linear   );
    glLightf(this->lightNum, GL_QUADRATIC_ATTENUATION, quadratic);
}

GLint Light::getLightNum()
{
    return this->lightNum;
}

GLvoid Light::updateLight()
{
    glLightfv(this->lightNum, GL_POSITION, this->position);
    glLightfv(this->lightNum, GL_SPOT_DIRECTION, this->spotDirection);
}

GLvoid Light::Initialize()
{
    glGetIntegerv(GL_MAX_LIGHTS, &(Light::numLights));

    for (int i = 0; i < Light::numLights; i++)
    {
        Light::availableLights.push_back(GL_LIGHT0 + i);
        glEnable(GL_LIGHT0 + i);
    }
}
