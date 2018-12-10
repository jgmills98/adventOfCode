#include <fstream>
#include <iostream>
#include <sstream>

#include <string>
#include <set>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <iomanip>

using namespace std;

void formatData()
{
    set<string> texts;

    ifstream inFile;
    inFile.open("data.txt");
    //format this data into new output file first
    string str1;
    while(!inFile.eof())
    {
    getline(inFile,str1);
    texts.insert(str1);
    }
    inFile.close();

    ofstream ofFile;
    ofFile.open("format_data.txt");
    for(auto i:texts)
        ofFile << i << endl;
    ofFile.close();

}

int main()
{

    // formatData();
    unordered_map<int,int> guards;//map of guard id and sleep time
    unordered_map<int,unordered_multiset<int>> guardCount;//keeps track of which minutes the guards were asleep for 

    ifstream inFile;
    inFile.open("format_data.txt");

    string str;

    int oldpos;
    bool found;

    int guardNum;

    int numstart;
    int numend; 

    int startTime;
    int endTime;

    while(!inFile.eof())
    {

        queue<string> section;

        guardNum = 0;
        found = false;

        while(!inFile.eof())//creates a quq of the guard id and each sleep/wake cycle
        {
            oldpos = inFile.tellg();
            getline(inFile,str);

            if(found == false && str.find('#') != string::npos)
            {
                found = true;
                section.push(str);
            }
            else if(str.find('#') == string::npos)
            {
                section.push(str);
            }
            else
            {
                inFile.seekg(oldpos);
                break;
            }
        }
        numstart = section.front().find('#')+1;
        numend = section.front().find(' ',numstart);
        istringstream iss(section.front().substr(numstart,numend-numstart));

        iss >> guardNum;
        section.pop();
        
        while(!section.empty())
        {
            //gets the start and end of sleep time, adds the total time to guards map and then each minute to the guardCount map
            istringstream t1(section.front().substr(15,2));
            t1 >> startTime;
            section.pop();
            istringstream t2(section.front().substr(15,2));
            t2 >> endTime;
            section.pop();

            guards[guardNum] += endTime-startTime;
            
            for(int i = startTime; i<endTime; i++)
                guardCount[guardNum].insert(i);
            
        }   

    }
    int maxTime = 0;
    int maxTimeKey;

    for(auto it:guards)
    {

        if(it.second > maxTime)
        {
            maxTime = it.second;
            maxTimeKey = it.first;
        }

    }
    int maxMin = 0;
    int maxMinKey;
    for(int i = 0; i <= 59; i++)
    {
        if(guardCount[maxTimeKey].count(i) > maxMin)
        {
            maxMin = guardCount[maxTimeKey].count(i);
            maxMinKey = i;
        }
    }

    cout << maxTimeKey*maxMinKey << endl;;

    //part2 part:
    maxMin = 0;
    maxMinKey = 0;
    int maxGuardKey = 0;
    for(auto it: guardCount)
    {
        for(int i = 0; i <= 59; i++)
        {
            if(it.second.count(i) > maxMin)
            {
                maxMin = it.second.count(i);
                maxGuardKey = it.first;
                maxMinKey = i;
            }
        }
    }

    cout << maxGuardKey*maxMinKey << endl;
    
}