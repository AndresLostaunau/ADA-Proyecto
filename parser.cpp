#include <fstream>
#include <map>
using namespace std;

struct rule{
    string identifier;
    string sequence;

    rule(string const &identifier, string const &sequence) : identifier(identifier), sequence(sequence) {}
};

struct query{
    string identifier;
    string sequence;
    int var_pos;

    query(string const &identifier, string const &sequence, int varPos) : identifier(identifier), sequence(sequence),
                                                                          var_pos(varPos) {};

    void execute_query(Answer ans){
        auto sptrie = ans.sptrie;
        auto perm = ans.perm;
        auto candidate_vec = vector<bool>();
        auto value_vec = vector<char>();
        for(int i = 0; i < sptrie[0].size(); i++){
            candidate_vec.push_back(true);
        }
        for(auto const &sp:sptrie){
            for(int i = 0; i < sptrie[0].size(); i++){
                if(candidate_vec[i]){
                    if(sequence[i]=='X'){

                    }
                }
            }
        }
    }

    void execute_query(AnswerD ans){
        auto sptrie = ans.sptrie;
        auto perm = ans.perm;
        auto candidate_vec = vector<bool>();
        auto value_vec = vector<char>();
        for(int i = 0; i < sptrie[0].size(); i++){
            candidate_vec.push_back(true);
        }
        for(auto const &sp:sptrie){
            for(int i = 0; i < sptrie[0].size(); i++){
                if(candidate_vec[i]){
                    if(sequence[i]=='X'){

                    }
                }
            }
        }
    }
};

vector<rule> parse(string const &filename){
    ifstream file;
    char c;
    int state = 0;
    string identifier, sequence;
    vector<rule> ans = vector<rule>();
    file.open(filename);
    while(file.get(c)){
        if(c == '\n'){
            continue;
        }else if(state == 0){
            if(c == '('){
                state=1;
            }else{
                identifier+=c;
            }
        }else if(state == 1){
            if(c == ')'){
                ans.emplace_back(rule(identifier,sequence));
                identifier.clear();
                sequence.clear();
                state=0;
            }else if(c != ','){
                sequence+=c;
            }
        }
    }
    return ans;
}

vector<query> query_parse(string const &filename){
    ifstream file;
    char c;
    int state = 0, var_pos=0, pos=0;
    string identifier, sequence;
    vector<query> ans = vector<query>();
    file.open(filename);
    while(file.get(c)){
        if(c == '\n'){
            continue;
        }else if(state == 0){
            if(c == '('){
                state=1;
            }else{
                identifier+=c;
            }
        }else if(state == 1){
            if(c == ')'){
                ans.emplace_back(query(identifier,sequence,var_pos));
                identifier.clear();
                sequence.clear();
                state=0;
            }else if(c == 'X'){
                sequence+=c;
                var_pos = pos;
            }else if(c != ','){
                sequence+=c;
                pos++;
            }
        }
    }
    return ans;
}

map<string,Answer> heuristic_compilation(string const& filename){
    auto rules = parse(filename);
    auto pre_map = map<string,vector<string>>();
    for(auto const &it:rules){
        auto id = pre_map.find(it.identifier);
        if(id == pre_map.end()){
            pre_map.insert(pair<string,vector<string>>(it.identifier,vector<string>()));
            id = pre_map.find(it.identifier);
        }
        (*id).second.push_back(it.sequence);
    }
    auto ans_map = map<string,Answer>();
    for(auto const &it:pre_map){
        ans_map.insert(pair<string,Answer>(it.first,greedy_algorithm(it.second)));
    }
    return ans_map;
}

map<string,AnswerD> optimal_compilation(string const& filename){
    auto rules = parse(filename);
    auto pre_map = map<string,vector<string>>();
    for(auto const &it:rules){
        auto id = pre_map.find(it.identifier);
        if(id == pre_map.end()){
            pre_map.insert(pair<string,vector<string>>(it.identifier,vector<string>()));
            id = pre_map.find(it.identifier);
        }
        (*id).second.push_back(it.sequence);
    }
    auto ans_map = map<string,AnswerD>();
    for(auto const &it:pre_map){
        ans_map.insert(pair<string,AnswerD>(it.first,dynamic_algorithm(it.second)));
    }
    return ans_map;
}

