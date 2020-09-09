//sg初始化置为-1

int SG(int x) {
    if (x < 0) return 0;
    if (sg[x] >= 0) return sg[x]; //记忆化
    vector<int> vis(n + 1);
    for (int i = 1; i <= x; i++) {
        int t = SG(i - 3) ^ SG(x - i - 2);
        vis[t] = 1; //标记后继SG集合
    }
    for (int i = 0; ;i++) { //mex
        if (!vis[i]) return sg[x] = i;
    }
}

int SG(int w, int h) {
    if (sg[w][h] != -1) return sg[w][h];
    set<int> s;
    for (int i = 2; w - i >= 2; i++) {
        s.insert(SG(i, h) ^ SG(w - i, h));
    }
    for (int i = 2; h - i >= 2; i++) {
        s.insert(SG(w, i) ^ SG(w, h - i));
    }
    int res = 0;
    while (s.count(res)) res++;
    return sg[w][h] = res;
}
