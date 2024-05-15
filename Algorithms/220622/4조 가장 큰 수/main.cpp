#include <string>
#include <vector>
#include <algorithm>    // sort 정렬 함수 사용 위한 헤더 파일 선언

using namespace std;

bool numCompare(string, string);    // 사용자 정렬 함수 정의
/*
정렬 할 때 두 가지 요소를 비교 하는데 두 개 숫자를
조합해서 만들 수 있는 가장 큰 수를 비교하기 위해서는 int형이 아닌 string형으로 하는 것이 편하다.

예를 들어 3과 15라는 숫자를 조합해서 비교한다고 하자.
int형으로 할 시 3 + 15, 15 + 3은 둘 다 18이다.
하지만 string형으로 하게 되면 “3” + “15” = “315”가 될 것이고, “15” + “3” = “153”이 될 것이다.

이 두 개를 비교하면 어떤 수가 더 커질 것인지 비교 가능할 것 같다.
때문에 int 형 numbers를 string 형으로 바꾸어 저장 하고 sort 내부의 정렬 함수를 만들어
비교해서 출력하는 것을 목표로 한다.
*/
string solution(vector<int> numbers) {
    string answer = "";
    vector<string> strNumbers;
    for (auto n : numbers)
        strNumbers.push_back(to_string(n)); // int형 -> string형으로 저장

    // sort(verctor의 첫 번째 주소, vector의 마지막 주소, 사용자 정렬 함수)
    // 정렬 하고자 하는 vector의 범위를 지정한다.
    sort(strNumbers.begin(), strNumbers.end(), numCompare);
    for (int idx = 0; idx < strNumbers.size(); idx++)
        answer += strNumbers.at(idx);

    // 모든 값들이 0 일 때 string형으로 합하기 때문에
    // "00000.." 이 출력된다. 모든 값이 0 일때
    // "0" 만 출력되게 하기 위해 아래 코드를 추가 했다.
    if (answer.at(0) == '0') answer = '0';

    return answer;
}
bool numCompare(string num1, string num2) {
    return (num1 + num2) > (num2 + num1);
    //"num1num2" 과 "num2num1"값을 비교
    // num1 = 10, num2 = 3 이면
    // "103", "310" 비교
}