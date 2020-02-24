#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <sstream>
#include <queue>
#include <bitset>
#include <cmath>

#define get_distance(state)

using namespace std;

map<int, int> bfs(vector<vector<int>> &, vector<vector<int>> &, const int, const int);
vector<int> gen_states(const int, vector<vector<int>> &, vector<vector<int>> &);
vector<string> backtracking(map<int, int> &, const int, const int);

int r, d, s;

int main(int argc, char **argv)
{
    string line;
    int villa_no = 0;
    while (getline(cin, line, '\n'))
    {
        villa_no++;
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
        int final_state = (1 << (3 + r)) | (r - 1);
        int init_state = 0x10;
        map<int, int> parents = bfs(doors, switches, init_state, final_state);
        vector<string> path = backtracking(parents, init_state, final_state);
        
        cout << "Villa #" << villa_no << endl;

        if(final_state != init_state && path.size() == 0){
            cout << "The problem cannot be solved." << endl << endl;
            continue;
        }

        cout << "The problem can be solved in " << path.size() << " steps:" << endl;
        for (auto i = path.rbegin(); i != path.rend(); i++)
        {
            cout << *i << endl;
        }
        cout << endl;
    }
    return 0;
}

map<int, int> bfs(vector<vector<int>> &doors, vector<vector<int>> &switches, const int init, const int end)
{
    set<int> visited;
    map<int, float> distances;
    map<int, int> parents;
    queue<int> q;

    q.push(init);
    distances[init] = 0;

    while (!q.empty())
    {
        int curr_state = q.front();
        q.pop();
        visited.insert(curr_state);
        auto curr_distance_ref = distances.find(curr_state);
        float curr_distance = (curr_distance_ref != distances.end()) ? curr_distance_ref->second : INFINITY;

        for (int next_state : gen_states(curr_state, doors, switches))
        {
            auto old_distance_ref = distances.find(next_state);
            float old_distance = (old_distance_ref != distances.end()) ? old_distance_ref->second : INFINITY;
            float new_distance = curr_distance + 1;
            if (visited.count(next_state) == 0)
                q.push(next_state);

            if (new_distance < old_distance)
            {
                distances[next_state] = new_distance;
                parents[next_state] = curr_state;
            }
        }
    }

    return parents;
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
        if (room == curr_room)
            continue;
        next_state = curr_state ^ (1 << (4 + room));
        next_states.push_back(next_state);
    }
    return next_states;
}

int log_2(const int n)
{
    int i = 0;
    int m = n;
    while (m)
    {
        m >>= 1;
        i++;
    }
    return i;
}

string get_step_name(const int parent, const int curr)
{
    int parent_room = parent & 0xF;
    int curr_room = curr & 0xF;

    if (parent_room != curr_room)
        return "- Move to room " + to_string(curr_room + 1) + ".";

    int bit_diferent = parent ^ curr;
    int room_light = log_2(bit_diferent);
    bool room_was_turn_on = bit_diferent & curr;
    string switch_string_operation = (room_was_turn_on ? "on" : "off");

    return "- Switch " + switch_string_operation + " light in room " + to_string(room_light - 4) + ".";
}

vector<string> backtracking(map<int, int> &parents, const int init, const int final)
{
    vector<string> path;

    if (!parents.count(final))
        return path;

    int curr = final;
    while (curr != init)
    {
        int parent = parents[curr];
        string step_name = get_step_name(parent, curr);
        path.push_back(step_name);
        curr = parent;
    }

    return path;
}
