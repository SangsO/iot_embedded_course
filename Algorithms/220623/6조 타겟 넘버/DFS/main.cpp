#include <iostream>
#include <string>
#include <vector>

using namespace std;

int answer = 0;

void dfs(vector<int> numbers, int target, int sum, int index) {
	//종료 조건
	if (index == numbers.size()) {
		if (sum == target) {
			answer++;
		}
		return;
	}

	//종료 조건에 만족하지 않을 때
	dfs(numbers, target, sum + numbers[index], index + 1);
	dfs(numbers, target, sum - numbers[index], index + 1);
}

int solution(vector<int> numbers, int target) {
	dfs(numbers, target, 0, 0);
	return answer;
}

int main() {
	vector<int> v1 = { 1,1,1,1,1 };
	cout << solution(v1, 3) << endl;

	answer = 0;
	vector<int> v2 = { 4,1,2,1 };
	cout << solution(v2, 4) << endl;
}