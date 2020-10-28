#include <string>

class Animal
{
private:
    std::string species;
    int duration;

public:
    Animal(std::string newSpecies);
    std::string getSpecies();
    int getDuration();
    void uptickDuration();
};