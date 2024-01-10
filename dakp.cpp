#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <unordered_map>

typedef long long ll;
typedef unsigned long long ull;

namespace archive{
    namespace RLE
    {
        struct Pair{
            ll symbol;
            ll count;
        };

        std::vector<ll> Decode(std::vector<Pair> pairStr){
            std::vector<ll> strNums;
            for(Pair p: pairStr){
                for(ll i = 0; i < p.count; i++){
                    strNums.push_back(p.symbol);
                }
            }
            return strNums;
        }

        std::vector<Pair> Encode(std::vector<ll> str){
            std::vector<Pair> pairStr;
            Pair p = {str[0], 1};
            for(ll i = 1; i < str.size(); i++){
                if (str[i] == p.symbol){
                    p.count++;
                } else {
                    pairStr.push_back(p);
                    p = {str[i], 1};
                }
            }
            pairStr.push_back(p);
            return pairStr;
        }

        void Print(std::vector<Pair> pairStr){
            for(Pair p: pairStr){
                std::cout << p.count << " " << p.symbol << "\n";
            }
        }

        std::vector<Pair> Scan(){
            std::stringstream ss;
            ll symbol, count;
            std::string buf;
            std::vector<Pair> res;
            while (std::getline(std::cin, buf)){
                ss << buf;
                ss >> count >> symbol;
                Pair p;
                p.symbol = symbol;
                p.count = count;
                res.push_back(p);
                ss.clear();
                ss.str("");
            }
            return res;
        }

    } // namespace RLE

    namespace MTF
    {
        const std::string ABC = "$abcdefghijklmnopqrstuvwxyz";

        void ToBegin(std::string &s, ll pos){
            char sym = s[pos];
            s.erase(pos, 1);
            s = sym + s;
        }

        ll FindFirst(std::string s, char c){
            for(ll i = 0; i < s.size(); i++){
                if (s[i] == c){
                    return i;
                }
            }
            return -1;
        }

        std::vector<ll> Encode(std::string str){
            std::string localABC = "";
            localABC += ABC;
            std::vector<ll> strNums;
            for(ll i = 0; i < str.size(); i++){
                ll pos = FindFirst(localABC, str[i]);
                ToBegin(localABC, pos);
                strNums.push_back(pos);
            }
            return strNums;
        }

        std::string Decode(std::vector<ll> strNums){
            std::string localABC = "";
            localABC += ABC;
            std::string str = "";
            for(ll i = 0; i < strNums.size(); i++){
                str += localABC[strNums[i]];
                ToBegin(localABC, strNums[i]);
            }
            return str;
        }

        void Print(std::vector<ll> strNums){
            for(ll i: strNums){
                std::cout << i << " ";
            }
            std::cout << "\n";
        }
    } // namespace MTF

    namespace BWT
    {
        const std::string ABC = "$abcdefghijklmnopqrstuvwxyz";
        const ull MASK_SIZE = 16;
        const ull MASK = (1<<MASK_SIZE) - 1;
        std::unordered_map<char, ll> ABCtoll;

        void CountingSort(std::vector<std::pair<ll, ll>> &arr1, std::vector<std::pair<ll, ll>> &arr2, ll iter){
            ll index;
            std::vector<ll> count(1<<MASK_SIZE, 0);
            for(ll i = 0; i < arr1.size(); i++){
                count[(arr1[i].second >> MASK_SIZE * iter) & MASK]++;
            }
            for(ll i = 1; i < 1<<MASK_SIZE; i++){
                count[i] += count [i - 1];
            }
            for (ll i = arr1.size() - 1; i >= 0; i--) {
                arr2[count[(arr1[i].second >> MASK_SIZE * iter) & MASK] - 1] = arr1[i];
                count[(arr1[i].second >> MASK_SIZE * iter) & MASK]--;
            }
        }

        void RadixSort(std::vector<std::pair<ll, ll>> &arr){
            std::vector<std::pair<ll, ll>> temp(arr.size());
            for(ll i = 0; i < 64/MASK_SIZE; i++){
                if(i % 2 == 0){
                    CountingSort(arr, temp, i);
                } else {
                    CountingSort(temp, arr, i);
                }
            }
        }

