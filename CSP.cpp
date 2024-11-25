#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int wordToNumber(const string& word, const vector<int>& mapping) {
    int number = 0;
    for(char c : word) {
        number = number * 10 + mapping[c - 'A'];
    }
    return number;
}

void CSP() {
    string word1 = "MATH";
    string word2 = "MYTH";
    string result = "HARD";

    string letters = "MATHYRD";

    if(letters.size() > 10) {
        cout << "There are too many letters, abort!" << endl;
        return;
    }

    vector<int> digits = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    bool foundSolution = false;

    do {
        vector<int> mapping(26, -1);
        for(int i = 0; i < letters.size(); i++) {
            mapping[letters[i] - 'A'] = digits[i];
        }

        int number1 = wordToNumber(word1, mapping);
        int number2 = wordToNumber(word2, mapping);
        int numberResult = wordToNumber(result, mapping);

        if(number1 + number2 == numberResult) {
            foundSolution = true;
            cout << "Solution Found: " << endl;
            for(int i = 0; i < letters.size(); i++) {
                cout << letters[i] << " = " << digits[i] << endl;
            }
            cout << word1 << " + " << word2 << " = " << result << endl;
            cout << number1 << " + " << number2 << " = " << numberResult << endl;
            // break;
        }

    } while(next_permutation(digits.begin(), digits.begin()+letters.size()));

    if(!foundSolution) {
        cout << "No solution found! " << endl;
    }
}

int main() {
    CSP();
    return 0;
}

// #include <iostream>
// #include <vector>
// #include <algorithm>

// using namespace std;

// int wordToNumber(const string& word, const vector<int>& mapping) {
//     int number = 0;
//     for (char c : word) {
//         number = number * 10 + mapping[c - 'A'];
//     }
//     return number;
// }

// bool manualNextPermutation(vector<int>& digits) {
//     int n = digits.size();

//     // Step 1: Find the rightmost ascending pair
//     int i = n - 2;
//     while (i >= 0 && digits[i] >= digits[i + 1]) {
//         --i;
//     }

//     // If no such pair exists, the current permutation is the last one
//     if (i < 0) {
//         return false;
//     }

//     // Step 2: Find the smallest larger element to the right of digits[i]
//     int j = n - 1;
//     while (digits[j] <= digits[i]) {
//         --j;
//     }

//     // Swap them
//     swap(digits[i], digits[j]);

//     // Step 3: Reverse the suffix
//     reverse(digits.begin() + i + 1, digits.end());

//     return true;
// }

// void CSP() {
//     string word1 = "MATH";
//     string word2 = "MYTH";
//     string result = "HARD";

//     string letters = "MATHYRD";

//     if (letters.size() > 10) {
//         cout << "There are too many letters, abort!" << endl;
//         return;
//     }

//     vector<int> digits = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

//     bool foundSolution = false;

//     do {
//         vector<int> mapping(26, -1);
//         for (int i = 0; i < letters.size(); i++) {
//             mapping[letters[i] - 'A'] = digits[i];
//         }

//         int number1 = wordToNumber(word1, mapping);
//         int number2 = wordToNumber(word2, mapping);
//         int numberResult = wordToNumber(result, mapping);

//         if (number1 + number2 == numberResult) {
//             foundSolution = true;
//             cout << "Solution Found: " << endl;
//             for (int i = 0; i < letters.size(); i++) {
//                 cout << letters[i] << " = " << digits[i] << endl;
//             }
//             cout << word1 << " + " << word2 << " = " << result << endl;
//             cout << number1 << " + " << number2 << " = " << numberResult << endl;
//             break;
//         }

//     } while (manualNextPermutation(digits));

//     if (!foundSolution) {
//         cout << "No solution found! " << endl;
//     }
// }

// int main() {
//     CSP();
//     return 0;
// }
