#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Animal
{
public:
    string name;
    string species;
    int age;
    string foodType;

    Animal(string name, string species, int age, string foodType)
    {
        // animal constructor
        // fill this in!
    }

    void print()
    {
        // prints the animal to standard output
        // fill this in!
    }
};

class Zoo
{
public:
    vector<Animal> animals;
    void addAnimal(Animal animal)
    {
        // this function adds an animal to the "animals" vector
        // fill this in!
        // HINT: use push_back with the "animals" vector
    }

    void printAnimals()
    {
        // this function should print out all of the animals and their properties
        // fill this in!
    }
};

int main()
{
    Zoo myZoo;

    // making some animals
    Animal a1("Jeff", "Lion", 12, "Meat");
    Animal a2("Anne", "Owl", 3, "Meat");
    Animal a3("Zain", "Elk", 6, "Plants");

    // Add some animals to the zoo
    myZoo.addAnimal(a1);
    myZoo.addAnimal(a2);
    myZoo.addAnimal(a3);

    // Print out the animals in the zoo
    myZoo.printAnimals();

    return 0;
}
