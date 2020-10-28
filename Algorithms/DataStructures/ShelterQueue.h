#include <queue>
#include "Animal.h"

class ShelterQueue
{
private:
    std::queue<Animal *> catQueue;
    std::queue<Animal *> dogQueue;
    void uptickShelterTimes(std::queue<Animal *>);

public:
    ShelterQueue();
    void enqueue(std::string animal);
    Animal dequeueAny();
    Animal dequeueCat();
    Animal dequeueDog();
};