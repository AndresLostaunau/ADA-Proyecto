
vector<pair<int,int>> find_route(int i, int j, vector<vector<vector<int>>> const &K, int value){ //n*n*m
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

int optimal(vector<string> const &input, int i, int j                                           //n3m + n2m2
        , vector<vector<vector<int>>> const &K, vector<vector<vector<int>>> const &R
        , vector<vector<int>> &V){
    int min = INT_MAX;
    if(i == j){
        return 0;
    }else if(V[j][i]!=-1){
        return V[j][i];
    }
    for(auto a:R[j][i]){//m
        int sum = 0;
        auto route = find_route(i,j,K,a);                       //n2m
        for(auto it:route){                                     //n
            sum += optimal(input,it.first,it.second,K,R,V) + K[it.second][it.first].size() - K[j][i].size(); //n
        }
        if(sum < min){
            min = sum;
        }
    }
    V[j][i]=min;
    return min;
}

void memoized_algorithm(vector<string> const &input){
    vector<vector<vector<int>>> R;
    vector<vector<vector<int>>> K;
    vector<vector<int>> V;
    vector<vector<vector<pair<int,int>>>> C;

    for(int i=0; i < input.size(); i++){            //n*n*m
        R.emplace_back(vector<vector<int>>());
        K.emplace_back(vector<vector<int>>());
        V.emplace_back(vector<int>());
        C.emplace_back(vector<vector<pair<int,int>>>());
        for(int j = 0; j < i+1; j++) {
            R[i].emplace_back(vector<int>());
            K[i].emplace_back(vector<int>());
            C[i].emplace_back(vector<pair<int,int>>());
            V[i].push_back(-1);
            for(int k=0; k < input[0].size(); k++){
                if(input[i][k]==input[j][k]){
                    K[i][j].emplace_back(k);
                }else{
                    R[i][j].emplace_back(k);
                }
            }
        }
    }
    int i = optimal(input,0,input.size()-1,K,R,V);
    cout<<i;
}


