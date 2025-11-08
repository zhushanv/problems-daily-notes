// /*
// 抽象为图来讲：
// 一个可以推出确定排列关系的关系图包含下列几个条件——“无环”，“一次只能出现一个无前驱的节点”
//  */
// #include<bits/stdc++.h>

// using namespace std;

// int dir[30][30], indegree[30], in[30],vis[30], topo[30];
// int n, m, ans = 0;
// //记录当前一共有多少个点出现
// set<int>st;
// void dfs(int id, int &cnt){
//     topo[cnt] = id;
//     vis[id] = 1;
//     bool isend = true;
//     for(int i = 1; i <= n; i++){
//         if(dir[id][i] && !vis[i]){
//             indegree[i]--;
//             isend = false;
//         }
//     }
//     if(isend) return;
//     for(int i = 1; i <= n; i++) {
//         if(!indegree[i] && !vis[i] && st.count(i)){
//             cnt++;
//             dfs(i, cnt);
//             break;
//         }
//     }
// }
    
// void circle(int id, int &cnt){
//     for(int i = 1; i <= n; i++){
//         if(dir[id][i] && !vis[i]){
//             indegree[i]--;
//         }
//     }

//     for(int i = 1; i<= n; i++){
//         if(!indegree[i] && !vis[i] && st.count(i)){
//             cnt++;
//             dfs(i, cnt);
//         }
//     }
// }
// int main(){
//     cin >> n >> m;
//     string s;
//     for(int j = 1; j <= m; j++){
//         cin >> s;
//         int a = s[0] - 'A' + 1, b = s[2] - 'A' + 1;
//         st.insert(a);
//         st.insert(b);
//         dir[a][b] = 1;
//         in[b]++;
//         memset(vis, 0, sizeof(vis));
//         for(int i = 1; i <= n; i++) indegree[i] = in[i];
//         int cnt = 1;
//         for(int i =1; i <= n; i++){
//             if(!indegree[i] && st.count(i)){
//                 dfs(i, cnt);
//                 break;
//             }
//         }
//         if(cnt == st.size() && cnt != n && j == m){
//             printf("Sorted sequence cannot be determined.");
//         }
//         if(cnt == st.size() && cnt == n){
//             printf("Sorted sequence determined after %d relations:", j);
//             for(int i = 1; i <= n; i++){
//                 printf("%c", topo[i] - 1 + 'A');
//             }
//             cout << ".";
//             break;
//         }
//         //有环或者不存在结果，所以得判断剩下的图里面有没有环
//         if(cnt != st.size()){
//             for(int i = 1; i <= n; i++){
//                 if(!indegree[i] && !vis[i]){
//                     cnt++;
//                     circle(i, cnt);
//                 }
//             }
//             if(cnt != st.size()){
//                 printf("Inconsistency found after %d relations.", j);
//                 break;
//             }else if(j == m){
//                 printf("Sorted sequence cannot be determined.");
//             }
//         }
//     }
    
//     return 0;
// }

/*
太乱了，我还是直接学习别人的写法吧
*/
/* 
相比于dfs实现，这道题用bfs实现更好，方便识别同时存在多个入度为0的点的情况
数据结构：相比于直接用邻接矩阵存图， 邻接表更不容易出错
 */

#include<bits/stdc++.h>

using namespace std;
int n, m;
vector<int>node[30];
stack<int>s;
set<int>st;
int vis[30], indegree[30], in[30];
int ans[30], res = 0;
bool topo(int r){
    bool isPlusible = true;
    int cnt = 0;
    for(int i = 0; i < n; i++){
        if(!indegree[i]){
            vis[i] = 1;
            s.push(i);
        }
    }

    while(!s.empty()){
        //一次有多个入度为0的点，排序不能确定，用符号标记即可，争取在模板上做最小的修改
        if(s.size() > 1) isPlusible = false;
        int k = s.top();
        ans[cnt++] = k;
        s.pop();
        for(int x : node[k]){
            indegree[x]--;
        }

        for(int i = 0; i < n; i++){
            if(!indegree[i] && !vis[i]){
                vis[i] = 1;
                s.push(i);
            }
        }
    }
    if(cnt < n){
        return false;
    }
    if(isPlusible && !res){
        res = r;
    }
    return true;
}
int main(){
    cin >> n >> m;
    string ss;
    for(int i = 1; i <= m; i++){
        cin >> ss;
        int a = ss[0] - 'A', b = ss[2] - 'A';
        node[a].push_back(b);
        in[b]++;
        for(int j = 0; j < n; j++) indegree[j] = in[j];
        memset(vis, 0, sizeof(vis));
        //若已经找到可行解，则可忽略后面出现的矛盾
        if(!topo(i) && !res){
            printf("Inconsistency found after %d relations.", i);
            return 0;
        }
    }

    if(res){
        printf("Sorted sequence determined after %d relations: ", res);
        for(int k = 0; k < n; k++){
            cout << char(ans[k] + 'A');
        }
        cout << ".";
    }else{
        cout << "Sorted sequence cannot be determined.";
    }
}