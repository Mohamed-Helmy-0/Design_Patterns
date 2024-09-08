#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <typeinfo>

using namespace std;


class Button
{ 
public:
    virtual ~Button() {};
    virtual void buttonName()=0;
};
class WinButton: public Button
{
     void buttonName() override { cout << "Windows Button" << endl; }
};
class LinuxButton: public Button
{
     void buttonName() override { cout << "Linux Button" << endl; }
};

class Rectangle
{
public:
    virtual void RectangleName()=0;
};
class WinRectangle: public Rectangle
{
     void RectangleName() override { cout << "Windows Rectangle" << endl; }
};
class LinuxRectangle: public Rectangle
{
     void RectangleName() override { cout << "Linux Rectangle" << endl; }
};


class AbstractFactory
{
    public:
        virtual ~AbstractFactory() {};  // virtual destructor to avoid memory leakage.
        virtual Button* createButton()=0;
        virtual Rectangle* createRectangle()=0;
};
class WindowsFactory: public AbstractFactory
{
    Button* createButton() override { return new WinButton(); }
    Rectangle* createRectangle() override { return new WinRectangle(); }
};
class LinuxFactory: public AbstractFactory
{
    Button* createButton() override { return new LinuxButton(); }
    Rectangle* createRectangle() override { return new LinuxRectangle(); }
};

int main()
{
    cout<< "Start Code Main." << endl;

    AbstractFactory* factory;
    factory = new WindowsFactory();
    Button* button = factory->createButton();
    Rectangle* rectangle = factory->createRectangle();
    rectangle->RectangleName();
    button->buttonName();
    delete rectangle;
    delete button;
    delete factory;
    factory = new LinuxFactory();
    button = factory->createButton();
    button->buttonName();

    cout << "End Code Main." << endl;
    return 0;
}