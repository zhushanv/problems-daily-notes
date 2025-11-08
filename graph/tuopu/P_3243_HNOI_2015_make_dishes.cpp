/*
思路一:(属于是耍小聪明,在原本的模板上走得太远,吃了大亏)
从目标点先上搜索,合并子树答案, 合并答案的复杂度略高,且有逻辑上的bug,因为保证不了完成的先后顺序,nonono
思路二:
建图,双向边,调用dfs前,向上搜索能够到达的点,随后拓扑排序,找到在搜索路径上的点进行排序,且当前入度为0的点
应该存入优先队列中,每次调用最小的点,也有bug,质量更高的还没有入度为0,关键问题是如何选择入度为0的点,不会
正确思路:
反向拓扑排序的最大字典序的序列,多画几个图可以找出规律,难的是证明,证明链接(https://www.luogu.com.cn/article/tp38r8c9),思路一与其有点类似,只不过我把思路一做成了树上的分治,如何在思路一的基础上考虑怎么
选择入度为0的点进行新的拓扑排序,会好很多.
*/

#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
vector<int>from[N];
int indegree[N], vis[N];
int n, m, cnt;
priority_queue<int>pq;

vector<int> bfs(){
    vector<int>ans;
    while(!pq.empty()){
        int id = pq.top();  
        pq.pop();
        vis[id] = 1;
        ans.push_back(id);
        for(auto x : from[id]){
            indegree[x]--;
            if(!indegree[x]) pq.push(x);
        }
    }
    return ans;
}
int main(){
    int T;
    cin >> T;
    while(T--){
        cin >> n >> m;
        memset(vis, 0, sizeof(vis));
        memset(indegree, 0, sizeof(indegree));
        for(int i = 1; i <= n; i++){
            from[i].clear();
        }
        int x, y;
        while(m--){
            cin >> x >> y;
            from[y].push_back(x);
            indegree[x]++;
        }

        for(int i = 1; i <= n; i++){
            if(!indegree[i]){ pq.push(i);}
        }

        //起点不是i
        vector<int>ans = bfs();
        if(ans.size() < n){
            cout << "Impossible!";
        }else{
            for(auto it = ans.rbegin(); it != ans.rend(); it++){
                cout << *it << " ";
            }
        }
        cout << endl;
    }   
    return 0;
}