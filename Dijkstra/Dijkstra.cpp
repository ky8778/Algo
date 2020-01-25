// 2019.10.23
// Dijkstra algorithm
#define heapDijk
// 2차원 배열을 사용해서 매번 index로 최소 거리인 노드를 확인하게 되면(선형탐색) O(N^2)가 된다.
#ifdef arrayDijk
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

const int MAX = 20050;
int infoPath[MAX][MAX];                 // entire Path info
int shortestPath[MAX];
int V,E,K;
bool checkNode[MAX];

bool compare(pair <int,int> a, pair <int,int> b){
    return a.second<b.second;
}

void printInfo(){
    for(int i=1;i<=V;i++){
        for(int j=1;j<=V;j++){
            printf("%d ",infoPath[i][j]);
        }
        printf("\n");
    }
}

void updateInfo(int node){
    for(int v=1;v<=V;v++){
        if(!checkNode[v] && infoPath[node][v]!=0){
            if(infoPath[K][v]==0) infoPath[K][v] = infoPath[node][v] + shortestPath[node];
            else{
                if(infoPath[K][v]>infoPath[node][v]+shortestPath[node])
                    infoPath[K][v] = infoPath[node][v]+shortestPath[node];
            }
        }
    }
}

void getResult(){
    int n = 1;
    checkNode[K] = true;
    
    // for(int i=0;i<Path.size();i++) printf("i : %d, %d %d\n",i,Path[i].first,Path[i].second);
    while(n<V){
        // select shortest path
        int minPath = 0;
        int minDist = 987987987;
        for(int v=1;v<=V;v++){
            if(infoPath[K][v]!=0 && minDist>infoPath[K][v] && checkNode[v]==false){
                minDist = infoPath[K][v];
                minPath = v;
            } 
        }
        //printf("add shortest Path : %d, dist : %d\n",minPath,minDist);
        if(minPath==0) break;
        // include new node to solution set
        checkNode[minPath] = true;
        shortestPath[minPath] = minDist;

        // update Path info
        updateInfo(minPath);
        printInfo();
    }
}

int main(){
    scanf("%d %d",&V,&E);
    scanf("%d",&K);
    for(int e=0;e<E;e++){
        int u,v,w;
        scanf("%d %d %d",&u,&v,&w);
        if(infoPath[u][v]==0 || infoPath[u][v]>w) infoPath[u][v] = w;
    }
    //printInfo();
    getResult();
    for(int i=1;i<=V;i++){
        if(i==K) printf("0\n");
        else{
            if(checkNode[i]==false) printf("INF\n");
            else printf("%d\n",shortestPath[i]);
        }
    }

    return 0;
}
#endif

// Heap 구조를 이용한다.(항상 가장 큰 값/작은 값이 최 상단 노드에 존재한다.)
// 최단거리 노드를 가져오는 과정을 O(logN)으로 만들 수 있다.
#ifdef heapDijk
#include<iostream>
#include<vector>
#include<queue>
// c++에서 제공하는 우선순위 큐 : queue 헤더에 있음.
// 우선순위큐 : Heap과 같은 방식으로 작동됨.
using namespace std;

const int MAX = 20050;
int number = 6;
int INF = 1000000000;

vector <pair<int,int>> a[MAX];  // 간선 정보
int d[MAX];                     // 최소 비용

void dijkstra(int start){
    d[start] = 0;
    priority_queue<pair<int,int>> pq;   // heap structure
    // 가까운 순서대로 처리하므로 큐를 사용한다.
    pq.push(make_pair(start,0));
    while(!pq.empty()){
        int current = pq.top().first;   // 가장 적은 비용을 가지는 노드
        // 우선순위 큐는 더 큰값을 우선으로 하기 때문에
        // 짧은 것이 먼저 오도록 음수화(-) 한다.
        int distance = -pq.top().second;
        pq.pop();
        // 최단 거리가 아닌 경우 스킵한다.
        if(d[current]<distance) continue;
        for(int i=0;i<a[current].size();i++){
            // 선택된 노드의 인접 노드를 담는다.
            int next = a[current][i].first;
            // 선택된 노드를 거쳐서 인접 노드로 가는 비용
            int nextDistance = distance + a[current][i].second;
            // 기존의 최소 비용보다 더 저렴하다면 교체합니다.
            if(nextDistance<d[next]){
                d[next] = nextDistance;
                pq.push(make_pair(next,-nextDistance));
            }
        }
    }
}

int main(){
    // 기본적으로 연결되지 않은 경우 비용은 무한입니다.
    for(int i=1;i<= number;i++){
        d[i] = INF;
    }
    a[1].push_back(make_pair(2,2));
    a[1].push_back(make_pair(3,5));
    a[1].push_back(make_pair(4,1));
    a[2].push_back(make_pair(1,2));
    a[2].push_back(make_pair(3,3));
    a[2].push_back(make_pair(4,2));
    a[3].push_back(make_pair(1,5));
    a[3].push_back(make_pair(2,3));
    a[3].push_back(make_pair(4,3));
    a[3].push_back(make_pair(5,1));
    a[3].push_back(make_pair(6,5));
    a[4].push_back(make_pair(1,1));
    a[4].push_back(make_pair(2,2));
    a[4].push_back(make_pair(3,3));
    a[4].push_back(make_pair(5,1));
    a[5].push_back(make_pair(3,1));
    a[5].push_back(make_pair(4,1));
    a[5].push_back(make_pair(6,2));
    a[6].push_back(make_pair(3,5));
    a[6].push_back(make_pair(5,2));
    dijkstra(1);
    // 결과를 출력
    for(int i=1;i<=number;i++){
        printf("%d ",d[i]);
    }
    return 0;
}
#endif