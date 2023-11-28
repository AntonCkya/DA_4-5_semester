#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const long long INF = LLONG_MAX;

struct TEdge {
    long long begin;
    long long end;
    long long weight;
    TEdge(long long b, long long e, long long w): begin(b), end(e), weight(w) {}
};

int main(){
    long long n, m, start, finish;
    vector<TEdge> graph;
    cin >> n >> m >> start >> finish;
    for (long long i = 0; i < m; i++){
        long long edgeBegin, edgeEnd, edgeWeight;
        cin >> edgeBegin >> edgeEnd >> edgeWeight;
        graph.push_back(TEdge(edgeBegin, edgeEnd, edgeWeight));
    }
    vector<long long> solve(n, INF);
    solve[start - 1] = 0;
    while(true){
        bool change = false;
        for (long long i = 0; i < graph.size(); i++){ 
            if(solve[graph[i].begin - 1] < INF){
                if (solve[graph[i].end - 1] > solve[graph[i].begin - 1] + graph[i].weight){
                    solve[graph[i].end - 1] = solve[graph[i].begin - 1] + graph[i].weight;
                    change = true;
                }
            }
        }
        if (!change){
            break;
        }
    }
    if (solve[finish - 1] == INF){
        cout << "No solution\n";
    } else {
        cout << solve[finish - 1] << "\n";
    }
    return 0;
}
