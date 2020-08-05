#include <iostream>
#include <vector>
#include <string>
#include "board.h"

using namespace std;

int print_board() {
    // vector<vector<int>> board { {0, 0, 0, 0, 0, 0, 0, 0 }, 
    //                             {0, 0, 0, 0, 0, 0, 0, 0 },
    //                             {0, 0, 0, 0, 0, 0, 0, 0 },
    //                             {0, 0, 0, 0, 0, 0, 0, 0 },
    //                             {0, 0, 0, 0, 0, 0, 0, 0 },
    //                             {0, 0, 0, 0, 0, 0, 0, 0 },
    //                             {0, 0, 0, 0, 0, 0, 0, 0 },
    //                             {0, 0, 0, 0, 0, 0, 0, 0 } };

    // for (int i = 0; i < board.size(); i++) { 
    //     for (int j = 0; j < board[i].size(); j++)
    //         cout << board[i][j] << "";
    //     cout << endl;
    // }
    int n = 8; 
    int m = 8; 
  
    // Create a vector containing n 
    //vectors of size m.  
    vector<vector<int> > board( n , vector<int> (m));  

    cout << "\n    0   1   2   3   4   5   6   7" << endl;
    for (int i = 0; i < n; i++) { 
        cout<<"----------------------------------- "<<endl;
        cout << "\n" << i << " ";
        
        for (int j = 0; j < m; j++){ 
            cout<< "| " << board[i][j]<< " "; 
        } 
        cout<< "| \n"; 
        
    } 
    cout<<"----------------------------------- "<<endl;
  
return 0; 
} 



int main(){
    print_board();
    return 0;
}
