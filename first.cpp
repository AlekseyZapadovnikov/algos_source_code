#include <iostream>
#include <vector>

using namespace std;

pair<int, int> solution(int n, vector<int> flouersType) {
  int lng = 0, l = 0, r = -1;
  int ansl = l, ansr = r;
  int counter = 0, prev_t = flouersType[0];
  while (r < n - 1) {
    r++;
    int cur_fl_t = flouersType[r];
    if (prev_t == cur_fl_t) {
      counter++;
    } else {
      counter = 1;
    }
    if (counter == 3) {
      int cur_l = r - l;
      if (cur_l > lng) {
        lng = cur_l;
        ansl = l + 1;
        ansr = r;
      }
      l = r - 1;
      counter = 2;
    }
    prev_t = flouersType[r];
  }
  int flng = r - l + 1;
  if (flng > lng) {
    ansl = l + 1;
    ansr = r + 1;
  }
  return {ansl, ansr};
}

int main() {
  int n;
  if (!(cin >> n)) {
    return 0;
  }

  vector<int> fl(n);
  for (int i = 0; i < n; i++) {
    cin >> fl[i];
  }

  pair<int, int> res = solution(n, fl);
  cout << res.first << " " << res.second << endl;

  return 0;
}