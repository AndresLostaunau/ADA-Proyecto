
vector<pair<int,int>> fin_route(int i, int j, vector<vector<vector<int>>> const &K, int value){ //m*m*n
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

int optimal(vector<string> const &input, int i, int j
        , vector<vector<vector<int>>> const &K, vector<vector<vector<int>>> const &R){
    int min = INT_MAX;
    if(i == j){
        return 0;
    }
    for(auto a:R[j][i]){
        int sum = 0;
        auto route = fin_route(i,j,K,a);
        for(auto it:route){
            sum += optimal(input,it.first,it.second,K,R) + K[it.second][it.first].size() - K[j][i].size();
        }
        if(sum < min){
            min = sum;
        }
    }
    return min;
}

void recursive_algorithm(vector<string> const &input){
    vector<vector<vector<int>>> R;
    vector<vector<vector<int>>> K;
    for(int i=0; i < input.size(); i++){            //n*n*m
        R.emplace_back(vector<vector<int>>());
        K.emplace_back(vector<vector<int>>());
        for(int j = 0; j < i+1; j++) {
            R[i].emplace_back(vector<int>());
            K[i].emplace_back(vector<int>());
            for(int k=0; k < input[0].size(); k++){
                if(input[i][k]==input[j][k]){
                    K[i][j].emplace_back(k);
                }else{
                    R[i][j].emplace_back(k);
                }
            }
        }
    }
    int i = optimal(input,0,input.size()-1,K,R);
    cout<<i;
}




