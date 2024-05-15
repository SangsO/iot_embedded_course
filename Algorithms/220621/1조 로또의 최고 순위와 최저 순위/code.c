#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> lottos, vector<int> win_nums) {
    vector<int> answer;
    
    int unknown=0;
    int same=0; 
    
    for(int i=0; i<lottos.size();i++){
        if(lottos.at(i)==0)
            unknown++;
        for(int j=0;j<win_nums.size();j++)
            if(lottos.at(i)==win_nums.at(j))
                same++;
    }
    
    int max=7-(unknown+same);
    int min=7-same;
    
    if(max>6) max=6;
    if(min>6) min=6;
    
    answer.push_back(max);
    answer.push_back(min);
    
    
    return answer;
}