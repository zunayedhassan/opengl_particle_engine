#ifndef SLIDER_H
#define SLIDER_H

#include "Control.h"
#include "CommonTools.h"

class Slider : public Control
{
    public:
        Slider(string lbl, float in_min, float in_max, int positionX, int positionY, int width, int height);

        void setValue(float *value);


        virtual bool updateControl(MouseState &state);
        virtual void drawControl();
        virtual string getType();

    protected:
        float defaultValue;

        float min;
        float max;
        float *current;

        string label;

        bool dragging;

    private:
        CommonTools *_commonTools = new CommonTools();
};

#endif // SLIDER_H
