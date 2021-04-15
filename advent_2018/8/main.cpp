#include <bits/stdc++.h>

typedef vector<int> vi;
typedef vector<int>::iterator vit;
typedef string str;
vi nums;
int ans=0;

int dfs(int pos);
void parse(str &s);

int main(){
    ifstream file("ii.txt");
    string s;
    getline (file,s);
    parse(s);
    int pos=0;
    int j=dfs(pos);

    cout << ans << endl;
    return 0;
}

void parse(str &s){
    int i=0;
    str tmp;
    while (i<s.length()){
        while (i<s.length() && s[i]!=' '){
            tmp+=s[i]; i++;
        }
        i++;
        int n=stol(tmp,nullptr,10);
        nums.push_back(n);
        tmp.clear();
    }
}

int dfs(int pos){
    int i, add=2, j=0;
    if (pos<nums.size() && !nums[pos]){
        for (i=pos+2;i<nums.size() && i<pos+2+nums[pos+1];i++) ans+=nums[i];
        return i;
    }
    else{
        //calc how many child this node has
        int childs=nums[pos]; 
        add+=pos;
        for (j=0;j<childs;j++){
            add=dfs(add);
        }
        for (i=0;i<nums[pos+1];i++) ans+=nums[add+i];
    }
    return add+i;
}