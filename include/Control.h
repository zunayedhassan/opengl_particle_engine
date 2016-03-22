#ifndef CONTROL_H
#define CONTROL_H

#include <list>
#include <string>

#include "GLEngine.h"

using std::list;
using std::string;

struct MouseState
{
    int LeftButtonDown;
    int RightButtonDown;
    int MiddleButtonDown;

    int x;
    int y;

    MouseState()
    {
        this->LeftButtonDown = 0;
        this->RightButtonDown = 0;
        this->MiddleButtonDown = 0;

        this->x = 0;
        this->y = 0;
    }
};

class Control
{
    public:
        static list<Control *> controls;

    public:
        Control(int positionX, int positionY, int width, int height);
        virtual ~Control();

        virtual bool updateControl(MouseState &state);
        virtual void drawControl() = 0;
        virtual string getType() = 0;

        void setPosition(int x, int y);
        void setSize(int width, int height);

        int getWidth();
        int getHeight();


    protected:
        bool inside;

        int posX, posY;
        int width, height;
};

Control* addControl(Control *control);

#endif // CONTROL_H
