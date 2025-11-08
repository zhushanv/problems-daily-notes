/*
第一次提交： 只过了一个
错误点:
没有考虑到可以有重复字符串的出现,即isEnd应该计数
没有搞清楚计算前缀的逻辑,在错误的地方累积了结果并返回了错误的值
*/

#include<bits/stdc++.h>

using namespace std;
const int N = 5e6;
const int B = 1e4 + 5;
struct node{
    int son[2];
    int num; //被作为前缀的次数,包含isEnd
    int isEnd; //在该位置处结尾的前缀
}t[N];
int cnt = 1;
int a[N];
void insert(int b[],int size){
    int now = 0;
    for(int i = 0; i < size; i++){
        int ch = b[i];
        if(t[now].son[ch] == 0){
            t[now].son[ch] = cnt++;
        }
        now = t[now].son[ch];
        t[now].num++;
    }
    t[now].isEnd++;
}

//能够匹配到的前缀 = 匹配路径上的完整前缀 + 匹配终点处的num
int find(int a[], int size){
    int now = 0;
    int ans = 0;
    for(int i = 0; i < size; i++){
        int ch = a[i];
        if(t[now].son[ch] == 0){
            // return t[now].num + ans;
            return ans;
        }
        //匹配到一个完整的前缀是需要特殊处理
        //注意什么时候进行判断，应该是在当前节点能够顺利转移到下一个节点之前
        // if(t[now].isEnd){
        //     // cout << i << endl;
        //     ans += t[now].isEnd;
        // }
        now = t[now].son[ch];
        ans += t[now].isEnd;
    }
    return t[now].num + ans - t[now].isEnd; //重复计算了一次
}
int main(){
    int m, n, x;
    cin >> m >> n;
    while(m--){
        cin >> x;
        for(int i = 0; i < x; i++){
            cin >> a[i];
        }
        insert(a, x);
    }

    while(n--){
        cin >> x;
        for(int i = 0; i < x; i++){
            cin >> a[i];
        }
        cout << find(a, x) << endl;
    }
    return 0;
}