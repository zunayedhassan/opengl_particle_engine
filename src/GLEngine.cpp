#include "GLEngine.h"

const GLint fontSize  = 16;
const GLint fontSpace = 9;

string GLEngine::resourcePath = "";

GLEngine::GLEngine()
{
    //ctor
}

GLEngine::~GLEngine()
{
    //dtor
}

GLvoid GLEngine::Uninitialize()
{
    delete GLEngine::getEngine();
}

GLEngine* GLEngine::getEngine()
{
    static GLEngine *engine = new GLEngine();

    return engine;
}

GLvoid GLEngine::Initialize(GLint width, GLint height, string resourcePath)
{
    GLEngine::resourcePath = resourcePath;

    Light::Initialize();

    this->fontTexture = new Texture(GLEngine::resourcePath + "font.tga");
    this->buildTextureFont();
}

GLvoid GLEngine::buildTextureFont()
{
    this->fontBase = glGenLists(256);

    glBindTexture(GL_TEXTURE_2D, this->fontTexture->texID);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    for (GLint i = 0; i < 256; i++)
    {
        GLfloat cx = (GLfloat) (i % 16) / 16.0f;
        GLfloat cy = (GLfloat) (i / 16) / 16.0f;

        glNewList(this->fontBase + i, GL_COMPILE);

        glBegin(GL_QUADS);

            glTexCoord2f(cx,                  1 - cy - 0.0625);     // 0.0625 = 1 / 16
            glVertex2i(0, fontSize);

            glTexCoord2f(cx + 0.0625,         1 - cy - 0.0625);
            glVertex2i(fontSize, fontSize);

            glTexCoord2f(cx + 0.0625,         1 - cy         );
            glVertex2i(fontSize, 0);

            glTexCoord2f(cx,                  1 - cy         );
            glVertex2i(0, 0);

        glEnd();

        glTranslated(fontSpace, 0, 0);

        glEndList();
    }
}

GLvoid GLEngine::drawText(GLint x, GLint y, const char *in_text, ...)
{
    char text[256];

    va_list ap;

    va_start(ap, in_text);
        vsprintf(text, in_text, ap);
    va_end(ap);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glBindTexture(GL_TEXTURE_2D, this->fontTexture->texID);

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    glLoadIdentity();

    glTranslated(x, y, 0);

    glListBase(this->fontBase - 32);
    glCallLists((GLuint) strlen(text), GL_BYTE, text);

    glMatrixMode(GL_MODELVIEW);

    glPopMatrix();
}

GLuint GLEngine::getTextWidth(const char *text)
{
    return ((strlen(text) + 1) * fontSpace);
}

GLuint GLEngine::getTextHeight()
{
    return fontSize;
}
