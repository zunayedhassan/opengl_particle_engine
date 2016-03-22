#include "Control.h"

list<Control *> Control::controls;

Control::Control(int positionX, int positionY, int w, int h)
{
    Control::controls.push_back(this);

    this->setPosition(positionX, positionY);

    this->width = w;
    this->height = h;
}

Control::~Control()
{
    Control::controls.remove(this);
}

bool Control::updateControl(MouseState &state)
{
    int x = state.x;
    int y = state.y;

    this->inside = false;

    if ((x >= this->posX) && (x <= this->posX + width ) &&
        (y >= this->posY) && (y <= this->posY + height))
    {
        this->inside = true;
    }

    return false;
}

void Control::setPosition(int x, int y)
{
    this->posX = x;
    this->posY = y;
}

void Control::setSize(int w, int h)
{
    this->width = w;
    this->height = h;
}

int Control::getWidth()
{
    return this->width;
}

int Control::getHeight()
{
    return this->height;
}

Control* addControl(Control *control)
{
    static int lastX = 5;
    static int lastY = 5;

    control->setPosition(lastX, lastY);

    lastY += control->getHeight() + 5;

    return control;
}
