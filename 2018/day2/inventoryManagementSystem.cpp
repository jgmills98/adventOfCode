#include <iostream>
#include <fstream>
#include <unordered_set>
#include <set>
#include <vector>
#include <string>

using namespace std;

void part1()
{

    ifstream inFile;
    inFile.open("data.txt");

    string str;
    char c;
    int sum = 0;

    int twoCount = 0;
    int threeCount = 0;

    bool foundTwo;
    bool foundThree;


    while(!inFile.eof())
    {

        foundTwo = false;
        foundThree = false;

        unordered_multiset<char> chars;
        set<char> uniqueChar;

        getline(inFile,str);
        for(int i = 0; i< str.size();i++)
        {
            chars.insert(str[i]);
            uniqueChar.insert(str[i]);
        }

        for(auto i:uniqueChar)
        {
            if(foundTwo == false && chars.count(i) == 2)
            {
                ++twoCount;
                foundTwo = true;
            }
            else if(foundThree == false && chars.count(i) == 3)
            {
                ++threeCount;
                foundThree = true;
            }
        }

    }

    cout << twoCount*threeCount << endl;

}

void part2()
{
    string str;
    string out;
    vector<string> words;
    unordered_set<string> checked; //set is used to make sure a string isnt repeated in double for loop

    ifstream inFile;
    inFile.open("data.txt");

    while(!inFile.eof())
    {

        getline(inFile,str);
        words.push_back(str);//adds each line into a vector of strings
        int dif = 0;

        for(auto i: words)//double loop through each string in order to check all combinations excluding repeats
        {
            dif = 0;
            for(auto j: words)
            {
                if(i == j || checked.find(j) != checked.end()) //go to next string if already been used or is the same string in memory
                    continue;

                for(int z = 0; z < i.size(); z++)//check for any differences in the strings
                {
                    if(i[z] != j[z])
                        ++dif;
                }
                if(dif == 1)//if the difference equals 1, add the equal chars together for the output
                {
                    for(int z = 0; z < i.size(); z++)
                    {
                        if(i != j && i[z] == j[z])
                            out += i[z];
                    }
                    
                }

                
            }
            checked.insert(i);
        }
    }

    cout << out;
    
}

int main()
{

    // part1();
    part2();


    return 0;
}