void compiler(string const &rule_filename, string const &query_filename){
    cout<<"Inicializando compilador...\n"
          "Tipo de procesamiento?\n"
          "1. Heuristico\n"
          "2. Optimo\n";
    bool valid_answer = false;
    string in_string;
    int value=0;
    do{
        cin>>in_string;
        if(in_string == "1" or in_string == "2"){
            valid_answer = true;
            value = stoi(in_string);
        }else{
            cout<<"Ingrese una opcion valida.\n";
        }
    }while(!valid_answer);
    if(value==1){
        auto ans = heuristic_compilation(rule_filename);
        auto queries = query_parse(query_filename);
        for(auto it:queries){
            auto query_ans = ans.find(it.identifier);
            if(query_ans != ans.end()){
                auto sptrie = query_ans->second.sptrie;
                auto perm = query_ans->second.perm;
                auto candidate_vec = vector<bool>();
                auto value_vec = vector<char>();
                string shuffled_query;
                for(auto it2:query_ans->second.perm){
                    shuffled_query += it.sequence[it2];
                }
                for(int i = 0; i < sptrie[0].size(); i++){
                    candidate_vec.push_back(true);
                    value_vec.push_back('\0');
                }
                for(int i = 0; i < sptrie.size(); i++){
                    for(int j = 0; j < sptrie[0].size(); j++){
                        if(candidate_vec[j]){
                            if(shuffled_query[i]=='X'){
                                value_vec[j] = sptrie[i][j];
                            }else if(sptrie[i][j] == '@') {
                                candidate_vec[j] = candidate_vec[j-1];
                            }else if(shuffled_query[i] != sptrie[i][j]){
                                candidate_vec[j] = false;
                            }
                        }
                    }
                }
                cout<<query_ans->first<<":\n";
                for(int i = 0; i < candidate_vec.size(); i++){
                    if(candidate_vec[i]){
                        cout<<"X="<<value_vec[i]<<",";
                    }
                }
                cout<<'\n';
            }
        }
    }else{
        auto ans = optimal_compilation(rule_filename);
        auto queries = query_parse(query_filename);
        for(auto it:queries){
            auto query_ans = ans.find(it.identifier);
            if(query_ans != ans.end()){
                auto sptrie = query_ans->second.sptrie;
                auto perm = query_ans->second.perm;
                auto candidate_vec = vector<bool>();
                auto value_vec = vector<char>();
                vector<string> shuffled_query;
                for(int i = 0; i<query_ans->second.perm.size(); i++){
                    shuffled_query.emplace_back(string());
                    for(int j = 0; j < query_ans->second.perm[0].size(); j++){
                        shuffled_query[i] += it.sequence[perm[i][j]];
                    }
                }
                for(int i = 0; i < sptrie[0].size(); i++){
                    candidate_vec.push_back(true);
                    value_vec.push_back('\0');
                }
                for(int i = 0; i < sptrie.size(); i++){
                    for(int j = 0; j < sptrie[0].size(); j++){
                        if(candidate_vec[j]){
                            if(shuffled_query[i][j]=='X'){
                                value_vec[j] = sptrie[i][j];
                            }else if(sptrie[i][j] == '@') {
                                candidate_vec[j] = candidate_vec[j-1];
                            }else if(shuffled_query[i][j] != sptrie[i][j]){
                                candidate_vec[j] = false;
                            }
                        }
                    }
                }
                cout<<query_ans->first<<":\n";
                for(int i = 0; i < candidate_vec.size(); i++){
                    if(candidate_vec[i]){
                        cout<<"X="<<value_vec[i]<<",";
                    }
                }
                cout<<'\n';
            }
        }
    }
}
