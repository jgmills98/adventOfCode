#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <utility>
#include <unordered_set>
#include <unordered_map>


using namespace std;

int getDist(int p1,int p2,int o1,int o2)
{
    int ret;
    if(p2 <= o2)
        ret += o2-p2;
    else
        ret += p2-o2;
    if(p1 <= o1)
        ret += o1-p1;
    else
        ret += p1-o1;
    return ret;

}

int main()
{
    ifstream inFile;
    inFile.open("data.txt");
    int x,y;


    vector<vector<pair<int,int>>> grid(500);
    //pair stores value,distance from value

    // grid.resize(10);
    for(int i = 0; i < 500; i++)
        grid.at(i).resize(500);

    int count = 1;

    while(!inFile.eof())
    {

        inFile >> x;
        inFile.ignore(2);
        inFile >> y;
        inFile.ignore(1);
        grid[y][x].first = count;
        grid[y][x].second = 0;

        int n=0,e=0,s=0,w=0;
        int i=y,j=x;

        while(i > 0)
        {
            i--;
            n++;
        }

        i=y;

        while(i < grid.size()-1)
        {
            i++;
            s++;
        }

        while(j > 0)
        {
            j--;
            w++;
        }
        j=x;

        while(j < grid.size()-1)
        {
            j++;
            e++;
        }
        
        for(i = y-n; i <= y + s; i++)
        {
            for(j = x-w; j <= x+e; j++)
            {
                
                if(grid[i][j].first == 0)
                {
                    grid[i][j].first = count;
                    grid[i][j].second = getDist(i,j,y,x);
                
                }
                else if(grid[i][j].first != 0 && grid[i][j].first != count)
                {
                    if(grid[i][j].second > getDist(i,j,y,x))
                    {
                        // cout << "i: " << i << " j: " << j << endl;
                        grid[i][j].first = count;
                        grid[i][j].second = getDist(i,j,y,x);
                    }
                    else if(grid[i][j].second == getDist(i,j,y,x))
                    {
                        grid[i][j].first = -1;
                        
                    }

                }

            }
        }
        count++;
    }
    unordered_set<int> hitsBorder;
    unordered_map<int,int> counts;
    int max = 0;

    for(int i = 0; i < grid.size(); i++)
    {
        for(int j = 0; j < grid.size(); j++)
        {
            // cout << setw(3) << grid[i][j].first;
            if((i == 0 || i == grid.size()-1 || j == 0 || j == grid.size()-1) && grid[i][j].first != -1)
            {   
                hitsBorder.insert(grid[i][j].first);
                if(counts.find(grid[i][j].first) != counts.end())
                {
                    counts.erase(grid[i][j].first);
                    continue;
                }
            }
            if(hitsBorder.find(grid[i][j].first) == hitsBorder.end() && grid[i][j].first != -1)
            {
                counts[grid[i][j].first]++;
            }
        }
        // cout << endl;
    }
    cout << endl;

    for(auto l:counts)
        if(l.second > max)
            max = l.second;
    cout << max;
    return 0;
}