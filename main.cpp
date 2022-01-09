#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class n_color_solution {
 private:
  vector<vector<int>> adjacent;
  vector<string> colors;
  vector<int> coloring;
  unordered_set<int> visited;

  bool clash(int curr_color, int node) {
    for (const auto& neighbor : adjacent[node])
      if (coloring[neighbor] == curr_color) return true;
    return false;
  }

 public:
  n_color_solution(const auto& adjacent, const auto& colors) {
    this->adjacent = adjacent;
    this->colors = colors;
    this->coloring.resize(adjacent.size(), -1);
  }

  bool solvable(int node = 0, int curr_color = 0) {
    if (visited.contains(node) or clash(curr_color, node)) return false;
    visited.emplace(node);
    coloring[node] = curr_color;
    if (visited.size() == adjacent.size()) {
      for (int i = 0; i < adjacent.size(); ++i)
        cout << "Node " << i + 1 << ' ' << colors[coloring[i]] << endl;
      return true;
    }
    for (const auto& neighbor : adjacent[node])
      for (int color = 0; color < colors.size(); ++color)
        if (solvable(neighbor, color)) return true;
    return false;
  }
};

int main() {
  char input;
  cout << "Do you wanna use the default case of the question in class (Y/N)? ";
  cin >> input;
  vector<vector<int>> adjacent;
  vector<string> colors;
  if (toupper(input) != 'Y') {
    int n_nodes, n_colors;
    cout << "Enter number of nodes: ";
    cin >> n_nodes;
    cout << "Enter number of colors: ";
    cin >> n_colors;
    adjacent.resize(n_nodes);
    colors.resize(n_colors);
    for (int i = 0; i < n_nodes; ++i) {
      string input;
      while (input != "end") {
        cout << "Enter neighbor of node " << i + 1 << "(input end to stop entering): ";
        cin >> input;
        if (input != "end") adjacent[i].emplace_back(stoi(input) - 1);
      }
    }
    for (int i = 0; i < n_colors; ++i) {
      string input;
      cout << "Enter name of the color " << i + 1 << ": ";
      cin >> input;
      colors[i] = input;
    }
  } else {
    adjacent = {
        {1, 2},              // 1
        {0, 2, 3, 4, 5},     // 2
        {0, 1, 3, 7, 8},     // 3
        {1, 2, 4, 6, 8, 9},  // 4
        {1, 3, 5, 6},        // 5
        {1, 4},              // 6
        {3, 4, 8, 9},        // 7
        {2, 8},              // 8
        {2, 3, 6, 7, 9},     // 9
        {3, 6, 8}};          // 10
    colors = {"RED", "GREEN", "BLUE", "YELLOW"};
  }
  n_color_solution s(adjacent, colors);
  cout.setf(ios::boolalpha);
  cout << s.solvable();
};
