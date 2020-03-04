#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <bitset>

#define north 0x0
#define east 0x1
#define south 0x2
#define west 0x3

#define green 0x0
#define black 0x1
#define red 0x2
#define blue 0x3
#define white 0x4

using namespace std;

int m, n;

map<int, int> bfs(vector<char> &, const int, const int);
int find_distances(map<int, int> &, const int, const int);

int main()
{
  string line;
  int num_test = 1;
  while (getline(cin, line, '\n'))
  {
    stringstream ss;
    int init_state = 0, final_state = 0;
    ss << line;
    ss >> m >> n;
    if (!m)
      break;
    
    if(num_test != 1) cout << endl << endl;

    vector<char> grid(m * n);
    for (int i = 0; i < m; i++)
    {
      getline(cin, line, '\n');
      int j = 0;
      for (char c : line)
      {
        switch (c)
        {
        case 'S':
          init_state = (j << 5) | i;
          grid[i * n + j] = '.';
          break;
        case 'T':
          final_state = (j << 5) | i;
          grid[i * n + j] = '.';
          break;
        default:
          grid[i * n + j] = c;
        }
        j++;
      }
    }

    map<int, int> distances = bfs(grid, init_state, final_state);
    int min_distance = find_distances(distances, init_state, final_state);

    cout << "Case #" << num_test << endl;
    if (min_distance != -1) 
      cout << "minimum time = " << min_distance << " sec" ;
    else cout << "destination not reachable" ;
    num_test++;
  }
  return 0;
}

inline bool allowed_cell(int x, int y, vector<char> &grid)
{
  return x < m && x >= 0 && y < n && y >= 0 && grid[x * n + y] == '.';
}

vector<int> generate_states(vector<char> grid, const int state)
{
  vector<int> next_states;

  int i = 0x1F & state;
  int j = 0x1F & (state >> 5);

  int curr_direction = (state >> 10) & 0x3;

  int curr_color = state >> 12;
  int next_color = ((curr_color + 1) % 5) << 12;

  int north_state = (0x73FF & state) | (north << 10);
  int south_state = (0x73FF & state) | (south << 10);
  int east_state = (0x73FF & state) | (east << 10);
  int west_state = (0x73FF & state) | (west << 10);

  switch (curr_direction)
  {
  case north:
    next_states.push_back(east_state);
    next_states.push_back(west_state);
    if (allowed_cell(i - 1, j, grid))
      next_states.push_back((state & 0xFFFF8FE0) | (i - 1) | next_color);
    break;
  case east:
    next_states.push_back(north_state);
    next_states.push_back(south_state);
    if (allowed_cell(i, j + 1, grid))
      next_states.push_back((state & 0xFFFF8C1F) | ((j + 1) << 5) | next_color);
    break;
  case south:
    next_states.push_back(east_state);
    next_states.push_back(west_state);
    if (allowed_cell(i + 1, j, grid))
      next_states.push_back((state & 0xFFFF8FE0) | (i + 1) | next_color);
    break;
  case west:
    next_states.push_back(north_state);
    next_states.push_back(south_state);
    if (allowed_cell(i, j - 1, grid))
      next_states.push_back((state & 0xFFFF8C1F) | ((j - 1) << 5) | next_color);
    break;
  }

  return next_states;
}

map<int, int> bfs(vector<char> &grid, const int init_state, const int final_state)
{
  map<int, int> parents;
  map<int, int> distances;
  set<int> visited;
  queue<int> q;

  q.push(init_state);
  distances[init_state] = 0;

  while (!q.empty())
  {
    int curr_state = q.front(); q.pop();
    int curr_distance = distances[curr_state];
    visited.insert(curr_state);

    if ((final_state & 0x73FF) == (curr_state & 0x73FF))
      return distances;

    for (int next_state : generate_states(grid, curr_state))
    {
      if (visited.count(next_state) != 0) 
        continue;
        
      q.push(next_state);
      auto ref_old_distance = distances.find(next_state);
      float old_distance = (ref_old_distance == distances.end() ? INFINITY : ref_old_distance->second);
      float new_distance = curr_distance + 1;

      if (new_distance < old_distance)
      {
        distances[next_state] = new_distance;
        parents[next_state] = curr_state;
      }
    }
  }

  return distances;
}

int find_distances(map<int, int> &distances, const int init_state, const int final_state)
{ 
  int direction = north;
  int min_distance = INT8_MAX;
  while (direction < 4) {
    auto ref_direction = distances.find(final_state | (direction++ << 10));
    if(ref_direction == distances.end()) continue;
    min_distance = min(ref_direction->second, min_distance);
  }

  if(min_distance == INT8_MAX) return -1;
  return min_distance;
}