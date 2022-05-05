#include <algorithm>
#include <cstdint>
#include <iostream>
#include <numeric>

using namespace std;
int n;
constexpr int MAX_N = 500000;
using ll = int64_t;
int arrayA[MAX_N];
struct Operation {
    enum Type { PushBack,
                Query } op;
    int id, value, opId;
} operations[MAX_N];
ll answers[MAX_N]{};
void solve(int l, int r) {
    if (l == r) return;
    int mid = l + (r - l) / 2;
    solve(l, mid);
    solve(mid + 1, r);
    //左右的查询都完成了，answers更新完了。只差左边修改对右边查询的影响。
    // 如果 我排好序了（从大到小）， 我就可以 遍历 mid之后的查询操作，给查询答案增加值。
    // 
    inplace_merge(operations + l, operations + mid + 1, operations + r + 1, [](const Operation &a, const Operation &b) {
        if (a.value == b.value) return a.op>b.op;
        return a.value > b.value;
    });
    int influence{0};
    for (int i = l; i <= r; i++) {
        if (operations[i].op == Operation::PushBack && operations[i].opId <= mid) {
            influence++;
        }
        if (operations[i].op == Operation::Query && operations[i].opId> mid) {
            answers[operations[i].id] += influence;
        }
    }
}
int main(int argc, const char **argv) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arrayA[i];
        operations[i * 2 - 1] = {Operation::PushBack, i, arrayA[i], i * 2 - 1};
        operations[i * 2] = {Operation::Query, i, arrayA[i], i * 2};
    }
    solve(1, 2 * n);
    cout << accumulate(answers + 1, answers + n + 1, 0ll) << endl;
    return 0;
}