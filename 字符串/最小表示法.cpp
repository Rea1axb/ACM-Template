/*
序列S的最小表示为与S循环同构的所有序列中最小的序列
*/
vector<int> min_shift(vector<int> vec) {
    int len = vec.size();
    int k = 0, i = 0, j = 1;
    while (k < len && i < len && j < len) {
        if (vec[(i + k) % len] == vec[(j + k) % len]) {
            k++;
        } else {
            vec[(i + k) % len] > vec[(j + k) % len] ? i = i + k + 1 : j = j + k + 1;
            if (i == j) i++;
            k = 0;
        }
    }
    i = min(i, j);
    vector<int> res;
    for (int cnt = 0; cnt < len; cnt++) {
        res.push_back(vec[(i + cnt) % len]);
    }
    return res;
}
