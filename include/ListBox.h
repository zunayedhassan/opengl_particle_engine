#ifndef LISTBOX_H
#define LISTBOX_H

#include <vector>

#include "Control.h"

using std::vector;


class ListBox : public Control
{
    public:
        ListBox(int positionX, int positionY, int width, int height);

        void addItem(string item);
        void removeItem(int deleteIndex);
        void setCurrent(int i);

        int getIndex();
        int getCount();

        virtual bool updateControl(MouseState &state);
        virtual void drawControl();
        virtual string getType();

    protected:
        int index;
        vector<string> items;
};

#endif // LISTBOX_H
