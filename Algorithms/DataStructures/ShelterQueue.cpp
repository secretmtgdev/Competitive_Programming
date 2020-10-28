#include "ShelterQueue.h"

using namespace std;
ShelterQueue::ShelterQueue()
{
}

void ShelterQueue::enqueue(string animal)
{
    Animal *newAnimal = new Animal(animal);
    uptickShelterTimes(catQueue);
    uptickShelterTimes(dogQueue);
    if (animal.compare("cat") == 0)
    {
        catQueue.push(newAnimal);
    }
    else
    {
        dogQueue.push(newAnimal);
    }
}

Animal ShelterQueue::dequeueAny()
{
    Animal topCat = *catQueue.front();
    Animal topDog = *dogQueue.front();
    if (topCat.getDuration() > topDog.getDuration())
    {
        catQueue.pop();
        return topCat;
    }
    else
    {
        dogQueue.pop();
        return topDog;
    }
}

Animal ShelterQueue::dequeueCat()
{
    Animal toAdopt = *catQueue.front();
    catQueue.pop();
    return toAdopt;
}

Animal ShelterQueue::dequeueDog()
{
    Animal toAdopt = *dogQueue.front();
    dogQueue.pop();
    return toAdopt;
}

void ShelterQueue::uptickShelterTimes(queue<Animal *> animals)
{
    queue<Animal *> tmp;
    while (!animals.empty())
    {
        Animal *currAnimal = animals.front();
        currAnimal->uptickDuration();
        catQueue.pop();
        tmp.push(currAnimal);
    }
    while (!tmp.empty())
    {
        Animal *currAnimal = tmp.front();
        tmp.pop();
        animals.push(currAnimal);
    }
}