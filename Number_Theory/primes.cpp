#include <iostream>
#include <stdio.h>
#include <string>
#include <chrono>
#include <thread>
#include <vector>

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
void kthPrime();
void printPrimeFactorization(ll);

int main()
{
    timeFunction("Naive", isPrimeNaive);
    timeFunction("Sqrt", isPrimeSqrt);
    timeFunction("Sieve", isPrimeSieve);
    kthPrime();
    printPrimeFactorization(LLONG_MAX);
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

vector<int> kthPrimeHelper()
{
    int k = 1000000;
    bool notPrimes[k]; // false by default
    vector<int> primes;
    // zero and 1 are not primes
    notPrimes[0] = notPrimes[1] = true;
    for (int i = 2; i * i < k; i++)
    {
        // found a value that is considered to be a prime
        if (!notPrimes[i])
        {
            for (int j = i * i; j <= k; j += i)
            {
                // mark the composite of the current prime to be true
                notPrimes[j] = true;
            }
        }
    }

    for (int i = 2; i <= k; i++)
    {
        // if the number is prime
        if (!notPrimes[i])
        {
            primes.push_back(i);
        }
    }

    return primes;
}

void kthPrime()
{
    cout << "Input number of queries for the kth prime: ";
    int q, n;
    cin >> q;
    vector<int> sieve = kthPrimeHelper();
    while (q--)
    {
        cout << "Enter kth prime query: ";
        cin >> n;
        cout << "queries left: " << q << endl;
        cout << "query: " << n << endl;
        cout << "sieve size: " << sieve.size() << endl;
        cout << sieve[n - 1] << endl;
    }
}

void printPrimeFactorization(ll n)
{
    for (ll i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            int pow = 0;
            while (n % i == 0)
            {
                pow++;
                n /= i;
            }
            printf("(%lld^%d) ", i, pow);
        }
    }

    // pseudo base case
    // in the event that n is not divisible by anything
    // it in itself is the prime
    if (n > 1)
    {
        printf("(%lld^%d)", n, 1);
    }

    cout << "\n"
         << flush;
}