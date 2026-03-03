#include <cctype>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

struct Node {
  char letter;
  int ind;
  bool is_trap;
};

struct Stack {
  std::vector<Node> data;

  void Push(Node r) {
    data.push_back(r);
  }

  std::pair<Node, bool> Pop() {
    if (data.empty()) {
      return std::make_pair(Node{}, false);
    }
    Node last = data[data.size() - 1];
    data.pop_back();
    return std::make_pair(last, true);
  }

  std::pair<Node, bool> Top() {
    if (data.empty()) {
      return std::make_pair(Node{}, false);
    }
    return std::make_pair(data[data.size() - 1], true);
  }

  int Len() {
    return static_cast<int>(data.size());
  }
};

Stack NewStack(int cap) {
  std::vector<Node> dt;
  dt.reserve(cap);
  return Stack{dt};
}

std::pair<bool, std::vector<int>> Solution(const std::string& letters) {
  Stack stack = NewStack(0);
  std::vector<int> ans(letters.size() / 2);
  int animal_num = 0;
  int trap_num = 0;

  for (char letter : letters) {
    Node cur{
        static_cast<char>(std::tolower(static_cast<unsigned char>(letter))),
        0,
        std::isupper(static_cast<unsigned char>(letter)) != 0,
    };

    if (cur.is_trap) {
      trap_num++;
      cur.ind = trap_num;
    } else {
      animal_num++;
      cur.ind = animal_num;
    }

    if (stack.Len() > 0) {
      std::pair<Node, bool> top_res = stack.Top();
      Node top = top_res.first;
      if (top.letter == cur.letter && top.is_trap != cur.is_trap) {
        std::pair<Node, bool> pop_res = stack.Pop();
        Node v = pop_res.first;

        if (v.is_trap) {
          ans[v.ind - 1] = cur.ind;
        } else {
          ans[cur.ind - 1] = v.ind;
        }
        continue;
      }
    }

    stack.Push(cur);
  }

  return std::make_pair(stack.Len() == 0, ans);
}

int main() {
  std::string s;
  std::cin >> s;
  std::pair<bool, std::vector<int>> result = Solution(s);
  bool ok = result.first;
  std::vector<int> ans = result.second;

  if (!ok) {
    std::cout << "Impossible\n";
  } else {
    std::cout << "Possible\n";
    for (int i = 0; i < static_cast<int>(ans.size()); i++) {
      if (i > 0) {
        std::cout << " ";
      }
      std::cout << ans[i];
    }
    std::cout << "\n";
  }
}