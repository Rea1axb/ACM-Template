/*
点差分
*/
//将u,v之间路径上德所有点权增加x
diff[u] += x, diff[v] += x, diff[lca] -= x, diff[fa[lca]] -= x;

/*
边差分
*/
//将u,v之间路径上德所有边权增加x
//以每条边两端深度较大德节点存储改变的差分数组
diff[u] += x, diff[v] += x, diff[lca] -= 2*x;
