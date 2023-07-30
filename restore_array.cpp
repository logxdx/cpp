#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int t;
    cin >> t;
    vector<string> ans(t);
    for (int i = 0; i < t; i++) {
        int n, d;
        cin >> n >> d;
        string num;
        cin >> num;
        for (int j = 0; j < n; j++) {
            if (num[j] < d + '0') {
                num.insert(j, 1, d + '0');
                break;
            }
}
        if (num.size() == n) {
            num.push_back(d + '0');
        }
        ans[i] = num;
    }
    for (const string& num : ans) {
        cout << num << endl;
    }
    return 0;
}