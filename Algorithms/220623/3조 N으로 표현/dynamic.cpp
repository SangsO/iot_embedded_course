#include <iostream>
#include <vector> 
#include <unordered_set> 
using namespace std; 

/* 5, 55, 555, 5555, 55555, ... 만드는 함수 */
int get_Ns(int N, int idx) { 
    // NN(idx==1), NNN(idx==2), NNNN(idx==3)...과 같은 형태만드는 함수
    int result = N; 
    for (int i = 1; i <= idx; i++) { 
        result = result * 10 + N; 
    } 
    return result; 
} 

int solution(int N, int number) { 
		// N과 number가 같다면, N을 한번 사용해서 number를 만들 수 있음 ex : N=5, number=5
    if (N == number) return 1;

    /* DP에 저장할 것 -> DP[i] : i개의 N으로 만들 수 있는 숫자들 (set) */
		/* ex : DP[0] : 한자리 경우의 수, DP[1] : 두자리 경우의 수, DP[2] : 세자리 경우의 수 */
    vector< unordered_set<int> > DP(8); 


    DP[0].insert(N); // 한개의 N으로 만들 수 있는 수는 N뿐임
    
    for (int k = 1; k < 8; k++) { 
        
        /* DP[k]에 NNN...(k+1만큼 반복)과 같은 형태 삽입 ex:5, 55, 555 */
        DP[k].insert(get_Ns(N, k));
        
        // DP[k]에 사칙 연산의 결과또한 삽입
        for (int i = 0; i < k; i++) { 
            for (int j = 0; j < k; j++) { 
								/* [k : 1]i=0, j=0 => 1
									 [k : 2]i=0, j=0 => 1 (x)
									 [k : 2]i=0, j=1 => 2
									 [k : 2]i=1, j=0 => 2 */
                if (i + j + 1 != k) continue; 
                // i+j+1 == k 일때
                for (int a : DP[i]) { 
                    for (int b : DP[j]) { 
                        DP[k].insert(a + b); 
                        // 검사가 필요한 연산들
                        
                        // (1) 음수 존재하면 안됨
                        if (a - b > 0){
                            DP[k].insert(a - b);
                            cout << " a - b : " << a-b << endl;
                        }
                        
                        DP[k].insert(a * b);
                        
                        // (2) 0 존재하면 안됨
                        if (a / b > 0){
                            DP[k].insert(a / b);
                            cout << "a / b : " << a/b << endl;
                        }
                    } 
                } 
            } 
        }
        
        if (DP[k].find(number)!=DP[k].end()) //DP set에 number에 해당하는 값이 있으면 k+1을 반환
            return k + 1; 
    } 
    return -1; 
}

int main(){

    int answer;

    answer = solution(5, 8913);
    cout << "answer : " << answer << endl;
}