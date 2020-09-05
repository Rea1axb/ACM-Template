struct Heap {
    priority_queue<int> q, era;

    void ins(int val) {
        q.push(val);
    }

    void del(int val) {
        if (val) era.push(val);
    }

    int get_max() { //第一大元素
        while (!q.empty() && !era.empty() && era.top() == q.top()) {
            q.pop();
            era.pop();
        }
        if (q.empty()) return 0;
        return q.top();
    }

    int get_semax() { //第二大元素
        int tmp = get_max();
        del(tmp);
        int res = get_max();
        ins(tmp);
        return res;
    }
}
