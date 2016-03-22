#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <vector>
#include <fstream>

// If this is Mac OS
#ifdef __APPLE__
	#include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
// Otherwise, for Linux and Windows OS
#else
	#include <GL/gl.h>
    #include <GL/glu.h>
#endif

using std::string;
using std::vector;
using std::ifstream;

enum TEXTURE_MODE
{
    MODE_NORMAL,
    MODE_DARKEN
};

struct TGA_Header
{
    GLubyte     ID_Length;
    GLubyte     ColorMapType;
    GLubyte     ImageType;
    GLubyte     ColorMapSpecification[5];
    GLshort     xOrigin;
    GLshort     yOrigin;
    GLshort     ImageWidth;
    GLshort     ImageHeight;
    GLubyte     PixelDepth;
};

class Texture
{
    // Member functions
    public:
        Texture(string in_filename, string in_name = "", int in_mode = MODE_NORMAL);
        ~Texture();

        int getMode();

    // Variables
    public:
        unsigned char* imageData;
        unsigned int   bpp;
        unsigned int   width;
        unsigned int   height;
        unsigned int   texID;
        string         name;

        static vector<Texture*> textures;

    private:
        bool loadTGA(string filename);
        bool createTexture(unsigned char* imageData, int width, int height, int type);

    private:
        int  mode;

};

#endif // TEXTURE_H
