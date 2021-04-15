#include <bits/stdc++.h>

typedef vector<int> vi;
typedef vector<int>::iterator vit;
typedef string str;
typedef map<int,int> mii;
vi nums;
mii valueNode;
vector<mii> positionChild(100000);
int ans=0;

int dfs(int pos);
void parse(str &s);
int getValue(int pos, int child);

int main(){
    ifstream file("ii.txt");
    string s;
    getline (file,s);
    parse(s);

    dfs(0);
    //part one
    cout << "part one: " << ans << endl;    
    //part two
    cout << "part two: " << valueNode[0] << endl;
    
    return 0;
}

int getValue(int pos, int child){
    /*
    if (!pos){
        for (auto &a : positionChild[pos]){
            cout << a.first << " " << a.second << endl;
        }
    }
    */
    if (child>positionChild[pos].size()) return 0;
    else return valueNode[positionChild[pos][child]];
}

int dfs(int pos){
    int i, add=2, j=10;
    if (pos<nums.size() && !nums[pos]){
        int thisNodeValue=0;
        for (i=pos+2;i<nums.size() && i<pos+2+nums[pos+1];i++) thisNodeValue+=nums[i];
        valueNode[pos]=thisNodeValue;
        ans+=thisNodeValue;
        return i;
    }
    else{
        //calc how many child this node has
        int childs=nums[pos]; 
        add+=pos;
        int numberChild=1;
        mii tmpMap;
        for (j=0;j<childs;j++,numberChild++){
            tmpMap[numberChild]=add;
            add=dfs(add);
        }
        positionChild[pos]=tmpMap;
        int parentNodeValue=0;
        for (i=0;i<nums[pos+1];i++){
            int t=getValue(pos,nums[add+i]);
            parentNodeValue+=t;
            ans+=nums[add+i];
        }
        valueNode[pos]=parentNodeValue;
    }
    return add+i;
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