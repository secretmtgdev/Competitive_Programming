#include <iostream>
#include <map>
#include <tuple>
#include <vector>
#include <stack>
#include <regex>
#include <set>
#include <queue>
#include <cmath>

using namespace std;

set<string> DICTIONARY = {"like", "lamp", "limp", "lime", "damp"};

//////////////////////////
// FUNCTION DECLARATION //
//////////////////////////
void combinationOfChars(string);
void permutations(string);
bool kmp(string, string);
void solveKMP();
string englishInt(int);
void wordTransform(string, string);

//////////////////////
// FUNCTION HELPERS //
//////////////////////
void testWordTransform();

int main()
{
    // combinationOfChars("abc");
    // permutations("aabc");
    // solveKMP();
    // limitation of ints doesn't allow for millions or billions
    // vector<int> numbers = {-1, 0, 1, 11, 55, 100, 111, 300, 999, 1000, 1001, 12345, 1234567, 123456789, 1234567987};
    // for (int number : numbers)
    // {
    //     printf("%d --> %s\n", number, englishInt(number).c_str());
    // }
    testWordTransform();
}

/////////////////////////////
// FUNCTION IMPLEMENTATION //
/////////////////////////////
//  RT: O(n^2) with prettier, O(n) w/out. SC: O(n)
string englishInt(int n)
{
    if (n == 0)
    {
        return "zero";
    }
    string res = "";
    if (n < 0)
    {
        res += "negative ";
        n *= -1;
    }
    vector<string> onesDigit = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    vector<string> oddTens = {"ten", "eleven", "twelve"};
    vector<string> tensDigit = {"", "", "twenty", "thirty", "fourty", "fifty", "sixty", "seventy", "eighty", "ninety"};
    vector<string> threeDigit = {"thousand", "million", "billion", "trillion"};
    stack<string> numStack;
    string h, t, o, hundredString;
    int tripleDigit = -1, hundreds, tens, ones;
    while (n != 0)
    {
        // Grab number by three digits
        hundreds = (n % 1000) / 100;
        tens = (n % 100) / 10;
        ones = n % 10;
        h = onesDigit[hundreds] + " " + (hundreds != 0 ? "hundred" : "");
        t = tens == 1 ? ((ones == 0 || ones == 1 || ones == 2) ? oddTens[ones] : onesDigit[ones] + "teen")
                      : (" " + tensDigit[tens]);
        o = onesDigit[ones];
        hundredString = h + " " + t + " " + (tens == 1 ? "" : o) + " " + (tripleDigit >= 0 ? threeDigit[tripleDigit] : "");
        numStack.push(hundredString);
        tripleDigit++;
        n /= 1000;
    }

    while (!numStack.empty())
    {
        res += numStack.top();
        numStack.pop();
        if (!numStack.empty())
        {
            res += ",";
        }
    }

    // prettify from https://www.quora.com/How-do-I-split-a-string-by-space-into-an-array-in-c++
    regex ws_re("\\s+");
    vector<string> split{
        sregex_token_iterator(res.begin(), res.end(), ws_re, -1), {}};

    res = "";
    for (const auto word : split)
    {
        res += word + " ";
    }
    return res;
}

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

void swapWords(string &src, int iStart, int iEnd, int jStart, int jEnd)
{
    while (iStart < iEnd && jStart > jEnd)
    {
        auto tmp = src[iStart];
        src[iStart] = src[jEnd + 1];
        src[jEnd + 1] = tmp;
        iStart++;
        jEnd++;
    }
}

void reverseLine(string &src)
{
    int iStart = 0;
    int iEnd = 0;
    int jStart = src.length() - 1;
    int jEnd = src.length() - 1;

    while (iStart < jStart)
    {
        while (src[iEnd] != ' ')
        {
            iEnd++;
        }
        while (src[jEnd] != ' ')
        {
            jEnd--;
        }
        swapWords(src, iStart, iEnd, jStart, jEnd);

        iEnd++;
        jEnd--;
        iStart = iEnd;
        jStart = jEnd;
    }
}

bool isExplored(set<string> explored, string word)
{
    return explored.find(word) != explored.end();
}

bool oneEdit(string src, string cmp)
{
    int diff = 0;
    for (int i = 0; i < src.length(); i++)
    {
        if (src[i] != cmp[i])
        {
            diff++;
        }
    }
    diff += abs((int)src.length() - (int)cmp.length());
    return diff == 1;
}

set<string> getEdges(string src)
{
    set<string> edges;
    for (string cmp : DICTIONARY)
    {
        if (oneEdit(src, cmp))
        {
            edges.insert(cmp);
        }
    }
    return edges;
}

void wordTransform(string src, string dst)
{
    map<string, string> parentLinks;
    queue<string> fringe;
    set<string> explored;
    fringe.push(src);
    explored.insert(src);
    bool found = false;
    parentLinks.insert(make_pair(src, ""));
    while (!fringe.empty())
    {
        string toExplore = fringe.front();
        fringe.pop();
        if (toExplore.compare(dst) == 0)
        {
            found = true;
            break;
        }
        set<string> edges = getEdges(toExplore);
        for (string edge : edges)
        {
            if (explored.find(edge) == explored.end())
            {
                parentLinks.insert(make_pair(edge, toExplore));
                explored.insert(edge);
                fringe.push(edge);
            }
        }
    }

    string curr = dst;
    string res = curr;
    curr = parentLinks.find(curr)->second;
    while (curr.compare(src) != 0)
    {
        res += " " + curr;
        auto ref = parentLinks.find(curr);
        if (ref != parentLinks.end())
        {
            curr = ref->second;
        }
    }
    res += " " + src;
    reverseLine(res);
    printf("Can transform: %s\n", found ? "true" : "false");
    printf("Path: [%s]\n", res.c_str());
}

void testWordTransform()
{
    wordTransform("damp", "like");
}