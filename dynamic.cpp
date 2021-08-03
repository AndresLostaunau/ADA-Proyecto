#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct AnswerD{
    vector<string> sptrie;
    vector<vector<int>> perm;
    int edges;

    AnswerD(){
        edges = -1;
    }

    void init(int x, int y){
        for(int i = 0; i < y; i++){
            sptrie.emplace_back("");
            perm.emplace_back(vector<int>());
            for(int j = 0; j < x; j++){
                sptrie[i].push_back('@');
                perm[i].push_back(-1);
            }
        }
    }

    void add(AnswerD const &ans, int offset_x, int offset_y){
        for(int i = 0; i < ans.sptrie[0].size(); i++){
            for(int j = 0; j < ans.sptrie.size(); j++){
                this->sptrie[offset_y+j][offset_x+i] = ans.sptrie[j][i];
                this->perm[offset_y+j][offset_x+i]=ans.perm[j][i];
            }
        }
    }

    void setperm(int p){
        for(int i = 0; i < this->sptrie.size(); i++){
            this->perm[0][i] = p;
        }
    }

    void setperm(vector<int> p){
        for(int i = 0; i < p.size(); i++){
            this->perm[i][0] = p[i];
        }
    }

    void print(){
        for(int i = 0; i < sptrie.size(); i++){
            for(int j = 0; j < sptrie[0].size(); j++){
                cout<<sptrie[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        for(int i = 0; i < sptrie.size(); i++){
            for(int j = 0; j < sptrie[0].size(); j++){
                cout<<perm[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<"\nAristas: "<<edges<<endl;
    }
};

vector<pair<int,int>> findd_route(int i, int j, vector<vector<vector<int>>> const &K, int value){ //m*m*n
    vector<pair<int,int>> route;
    bool break_enabled = false;
    int skip_until = -1;
    for(int a = i; a <= j; a++){
        if(a > skip_until){
            for(int b=j; b >= i; b--){
                if(!K[b][a].empty()){
                    for(auto it:K[b][a]){
                        if(it==value){
                            route.emplace_back(pair<int,int>(a,b));
                            skip_until = b;
                            break_enabled = true;
                            break;
                        }
                    }
                }
                if(break_enabled){
                    break_enabled = false;
                    break;
                }
            }
        }
    }
    return route;
}

AnswerD optimal(vector<string> const &input, int i, int j
        , vector<vector<vector<int>>> const &K, vector<vector<vector<int>>> const &R
        , vector<vector<AnswerD*>> &V
        , int pos
        , vector<int> remVec){
    /*if(V[j][i]->edges != -1){
        return *V[j][i];
    }*/
    auto ans = new AnswerD;
    int min = INT_MAX;
    vector<pair<int,int>> min_pair;
    ans->init(j-i+1,remVec.size());
    if(i == j){
        for(int k = 0;k < remVec.size();k++){
            ans->sptrie[k]=input[i][remVec[k]];
        }
        ans->edges = 0;
        ans->setperm(remVec);
        return *ans;
    }
    for(auto it:K[j][i]){
        auto candidate = find(remVec.begin(),remVec.end(),it);
        if(candidate!=remVec.end()){
            remVec.erase(find(remVec.begin(),remVec.end(),it));
            auto o = optimal(input,i,j,K,R,V,pos+1,remVec);
            ans->add(o,0,1);
            ans->sptrie[0][0] = input[i][it];
            ans->setperm(it);
            ans->edges = o.edges;
            V[j][i] = ans;
            return *ans;
        }
    }
    AnswerD ans_copy;
    AnswerD min_ans;
    for(auto a:R[j][i]){
        int sum = 0;
        ans_copy = *ans;
        auto route = findd_route(i,j,K,a);
        for(auto it:route){                                     //n*m
            auto lel = optimal(input,it.first,it.second,K,R,V,pos,remVec);
            sum += lel.edges + K[it.second][it.first].size() - K[j][i].size();
            ans_copy.add(lel,it.first-i,0);
        }
        if(sum < min){
            min = sum;
            min_pair=route;
            min_ans=ans_copy;
        }
    }
    min_ans.edges=min;
    *ans = min_ans;
    V[j][i]=ans;
    return *ans;
}

AnswerD dynamic_algorithm(vector<string> const &input){
    vector<vector<vector<int>>> R;
    vector<vector<vector<int>>> K;
    vector<vector<AnswerD*>> V;
    vector<int> remVec;
    for(int i=0; i < input.size(); i++){            //n*n*m
        R.emplace_back(vector<vector<int>>());
        K.emplace_back(vector<vector<int>>());
        V.emplace_back(vector<AnswerD*>());
        for(int j = 0; j < i+1; j++) {
            R[i].emplace_back(vector<int>());
            K[i].emplace_back(vector<int>());
            V[i].emplace_back(new AnswerD);
            for(int k=0; k < input[0].size(); k++){
                if(input[i][k]==input[j][k]){
                    K[i][j].emplace_back(k);
                }else{
                    R[i][j].emplace_back(k);
                }
            }
        }
    }
    for(int i = 0; i < input[0].size(); i++){
        remVec.push_back(i);
    }
    auto ans = optimal(input,0,input.size()-1,K,R,V,0,remVec);
    return ans;
}

