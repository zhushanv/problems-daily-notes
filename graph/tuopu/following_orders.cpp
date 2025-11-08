/*
拓扑排序的数量是指数级的，所以用到的题目一般存在很少的点和边，故直接用邻接表进行存图更方便
用vis数组模拟删点
 */

#include<bits/stdc++.h>

using namespace std;
int n, a[25], dir[30][30];
int topo[25], vis[30], indegree[30];
void dfs(int z, int cnt){
   topo[cnt] = z;
   if(cnt == n - 1){
      for(int i = 0; i <= cnt; i++){
        printf("%c", topo[i] + 'a');
      }
      cout << endl;
      return;
   }

   vis[z] = 1;
   for(int i = 0; i < n; i++){
    if(!vis[a[i]] && dir[z][a[i]]){
        indegree[a[i]]--;
    }
   }
   for(int i = 0; i < n; i++){
    if(!vis[a[i]] && !indegree[a[i]]){
        dfs(a[i], cnt + 1);
    }
   }

   for(int i = 0; i < n; i++){
     if(!vis[a[i]] && dir[z][a[i]]){
        indegree[a[i]]++;
     }
   }
   vis[z] = 0;
}
int main(){
    string s;
    int cnt = 0;
    getline(cin, s);
    for(int i = 0; i < s.length(); i++){
        if(s[i] <= 'z' && s[i] >= 'a'){
            a[cnt++] = s[i] - 'a';
        }
    }
    n = cnt;
    sort(a, a + n); //保证结果字典序排列
    getline(cin, s);
    for(int i = 0; i < s.length() - 2; i += 4){
        // cout << s[i] << " " << s[i + 2] << endl;
        int x = s[i] - 'a', y = s[i + 2] - 'a';
        dir[x][y] = 1;
        indegree[y]++;
    }

    for(int i = 0; i < n; i++){
        if(!indegree[a[i]]){
            dfs(a[i], 0);
        }
    }
    return 0;
}