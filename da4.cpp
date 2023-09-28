#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

struct numberedString{
    string value;
    int line;
    int pos;
};

int Compare(const string &x, const string &y){
    if(x.length() > y.length()){
        return 1;
    } else if (x.length() < y.length()){
        return -1;
    } else {
        for(int i = 0; i < x.length(); i++){
            if(x[i] > y[i]){
                return 1;
            } else if (x[i] < y[i]){
                return -1;
            }
        }
    }
    return 0;
}

bool IsEqualNS(numberedString &x, numberedString &y){
    return Compare(x.value, y.value) == 0;
}

string StringToLover(string &x){
    for(int i = 0; i < x.length(); i++){
        x[i] = tolower(x[i]);
    }
    return x;
}

vector <int> Zfunction(vector <numberedString> str){
    vector <int> z(str.size());
    int l = 0, r = 0;
    for(int i = 0; i < z.size(); i++){
        if(i <= r){
            z[i] = min(r - i + 1, z[i- l]);
        }
        while(i + z[i] < z.size() && IsEqualNS(str[z[i]], str[i + z[i]])){
            z[i]++;
        }
        if(i + z[i] - 1 > r){
            l = i;
            r = i + z[i] - 1;
        }
    }
    z[0] = 0;
    return z;
}

int main(){
    vector <numberedString> text;
    int patSize = 0;
    string a;
    int lineCount = 1;
    int posCount = 1;
    string str;
    stringstream ss;
    getline(cin, str);
    ss << str;
    while(ss >> a){
        patSize++;
        text.push_back({StringToLover(a), 0, patSize});
    }
    ss.clear();
    ss.str("");
    text.push_back({"#", 0, patSize + 1});
    while(getline(cin, str)){
        ss << str;
        posCount = 1;
        while(ss >> a){
            text.push_back({StringToLover(a), lineCount, posCount});
            posCount++;
        }
        lineCount++;
        ss.clear();
        ss.str("");
    }
    vector <int> z = Zfunction(text);
    for(int i = 0; i < z.size(); i++){
        if(z[i] == patSize){
            cout << text[i].line << ", " << text[i].pos << "\n";
        }
    }
    return 0;
}
