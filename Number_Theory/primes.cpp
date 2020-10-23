#include <iostream>
#include <stdio.h>
#include <string>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;
typedef long long ll;

vector<ll> sieve_primes;

///////////////////////////
// FUNCTION DECLARATIONS //
///////////////////////////
void timeFunction(string, function<bool(ll)>);
bool isPrimeNaive(ll);
bool isPrimeSqrt(ll);
bool isPrimeSieve(ll);
bool isPrimePrime(ll);
void generateSieveArray(ll *);
void kthPrime();
void printPrimeFactorization(ll);
int binaryExponentiation(int, int);
void printPrimesInRange(int, int);

///////////////////////
// TESTING FUNCTIONS //
///////////////////////
void testBasicPrimeFunctions();
void testPrimesInRange();
void testPrimePrime();

//////////////////////
// HELPER FUNCTIONS //
//////////////////////
void clean();

int main()
{
    //testBasicPrimeFunctions();
    //testPrimesInRange();
    testPrimePrime();
}

//////////////////////////////
// FUNCTION IMPLEMENTATIONS //
//////////////////////////////
// Number is prime prime, if the number of primes before it is prime
bool isPrimePrime(ll n)
{
    int count = 0;
    // assume that all of the contents to be assumed prime
    for (ll i = 0; i < n; i++)
    {
        sieve_primes.push_back(1);
    }

    // the number 1 can't be prime, so cross this out
    sieve_primes[0] = 0;
    sieve_primes[1] = 0;

    // generate sieves array
    for (int i = 2; i < n; i++)
    {
        // check to see if the number is prime
        if (sieve_primes[i])
        {
            count++;
            // start: first composite of the current prime
            for (int j = i * i; j <= n; j += i)
            {
                // mark the composite as not prime
                sieve_primes[j] = 0;
            }
        }
    }

    return isPrimeSqrt(count);
}

void printPrimesInRange(int L, int R)
{
    int primeCount = 0;
    printf("[ ");
    for (int i = L; i <= R; i++)
    {
        if (isPrimeSqrt(i))
        {
            printf("%d ", i);
            primeCount++;
        }
    }
    printf("]\n");
    printf("The total number of primes in the range [%d:%d]: %d\n", L, R, primeCount);
}

// RT: O(log(n))
int binaryExponentiation(int base, int power)
{
    // square base and halve power until power is 0
    int res = 1;
    while (power != 0)
    {
        if (power % 2 == 1)
        {
            res *= base;
            power -= 1;
        }
        else
        {
            base *= base;
            power /= 2;
        }
    }
    return res;
}

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
    sieve[1] = 0;
    for (ll i = 2; i * i < n; i++)
    {
        if (sieve[i])
        {
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

// This function expects an input indicating the number of following inputs
// be careful when using this function
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

void clean()
{
    sieve_primes.clear();
}

//////////////////////////////////////
// TESTING FUNCTION IMPLEMENTATIONS //
//////////////////////////////////////
void testBasicPrimeFunctions()
{
    timeFunction("Naive", isPrimeNaive);
    timeFunction("Sqrt", isPrimeSqrt);
    timeFunction("Sieve", isPrimeSieve);
    kthPrime();
    printPrimeFactorization(LLONG_MAX);
}
void testPrimesInRange()
{
    int base = 100;
    int power = 10;
    printf("%d^%d: %d\n", base, power, binaryExponentiation(base, power));
    printPrimesInRange(1, 100000000);
}
void testPrimePrime()
{
    vector<ll> sieves = {2, 3, 5, 7, 11, 13, 17, 19};
    for (int i = 0; i < sieves.size(); i++)
    {
        int num = sieves[i];
        printf("%d is a prime prime? %s\n", num, isPrimePrime(num) ? "true" : "false");
        clean();
    }
}