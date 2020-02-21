#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <sstream>
#include <queue>
#include <bitset>
#include <cmath>

using namespace std;

vector<int> bfs(vector<vector<int>> &, vector<vector<int>> &, const int, const int);
vector<int> gen_states(const int, vector<vector<int>> &, vector<vector<int>> &);

int r, d, s;

int main(int argc, char **argv)
{
    string line;
    while (getline(cin, line, '\n'))
    {
        stringstream ss;
        ss << line;

        ss >> r >> d >> s;

        if (r == 0)
            break;

        vector<vector<int>> doors(r), switches(r);
        int room_a, room_b;

        while (d-- && getline(cin, line, '\n'))
        {
            ss.clear();
            ss << line;
            ss >> room_a >> room_b;

            room_a--;
            room_b--;
            doors[room_a].push_back(room_b);
            doors[room_b].push_back(room_a);
        }

        while (s-- && getline(cin, line, '\n'))
        {
            ss.clear();
            ss << line;
            ss >> room_a >> room_b;

            room_a--;
            room_b--;
            switches[room_a].push_back(room_b);
        }

        getline(cin, line, '\n');

        bfs(doors, switches, 0x10, (1 << (3 + r)) | (r - 1));
    }
    return 0;
}

vector<int> bfs(vector<vector<int>> &doors, vector<vector<int>> &switches, const int init, const int end)
{
    vector<float> distances(0xFFFF, INFINITY);
    vector<int> parents();
    set<int> visited;
    queue<int> q;

    q.push(init);
    distances[init] = 0;

    while (!q.empty())
    {
        int curr_state = q.front();
        q.pop();
        visited.insert(curr_state);
        gen_states(curr_state, doors, switches);
        // for (int next_state : gen_states(curr_state, doors, switches));
    }
}

vector<int> gen_states(const int curr_state, vector<vector<int>> &doors, vector<vector<int>> &switches)
{
    vector<int> next_states;
    int curr_room = 0xF & curr_state;
    int next_state;
    for (int room : doors[curr_room])
    {
        if (curr_state & (1 << (room + 4)))
        {
            next_state = (curr_state & 0xFFFFFFF0) | room;
            next_states.push_back(next_state);
        }
    }
    for (int room : switches[curr_room])
    {
        next_state = curr_state ^ (1 << (4 + room));
        next_states.push_back(next_state);
    }

    for (int state : next_states)
    {
        cout << bitset<8>(state) << ", ";
    }
    cout << endl;
}
