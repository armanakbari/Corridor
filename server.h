#include <httplib.h>
#include <iostream>
#include <vector>
#include<string>  
using namespace httplib;
using namespace std;


class Player{
    public:
        string name;
        int p_x;
        int p_y;
        Player(string na, int x, int y){
            name = na;
            p_x = x;
            p_y = y;
        }
};

class Game{
    private:
        int no_of_player;
        int map[11][11] = {0};
        vector <Player> p;
    public:
        int winner_flag = 0;
        int stop_flag = 0;
        Game(int n = 2){
            no_of_player = n;
        }
        string addPlayer(string);
        int movementValidation();
        string playerMovementHandler(int, char);
        int getNoOfPlayers(){ return no_of_player ; }
        void setNoOfPlayers(int n){no_of_player  = n ; }
        string renderMap();
        string playerWallPlacementHandler(int , int, int );
};