#include<bits/stdc++.h>

using namespace std;
const int N = 1e5;

struct node{
    int isEnd;
    int son[26];
}t[N];
int cnt = 1;
void insert(string s){
    int now = 0;
    for(int i = 0; s[i]; i++){
        int ch = s[i] - 'a';
        if(t[now].son[ch] == 0){
            t[now].son[ch] = cnt++;
        }
        now = t[now].son[ch];
    }
    t[now].isEnd = true;
}
//返回最后一个匹配的位置
int find(string s, int start){
    int now = 0;
    int end = start -1; //记录最近一个匹配到单词末尾的位置
    for(int i = start; s[i]; i++){
        int ch = s[i] - 'a';
        // cout << s[i] << " " << endl;
        if(t[now].son[ch] == 0){
            return end;
        }
        now = t[now].son[ch];
        if(t[now].isEnd) end = i;
    }
    if(t[now].isEnd) return s.length() - 1;
    
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    string s;
    cin >> n >> m;
    while(n--){
        cin >> s;
        insert(s);
    }

    while(m--){
        cin >> s;
        int pre, now;
        pre = now = -1;
        now = find(s, 0);
        while(now < s.length()-1 && now != pre){
            pre = now;
            now = find(s, now+1);
            // cout << pre << " " << now << endl;
        }
        cout << now + 1 << endl;
    }
    return 0;
}