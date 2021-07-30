#include <httplib.h>
#include <iostream>
#include <vector>
#include<string>  
//map
//Player
//wall: walls are represented by * in the map.
//    Every wall has lenght of three that can either horizental or vertical
//1, 2, 3, 4 are four players that place in the corner of the map at the begging of the game
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

string Game::addPlayer(string playerNo){
    string msg = "";
    int name = stoi(playerNo)-stoi("0");
    if(name == 1){
        Player p_obj1(playerNo, 0, 0);
        map[0][0] = 1;
        p.push_back(p_obj1);
    }else if (name == 2){
        Player p_obj2(playerNo, 0, 10);
        map[0][10] = 2;
        p.push_back(p_obj2); 
    }else if (name == 3){
        Player p_obj3(playerNo, 10, 10);
        map[10][10] = 3;
        p.push_back(p_obj3);
    }else if (name == 4){
        Player p_obj4(playerNo, 10, 0);
        map[10][0] = 4;
        p.push_back(p_obj4);
    }
    for (int i = 0; i < 11; ++i)
    {   
        for (int j = 0; j < 11; ++j)
        {
            msg += to_string(map[i][j]);
        }
    }
    
    return msg+"%";
}

string Game::playerMovementHandler(int pn, char move){
    string msg = "";
    pn -= 1;
    
      
    if(move == 'w'){
        if(p[pn].p_x > 0){
            if (map[p[pn].p_x-1][p[pn].p_y] == 0){
                map[p[pn].p_x][p[pn].p_y] = 0; 
                map[p[pn].p_x-1][p[pn].p_y] = pn+1; 
                p[pn].p_x -= 1;
            }else
                msg = "Invalid move. Try another one.";
        }else
            msg = "Invalid move. Try another one."; 
    }else if(move == 'a'){
        if(p[pn].p_y > 0){
            if (map[p[pn].p_x][p[pn].p_y-1] == 0){
                map[p[pn].p_x][p[pn].p_y] = 0; 
                map[p[pn].p_x][p[pn].p_y-1] = pn+1; 
                p[pn].p_y -= 1;
            }else
                msg = "Invalid move. Try another one.";
        }else
            msg = "Invalid move. Try another one.";
    }else if(move == 's'){
        if(p[pn].p_x  < 10){
            if (map[p[pn].p_x+1][p[pn].p_y] == 0){
                map[p[pn].p_x][p[pn].p_y] = 0; 
                map[p[pn].p_x+1][p[pn].p_y] = pn+1; 
                p[pn].p_x += 1;
            }else
                msg = "Invalid move. Try another one.";
        }else
            msg = "Invalid move. Try another one.";
    }else if(move == 'd'){
        if(p[pn].p_y  < 10){
            if(map[p[pn].p_x][p[pn].p_y+1] == 0){
                map[p[pn].p_x][p[pn].p_y] = 0; 
                map[p[pn].p_x][p[pn].p_y+1] = pn+1; 
                p[pn].p_y += 1;
            }else
                msg = "Invalid move. Try another one.";
        }else
            msg = "Invalid move. Try another one.";
    }
    if(msg != "Invalid move. Try another one."){
        for (int i = 0; i < 11; ++i)
        {   
            for (int j = 0; j < 11; ++j)
            {
                msg += to_string(map[i][j]);
            }
        }
    }
    
    
    return msg+"%";
}

string Game::renderMap(){
    string msg = "";
    for (int i = 0; i < 11; ++i)
    {   
        for (int j = 0; j < 11; ++j)
        {
            msg += to_string(map[i][j]);
        }
    }
    return msg+"%";
}

