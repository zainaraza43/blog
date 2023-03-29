#include <iostream>
using namespace std;

class Rectangle
{
private:
    int width;
    int height;

public:
    Rectangle()
    {
        width = 0;
        height = 0;
    }
    Rectangle(int w, int h)
    {
        width = w;
        height = h;
    }
    void setWidth(int w)
    {
        width = w;
    }
    void setHeight(int h)
    {
        height = h;
    }
    int getWidth()
    {
        return width;
    }
    int getHeight()
    {
        return height;
    }
    int area()
    {
        return width * height;
    }
    void print()
    {
        cout << "Width: " << width << endl;
        cout << "Height: " << height << endl;
        cout << "Area: " << area() << endl;
    }
};

struct Point
{
    int x;
    int y;
};

int main()
{
    Rectangle r1;
    Rectangle r2(3, 4);

    r1.print();
    r2.print();

    r1.setWidth(5);
    r1.setHeight(6);

    cout << "Width of r1: " << r1.getWidth() << endl;
    cout << "Height of r1: " << r1.getHeight() << endl;
    cout << "Area of r1: " << r1.area() << endl;

    Point p = {2, 3};
    cout << "Point p: (" << p.x << ", " << p.y << ")" << endl;

    return 0;
}
