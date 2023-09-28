#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef bool Tcolor;
const Tcolor RED = true;
const Tcolor BLACK = false;

typedef unsigned long long ull;

struct node{
    node * parent;
    node * left;
    node * right;
    Tcolor color;
    string key;
    ull value;
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

string StringToLover(string &x){
    for(int i = 0; i < x.length(); i++){
        x[i] = tolower(x[i]);
    }
    return x;
}

class Dict{
    private:

    node * NullNode;

    void LRotate(node * x);
    void RRotate(node * x);

    node * MinRight(node * x);
    node * MaxLeft(node * x);

    void AddFix(node * x);
    void DeleteFix(node * x);
    
    public:

    node * root;

    Dict();
    ~Dict();

    string Add(const string &key, ull value);
    string Delete(const string &key);

    void Erace(node * x);
    void Get(const string &key);

    void SaveFile(ofstream &file, node * x);
    void LoadFile(ifstream &file);

    void Print(node * x, int level);
};

Dict::Dict(){
    NullNode = new node();
    NullNode->color = BLACK;
    root = NullNode;
}

Dict::~Dict(){
    Erace(root);
    delete NullNode;
}

void Dict::LRotate(node * x){
    node * xRight = x->right;
    x->right = xRight->left;
    if (xRight->left != NullNode) {
        xRight->left->parent = x;
    }
    xRight->parent = x->parent;
    if (x->parent == nullptr) {
        root = xRight;
    }
    else if (x == x->parent->left) {
        x->parent->left = xRight;
    }
    else {
        x->parent->right = xRight;
    }
    xRight->left = x;
    x->parent = xRight;
}

void Dict::RRotate(node * x){
    node * xLeft = x->left;
    x->left = xLeft->right;
    if (xLeft->right != NullNode) {
        xLeft->right->parent = x;
    }
    xLeft->parent = x->parent;
    if (x->parent == nullptr) {
        root = xLeft;
    }
    else if (x == x->parent->right) {
        x->parent->right = xLeft;
    }
    else {
        x->parent->left = xLeft;
    }
    xLeft->right = x;
    x->parent = xLeft;
}

node * Dict::MinRight(node * x){
    while(x->left != NullNode){
        x = x->left;
    }
    return x;
}

node * Dict::MaxLeft(node * x){
    while(x->right != NullNode){
        x = x->right;
    }
    return x;
}

void Dict::AddFix(node * x){
    while(x->parent != nullptr && x->parent->color == RED){
        if(x->parent == x->parent->parent->left){
            node * uncle = x->parent->parent->right;
            if(uncle->color == RED){
                uncle->color = BLACK;
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {
                if(x == x->parent->right){
                    x = x->parent;
                    LRotate(x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                RRotate(x->parent->parent);
            }
        } else {
            node * uncle = x->parent->parent->left;
            if(uncle->color == RED){
                uncle->color = BLACK;
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {
                if(x == x->parent->left){
                    x = x->parent;
                    RRotate(x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                LRotate(x->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void Dict::DeleteFix(node * x) {
    node * bro;
    while(x != root && x->color == BLACK){
        if(x == x->parent->left){
            bro = x->parent->right;
            if(bro->color == RED){
                bro->color = BLACK;
                x->parent->color = RED;
                LRotate(x->parent);
                bro = x->parent->right; 
            }
            if(bro->left->color == BLACK && bro->right->color == BLACK){
                bro->color = RED;
                x = x->parent;
            } else {
                if(bro->right->color == BLACK){
                    bro->left->color = BLACK;
                    bro->color = RED;
                    RRotate(bro);
                    bro = x->parent->right;
                }
                bro->color = x->parent->color;
                x->parent->color = BLACK;
                bro->right->color = BLACK;
                LRotate(x->parent);
                x = root;
            }
        } else {
            bro = x->parent->left;
            if(bro->color == RED){
                bro->color = BLACK;
                x->parent->color = RED;
                RRotate(x->parent);
                bro = x->parent->left;
            }
            if(bro->right->color == BLACK && bro->left->color == BLACK){
                bro->color = RED;
                x = x->parent;
            } else {
                if(bro->left->color == BLACK){
                    bro->right->color = BLACK;
                    bro->color = RED;
                    LRotate(bro);
                    bro = x->parent->left;
                }
                bro->color = x->parent->color;
                x->parent->color = BLACK;
                bro->left->color = BLACK;
                RRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

string Dict::Add(const string &key, ull value){
    node * newNode = new node();
    newNode->key = key;
    newNode->value = value;
    newNode->left = NullNode;
    newNode->right = NullNode;
    newNode->parent = nullptr;
    newNode->color = RED;

    node * curr = root;
    node * currPar = nullptr;

    while(curr != NullNode){
        currPar = curr;
        int comp = Compare(curr->key, key);
        if(comp == 1){
            curr = curr->left;
        } else if (comp == -1){
            curr = curr->right;
        } else {
            delete newNode;
            return "Exist\n";
        }
    }

    newNode->parent = currPar;
    if(currPar == nullptr){
        root = newNode;
    } else {
        int comp = Compare(newNode->key, currPar->key);
        if(comp == 1){
            currPar->right = newNode;
        } else {
            currPar->left = newNode;
        }
    }
        
    if(newNode->parent == nullptr){
        newNode->color = BLACK;
        return "OK\n";
    } else if(newNode->parent->parent == nullptr){
        return "OK\n";
    }
    AddFix(newNode);
    return "OK\n";
}

string Dict::Delete(const string &key){
    node * curr = root;
    node * rem = NullNode, * fix, * temp;
    while(curr != NullNode){
        int comp = Compare(curr->key, key);
        if(comp == 1){
            curr = curr->left;
        } else if (comp == -1){
            curr = curr->right;
        } else {
            rem = curr;
            break;
        }
    }
 
    if(rem == NullNode){
        return "NoSuchWord\n";
    }
        
    temp = rem;
    Tcolor TempColor = temp->color;
    if(rem->left == NullNode){
        fix = rem->right;
        if(rem->parent == nullptr){
            root = rem->right;
        } else {
            if(rem == rem->parent->left){
                rem->parent->left = rem->right;
            } else {
                rem->parent->right = rem->right;
            }
        }
        rem->right->parent = rem->parent;
    } else if(rem->right == NullNode){
        fix = rem->left;
        if(rem->parent == nullptr){
            root = rem->left;
        } else {
            if(rem == rem->parent->left){
                rem->parent->left = rem->left;
            } else {
                rem->parent->right = rem->left;
            }
        }
        rem->left->parent = rem->parent;
    } else {
        temp = MinRight(rem->right);
        TempColor = temp->color;
        fix = temp->right;
        if(temp->parent == rem){
            fix->parent = temp;
        } else {
            if(temp->parent == nullptr){
                root = temp->right;
            } else {
                if(temp == temp->parent->left){
                    temp->parent->left = temp->right;
                } else {
                    temp->parent->right = temp->right;
                }
            }
            temp->right->parent = temp->parent;
            temp->right = rem->right;
            temp->right->parent = temp;
        }
        if(rem->parent == nullptr){
            root = temp;
        } else {
            if(rem == rem->parent->left){
                rem->parent->left = temp;
            } else {
                rem->parent->right = temp;
            }
        }
        temp->parent = rem->parent;
        temp->left = rem->left;
        temp->left->parent = temp;
        temp->color = rem->color;
    }
    delete rem;
    if(TempColor == BLACK){
        DeleteFix(fix);
    }
    return "OK\n";
}

void Dict::Erace(node * x){
    if(x == NullNode){
        return;
    }
    if(x->left != NullNode){
        Erace(x->left);
    }
    if(x->right != NullNode){
        Erace(x->right);
    }
    delete x;
    root = NullNode;
}

void Dict::Get(const string &key){
    node * curr = root;
    while(curr != NullNode){
        int comp = Compare(curr->key, key);
        if(comp == 1){
            curr = curr->left;
        } else if (comp == -1){
            curr = curr->right;
        } else {
            cout << "OK: " << curr->value << "\n";
            return;
        }
    }
    cout << "NoSuchWord\n";
}

void Dict::SaveFile(ofstream &file, node * x){   //naive
    if(x == NullNode){
        return;
    } else {
        size_t n = x->key.size();
        string key = x->key;
        ull value = x->value;
        file.write((char *)&n, sizeof(size_t));
        file.write(key.c_str(), sizeof(char) * n);
        file.write((char *)&value, sizeof(ull));
        SaveFile(file, x->left);
        SaveFile(file, x->right);
    }
} //after that write -1 for end of file

void Dict::LoadFile(ifstream &file){
    Erace(root);
    if(file.peek() == EOF){
        cout << "OK\n";
        return;
    }
    size_t n;
    string key;
    ull value;
    file.read((char *)&n, sizeof(size_t));
    while(n != -1){
        key.clear();
        key.resize(n);
        file.read((char *)key.data(), sizeof(char) * n);
        file.read((char *)&value, sizeof(ull));
        Add(key, value);
        file.read((char *)&n, sizeof(size_t));
    }
    cout << "OK\n";
}

void Dict::Print(node * x, int level){    //method for debugging (helpful)
    if(x != NullNode){
        cout << level << " " << x->key << " " << x->value << " " << x->color << "\n";
        level++;
        Print(x->left, level);
        Print(x->right, level);
        cout << "--" << x->key << "--\n";
    }
}

int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(0);
    Dict d;
    string command, key, path, answer;
    ull value;
    while(cin >> command){
        if(command == "+"){
            cin >> key >> value;
            key = StringToLover(key);
            answer = d.Add(key, value);
            cout << answer;
        } else if (command == "-"){
            cin >> key;
            key = StringToLover(key);
            answer = d.Delete(key);
            cout << answer;
        } /* else if (command == "print"){
            d.Print(d.root, 0);
        } else if (command == "erace"){
            d.Erace(d.root);
        } */ else if (command == "!"){
            cin >> command;
            if(command == "Save"){
                cin >> path;
                ofstream file;
                file.open(path, ios_base::binary);
                d.SaveFile(file, d.root);
                cout << "OK\n";
                size_t i = -1;
                file.write((char *)&i, sizeof(size_t));
                file.close();
            } else if(command == "Load"){
                cin >> path;
                ifstream file;
                file.open(path, ios_base::binary);
                d.LoadFile(file);
                file.close();
            }
        }else {
            key = StringToLover(command);
            d.Get(key);
        }
    }
    return 0;
}
