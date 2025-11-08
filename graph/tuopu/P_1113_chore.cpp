/* 
第一次错误的原因：忽略了时间因素的影响
第二次错误的原因：没有vis数组记录已处理的点，导致重复调用
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e4 + 5;
vector<int>a[N];
int end_time[N], vis[N], t[N], indegree[N];
int ans = 0, n;
void dfs(int id){
    for(int to : a[id]){
        // printf("%d, %d, %d\n", id, end_time[to], end_time[id] + t[to]);
        end_time[to] = max(end_time[to], end_time[id] + t[to]);
        indegree[to]--;
    }
    for(int to : a[id]){
        if(!indegree[to] && !vis[to]){
            vis[to] = 1;
            dfs(to);
        }
    }
}
int main(){
    int x, y, z;
    cin >> n;
    memset(end_time, 0, sizeof(end_time));
    for(int i = 0; i < n; i++){
        cin >> x >> y >> z;
        t[x] = y;
        while(z){
            a[z].push_back(x);
            indegree[x]++;
            cin >> z;
        }
    }
    for(int i = 1; i <= n; i++){
        //遍历初始入度为0且还没有被访问过的点（一轮dfs后会出现很多处理过的无入度节点）
        if(!indegree[i] && !vis[i]){
            end_time[i] = t[i];
            vis[i] = 1;
            dfs(i);
        }
    }
    for(int i = 1; i <= n; i++){
        // cout << end_time[i] << endl;
        ans = max(ans, end_time[i]);
    }
    cout << ans;
    return 0;
}