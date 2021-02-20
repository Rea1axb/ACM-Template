void print(long double ans, int x) {
    char str[100];
    sprintf(str, "%.15Lf", ans);
    int pos = 0, cnt = 0;
    while (cnt < x) {
        char ch = str[pos++];
        if ((ch != '0' && ch!= '.') || cnt) cnt++;
    }
    if (str[pos] >= '5') str[pos - 1] += 1; //四舍五入
    str[pos] = 0;
    for (int i = pos; i >= 0; i--) {
        if (str[i] == '.') break;
        if (str[i] > '9') str[i - 1]++, str[i] = '0';
    }
    printf("%s", str);
}
