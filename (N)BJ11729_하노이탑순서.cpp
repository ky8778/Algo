//! 2020.03.19
// TODO BJ11729_하노이탑이동순서

//! 2020.03.20
/* 분할정복 알고리즘을 잘못 구상하였다.
#include<cstdio>
#include<vector>
using namespace std;

const int INF = 987654321;
int N,K;
vector <pair<int,int>> result;
vector <int> inData[3];

void print(){
    for(int i=0;i<3;i++){
        printf("i : %d\n",i);
        for(int s=0;s<inData[i].size();s++){
            printf("%d ",inData[i][s]);
        }
        printf("\n");
    }
}

void moveTower(int from, int to){
    int idx = inData[from].size();
    int val = inData[from][idx-1];
    int next;
    for(int i=0;i<3;i++){
        if(i!=from && i!=to){
            next = i;
            break;
        }
    }

    for(int i=3;i>=1;i--){
        inData[to].push_back(inData[from][idx-i]);
    }
    for(int i=0;i<3;i++){
        inData[from].pop_back();
    }

    return;
}

void getResult(int from, int to, int n,int start){
    printf("test");
    if(n==3){
        moveTower(from,to);
        print();
        return;
    }

    for(int i=0;i<3;i++){
        if(i!=from && i!=to)
            getResult(from,i,n-1,start+1);
    }
    int move = inData[from][start];
    inData[from].pop_back();
    inData[to].push_back(move);
    for(int i=0;i<3;i++){
        if(i!=from && i!=to)
            getResult(i,to,n-1,start);
    }
    print();
}

int main(){
    scanf("%d",&N);

    for(int i=0;i<3;i++) inData[i].push_back(INF);
    for(int i=N;i>0;i--) inData[0].push_back(i);

    getResult(0,2,N,1);

    printf("%d\n",K);
    for(int i=0;i<result.size();i++){
        printf("%d %d\n",result[i].first,result[i].second);
    }
    return 0;
}
*/