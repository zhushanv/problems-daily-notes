/*
错误点:
在main函数中dfs入口处没有vis判断,导致重复
在错误的地方维护了ct[id], 应该是在每次被前驱节点访问的时候更新,而不是在被调用之后
bfs和dfs实现拓扑排序的逻辑搞混了
dfs就是记忆法搜索
bfs更适合拓扑排序

超时了, 把set改为数组并且变换了一下输入方式, 毕竟数据很小, 不超时了但是wa了(眼瞎了)
下次交之前麻烦自己检查一下, 计算入度本来是in[i], 你给写成in[j],你真行
*/

/*
好好区分一下dfs实现拓扑排序和bfs实现拓扑排序,以后拓扑排序优先选用bfs,dfs会很痛
用bfs写就是一次过.....
 */
#include<bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5;
// set<int>a[N];
int dir[N][N];
int in[N], ans = 0, ct[N], vis[N];
int n,m;

//需要维护到达每一个点的最大cnt
int dfs(int id){
    if(ct[id])  return ct[id];
    ct[id] = 1; // 自身路径长度至少为1
    // for (int v : a[id]) {
    //     ct[id] = max(ct[id], dfs(v) + 1);
    // }s
    for(int i = 1; i<= n; i++){
        if(dir[id][i]){
            ct[id] = max(ct[id], dfs(i) + 1);
        }
    }
    return ct[id];
}

void bfs(){
    queue<int>q;
    for(int i = 1; i <= n; i++){
        if(!in[i]) {q.push(i); ct[i]= 1;}
    }

    while(!q.empty()){
        int id = q.front();
        ans = max(ans, ct[id]);
        q.pop();
        for(int i = 1; i <= n; i++){
            if(dir[id][i]){
                in[i]--;
                ct[i] = max(ct[i], ct[id] + 1);
                if(!in[i]) q.push(i);
            }
        }
    }
}
int main(){
    cin >> n >> m;
    int t, stop[N];
    while(m--){
        cin >> t;
        memset(vis, 0, sizeof(vis));
        for(int i = 0; i< t; i++){
            cin >> stop[i];
            vis[stop[i]] = 1;
        }
        for(int i = stop[0]+1; i < stop[t-1]; i++){
            if(!vis[i]){
                for(int j = 0; j < t; j++){
                    if(!dir[stop[j]][i]){
                        dir[stop[j]][i] = 1;
                        in[i]++;
                    }
                }
            }
        }

    }

    // for(int i = 1; i <= n; i++){
    //     if(!in[i]) ans = max(dfs(i), ans);
    // }
    bfs();
    cout << ans;
    return 0;
}