#ifndef GLENGINE_H
#define GLENGINE_H

#include <iostream>
#include <list>

// If this is Windows OS
#ifdef _WIN32
    #include <windows.h>
#endif // _WIN32

// If this is Mac OS
#ifdef __APPLE__
	#include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <OpenGL/glext.h>
// Otherwise, for Linux and Windows OS
#else
	#include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/glext.h>
#endif

#include "Texture.h"
#include "Light.h"

using namespace std;

#define iGLEngine GLEngine::getEngine()


class GLEngine
{
    public:
        GLEngine();
        ~GLEngine();

        static GLvoid Uninitialize();
        static GLEngine* getEngine();
        static string resourcePath;

        GLvoid Initialize(GLint width, GLint height, string resourcePath);

        GLvoid buildTextureFont();
        GLvoid drawText(GLint x, GLint y, const char *text, ...);
        GLuint getTextWidth(const char *text);
        GLuint getTextHeight();

    private:
        GLint fontBase;

        Texture *fontTexture;
};

#endif // GLENGINE_H
