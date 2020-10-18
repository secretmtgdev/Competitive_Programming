#include <iostream>
#include <stdio.h>
#include <string>
#include <chrono>
#include <thread>

using namespace std;
typedef long long ll;

///////////////////////////
// FUNCTION DECLARATIONS //
///////////////////////////
void timeFunction(string, function<bool(ll)>);
bool isPrimeNaive(ll);
bool isPrimeSqrt(ll);
bool isPrimeSieve(ll);
void generateSieveArray(ll *);

int main()
{
    timeFunction("Naive", isPrimeNaive);
    timeFunction("Sqrt", isPrimeSqrt);
    timeFunction("Sieve", isPrimeSieve);
}

//////////////////////////////
// FUNCTION IMPLEMENTATIONS //
//////////////////////////////
bool isPrimeNaive(ll n)
{
    if (n < 2)
        return false;
    for (ll i = 2; i < n; i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

bool isPrimeSqrt(ll n)
{
    if (n < 2)
        return false;
    for (ll i = 2; i * i < n; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

bool isPrimeSieve(ll n)
{
    ll sieveArray[n];
    generateSieveArray(sieveArray);
    return sieveArray[n - 1];
}

//////////////////////
// HELPER FUNCTIONS //
//////////////////////
void timeFunction(string functionName, function<bool(ll)> callback)
{
    auto start = chrono::high_resolution_clock::now();
    auto result = callback(LLONG_MAX);
    auto stop = chrono::high_resolution_clock::now();
    ll elapsedTime = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
    printf("Function %s took a total of %lld nanoseconds\n", functionName.c_str(), elapsedTime);
}

void generateSieveArray(ll *sieve)
{
    ll n = sizeof(sieve) / sizeof(*sieve);

    // Assume the contents of the array are all primes
    for (ll i = 0; i < n; i++)
    {
        sieve[i] = 1;
    }

    // first value in the sieves, aka '1', can't be prime
    sieve[0] = 0;
    for (ll i = 1; i * i < n; i++)
    {
        if (sieve[i])
        {
            ll startFactor = 2;
            for (int j = i * i; i <= n; j += i)
            {
                sieve[j] = 0;
            }
        }
    }
}