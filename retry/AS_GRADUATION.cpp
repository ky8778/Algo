// TODO AS_GRADUATION
//! 2020.03.25
/* 정답 */
#include<cstdio>
using namespace std;

const int INF = 987654321;
const int MAX = 15;
int N,K,M,L,T;
// preLect[i] : i번째 과목의 선수과목의 집합
int preLect[MAX];
// Lect[i] : i번째 학기에 개설되는 과목의 집합
int Lect[MAX];
int DP[MAX][1<<MAX];
// n의 이진수 표현에서 켜진 비트의 수를 반환
int bitCount(int n){
    int cnt = 0;
    for(int i=0;i<N;i++){
        if(n&(1<<i)) cnt++;
    }
    return cnt;
}

int getMin(int n1,int n2){
    if(n1<n2) return n1;
    else return n2;
}
// 이번 학기가 now이고, 지금까지 들은 과목이 set
// k개 이상의 과목을 모두 들으려면 몇 학기나 더 있어야 하는가
// 불가능하면 INF를 반환
int getResult(int now, int set){
    if(bitCount(set)>=K) return 0;
    if(now>=M) return INF;
    int& ret = DP[now][set];
    if(ret!=-1) return ret;
    ret = INF;
    // 이번학기에 들을 수 있는 과목 중 아직 듣지 않은 과목
    int canTake = (Lect[now] & ~set);
    // 선수과목 듣지 않은 과목은 제거
    for(int i=0;i<N;i++){
        if((canTake & (1<<i)) && (set&preLect[i])!=preLect[i]){
            canTake &= ~(1<<i);
        }
    }
    // 모든 subset 순회
    for(int sub = canTake; sub>0;sub=((sub-1)&canTake)){
        // 한 학기 최대 과목은 L
        if(bitCount(sub)>L) continue;
        ret = getMin(ret, getResult(now+1,set|sub)+1);
    }
    // 휴학할 경우
    ret = getMin(ret, getResult(now+1,set));
    return ret;
}

void init(){
    for(int i=0;i<N;i++){
        int R;
        scanf("%d",&R);
        int num = 0;
        for(int r=0;r<R;r++){
            int prev;
            scanf("%d",&prev);
            num |= (1<<prev);
        }
        preLect[i] = num;
    }
    for(int i=0;i<M;i++){
        int C;
        scanf("%d",&C);
        int num = 0;
        for(int c=0;c<C;c++){
            int current;
            scanf("%d",&current);
            num |= (1<<current);
        }
        Lect[i] = num;
    }
    for(int i=0;i<MAX;i++){
        for(int j=0;j<(1<<MAX);j++){
            DP[i][j] = -1;
        }
    }
}

int main(){
    // freopen("input.txt","r",stdin);
    scanf("%d",&T);
    for(int t=0;t<T;t++){
        scanf("%d %d %d %d",&N,&K,&M,&L);
        init();
        int result = getResult(0,0);
        if(result>=INF) printf("IMPOSSIBLE\n");
        else printf("%d\n",result);
    }
    return 0;
}

//! 2020.03.23
//! 2020.03.25
/* 오답
#include<cstdio>
using namespace std;

const int INF = 987654321;
const int MAX = 15;
int numOfSetLect[MAX];          // 선수과목들의 수를 담는 변수
int setLect[MAX];               // 선수과목들을 담는 변수 (비트마스크로 담는다.)
int numOfLect[MAX];             // 각 학기에 열리는 과목들의 수를 담은 변수
int lecture[MAX];               // 각 학기에 열리는 과목들을 담은 변수 (비트마스크로 담는다.)
int minResult;
int T,N,K,M,L;

int getSetSize(int set){
    int cnt = 0;
    for(int i=0;i<N;i++){
        if(set&(1<<i)) cnt++;
    }
    return cnt;
}

int getMin(int n1,int n2){
    if(n1<n2) return n1;
    else return n2;
}

void printBinary(int n){
    for(int j=N-1;j>=0;j--){
        if(n&(1<<j)) printf("1");
        else printf("0");
    }
    printf("\n");
}

void getResult(int idx,int total,int set){
    int setSize = getSetSize(set);
    if(setSize>=K){
        minResult = getMin(total,minResult);
        return;
    }
    else if(idx>=M || total>=minResult) return;
    else{
        // 현재 학기에 휴학하는 경우
        getResult(idx+1,total,set);

        int current = 0;
        int currentSize = 0;
        for(int i=0;i<N;i++){
            if((lecture[idx]&(1<<i)) && (set&(1<<i))==0){
                // 현재 학기 lecture에 i가 있고 set에는 i가 없을 때
                if(getSetSize(setLect[i]&set)==numOfSetLect[i]){
                    // lecture 목록에서 각각의 과목을 idx로 삼아서 setLect[idx]&set의 크기가 numOfSetLect[idx]와 같다면
                    // 현재 학기에서 수강 가능한 과목이라고 담는다.
                    current |= (1<<i);
                    currentSize++;
                }
            }
        }
        // printf("current : ");
        // printBinary(current);
        if(currentSize==0) return;
        else if(currentSize<=L){
            // 현재 학기에서 수강 가능한 과목이 L보다 작거나 같다면 set에 추가해서 다음 백트래킹으로 넘긴다.
            getResult(idx+1,total+1,set|current);
        }
        else{
            // L보다 크다면 현재 학기에서 수강 가능한 과목들 중 L개를 뽑아서 set에 추가해서 다음 백트래킹으로 넘긴다.
            for(int i=1;i<(1<<currentSize);i++){
                if(getSetSize(i)==L){
                    int next = 0;
                    for(int j=0;j<N;j++){
                        if(current & (1<<j)){
                            next |= (i & (1<<j));
                        }
                    }
                    getResult(idx+1,total+1,set|next);
                }
            }
        }
    }
}

void print(){
    printf("setLect\n");
    for(int i=0;i<N;i++){
        for(int j=N-1;j>=0;j--){
            if(setLect[i]&(1<<j)) printf("1");
            else printf("0");
        }
        printf("\n");
    }
    printf("lecture\n");
    for(int i=0;i<M;i++){
        for(int j=N-1;j>=0;j--){
            if(lecture[i]&(1<<j)) printf("1");
            else printf("0");
        }
        printf("\n");
    }
}

void init(){
    for(int i=0;i<MAX;i++){
        numOfLect[i] = 0;
        numOfSetLect[i] = 0;
        lecture[i] = 0;
        setLect[i] = 0;
    }
}

int main(){
    // freopen("input.txt","r",stdin);
    scanf("%d",&T);
    for(int t=0;t<T;t++){
        scanf("%d %d %d %d",&N,&K,&M,&L);
        for(int i=0;i<N;i++){
            int R;
            scanf("%d",&R);
            numOfSetLect[i] = R;
            int num = 0;
            for(int r=0;r<R;r++){
                int prev;
                scanf("%d",&prev);
                num |= (1<<prev);
            }
            setLect[i] = num;
        }
        for(int i=0;i<M;i++){
            int C;
            scanf("%d",&C);
            numOfLect[i] = C;
            int num = 0;
            for(int c=0;c<C;c++){
                int current;
                scanf("%d",&current);
                num |= (1<<current);
            }
            lecture[i] = num;
        }
        // print();
        minResult = INF;
        getResult(0,0,0);
        if(minResult>=INF) printf("IMPOSSIBLE\n");
        else printf("%d\n",minResult);
    }
    return 0;
}
*/