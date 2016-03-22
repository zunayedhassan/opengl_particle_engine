#include "Button.h"

Button::Button(string lbl, int positionX, int positionY, int width, int height) : Control(positionX, positionY, width, height)
{
    this->label = lbl;
    this->down = false;
}

bool Button::updateControl(MouseState &state)
{
    Control::updateControl(state);

    if (this->inside == true)
    {
        if (state.LeftButtonDown)
        {
            this->down = true;
        }
        else if (this->down)
        {
            this->down = false;

            return true;
        }
    }

    return false;
}

void Button::drawControl()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_TEXTURE_2D);

    glColor4f(0.7f, 0.7f, 0.7f, 0.8f);

    glBegin(GL_QUADS);

        glVertex2d(this->posX + this->width, this->posY               );
        glVertex2d(this->posX,               this->posY               );
        glVertex2d(this->posX,               this->posY + this->height);
        glVertex2d(this->posX + this->width, this->posY + this->height);

    glEnd();

    if (this->inside)
    {
        glColor4f(0.2f, 0.2f, 0.7f, 0.5f);
        glLineWidth(3.0f);
    }
    else
    {
        glColor4f(0.2f, 0.2f, 0.7f, 0.0f);
        glLineWidth(2.0f);
    }

    glBegin(GL_LINE_STRIP);

        glVertex2d(this->posX + this->width, this->posY               );
        glVertex2d(this->posX,               this->posY               );
        glVertex2d(this->posX,               this->posY + this->height);
        glVertex2d(this->posX + this->width, this->posY + this->height);
        glVertex2d(this->posX + this->width, this->posY               );

    glEnd();

    glColor4f(0.7f, 0.7f, 0.7f, 1.0f);

    int textX = posX + (this->width  - iGLEngine->getTextWidth (this->label.data())) / 2;
    int textY = posY + (this->height - iGLEngine->getTextHeight()) / 2;

    if (this->inside)
    {
        glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
    }
    else
    {
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    }

    iGLEngine->drawText(textX, textY, label.data());
}

string Button::getType()
{
    return "Button";
}

string Button::getLabel()
{
    return this->label;
}
