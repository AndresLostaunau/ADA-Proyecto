#include <vector>
using namespace std;

struct Answer{
    vector<string> sptrie;
    int edges;
};

void print(Answer ans){                           // O(mn)
    for(int i = 0; i < ans.sptrie.size(); i++){
        for(int j = 0; j < ans.sptrie[0].size(); j++){
            std::cout<<ans.sptrie[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<"Aristas: "<<ans.edges;
}

int build_strie(vector<string>* input){                      // O(mn)
    int removed_edge_counter = 0;
    char current_char = ' ';
    for(int i = 0; i < input->size(); i++){
        for(int j = 0; j < input[0].size(); j++){
            if((*input)[i][j] != current_char){
                current_char = (*input)[i][j];
            }else if(i - 1 < 0) {
                (*input)[i][j] = '@';
                removed_edge_counter++;
            }else if((*input)[i - 1][j] == '@') {
                (*input)[i][j] = '@';
                removed_edge_counter++;
            }
        }
        current_char=' ';
    }
    return removed_edge_counter;
}

void merge(vector<int>* score_vec, vector<string>* input, int l, int mid, int r){
    vector<int> lArray, rArray, orderedArray;
    vector<string> lMatrixArray, rMatrixArray, orderedMatrixArray;
    for(int i = l; i < mid; i++){
        lArray.push_back((*score_vec)[i]);
        lMatrixArray.push_back((*input)[i]);
    }
    for(int i = mid; i < r; i++){
        rArray.push_back((*score_vec)[i]);
        rMatrixArray.push_back((*input)[i]);
    }
    int rIndex = 0, lIndex = 0;
    while(lIndex != lArray.size() || rIndex != rArray.size()){
        if(lIndex < lArray.size() && (rIndex == rArray.size() || (lArray[lIndex] < rArray[rIndex]))){
            orderedArray.emplace_back(lArray[lIndex]);
            orderedMatrixArray.emplace_back(lMatrixArray[lIndex]);
            lIndex++;
        }else{
            orderedArray.emplace_back(rArray[rIndex]);
            orderedMatrixArray.emplace_back(rMatrixArray[rIndex]);
            rIndex++;
        }
    }
    for(int i = l; i < r; i++){
        (*score_vec)[i] = orderedArray[i-l];
        (*input)[i] = orderedMatrixArray[i-l];
    }
}

void merge_sort_matrix(vector<int>* score_vec, vector<string>* input, int begin, int end){
    if(begin >= end){
        return;
    }
    int mid = (begin+end)/2;
    merge_sort_matrix(score_vec,input,begin,mid);
    merge_sort_matrix(score_vec,input,mid+1,end);
    merge(score_vec,input,begin,mid,end);
}

vector<string> transpose(vector<string> input){
    vector<string> t_matrix;
    for(int i = 0; i < input[0].size(); i++){                         // O(mn)
        t_matrix.emplace_back("");
        for(int j = 0; j < input.size(); j++){
            t_matrix[i].push_back(input[j][i]);
        }
    }
    return t_matrix;
}

vector<int> get_score(vector<string> t_matrix){
    int score;
    char actual_char;
    vector<int> score_vec;
    for(int i = 0; i < t_matrix.size(); i++){                         // O(mn)
        actual_char = ' ';
        score = 0;
        for(int j = 0; j < t_matrix[0].size(); j++){
            if(t_matrix[i][j] != actual_char){
                score++;
                actual_char=t_matrix[i][j];
            }
        }
        score_vec.emplace_back(score);
    }
    return score_vec;
}

void sort(vector<string> *t_matrix){
    vector<int> score_vec = get_score(*t_matrix);
    merge_sort_matrix(&score_vec,t_matrix,0,t_matrix->size());                     // O(mlg(m))
}

Answer greedy_algorithm(vector<string> const input){
    vector<string> t_matrix = transpose(input);
    sort(&t_matrix);
    int removed_edges = build_strie(&t_matrix);

    Answer ans;
    ans.edges = (t_matrix.size()*t_matrix[0].size()) - removed_edges;
    ans.sptrie = t_matrix;
    return ans;
}

