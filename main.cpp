#include <fstream>
#include "greedy.cpp"
#include "recursive.cpp"
#include "memoized.cpp"
#include "dynamic.cpp"
#include "parser.cpp"

void test(vector<string> const &input){
    AnswerD ans = dynamic_algorithm(input);
    ans.print();
}

void write_test(vector<string> const &input){
    AnswerD ans = dynamic_algorithm(input);
    fstream outfile;
    outfile.open("out.txt");
    for(auto const &it:ans.sptrie){
        outfile<<it<<'\n';
    }
    /*cout<<"Permutacion: (";
    outfile<<"Permutacion: (";
    for(auto it:ans.perm){
        cout<<it<<" ";
        outfile<<it<<" ";
    }*/
    //cout<<")\n";
    //outfile<<")\n";
    std::cout<<"Aristas: "<<ans.edges;
    outfile<<"Aristas: "<<ans.edges;
    outfile.close();
}

void text_test(string filename){
    fstream file, outfile;
    file.open(filename);
    string line;
    vector<string> input;
    getline(file,line);
    while(getline(file,line)){
        input.push_back(line);
    }
    write_test(input);
}

int main() {
    // Standard case
    //text_test("inMed.txt");
    //test({"jlzrkxp","jrbrkze","shhyfzc","ghhbwzc","ahvbozc"});
    // Best case
    //test({"aaa","baa","cba","dba"});"aaa","bab","cab","cbb","dcb","dcc"
    // Custom input
    //test({"aaa","bab","cab","cbb","dcb","dcc"});
    //test();
    //auto ans2 = greedy_algorithm({"cba","cdb"});
    //auto ans = heuristic_compilation("prologfile.txt");
    compiler("prologfile.txt","query.txt");
    return 0;
}