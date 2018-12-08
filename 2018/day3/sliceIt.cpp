#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <unordered_set>
#include <utility>

#include <iomanip>


using namespace std;

int main()
{

    set<pair<int,int>> contested;//points that have already been hit by others
    unordered_set<int> uncontestedSheets;//stores sheets that were inputed into the array without collisions

    vector<vector<int>> fabric;
    fabric.resize(1000);
    for(int i = 0; i< 1000; i++)
    {
        fabric[i].resize(1000,0);
    }

    int num;
    int x,y;
    int sizeX,sizeY;

    int count = 0;
    bool hit;
    bool hitCheck;

    ifstream inFile;
    inFile.open("data.txt");

    while(!inFile.eof())
    {
        hit = false;//used to check once if there was a collision
        hitCheck = false;

        //cin each line into specific variables
        inFile.ignore();
        inFile >> num;
        inFile.ignore(3);
        inFile >> x;
        inFile.ignore();
        inFile >> y;
        inFile.ignore(2);
        inFile >> sizeX;
        inFile.ignore();
        inFile >> sizeY;
        inFile.ignore(1000,'\n');

        for(int i = 0; i < sizeY; i++)//double for loop through the y+size,x+size of the array to add value
        {
            for(int j = 0; j < sizeX; j++)
            {
                if(fabric[y+i][x+j] == 0)//adds the tag if there nothing has beena added there
                {
                    fabric[y+i][x+j] = num;
                    

                }
                else
                {
                    //checks if the arrays current location's value is in the set, if so erase it because it is now been touched
                        if(uncontestedSheets.find(fabric[y+i][x+j]) != uncontestedSheets.end())
                        {
                            uncontestedSheets.erase(fabric[y+i][x+j]);
            
                        }
                        if(hitCheck == false)//sets both to true and will not need to change multiple times per tag
                        {
                            hit = true;
                            hitCheck = true;
                        }
                        fabric[y+i][x+j] = -1;
                        contested.insert(make_pair(y+i,x+j));//inserts the current point as a contestion point and adds -1 to the array show this
                        count ++;

                }

            }
        }
        if(hit == false) //if the tag was inputted with no collision, it gets added to the set
            uncontestedSheets.insert(num);

    }

    for(auto const& i: uncontestedSheets)
    {
        cout << "count: " << count << " " << "untouched tag: "<< i << " " << endl; //prints the value that has not been touched
    }


    // for(int i = 158-2; i < 158 + 30;i++)//shows the area around it
    // {
    //     for(int j = 654-2; j < 654 + 20;j++)
    //         cout << setw(5) << fabric[i][j];
    //     cout << endl;
    // }


}