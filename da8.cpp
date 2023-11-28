#include <iostream>
#include <vector>

using namespace std;

int main(){
    int countOne = 0, countTwo = 0, countThree = 0;
    int n, digit;
    cin >> n;
    vector<int> array;
    for (int i = 0; i < n; i++){
        cin >> digit;
        array.push_back(digit);
        switch(digit){
            case 1:
                countOne++;
                break;
            case 2:
                countTwo++;
                break;
            case 3:
                countThree++;
                break;
        }
    }
    int ans = 0;
    for (int i = 0; i < countOne; i++){
        if (array[i] == 2){
            int pos;
            for (int j = countOne; j < n; j++){
                if (array[j] == 1){
                    pos = j;
                    break;
                }
            }
            int temp;
            temp = array[i];
            array[i] = array[pos];
            array[pos] = temp;
            ans++;
        } else if (array[i] == 3){
            int pos;
            for (int j = n; j >= countOne; j--){
                if (array[j] == 1){
                    pos = j;
                    break;
                }
            }
            int temp;
            temp = array[i];
            array[i] = array[pos];
            array[pos] = temp;
            ans++;
        }
    }
    for (int i = countOne; i < countOne + countTwo; i++){
        if (array[i] == 3){
            int pos;
            for (int j = countOne + countTwo; j < n; j++){
                if (array[j] == 2){
                    pos = j;
                    break;
                }
            }
            int temp;
            temp = array[i];
            array[i] = array[pos];
            array[pos] = temp;
            ans++;
        }
    }
    cout << ans << "\n";
    return 0;
}