string Game::playerWallPlacementHandler(int x, int y, int v){
    string msg = "";
    if (v == 1){
        if((x != 0) && (x != 10)){
            if( (map[x][y] == 0) && (map[x-1][y] == 0) && (map[x+1][y] == 0)){
                map[x][y] = 8;
                map[x+1][y] = 8;
                map[x-1][y] = 8;
            }else 
                msg = "can't place a wall there!";
        }else
            msg = "can't place a wall there!";

    }else {
        if((y != 0) && (y != 10)){
            if( (map[x][y] == 0) && (map[x][y-1] == 0) && (map[x][y+1] == 0)){
                map[x][y] = 8;
                map[x][y+1] = 8;
                map[x][y-1] = 8;
            }else
                msg = "can't place a wall there!";
        }else
            msg = "can't place a wall there!";
    }
    if(msg != "can't place a wall there!"){
        for (int i = 0; i < 11; ++i)
        {   
            for (int j = 0; j < 11; ++j)
            {
                msg += to_string(map[i][j]);
            }
        }
    }
    return msg+"%";
}

int main(void)
{
    Server svr;
    int n;
    
    cout<<"WELCOME"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    cout<<"1.Two player"<<endl
        <<"2.Three Platers"<<endl
        <<"3.Four Platers"<<endl;
    cout<<"Enter the game mode(1, 2, 3): \n";
    cin>>n;
    n += 1;
    int nn = n;
    Game Corridor(n);
    string msg = "";
    string masg = "";
    int turn = 1;

    svr.Post("/hi", [&](const Request &req, Response& res) {
        if(n == 0){
            msg = "Sorry "+req.body+". This game is full right now, maybe next game. \n";
            res.set_content(msg, "text/plain");
        }else{
            cout<<req.body<<endl;
            //res.set_content(req.body, "text/plain");
            if(n == 1)
                cout<<"All players are ready! Let's start the game. \n";
            masg = req.body;
            masg = Corridor.addPlayer(masg);
            res.set_content(masg, "text/plain");
            n -= 1;
        }
    });

    svr.Post("/move", [&](const Request &req, Response& res) {
        cout<<req.body<<endl<<endl;
        msg = req.body;
        string player_name = to_string(msg[0]);
        char move = msg[2];
        cout<<"turn: "<< n<<endl;
        cout<<"player name: "<< stoi(player_name)-48<<endl;
        cout<<"Move: "<< move<<endl;

        if(turn == (stoi(player_name)-48) ){
            masg = Corridor.playerMovementHandler(stoi(player_name)-48, move);
            if(masg != "Invalid move. Try another one.%"){
                if(turn == nn)
                    turn = 1;
                else
                    turn++;
            }

        }else{
            masg = "It's not your turn to move.%";
        }
        cout<<masg<<endl;
        res.set_content(masg, "text/plain");
    });

    svr.Get("/renderMap", [&](const Request &req, Response& res) {
        masg = Corridor.renderMap();
        res.set_content(masg, "text/plain");
    });

    svr.Post("/wallPlacement", [&](const Request &req, Response& res) {
        cout<<req.body<<endl<<endl;
        msg = req.body;
        string player_name = to_string(msg[0]);
        string wall_x = to_string(msg[2]);
        string wall_y = to_string(msg[4]);
        string vertical = to_string(msg[6]);
        
        
        if(turn == (stoi(player_name)-48) ){
            masg = Corridor.playerWallPlacementHandler(stoi(wall_x)-48, stoi(wall_y)-48, stoi(vertical)-48);
            if(masg != "can't place a wall there!%"){
                if(turn == nn)
                    turn = 1;
                else
                    turn++;
            }

        }else{
            masg = "It's not your turn to move.";
        }
        cout<<masg<<endl;
        res.set_content(masg, "text/plain");
    });






    svr.Get(R"(/numbers/(\d+))", [&](const Request& req, Response& res) {
    auto numbers = req.matches[1];
    res.set_content(numbers, "text/plain");
    });

    svr.Get("/body-header-param", [](const Request& req, Response& res) {
    if (req.has_header("Content-Length")) {
      auto val = req.get_header_value("Content-Length");
    }
    if (req.has_param("key")) {
      auto val = req.get_param_value("key");
    }
    res.set_content(req.body, "text/plain");
    });

    svr.Get("/stop", [&](const Request& req, Response& res) {
    svr.stop();
    });

    svr.listen("localhost", 8080);
}