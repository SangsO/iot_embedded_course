#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;
    
    for (auto com : commands) {
        vector<int> align;

        for (int idx = com[0] - 1; idx < com[1]; idx++) {
            align.push_back(array.at(idx));
        }

        sort(align.begin(), align.end());
        answer.push_back(align[com[2] - 1]);
    }

    return answer;
}
int main(void) {
    vector<int> centernum;
    centernum = solution({ 1,5,2,6,3,7,4 }, { {2,5,3},{4,4,1},{1,7,3} });
    cout << centernum[0] << endl;
    cout << centernum[1] << endl;
    cout << centernum[2] << endl;

}
