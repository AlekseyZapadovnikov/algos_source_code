#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Stack {
  vector<int> data;

  void Push(int v) {
    data.push_back(v);
  }

  pair<int, bool> Pop() {
    if (data.empty()) {
      return {0, false};
    }
    int v = data.back();
    data.pop_back();
    return {v, true};
  }

  int Len() {
    return static_cast<int>(data.size());
  }

  int Top() {
    if (data.empty()) {
      return 0;
    }
    return data.back();
  }
};

void assignValue(
    unordered_map<string, Stack>& variabls,
    unordered_map<string, bool>& curBlock,
    const string& name,
    int val
) {
  Stack& st = variabls[name];

  if (st.Len() == 0) {
    st.Push(0);
  }

  if (curBlock[name]) {
    st.data[st.data.size() - 1] = val;
  } else {
    st.Push(val);
    curBlock[name] = true;
  }
}

bool ParseDeclaration(const string& line, string& name, int& d) {
  size_t pos = line.find('=');
  if (pos == string::npos) {
    return false;
  }

  string left = line.substr(0, pos);
  string right = line.substr(pos + 1);

  try {
    size_t idx;
    d = stoi(right, &idx);
    if (idx != right.size()) {
      return false;
    }
  } catch (...) {
    return false;
  }

  name = left;
  return true;
}

bool ParseAssignment(const string& line, string& name1, string& name2) {
  size_t pos = line.find('=');
  if (pos == string::npos) {
    return false;
  }

  string left = line.substr(0, pos);
  string right = line.substr(pos + 1);

  try {
    size_t idx;
    stoi(right, &idx);
    if (idx == right.size()) {
      return false;
    }
  } catch (...) {
  }

  name1 = left;
  name2 = right;
  return true;
}

void solutio(istream& in) {
  unordered_map<string, Stack> variabls;
  vector<unordered_map<string, bool>> blocks;
  blocks.push_back(unordered_map<string, bool>());  // глобальный блок

  string line;
  while (getline(in, line)) {
    if (line == "{") {
      blocks.push_back(unordered_map<string, bool>());
      continue;
    }

    if (line == "}") {
      unordered_map<string, bool> curBlock = blocks.back();
      blocks.pop_back();

      for (const auto& [name, _] : curBlock) {
        Stack& st = variabls[name];
        st.Pop();
      }
      continue;
    }

    string name;
    int d;
    bool ok = ParseDeclaration(line, name, d);
    if (ok) {
      assignValue(variabls, blocks[blocks.size() - 1], name, d);
      continue;
    }

    string name1, name2;
    ok = ParseAssignment(line, name1, name2);
    if (ok) {
      int val = 0;
      if (variabls.find(name2) != variabls.end()) {
        val = variabls[name2].Top();
      }

      cout << val << '\n';
      assignValue(variabls, blocks[blocks.size() - 1], name1, val);
    }
  }
}

int main() {
  solutio(cin);
}