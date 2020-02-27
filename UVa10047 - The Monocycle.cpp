#include <iostream>
#include <vector>
#include <sstream>
#include <map>

#define north 0x0
#define east 0x1
#define south 0x2
#define west 0x3

using namespace std;



map<int, int> bfs(char** , const int, const int);

int main()
{
  string line;
  while (getline(cin, line, '\n'))
  {
    stringstream ss;
    int m, n;
    int init_state = 0, final_state = 0;
    ss << line;
    ss >> m >> n;
    if (!m)
      break;

    char grid[m][n];
    for (int i = 0; i < m; i++)
    {
      getline(cin, line, '\n');
      int j = 0;
      for(char c : line){
        switch(c) {
          case 'S': 
            init_state = (j << 5) | i;
            grid[i][j] = '.';
            break;
          case 'T': 
            final_state = (j << 5) | i;
            grid[i][j] = '.';
            break;
          default:
            grid[i][j] = c;
        }
        j++;
      }
    }

    map<int, int> parents = bfs(grid, init_state, final_state);

    cout << "---------------------------------" << endl;
    cout << "init: " << (0x1F & init_state) << ", " <<  (init_state >> 5) << endl;
    cout << "final: " << (0x1F & final_state) << ", " <<  (final_state >> 5) << endl;
    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
        cout << grid[i][j];
      cout << endl;
    }
  }
  return 0;
}

// map<int, int> bfs(const char** grid,const int init_state, const int final_state){

// }