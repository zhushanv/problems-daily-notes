#include<bits/stdc++.h>

using namespace std;
const int N = 1e6;
//如何确定node的数量
struct node{
    bool isEnd;
    int son[26];
    set<int>passage;
}t[N];

int cnt = 1;
void insert(string s, int id){
    int now = 0;
    for(int i = 0; s[i]; i++){
        int ch = s[i] - 'a';
        if(t[now].son[ch] == 0){
            t[now].son[ch] = cnt++;
        }
        now = t[now].son[ch];
    }
    t[now].isEnd = true;
    t[now].passage.insert(id);
}

set<int> find(string s){
    set<int>ans;
    int now = 0;
    for(int i =0; s[i]; i++){
        int ch = s[i] - 'a';
        if(t[now].son[ch] == 0){
            return ans;
        }
        now = t[now].son[ch];
    }

    return t[now].passage;
}
int main(){
    int n, m, k;
    string s;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> k;
        while(k--){
            cin >> s;
            insert(s, i);
        }
    }

    cin >> m;
    while(m--){
        cin >> s;
        set<int>ans = find(s);
        for(auto x: ans){
            cout << x << " ";
        }
        cout << endl;
    }
    return 0;
}