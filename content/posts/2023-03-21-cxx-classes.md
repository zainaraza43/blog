---
title: Introduction to Classes, Structs, and Objects in C++
date: 2023-03-02
draft: false
author: Jeremie Bornais (With Help From ChatGPT 😎)
---

## Introduction

If you're familiar with programming in C++, you've likely heard of classes, structs, and objects. These concepts are at the core of object-oriented programming and are essential for creating efficient, reusable, and modular code.

In this article, we'll take a closer look at what classes, structs, and objects are, how they work, and provide examples to illustrate their use in C++.

## Classes and Structs

A class is a user-defined data type that encapsulates data and functions together into a single entity. It serves as a blueprint for creating objects that share common attributes and behaviors. In other words, a class defines the properties and methods that objects of that class will have.

A struct is similar to a class, except that the default access level for its members is public, whereas a class's default access level is private. Structs are typically used for simple data structures, whereas classes are used for more complex objects that have both data and behavior.

Here's an example of a class in C++:

```cxx
class Rectangle {
  private:
    int width;
    int height;
  public:
    void set_values(int, int);
    int area();
    int perimeter();
};
```

In this example, we define a class called "Rectangle" with two private member variables, "width" and "height", and three public member functions, "set_values", "area", and "perimeter". The "set_values" function is used to set the values of the width and height attributes, while the "area" and "perimeter" functions calculate the area and perimeter of the rectangle, respectively.

## Objects

An object is an instance of a class or struct. It is created by allocating memory for it and initializing its member variables. Once an object is created, its member functions can be called to manipulate its data.

Here's an example of how to create an object of the "Rectangle" class we defined earlier:

```cxx
Rectangle rect;
```

In this example, we create an object of the "Rectangle" class called "rect". By default, the width and height of the rectangle are uninitialized and have undefined values.

To initialize the values of the rectangle's width and height attributes, we can call the "set_values" function:

```cxx
rect.set_values(5, 6);
```

In this example, we call the "set_values" function to set the width and height of the rectangle to 5 and 6, respectively.

We can also call the "area" and "perimeter" functions to calculate the area and perimeter of the rectangle:

```cxx
int area = rect.area();
int perimeter = rect.perimeter();
```

In this example, we call the "area" and "perimeter" functions to calculate the area and perimeter of the rectangle and store the results in the "area" and "perimeter" variables, respectively.

## Access Modifiers

Access modifiers are keywords used to define the visibility and accessibility of a class's member variables and functions. There are three access modifiers in C++: public, private, and protected.

Public members can be accessed from outside the class, while private members can only be accessed from within the class. Protected members are similar to private members but can be accessed by derived classes.

Here's an example of how access modifiers are used in a class:

```cxx
class Circle {
  private:
    double radius;
  public:
    void set_radius(double r) {
      radius = r;
    }
    double get_radius() {
      return radius;
    }
  protected:
    double pi = 3.14159;
};
```

In this example, we define a class called "Circle" with a private member variable "radius", a public member function "set_radius" to set the value of "radius", and a public member function "get_radius" to retrieve the value of "radius". We also define a protected member variable "pi" that can be accessed by derived classes.

## Inheritance

Inheritance is a powerful feature of object-oriented programming that allows us to create new classes based on existing classes. The new class, called the derived class, inherits the properties and methods of the existing class, called the base class, and can also add its own properties and methods.

Here's an example of how inheritance works in C++:

```cxx
class Shape {
  protected:
    int x;
    int y;
  public:
    void set_position(int x_pos, int y_pos) {
      x = x_pos;
      y = y_pos;
    }
};

class Circle : public Shape {
  private:
    double radius;
  public:
    void set_radius(double r) {
      radius = r;
    }
    double area() {
      return 3.14159 * radius * radius;
    }
};
```

In this example, we define a base class called "Shape" with two protected member variables, "x" and "y", and a public member function "set_position" to set the position of the shape. We also define a derived class called "Circle" that inherits from "Shape" and adds its own private member variable, "radius", and two member functions, "set_radius" and "area", to set the radius of the circle and calculate its area, respectively.

## Constructors

Constructors are special member functions that are called when an object of a class is created. They are used to initialize the object's member variables with default or user-defined values. In C++, constructors have the same name as the class and do not have a return type, not even void.

Here's an example of a class with a constructor:

```cxx
class Rectangle {
  private:
    int width;
    int height;
  public:
    Rectangle(int w, int h) {
      width = w;
      height = h;
    }
    int area() {
      return width * height;
    }
};
```

In this example, we define a class called "Rectangle" with two private member variables, "width" and "height", and a constructor that takes two integer parameters and assigns them to the member variables. We also define a public member function "area" that calculates the area of the rectangle and returns it as an integer.

We can create an object of the "Rectangle" class and initialize it using the constructor as follows:

```cxx
Rectangle r(3, 4);
cout << "Area of the rectangle: " << r.area() << endl;
```

This will output "Area of the rectangle: 12", which is the product of the width and height of the rectangle.

Constructors can also be overloaded, meaning we can define multiple constructors with different parameter lists. For example, we can define a default constructor with no parameters that initializes the member variables with default values:

```cxx
class Rectangle {
  private:
    int width;
    int height;
  public:
    Rectangle() {
      width = 0;
      height = 0;
    }
    Rectangle(int w, int h) {
      width = w;
      height = h;
    }
    int area() {
      return width * height;
    }
};
```

Now we can create an object of the "Rectangle" class without providing any parameters, and the default constructor will be called:

```cxx
Rectangle r1;
cout << "Area of the rectangle: " << r1.area() << endl;
```

This will output "Area of the rectangle: 0", since the width and height are initialized to zero by the default constructor.

In summary, constructors are important member functions of a class that are used to initialize objects with default or user-defined values. They can be overloaded with different parameter lists and have the same name as the class. Constructors do not have a return type, not even void.

## Conclusion

Classes, structs, and objects are fundamental concepts in C++ and are essential for writing efficient, modular, and reusable code. By encapsulating data and behavior into a single entity, we can create objects that have well-defined attributes and methods. Access modifiers allow us to control the visibility and accessibility of our classes' member variables and functions, while inheritance allows us to create new classes based on existing ones. With these tools at our disposal, we can write powerful and flexible C++ programs.

I hope this article has provided a useful introduction to classes, structs, and objects in C++. Feel free to experiment with the code examples and explore other features of object-oriented programming in C++. Happy coding!
