#include "Animal.h"
#include <string>

using namespace std;

Animal::Animal(string newSpecies)
{
    duration = 0;
    species = newSpecies;
}

int Animal::getDuration()
{
    return duration;
}

string Animal::getSpecies()
{
    return species;
}

void Animal::uptickDuration()
{
    duration++;
}
