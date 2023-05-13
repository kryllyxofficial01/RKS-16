#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main() {
    string filepath = "tests/test.bin";
    vector<string> lines;

    ifstream reader(filepath);
    string line;
    while(getline(reader, line)) {
        lines.push_back(line);
    }

    return 0;
}