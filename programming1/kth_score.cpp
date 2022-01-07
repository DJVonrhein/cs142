#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
int main(){
    //sort
    int currScore;
    std::string n,k,num_m, m, entry = "";

    getline(std::cin, n);
    getline(std::cin, k);
    
    
    int numScores = std::stoi(n,nullptr,10);

    std::vector<int> scores;

    //Parse the scores and place in vector
    for(int i = 0; i < k.size(); ++i){
        
        if(k[i] != ' '){
            entry += k[i];
        }
        else{
            currScore = std::stoi(entry,nullptr,10);
            scores.push_back(currScore);
            entry = "";
        }
    }

    currScore = std::stoi(entry,nullptr,10);
    scores.push_back(currScore);

    std::sort(scores.begin(),scores.end());


    //eliminate duplicates!
    for (int i = scores.size() - 1; i >= 1;--i){
        if (scores.at(i-1) == scores.at(i))
            scores.erase(scores.begin() + i-1);
    }
    

    // std::cin.ignore();
    getline(std::cin, num_m);
    
    int numQueries = std::stoi(num_m,nullptr,10);
    int kquery[numQueries];
    //return kth distinct score, m times
    for(int i = 0; i < numQueries; ++i){
        getline(std::cin, m);
        kquery[i] = std::stoi(m,nullptr,10);
    }
    for (int i = 0; i < numQueries;++i){
        std::cout << scores.at(scores.size() - kquery[i]) << std::endl;
    }
    return 0;
}