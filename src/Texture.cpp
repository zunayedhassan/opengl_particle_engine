#include "Texture.h"

vector<Texture*> Texture::textures;

Texture::Texture(string in_filename, string in_name, int in_mode)
{
    this->imageData = NULL;

    this->loadTGA(in_filename);

    this->name = in_name;
    textures.push_back(this);

    this->mode = in_mode;
}

Texture::~Texture()
{
    for (vector<Texture*>::iterator it = textures.begin(); it != textures.end(); it++)
    {
        if ((*it) == this)
        {
            textures.erase(it);
        }
    }

    if (this->imageData)
    {
        delete this->imageData;
    }
}

bool Texture::loadTGA(string filename)
{
    TGA_Header TGAheader;

    ifstream file(filename.data(), std::ios_base::binary);

    if (!file.is_open())
    {
        std::cout << "ERROR: Can't open file \'" << filename << "\'" << std::endl;
        return false;
    }

    if(!file.read((char*) &TGAheader, sizeof(TGAheader)))
    {
        std::cout << "ERROR: Can't read TGA Header" << std::endl;
        return false;
    }

    if (TGAheader.ImageType != 2)
    {
        std::cout << "ERROR: Something wrong with image type" << std::endl;
        return false;
    }

    this->width = TGAheader.ImageWidth;
    this->height = TGAheader.ImageHeight;
    this->bpp = TGAheader.PixelDepth;

    if ((this->width <= 0) || (this->height <= 0) || ((this->bpp != 24) && (this->bpp != 32)))
    {
        std::cout << "ERROR: Something wrong with image width or height or image color format has problem" << std::endl;
        return false;
    }

    GLuint type = GL_RGBA;

    if (this->bpp == 24)
    {
        type = GL_RGB;
    }

    GLuint bytesPerPixel = this->bpp / 8;
    GLuint imageSize = this->width * this->height * bytesPerPixel;

    this->imageData = new GLubyte[imageSize];

    if (this->imageData == NULL)
    {
        std::cout << "ERROR: Not enough memory" << std::endl;
        return false;
    }

    if(!file.read((char*) this->imageData, imageSize))
    {
        std::cout << "ERROR: Can't read image data" << std::endl;

        delete this->imageData;

        return false;
    }

    // BGR --> RGB
    for (GLuint i = 0; i < (unsigned int) imageSize; i += bytesPerPixel)
    {
        GLuint temp = this->imageData[i];
        this->imageData[i] = this->imageData[i + 2];
        this->imageData[i + 2] = temp;
    }

    this->createTexture(this->imageData, this->width, this->height, type);

    // Everything Worked!!!
    return true;
}

bool Texture::createTexture(unsigned char* imageData, int width, int height, int type)
{
    glGenTextures(1, &(this->texID));
    glBindTexture(GL_TEXTURE_2D, this->texID);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, imageData);

    return true;
}

int Texture::getMode()
{
    return this->mode;
}
