#include <iostream>
#include <vector>
#include <stack>

struct vertex{
    int space;
    std::vector<int> adjacencyList;
};

struct graph{
    std::vector<vertex*> vertices;
};

int main(){
    std::stack<std::vector<int> >* BFS;
    int boardNumber, numBlocked, currBlockedSpace, startSpace, finishSpace, numMoves;
    std::string entry, numBlockedStr, blockedStr, startFinishStr;
    std::vector<int> blockedSpaces;

    graph board;
    boardNumber = 1;

    while(1){
        
        //obtain number of blocked spaces
        getline(std::cin, numBlockedStr);

        if(numBlockedStr[0] < 48 || numBlockedStr[0] > 57)  {  return 0; }
            
        numBlocked = std::stoi(numBlockedStr,nullptr,10);


        //represent board as graph

        for(int i = 0; i < 64; ++i){
            vertex* newSpace = new vertex;
            newSpace->space = i;

            //8 test cases for what is acceptable in an adjacency list
            if( ((i % 8) < 7) && (i < 47)){   //1 up 2 right (i + 17)
                newSpace->adjacencyList.push_back(i + 17);
            }
            if( ((i % 8) < 6) && (i < 54)){   //2 up 1 right  (i + 10)
                newSpace->adjacencyList.push_back(i + 10);
            }
            if( ((i % 8) < 6) && (i > 7)){   //2 up 1 left   (i - 6)
                newSpace->adjacencyList.push_back(i - 6);
            }
            if( ((i % 8) < 7) && (i > 15)){   //1 up 2 left   (i - 15)
                newSpace->adjacencyList.push_back(i - 15);
            }
            if( ((i % 8) > 0) && (i > 16)){   //1 down 2 left  (i - 17)
                newSpace->adjacencyList.push_back(i - 17);
            }
            if( ((i % 8) > 1) && (i > 9)){   //2 down 1 left     (i - 10)
                newSpace->adjacencyList.push_back(i - 10);
            }
            if( ((i % 8) > 1) && (i < 56)){   //2 down 1 right    (i + 6)
                newSpace->adjacencyList.push_back(i + 6);
            }
            if( ((i % 8) > 0) && (i < 48)){   //1 down 2 right    (i + 15)
                newSpace->adjacencyList.push_back(i + 15);
            }

            board.vertices.push_back(newSpace);
        }


        //obtain all blocked spaces
        getline(std::cin, blockedStr);
        for(int i = 0; i < blockedStr.size(); ++i){
            if(blockedStr[i] != 32 ){ // parses the blocked spaces
                entry += blockedStr[i];
            }
            else{       
                if(entry.size() >= 2){
                    currBlockedSpace = (entry[0] - 97) * 8;
                    currBlockedSpace += (entry[1] - 48) - 1;
                    blockedSpaces.push_back(currBlockedSpace);
                    entry.clear();
                }
            }
        }
        //need to do this for last space to be included
        if(entry.size() >= 2){
            currBlockedSpace = (entry[0] - 97) * 8;
            currBlockedSpace += (entry[1] - 48) - 1;
            blockedSpaces.push_back(currBlockedSpace);
        }
        
        //obtain start space and finish space
        getline(std::cin, startFinishStr);
        
        
        startSpace = (startFinishStr.at(0) - 97) * 8;
        startSpace += ((startFinishStr.at(1) - 48) - 1);
        finishSpace = (startFinishStr.at(3) - 97) * 8;
        finishSpace += ((startFinishStr.at(4) - 48) - 1);
        std::cout << finishSpace;

        std::cout << "Board ";
        std::cout << boardNumber << ": ";
        numMoves = 0;
        bool foundFinishSpace = false;

        if(finishSpace != startSpace){
            std::cout << "made it";
            numMoves = 1;
            for(int i = 0; i < board.vertices.at(startSpace)->adjacencyList.size(); ++i){   //Checks if immediately adjacent
                if(board.vertices.at(startSpace)->adjacencyList.at(i) == finishSpace)
                    foundFinishSpace = true;
            }
            std::vector<int> nextSearch = board.vertices.at(startSpace)->adjacencyList;
            BFS->push(nextSearch);
            nextSearch.clear();
            for (int i = 0; i < 8; ++i){ //maximum 9 total moves before BFS gives up
                if(foundFinishSpace) break;
                
                numMoves++;
                for (int j = 0; j < BFS->top().size(); ++j){   
                    if (BFS->top().at(j) == finishSpace){       //Check current search level for finishSpace
                        break;
                    }
                    for(int k = 0; k < board.vertices.at(BFS->top().at(j))->adjacencyList.size(); ++k) //populate next search level of BFS
                        nextSearch.push_back(board.vertices.at(BFS->top().at(j))->adjacencyList.at(k));

                }
                BFS->push(nextSearch);
            }

        }
        // else{
        //     std::cout << "same space wtf";
        // }

        std::cout << numMoves << " moves" << std::endl;
        boardNumber++;
    }
    delete BFS;
    for(int i = 0; i < 63; ++i)
        delete board.vertices.at(i);
}