        bool MakeClassEq(std::vector<ll> &arr, std::vector<std::pair<ll, ll>> &res, ll iter){
            RadixSort(res);
            std::vector<std::pair<ll, ll>> classEq(arr.size());
            ll currClassEq = 1;
            for(ll i = 0; i < arr.size(); i++){
                ll temp = res[i].first + iter;
                if(temp > res.size()){
                    temp -= res.size();
                }
                classEq[i].first = res[i].second;
                classEq[i].second = arr[temp - 1];
            }
            res[0].second = 1;
            for(ll i = 1; i < arr.size(); i++){
                if(classEq[i] != classEq[i - 1]){
                    currClassEq++;
                }
                res[i].second = currClassEq;
            }
            return currClassEq == arr.size();
        }

        std::vector<std::pair<ll, ll>> SuffArrRes(std::string &str){
            std::vector<std::pair<ll, ll>> res(str.size());
            for(ll i = 0; i < str.size(); i++){
                res[i].first = i + 1;
                res[i].second = str[i];
            }
            RadixSort(res);
            std::vector<ll> classEq(str.size());
            ll currClassEq = 1;
            classEq[0] = 1;
            for(ll i = 1; i < str.size(); i++){
                if(res[i].second != res[i - 1].second){
                    currClassEq++;
                }
                classEq[i] = currClassEq;
            }
            for(ll i = 0; i < str.size(); i++){
                res[i].second = classEq[i];
            }
            if(currClassEq == str.size()){
                return res;
            }
            ll iter = 1;
            while(iter <= str.size()){
                std::vector<ll> temp(res.size());
                for(ll i = 0; i < str.size(); i++){
                    temp[res[i].first - 1] = res[i].second;
                }
                for(ll i = 0; i < str.size(); i++){
                    res[i].first -= iter;
                    if(res[i].first <= 0){
                        res[i].first += str.size();
                    }
                    res[i].second = temp[res[i].first - 1];
                }
                bool stop = MakeClassEq(temp, res, iter);
                if(stop){
                    return res;
                }
                iter *= 2;
            }
            return res;
        }

        void FillMap(){
            for(ll i = 0; i < ABC.size(); i++){
                ABCtoll[ABC[i]] = i;
            }
        }

        std::string Encode(std::string &str){
            std::vector<std::pair<ll, ll>> resArr = SuffArrRes(str);
            std::string res = "";
            for(ll i = 0; i < resArr.size(); i++){
                res += str[(resArr[i].first + str.size() - 2) % str.size()];
            }
            return res;
        }

        std::string Decode(std::string str){
            FillMap();
            std::vector<ll> freq;
            freq.resize(ABC.size(), 0);
            std::vector<ll> transform;
            transform.resize(str.size(), 0);
            for(char x: str){
                freq[ABCtoll[x]]++;
            }
            ll s = 0;
            for(ll i = 0; i < freq.size(); i++){
                s += freq[i];
                freq[i] = s - freq[i];
            }
            for(ll i = 0; i < transform.size(); i++){
                transform[freq[ABCtoll[str[i]]]++] = i;
            }
            std::string res = "";
            ll pos = str.find('$');
            pos = transform[pos];
            for(ll i = 0; i < transform.size() - 1; i++){
                res += str[pos];
                pos = transform[pos];
            }
            return res;
        }
    } // namespace BWT

    std::vector<RLE::Pair> Encode(std::string str){
        str += '$';
        return RLE::Encode(MTF::Encode(BWT::Encode(str)));
    }
    std::string Decode(std::vector<RLE::Pair> pairs){
        return BWT::Decode(MTF::Decode(RLE::Decode(pairs)));
    }
} //namespace archive

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::string command;
    std::getline(std::cin, command);
    if (command == "compress"){
        std::string str;
        std::cin >> str;
        archive::RLE::Print(archive::Encode(str));
    } else if (command == "decompress") {
        std::vector<archive::RLE::Pair> p = archive::RLE::Scan();
        std::cout << archive::Decode(p) << "\n";
    }
    return 0;
}
