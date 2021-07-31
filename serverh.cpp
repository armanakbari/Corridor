#include "server.h"

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
                msg += to_string(map[i][j]);
        }
    }
    
    if(p[pn].p_y == 5 && p[pn].p_x == 5)
            winner_flag = pn+1;

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
                if(y == 5){
                    if(x != 5 && x != 4 && x != 6){
                        map[x][y] = 8;
                        map[x+1][y] = 8;
                        map[x-1][y] = 8;
                    }
                    else{
                        msg = "can't place a wall there!"; 
                    }
                }else{
                    map[x][y] = 8;
                    map[x+1][y] = 8;
                    map[x-1][y] = 8;
                }
            }else 
                msg = "can't place a wall there!";
        }else
            msg = "can't place a wall there!";

    }else {
        if((y != 0) && (y != 10)){
            if( (map[x][y] == 0) && (map[x][y-1] == 0) && (map[x][y+1] == 0)){
                if(x == 5){
                    if(y != 5 && y != 4 && y != 6){
                        map[x][y] = 8;
                        map[x][y+1] = 8;
                        map[x][y-1] = 8;
                    }else
                        msg = "can't place a wall there!";
                }else{
                    map[x][y] = 8;
                    map[x][y+1] = 8;
                    map[x][y-1] = 8;
                }
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