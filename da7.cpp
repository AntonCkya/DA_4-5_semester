#include <iostream>

using namespace std;

typedef unsigned long long TBigInt;
typedef char TSmallInt;

TBigInt memo[100][100]; // мемоизация

TBigInt Palindromes(string &str, TSmallInt begin, TSmallInt end){
    if (begin > end){
        return 0;
    } else if (begin == end){
        return 1;   // если один элемент, то он сам паллиндром, и больше нет
    } else {
        if (memo[begin][end] != 0){
            return memo[begin][end]; // если != 0, значит уже посчитано
        } else { // считаем 
            if (str[begin] == str[end]){
                memo[begin][end] = Palindromes(str, begin + 1, end) + Palindromes(str, begin, end - 1) + 1;
            } else {
                memo[begin][end] = Palindromes(str, begin + 1, end) + Palindromes(str, begin, end - 1) - Palindromes(str, begin + 1, end - 1);
            }
        }
        return memo[begin][end];
    }
}

int main(){
    string str;
    for(TSmallInt i = 0; i < str.size(); i++){
        for(TSmallInt j = 0; j < str.size(); j++){
            memo[i][j] = 0; // не может быть отрезка с 0 паллиндромов
        }
    }
    cin >> str;
    cout << Palindromes(str, 0, str.size() - 1) << "\n";
    return 0;
}
