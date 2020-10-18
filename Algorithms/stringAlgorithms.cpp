#include <iostream>
#include <map>

using namespace std;

//////////////////////////
// FUNCTION DECLARATION //
//////////////////////////
void combinationOfChars(string);

int main()
{
    combinationOfChars("abc");
}

/////////////////////////////
// FUNCTION IMPLEMENTATION //
/////////////////////////////
void print(string out, int len)
{
    // cout << "Printing contents, length = " << len << endl;
    for (int i = 0; i < len; i++)
    {
        cout << out[i];
    }
    cout << endl;
}

void combinationHelper(string str, string out, int pos, int count[], int len)
{
    print(out, len);
    int n = str.length();
    // cout << "Size = " << n << endl;
    for (int i = pos; i < n; i++)
    {
        if (count[i] != 0)
        {
            out[len] = str[i];
            count[i]--;
            combinationHelper(str, out, i, count, len + 1);
            count[i]++;
        }
    }
}

void combinationOfChars(string s)
{
    map<char, int> uniqueCharCounts;
    for (int i = 0; i < s.length(); i++)
    {
        char c = s[i];
        if (uniqueCharCounts.find(c) != uniqueCharCounts.end())
        {
            uniqueCharCounts[c] = uniqueCharCounts[c] + 1;
        }
        else
        {
            uniqueCharCounts.insert(make_pair(c, 1));
        }
    }
    // cout << "Printing map contents" << endl;
    // for (auto pair : uniqueCharCounts)
    // {
    //     printf("(%c, %d)\n", pair.first, pair.second);
    // }
    size_t mapSize = uniqueCharCounts.size();

    // indication of termination point in string
    // this is to avoid garbarge and an overstepping
    // of contents
    string str(mapSize, '\0');
    int count[mapSize];
    int i = 0;
    for (auto const &[key, val] : uniqueCharCounts)
    {
        str[i] = key;
        count[i] = val;
        i++;
    }

    // for (int i = 0; i < mapSize; i++)
    // {
    //     printf("Char: %c, Count: %d\n", str[i], count[i]);
    // }
    string output(s.length(), '\0');

    printf("Printing all linear combinations of %s", s.c_str());
    combinationHelper(str, output, 0, count, 0);
}