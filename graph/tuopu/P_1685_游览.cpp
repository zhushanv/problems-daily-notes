/* 
乍一看挺简单的，直接用dfs暴力搜索，但是超时了，dfs的复杂度怎么分析？与路径数量有关，其为指数级的
如何优化？考虑动态规划，利用已经搜索过的信息
考虑：拓朴排序预处理数据， 递推公式求解 
递推方程： dis[v] = dis[u] + cnt[u]*w
          cnt[v] += cnt[u]
需要好好消化一下这个递推的思想
*/
#include<bits/stdc++.h>

using namespace std;
const int N  = 5e4 + 5;
const int mod = 1e4;
//因为无环所以不需要记录已经删除的点
int s, t;
int n, m, t0;
struct edge{
    int to;
    int w;
    edge(int x, int y){ to = x, w = y;}
};
vector<edge>node[N];
int in[N] , vis[N], cnt[N], dis[N];
//dfs来写和bfs来写
void topo(int i){
    // printf("%d, %d, %d\n", i, dis[i], cnt[i]);
    for(auto x : node[i]){
        in[x.to]--;
        (dis[x.to]+=dis[i]+cnt[i]*x.w)%=mod;
        (cnt[x.to]+=cnt[i])%=mod;
        //这一坨有问题， 上面才是更专业的写法
        // cnt[x.to] += cnt[i];
        // dis[x.to] = (dis[i] % mod + (cnt[i] * x.w) % mod + dis[x.to]) % mod;
        if(!in[x.to]) topo(x.to); //移入队列的时机很重要,确保都是从起点能够延伸到的
    }
    //问题是无脑遍历了所有的点，以后需要思考什么时候对什么样的点做处理
    // for(int j = 1; j<= n; j++){
    //     if(!in[j] && !vis[j])
    //         topo(j);
    // }
}

void bfs(){
    queue<int>q;        
    for (int i = 1; i <= n; i++)
		if (in[i] == 0) q.push(i), cnt[i] = 1;

    while(!q.empty()){
        int k = q.front();
        q.pop();
        for(auto x : node[k]){
            in[x.to]--;
            (dis[x.to] += dis[k] + cnt[k] * x.w) %= mod;
            (cnt[x.to] += cnt[k]) %= mod;
            if(!in[x.to]) q.push(x.to);
        }
    }
}
int main(){
    cin >> n >> m >> s >> t >> t0;
    int a, b, tt;
    while(m--){
        cin >> a >> b >> tt;
        node[a].push_back(edge(b, tt));
        in[b]++;
    }
    dis[s] = 0;
    cnt[s] = 1;
    // topo(s);
    bfs();
    cout << (dis[t] + (cnt[t] - 1) * t0) % mod;
    return 0;
}