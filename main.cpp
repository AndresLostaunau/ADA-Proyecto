#include <iostream>
#include "greedy.cpp"



int main() {
    vector<string> input = {"aaa","baa","bac","cbb"};
    Answer ans = greedy_algorithm(input);
    print(ans);
    return 0;
}