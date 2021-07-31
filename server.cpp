#include <httplib.h>
#include <iostream>
#include <vector>
#include<string>  
#include "server.h"
//map
//Player
//wall: walls are represented by * in the map.
//    Every wall has lenght of three that can either horizental or vertical
//1, 2, 3, 4 are four players that place in the corner of the map at the begging of the game
using namespace httplib;
using namespace std;



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
    int turn = 1;
    
    Game Corridor(n);
    string msg = "";
    string masg = "";
    
    
    svr.Post("/hi", [&](const Request &req, Response& res) {
        if(n == 0){
            msg = "Sorry. This game is full right now, maybe next game.";
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

    svr.Get("/win", [&](const Request& req, Response& res) {
        res.set_content(to_string(Corridor.winner_flag), "text/plain");
    });
    svr.Get("/stop", [&](const Request& req, Response& res) {
        Corridor.stop_flag = 1;
        res.set_content(to_string(Corridor.stop_flag), "text/plain");
    });

    svr.listen("localhost", 8080);
}