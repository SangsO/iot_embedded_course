#include <string>
#include <vector>
#include <algorithm>
// 문제 요약 
//n편의 논문에서 h회 이상 인용된 논문이 h개 이상일 때, 이 둘을 동시에 만족하는 h의 
//최대값 찾는게 주요 목적이며 단, n편은 1,000이하, 인용 횟수는 10,000이하이어야 
//한다.
// 인용된 논문이 이상인 논문 수와 같아지거나 인용된 논문이 
//이상인 논문 수보다 작아지기 시작하는 숫자를 찾는 것이 포인트
using namespace std;
bool desc(int a, int b){ 
  return a > b; 
}
int solution(vector<int> citations) {
    int answer = 0;
    sort(citations.begin(),citations.end(), desc);
		// h이상의 인용논문을 찾기 위해 sort에 내림차수로 정리함.	
		
    for(int i=0; i<citations.size();i++){
        if(i+1<=citations[i]) answer++;
        else return answer;
				//citations값과 i+1값을 비교하여 크면 answer 증가 아닐시 리턴 시킴
    }
    
    return answer;
    
}