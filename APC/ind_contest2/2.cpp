#include <iostream>
#include <string>
using namespace std;

bool isSubarubaVowel(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y');
}

int main() {
    char ch;
    cin >> ch;
    int N;
    cin >> N;
    cin.get();  

    for(int i = 0; i < N; i++) {
        string line;
        getline(cin, line);
        if(ch == 'D') {
            string result;
            for(char c : line) {
                if(isSubarubaVowel(c)) {
                    result.push_back('u');
                    result.push_back('b');
                    result.push_back(c);
                } else {
                    result.push_back(c);
                }
            }
            cout << result << "\n";

        } else {
            
            
            string result;
            for(int j = 0; j < line.size(); j++) {
                
                if(j + 2 < line.size() &&
                   line[j] == 'u' &&
                   line[j+1] == 'b' &&
                   isSubarubaVowel(line[j+2])) {
                    
                    result.push_back(line[j+2]);
                    
                    j += 2;
                } else {
                    
                    result.push_back(line[j]);
                }
            }
            cout << result << "\n";
        }
    }
    return 0;
}
