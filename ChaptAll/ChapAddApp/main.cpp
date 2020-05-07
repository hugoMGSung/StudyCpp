#include <iostream>
#include <regex>
#include <vector>
using namespace std;

int main() {
    int a = 0;
    decltype(a) b = 2;

    cout << b << endl;

    vector<string> file_names = { "db-123-log.txt", "db-124-log.txt",
                                  "not-db-log.txt", "db-12-log.txt",
                                  "db-12-log.jpg" };
    regex re("db-\\d*-log\\.txt");
    for (const auto& file_name : file_names) {
        cout << file_name << ": " << boolalpha << regex_match(file_name, re) << endl;
    }
}