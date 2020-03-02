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

#define allowed_cell(i, j) (grid[i * n + j] == '.' && i < m && i >= 0 && j < n && j >= 0)

using namespace std;

int m, n;

map<int, int> bfs(vector<char>, const int, const int);

int main()
{
  string line;
  while (getline(cin, line, '\n'))
  {
    stringstream ss;
    int init_state = 0, final_state = 0;
    ss << line;
    ss >> m >> n;
    if (!m)
      break;

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

    init_state |= (east << 10);

    cout << "---------------------------------" << endl;
    cout << "---------------------------------" << endl;
    map<int, int> parents = bfs(grid, init_state, final_state);

    cout << "init: " << (0x1F & init_state) << ", " << (0x1F & (init_state >> 5)) << " -> " << bitset<12>(init_state) << endl;
    cout << "final: " << (0x1F & final_state) << ", " << (0x1F & (final_state >> 5)) << " -> " << bitset<12>(final_state) << endl;
    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
        cout << grid[i * n + j];
      cout << endl;
    }
    cout << "---------------parrents------------------" << endl;
    for (auto p : parents)
    {
      cout << bitset<12>(p.first) << ": " << bitset<12>(p.second) << endl;
    }
  }
  return 0;
}

vector<int> generate_states(vector<char> grid, const int state)
{
  vector<int> next_states;

  int i = 0x1F & state;
  int j = 0x1F & (state >> 5);

  int curr_direction = state >> 10;

  int north_state = (0x3FF & state) | (north << 10);
  int south_state = (0x3FF & state) | (south << 10);
  int east_state = (0x3FF & state) | (east << 10);
  int west_state = (0x3FF & state) | (west << 10);

  switch (curr_direction)
  {
  case north:
    next_states.push_back(east_state);
    next_states.push_back(west_state);
    if (allowed_cell(i - 1, j))
      next_states.push_back((state & 0xFFFFFFE0) | (i - 1));
    break;
  case east:
    next_states.push_back(north_state);
    next_states.push_back(south_state);
    if (allowed_cell(i, j + 1))
      next_states.push_back((state & 0xFFFFFC1F) | ((j + 1) << 5));
    break;
  case south:
    next_states.push_back(east_state);
    next_states.push_back(west_state);
    if (allowed_cell(i + 1, j))
      next_states.push_back((state & 0xFFFFFFE0) | (i + 1));
    break;
  case west:
    next_states.push_back(north_state);
    next_states.push_back(south_state);
    if (allowed_cell(i, j - 1))
      next_states.push_back((state & 0xFFFFFC1F) | ((j - 1) << 5));
    break;
  }

  return next_states;
}

map<int, int> bfs(vector<char> grid, const int init_state, const int final_state)
{
  map<int, int> parents;
  map<int, int> distances;
  set<int> visited;
  queue<int> q;

  q.push(init_state);
  distances[init_state] = 0;

  while (!q.empty())
  {
    int curr_state = q.front();
    q.pop();
    int curr_distance = distances[curr_state];
    visited.insert(curr_state);

    for (int next_state : generate_states(grid, curr_state))
    {
      auto ref_old_distance = distances.find(next_state);
      float old_distance = (ref_old_distance == distances.end() ? INFINITY : ref_old_distance->second);
      float new_distance = curr_distance + 1;

      if (visited.count(next_state) == 0)
        q.push(next_state);

      if (new_distance < old_distance)
      {
        if ((next_state & 0x3FF) ^ (curr_state & 0x3FF))
          cout << bitset<10>(curr_state) << ", " << bitset<10>(next_state) << endl;
        distances[next_state] = new_distance;
        parents[next_state] = curr_state;
      }
    }
  }

  return parents;
}