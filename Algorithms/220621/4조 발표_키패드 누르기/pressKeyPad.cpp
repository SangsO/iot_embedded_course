#include <string>
#include <vector>

using namespace std;
/*
벡터 요소 접근 함수 중 at 사용, 벡터의 idx 번째 요소 접근 하기 위함
int 형 자료형에 왼손과 오른손의 위치를 각 각 10, 12로 지정

pair 클래스에 키패드의 좌표((0, 0) ~ (3, 2))를 각각 지정한 후
x 좌표의 변화량 + y 좌표의 변화량으로 총 이동 거리를 구한다.

지정된 키패드와 손의 위치를 비교하여 거리로 계산 후
가장 짧은 거리에 있는 손의 위치를 해당 키패드로 이동.

** 키 패드 **
   1  2  3
   4  5  6
   7  8  9
  10 11 12 (* 0 #)
************
*/
vector<pair<int, int>> locate = {
    {0, 0}, {0, 1}, {0, 2},
    {1, 0}, {1, 1}, {1, 2},
    {2, 0}, {2, 1}, {2, 2},
    {3, 0}, {3, 1}, {3, 2}
};
string solution(vector<int> numbers, string hand) {
    string answer = "";
    int rightHandPosi = 12, leftHandPosi = 10, rightHandDis, leftHandDis;
    // 처음 오른손 위치 = 12, 처음 왼손 위치 = 10로 초기화

    for (int idx = 0; idx < numbers.size(); idx++) {          // 누르는 번호 만큼 반복문 실행
        if (numbers.at(idx) == 0) numbers.at(idx) = 11;      // 키패드 0은 11로 취급
        // 1, 4, 7번 누를 시 왼손 사용
        if (numbers.at(idx) == 1 || numbers.at(idx) == 4 || numbers.at(idx) == 7) {
            answer += 'L';
            leftHandPosi = numbers.at(idx);     // 왼손 위치 변경
        }
        // 3, 6, 9번 누를 시 오른 손 사용
        else if (numbers.at(idx) == 3 || numbers.at(idx) == 6 || numbers.at(idx) == 9) {
            answer += 'R';
            rightHandPosi = numbers.at(idx);    // 오른손 위치 변경
        }
        // 2, 5, 8, 0번 누를 시
        else {
            // 오른손 위치에서 눌러야 할 버튼 까지의 거리, x 좌표 변화량 + y 좌표 변화량
            rightHandDis = abs(locate[numbers.at(idx) - 1].first - locate[rightHandPosi - 1].first)
                         + abs(locate[numbers.at(idx) - 1].second - locate[rightHandPosi - 1].second);
            // 왼손 위치에서 눌러야 할 버튼 까지의 거리
            leftHandDis = abs(locate[numbers.at(idx) - 1].first - locate[leftHandPosi - 1].first) 
                        + abs(locate[numbers.at(idx) - 1].second - locate[leftHandPosi - 1].second);
            if (rightHandDis > leftHandDis) {        // 왼손이 움직여야 할 거리가 더 적을 경우
                answer += 'L';
                leftHandPosi = numbers.at(idx);
            }
            else if (rightHandDis < leftHandDis) {   // 오른손이 움직여야 할 거리가 더 적을 경우
                answer += 'R';
                rightHandPosi = numbers.at(idx);
            }
            else if (rightHandDis == leftHandDis) {  // 양 손의 움직일 거리가 같을 때
                if (hand == "left") {                // 왼손 잡이일 경우
                    answer += 'L';
                    leftHandPosi = numbers.at(idx);
                }
                else if (hand == "right") {          // 오른손 잡이일 경우
                    answer += 'R';
                    rightHandPosi = numbers.at(idx);
                }
            }
        }
    }
    return answer;
}