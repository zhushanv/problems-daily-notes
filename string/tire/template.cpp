#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
//用结构体数组存储字典树
struct node{
    int son[26];
    int num; //出现次数
    bool isEnd;
    bool repeat;
}t[N];

int cnt = 1; //cnt = 0 留给了根节点
void insert(string s){
    int now = 0;
    for(int i = 0; s[i]; i++){
        int ch = s[i] - 'a';
        if(t[now].son[ch] == 0){
            t[now].son[ch] = cnt++;
        }
        now = t[now].son[ch];
        t[now].num++; //统计前缀出现次数
        if(i == s.length() - 1) t[now].isEnd = true;
    }
}

int find(string s){
    int now = 0;
    for(int i = 0; s[i]; i++){
        int ch = s[i] - 'a';
        if(t[now].son[ch] == 0){
            return -1; //单词不存在
        }
        now = t[now].son[ch];
    }

    if(t[now].isEnd == false) return -1;
    if(!t[now].repeat){
        t[now].repeat = true;
        return 1;
    }
    return 0;
}
int main(){
    string s;
    int n;
    cin >> n;
    while(n--){
        cin >> s;
        insert(s); 
    }
    int m;
    cin >> m;
    while(m--){
        cin >> s;
        int r = find(s);
        if(r == 0) cout << "Repeat\n";
        else if(r == 1) cout << "OK\n";
        else cout << "Wrong\n";
    }
    return 0;
}