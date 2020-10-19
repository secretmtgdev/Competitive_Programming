#include <iostream>
#include <map>
#include <tuple>
#include <vector>

using namespace std;

//////////////////////////
// FUNCTION DECLARATION //
//////////////////////////
void combinationOfChars(string);
void permutations(string);
bool kmp(string, string);
void solveKMP();

int main()
{
    combinationOfChars("abc");
    permutations("aabc");
    solveKMP();
}

/////////////////////////////
// FUNCTION IMPLEMENTATION //
/////////////////////////////
void print(string out, int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << out[i];
    }
    cout << endl;
}

void combinationHelper(string str, string out, int pos, vector<int> count, int len)
{
    print(out, len);
    int n = str.length();
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

tuple<string, vector<int>> getCharCounts(string s)
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

    size_t mapSize = uniqueCharCounts.size();

    // indication of termination point in string
    // this is to avoid garbarge and an overstepping
    // of contents
    string str(mapSize, '\0');
    vector<int> count;
    int i = 0;
    for (auto const &[key, val] : uniqueCharCounts)
    {
        str[i++] = key;
        count.push_back(val);
    }
    return make_tuple(str, count);
}

void combinationOfChars(string s)
{
    tuple<string, vector<int>> charCountTuple = getCharCounts(s);
    string output(s.length(), '\0');

    string str = get<0>(charCountTuple);
    vector<int> count = get<1>(charCountTuple);

    printf("Printing all linear combinations of %s", s.c_str());
    combinationHelper(str, output, 0, count, 0);
}

void permutationsHelper(string str, string out, vector<int> count, int len)
{
    if (len == out.length())
    {
        print(out, out.length());
    }
    int n = str.length();
    for (int i = 0; i < n; i++)
    {
        if (count[i] != 0)
        {
            out[len] = str[i];
            count[i]--;
            permutationsHelper(str, out, count, len + 1);
            count[i]++;
        }
    }
}

void permutations(string s)
{
    tuple<string, vector<int>> charCountTuple = getCharCounts(s);
    string output(s.length(), '\0');

    string str = get<0>(charCountTuple);
    vector<int> count = get<1>(charCountTuple);

    printf("Printing all permutations of %s", s.c_str());

    permutationsHelper(str, output, count, 0);
}

void solveKMP()
{
    string s = "abcbcglx";
    string p = "bcgl";
    bool res = kmp(s, p);
    printf("%s is in %s? %s\n", p.c_str(), s.c_str(), res ? "true" : "false");
}

vector<int> kmpUtil(string p)
{
    vector<int> pattern;

    // zero at the vector
    for (int i = 0; i < p.length(); i++)
        pattern.push_back(0);
    int i = 1;
    int j = 0;
    while (i < p.length())
    {
        //printf("i: %d, j: %d, vector size: %lu\n", i, j, pattern.size());
        if (p[i] != p[j])
        {
            if (j != 0)
            {
                j = pattern[j - 1];
            }
            else
            {
                i++;
            }
        }
        else
        {
            // indicates that there is a prefix that is a suffix
            // avoid redundant comparisons
            pattern[i] = j + 1;
            i++;
            j++;
        }
    }
    return pattern;
}

bool kmp(string s, string p)
{
    vector<int> pattern = kmpUtil(p);
    int i = 0;
    int j = 0;
    cout << "here" << endl;
    while (i < s.length())
    {
        if (s[i] == p[j])
        {
            if (j == p.length() - 1)
                return true;
            // move both pointers forward
            i++;
            j++;
        }
        else
        {
            // DO NOT INCREMENT I, WE STILL NEED TO COMPARE
            if (j != 0)
                j = pattern[j - 1];
            // INCREMENT I BECAUSE WE ARE AT THE END OF THE PREFIX
            else
                i++;
        }
    }

    return false;
}