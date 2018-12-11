#include <iostream>
#include <fstream>
#include <string>

#include <algorithm>

using namespace std;



int main()
{

    ifstream inFile;
    string str;

    inFile.open("data.txt");
    inFile >> str;
    // str = "Abcdtefqdf";
    string copy = str;

    int pos = 0;
    bool found = false;

    int lowest = 1000000;//used to compare lowest reduction

    for(char ch = 'A'; ch <= 'Z'; ++ch)//loops through all chars
    {
        str = copy;
        int i = 0;

        while(true)//erases all instances of a char 
        {
            if(str[i] == ch || str[i] == ch+32)
            {
                str.erase(i,1);
                --i;
            }

            i++;
            if(i+1 == str.size())
                break;
        }

        while(true)
        {
            //if current posotion and the next are a match, erase the both and set found to true
            if(str[pos] == str[pos+1]+32 || str[pos] == str[pos+1]-32)
            {
                str.erase(pos,2);
                found = true;
            }

            if(pos+1 == str.size())//at the end of the string
            {
                if(found == true)//if a match has been found, and at the end, reset once
                {
                    pos = 0;
                    found = false;
                    continue;
                }
                else//if no match has been found at the end, thats it
                {
                    break;
                }
            }
            pos++;

            
            //checks through for reactions
            //if none resets to pos 0
            //if none ends loop
        }
        if(str.size() < lowest)
            lowest = str.size();
    }

    cout << str.size() << endl;
    cout << lowest;




    return 0;
}