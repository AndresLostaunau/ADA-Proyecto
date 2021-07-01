#include "greedy.cpp"
#include "recursive.cpp"


int main() {
    vector<string> input = {"aaa","aba","bca","bda"};
    Answer ans = greedy_algorithm(input);
    print(ans);
    return 0;
}