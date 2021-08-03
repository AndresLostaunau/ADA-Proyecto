#include <fstream>
#include "greedy.cpp"
#include "recursive.cpp"
#include "memoized.cpp"
#include "dynamic.cpp"

void test(vector<string> const &input){
    AnswerD ans = dynamic_algorithm(input);
    ans.print();
}

void write_test(vector<string> const &input){
    AnswerD ans = dynamic_algorithm(input);
    fstream outfile;
    outfile.open("C:\\Users\\alost\\OneDrive\\Escritorio\\ADA 2021-1\\Proyecto\\ADA-Proyecto\\out.txt");
    for(auto it:ans.sptrie){
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
    //text_test("C:\\Users\\alost\\OneDrive\\Escritorio\\ADA 2021-1\\Proyecto\\ADA-Proyecto\\inMed.txt");
    //test({"jlzrkxp","jrbrkze","shhyfzc","ghhbwzc","ahvbozc"});
    // Best case
    //test({"aaa","baa","cba","dba"});aaa","bab","cab","cbb","dcb","dcc"
    // Custom input
    //test({"bac","aab","cab","cbb"});
    //test();
    dynamic_algorithm({"jlzrkxp","jrbrkze","shhyfzc","ghhbwzc","ahvbozc"}).print();
    return 0;
}