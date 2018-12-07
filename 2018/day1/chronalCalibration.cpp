#include <iostream>
#include <fstream>

#include <unordered_set>


using namespace std;

void part1()
{
    char op;
    int val;
    int total = 0;


    ifstream inFile;
    inFile.open("data.txt");//open file to be read

    while(!inFile.eof()) //input the sign into op and int into val then add/sub based on op
    {
        inFile >> op;
        inFile >> val;
        if(op == '+')
            total += val;
        else
            total -= val;

    }
    inFile.close();
    cout << total << endl;
}

void part2()
{

    char op;
    int val;
    int total = 0;
    int twice = 0;

    unordered_multiset<int> values;

    ifstream inFile;
    inFile.open("data.txt");

    while(true)
    {
        values.insert(total);//intert value into multi_set and check if it has been added already

        if(values.count(total) > 1)
        {
            twice = total;
            cout << twice << endl;
            break;
        }

        inFile >> op;
        inFile >> val;

        if(op == '+')
            total += val;
        else
            total -= val;
        
        if(inFile.eof()) //reset to front of file if not finished
        {
            inFile.seekg(0,ios::beg);
        }
        
    }

    inFile.close();

}

int main()
{
    part1();
    part2();

    return 0;
}