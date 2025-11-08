/*
40分答案错误在哪?

*/
#include<bits/stdc++.h>

using namespace std;
const int N = 3e5 + 5;
struct node{
    int num; //统计前缀出现的数量
    int son[26];
    int isEnd;
    int id;
    string s;
    bool operator < (const node& a) const{
        return id < a.id;
    }
}t[N];
int cnt = 1;
int compare[26][26];
void insert(string s, int id){
    int now = 0;
    for(int i = 0; s[i]; i++){
        int ch = s[i] - 'a';
        if(t[now].son[ch] == 0){
            t[now].son[ch] = cnt++;
        }
        now = t[now].son[ch];
        t[now].num++;
    }
    t[now].isEnd = true;
    t[now].id = id;
    t[now].s = s;
}

int sub = 0;
bool fillCmp(int cmp[26][26], int now, int larger){
    for(int i = 0; i < 26; i++){
        if(t[now].son[i] == 0) continue;
        // printf("sign:%d, %c, %c\n", cmp[larger][i], larger + 'a', i + 'a');
        if(!cmp[larger][i]){
            cmp[larger][i] = i == larger ? 0 : 1;
            cmp[i][larger] = i == larger ? 0 : -1;
        }else if(cmp[larger][i] == -1){
            int next = t[now].son[larger];
            sub += t[next].num;
            return false;
        }
    }
    return true;
}
vector<node>ans;
void dfs(int now, int cmp[26][26]){
    if(t[now].isEnd){
        sub += t[now].num - 1;
        ans.push_back(t[now]);
        // cout << sub << " " << t[now].num << endl;
        return;
    }
    for(int i = 0; i < 26; i++){
        if(t[now].son[i]){
            int tmp[26][26];
            memcpy(tmp, cmp, sizeof(int) * 26 * 26);
            bool ok = fillCmp(cmp, now, i);
            if(!ok) continue;
            int next = t[now].son[i];
            dfs(next, cmp);
            //cmp还原
            memcpy(cmp, tmp,sizeof(int) * 26 * 26);
        }
    }
}
int main(){
    int n;
    string s;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> s;
        insert(s, i);
    }
    dfs(0, compare);
    sort(ans.begin(), ans.end());
    cout << n - sub << endl;
    for(auto x : ans){
        cout << x.s << endl;
    }
    return 0;
}