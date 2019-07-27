#include<iostream>
#include<algorithm>
#include<vector>
#include<set>

using namespace std;

struct House{
    int order;
    int left;
    int right;
    int height;
};
struct StartEndLine{
    int position;
    int height;
};


vector<int> string_split(string str){
    vector<int> result;
    str[str.size()-1] = ',';
    int size = str.size();
    int pos;
    for(int i=1; i<size; i++){
        pos = str.find(',', i);
        if(pos < size){
            result.push_back(stoi(str.substr(i,pos-i)));
            i=pos;
        }
    }
    return result;
}

bool houseLine_cmp(const House &t1, const House &t2)
{
    if(t1.left < t2.left)
        return true;
    return false;
}
bool startEndLine_cmp(const StartEndLine &t1, const StartEndLine &t2)
{
    if(t1.position < t2.position)
        return true;
    return false;
}


void print_res(StartEndLine t)
{
    cout << t.position << " " << t.height<<endl;
}

int main(){
    string str;
    vector<int> str_v;

    int n;
    cin >> n;
    vector<House> houseLine;
    vector<StartEndLine> startEndLine;
    for(int i=1;i<=n;i++){
        cin >> str;
        str_v = string_split(str);
        houseLine.push_back({i,str_v[0],str_v[1],str_v[2]});
    }
    sort(houseLine.begin(), houseLine.end(),houseLine_cmp);

    for(int i=0;i<houseLine.size();i++){
        startEndLine.push_back({houseLine[i].left,houseLine[i].height});
        startEndLine.push_back({houseLine[i].right,-houseLine[i].height});
    }
    sort(startEndLine.begin(), startEndLine.end(),startEndLine_cmp);

    multiset<int> heap;
    heap.insert(0);
    int curHeight, preHeight = 0;
    int curposition = 1, preposition = 1;

    for(auto &s : startEndLine){
        if(s.height > 0){
            heap.insert(s.height);
        }
        else{
            heap.erase(-s.height);
        }
        curHeight = *heap.rbegin();
        curposition = s.position;

        if(curHeight != preHeight){
            if(curposition != preposition && preHeight != 0){
                cout << '(' << preposition << ',' << curposition << ',' << preHeight<< ')' << endl;
            }
            curposition = s.position;

            preHeight = curHeight;
            preposition = curposition;
        }
    }


    //for_each(startEndLine.begin(), startEndLine.end(), print_res);

    return 0;
}










