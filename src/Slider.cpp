#include "Slider.h"

const int tickSize = 5;

Slider::Slider(string lbl, float in_min, float in_max, int positionX, int positionY, int width, int height) : Control(positionX, positionY, width, height)
{
    this->defaultValue = 0.0f;

    this->current = NULL;

    this->min = in_min;
    this->max = in_max;

    this->label = lbl;

    this->dragging = false;
}

void Slider::setValue(float *value)
{
    this->current = value;

    if (this->current != NULL)
    {
        this->defaultValue = *(this->current);
    }
}

bool Slider::updateControl(MouseState &state)
{
    Control::updateControl(state);

    int x = state.x;
    //int y = state.y;

    if (this->inside)
    {
        if (state.LeftButtonDown)
        {
            this->dragging = true;
        }

        if (state.RightButtonDown)
        {
            *(this->current) = this->defaultValue;
        }
    }

    if (!state.LeftButtonDown)
    {
        this->dragging = false;
    }

    if (dragging)
    {
        *(this->current) = (float) (x - this->posX) / (float) this->width * (this->max - this->min) + this->min;

        if (*(this->current) > this->max)
        {
            *(this->current) = this->max;
        }
        else if (*(this->current) < this->min)
        {
            *(this->current) = this->min;
        }
    }

    return this->dragging;
}

void Slider::drawControl()
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

    int currentX = (int) (*(this->current) - this->min) / (this->max - this->min) * (this->width - tickSize);

    glColor4f(0.3f, 0.3f, 1.0f, 0.5f);

    glBegin(GL_QUADS);

        glVertex2d(currentX + tickSize, this->posY               );
        glVertex2d(currentX,            this->posY               );
        glVertex2d(currentX,            this->posY + this->height);
        glVertex2d(currentX + tickSize, this->posY + this->height);

    glEnd();

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    string sliderText = this->label + this->_commonTools->GetStringFromNumber(*(this->current));

    iGLEngine->drawText(this->posX + 2, this->posY + 2, sliderText.data());
}

string Slider::getType()
{
    return "Slider";
}
