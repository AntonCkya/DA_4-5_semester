#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Node{
    int begin;
    int end;
    Node * sufflink;
    map<char, Node *> connects;
    Node(){
        begin = 0;
        end = 0;
    }
    Node(int b, int e){
        begin = b;
        end = e;
        sufflink = nullptr;
    }
};

class Trie{
private:
    string str;
    Node * root;
    Node * last;
    Node * current;
    int rem = 0;
    int edge = 0;
    int edgesize = 0;
public:
    Trie(){}
    void Build(string &newstr){
        str = newstr;
        root = new Node(str.size(), str.size());
        last = root;
        current = root;
        root->sufflink = root;
        for(int i = 0; i < str.size(); i++){
            last = root;
            rem++;
            while(rem){
                Node * newNode;
                if(edgesize == 0){
                    edge = i;
                }
                map<char, Node *>::iterator pos = current->connects.find(str[edge]);
                if(pos == current->connects.end()){
                    newNode = new Node(i, str.size());
                    current->connects[str[edge]] = newNode;
                    if(last != root){
                        last->sufflink = current;
                    }
                    last = current;
                } else {
                    newNode = pos->second;
                    int newEdgeSize = min(i + 1, newNode->end) - newNode->begin;
                    if (edgesize >= newEdgeSize){
                        edge += newEdgeSize;
                        edgesize -= newEdgeSize;
                        current = newNode;
                        continue;
                    } else if (str[newNode->begin + edgesize] == str[i]){
                        edgesize++;
                        if(last != root){
                            last->sufflink = current;
                        }
                        last = current;
                        break;
                    } else {
                        Node * split = new Node(newNode->begin, newNode->begin + edgesize);
                        Node * temp = new Node(i, str.size());
                        current->connects[str[edge]] = split;
                        split->connects[str[i]] = temp;
                        newNode->begin += edgesize;
                        split->connects[str[newNode->begin]] = newNode;
                        if(last != root){
                            last->sufflink = split;
                        }
                        last = split;
                    }
                }
                rem--;
                if(current == root && edgesize){
                    edgesize--;
                    edge = i - rem + 1;
                } else {
                    current = current->sufflink;
                }
            }
        }
    }
    vector<int> Search(string &substr){
        vector<int> res;
        int iter = 0;
        Node * currSearch = root;
        bool drop = false;
        int i = 0;
        while(i < substr.size()){
            map<char, Node *>::iterator pos = currSearch->connects.find(substr[i]);
            if(pos == currSearch->connects.end()){
                drop = true;
                break;
            } else {
                currSearch = pos->second;
                iter += currSearch->end - currSearch->begin;
                int j = 0;
                for(j = 0; i + j < substr.size() && currSearch->begin + j < currSearch->end; j++){
                    if(str[currSearch->begin + j] != substr[i + j]){
                        drop = true;
                        break;
                    }
                }
                i += j;
                if(i == substr.size()){
                    break;
                }
            }
        }
        if(substr.size() < str.size() && !drop){
            SearchRecurrent(currSearch, res, iter);
        }
        sort(res.begin(), res.end());
        return res;
    }
    void SearchRecurrent(Node * curr, vector<int> &res, int pos){
        if(curr->end == str.size()){
            res.push_back(str.size() - pos + 1);
        } else {
            for(const auto &node : curr->connects){
                SearchRecurrent(node.second, res, pos + node.second->end - node.second->begin);
            }
        }
    }
};

void Print(vector<int> res, int count){
    if(res.size() == 0){
        return;
    } else {
        cout << count << ": ";
        for(int i = 0; i < res.size(); i++){
            cout << res[i];
            if(i == res.size() - 1){
                cout << "\n";
                return;
            } else {
                cout << ", ";
            }
        }
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    Trie t;
    string str;
    cin >> str;
    str += "$";
    t.Build(str);
    int count = 1;
    string substr;
    while(cin >> substr){
        Print(t.Search(substr), count);
        count++;
    }
    return 0;
}
