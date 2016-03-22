#ifndef LIGHT_H
#define LIGHT_H

#include <vector>

// If this is Mac OS
#ifdef __APPLE__
	#include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
// Otherwise, for Linux and Windows OS
#else
	#include <GL/gl.h>
    #include <GL/glu.h>
#endif

using namespace std;

enum LIGHT_TYPE
{
    LIGHT_SPOT,
    LIGHT_POINT,
    LIGHT_DIRECTIONAL
};

class Light
{
    public:
        Light(LIGHT_TYPE light_type);
        ~Light();

        static GLvoid Initialize();

        GLvoid Visible(bool value = true);
        GLvoid setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
        GLvoid setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
        GLvoid setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
        GLvoid setLightType(LIGHT_TYPE type);
        GLvoid setPosition(GLfloat x, GLfloat y, GLfloat z);

        // Set spot light specific member function
        GLvoid setSpotDirection(GLfloat x, GLfloat y, GLfloat z);
        GLvoid setCutoff(GLfloat value);
        GLvoid setExponent(GLfloat value);

        GLvoid setAttenuation(GLfloat constant, GLfloat linear, GLfloat quadratic);

        GLint getLightNum();
        GLvoid updateLight();

        static GLint numLights;
        static vector<GLint> availableLights;
        static vector<Light *> lights;

    private:
        GLfloat position[4];
        GLfloat diffuse[4];
        GLfloat ambient[4];
        GLfloat specular[4];
        GLfloat spotDirection[4];

        GLfloat cutoff;
        GLfloat exponent;

        bool    visible;
        GLint   lightType;

        GLint   lightNum;
};

#endif // LIGHT_H
