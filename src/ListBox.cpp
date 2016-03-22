#include "ListBox.h"

const int itemHeight = 18;

ListBox::ListBox(int positionX, int positionY, int width, int height) : Control(positionX, positionY, width, height)
{
    this->index = 0;
}

void ListBox::addItem(string item)
{
    items.push_back(item);
}

void ListBox::removeItem(int deleteIndex)
{
    int i = 0;

    for (vector<string>::iterator it = this->items.begin(); it != this->items.end(); it++)
    {
        if (i == deleteIndex)
        {
            this->items.erase(it);
            break;
        }

        i++;
    }

    if (this->index > (int) this->items.size())
    {
        this->index = (int) this->items.size() - 1;
    }
}

void ListBox::setCurrent(int i)
{
    this->index = i;
}

int ListBox::getIndex()
{
    return this->index;
}

int ListBox::getCount()
{
    return (int) this->items.size();
}

bool ListBox::updateControl(MouseState &state)
{
    Control::updateControl(state);

    //int x = state.x;
    int y = state.y;

    if (this->inside && state.LeftButtonDown)
    {
        int tempIndex = (y - this->posY) / itemHeight;

        if ((tempIndex >= 0) && (tempIndex < (int) items.size()))
        {
            this->index = tempIndex;
            return true;
        }
    }

    return false;
}

void ListBox::drawControl()
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

    if (index >= 0)
    {
        glColor4f(0.3f, 0.3f, 1.0f, 0.5f);

        int currentY = this->posY + this->index * itemHeight;

        glBegin(GL_QUADS);

            glVertex2d(this->posX + this->width, currentY             );
            glVertex2d(this->posX,               currentY             );
            glVertex2d(this->posX,               currentY + itemHeight);
            glVertex2d(this->posX + this->width, currentY + itemHeight);

        glEnd();
    }

    glColor4f(0.7f, 0.7f, 0.7f, 1.0f);

    for (int i = 0; i < (int) this->items.size(); i++)
    {
        iGLEngine->drawText(this->posX + 2, this->posY + 2 + i * itemHeight, this->items[i].data());
    }
}

string ListBox::getType()
{
    return "ListBox";
}
