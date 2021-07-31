#include <httplib.h>
#include <iostream>
#include <string>
using namespace std;
using namespace httplib;
int main(void)
{
	int n = 0;
	string playerName = "";
	
	cout<<"WELCOME"<<endl;
	cout<<"----------------------------------------------------"<<endl;

	cout<<"Enter you name: \n";
	cin>>playerName;

	Client cli("localhost", 8080);
	int map[11][11] = {0};

	if (auto res = cli.Post("/hi", playerName, "text/plain")) {
		string msg = "";
		int tmp;
		if (res->status == 200) {
	    	cout << res->body << endl;
	    	msg = res->body;
	    	if(msg != "Sorry. This game is full right now, maybe next game."){
		    	int k = 0;
		    	for (int i = 0; i < 11; ++i){
		    		for (int j = 0; j < 11; ++j){
		    			tmp = msg[k];
		    			map[i][j] = tmp - 48;
		    			k++;	
		    		}
		    	}
		    	for (int i = 0; i < 11; ++i){
		    		for (int j = 0; j < 11; ++j)
		    			cout<<map[i][j]<<" ";	
		    		cout<<endl;
		    	}
		    }else
		    	return 0;
		}

	} else 
		auto err = res.error();

	int choice = 5500;
	char move;
	int turn = 1;
	while(1){
		cout<<"1. Moving my object."<<endl
			<<"2. Placing a wall."  <<endl
			<<"3. Render updated map."  <<endl
			<<"4. Exit"  <<endl;
			
		cin>>choice;
		if (auto res = cli.Get("/win")) {
			string msg = "";
			if (res->status == 200) {
				if(res->body!= "0"){
					cout<<"Player "+res->body+" has won the game!"<<endl;
					break;
				}
    		}
		}
		if (auto res = cli.Get("/stop")) {
			if (res->status == 200) {
				if(res->body == "1"){
					cout<<"Game has been stopped!"<<endl;
					break;
				}
    		}
		}
		if (choice == 1){
			cout<<"Enter you move with 'w', 'a', 's', 'd': "<<endl;
			cin>>move;
			
			if (auto res = cli.Post("/move", playerName+"$"+move, "text/plain")) {
				string msg = "";
				int tmp;
				if (res->status == 200) {
					cout << res->body << endl;
			    	msg = res->body;
	    			int k = 0;
	    			if(msg != "Invalid move. Try another one.%" && msg != "It's not your turn to move.%"){
	    				for (int i = 0; i < 11; ++i)
				    	{
				    		for (int j = 0; j < 11; ++j)
				    		{
				    			tmp = msg[k];
				    			map[i][j] = tmp - 48;
				    			k++;	
				    		}
				    	}
				    	for (int i = 0; i < 11; ++i)
				    	{
				    		for (int j = 0; j < 11; ++j)
				    		{
				    			cout<<map[i][j]<<" ";	
				    		}
				    		cout<<endl;
				    	}
	    			}

				}

			} else 
				auto err = res.error();
		}
		else if (choice == 2){
			string wall_x, wall_y, vertical;
			cout<<"Enter x of cell you wanna plce the wall: "<<endl;
			cin>>wall_x;
			cout<<"Enter y of cell you wanna plce the wall: "<<endl;
			cin>>wall_y;
			cout<<"Enter 1 for a vertical wall and 0 for a horizontal: "<<endl;
			cin>>vertical;

			if (auto res = cli.Post("/wallPlacement", playerName+"$"+wall_x+"$"+wall_y+"$"+vertical, "text/plain")) {
				string msg = "";
				int tmp;
				if (res->status == 200) {
					cout << res->body << endl;
			    	msg = res->body;
	    			int k = 0;
	    			if(msg != "Invalid move. Try another one.%" && msg != "It's not your turn to move.%" && msg != "can't place a wall there!%"){
	    				for (int i = 0; i < 11; ++i)
				    	{
				    		for (int j = 0; j < 11; ++j)
				    		{
				    			tmp = msg[k];
				    			map[i][j] = tmp - 48;
				    			k++;	
				    		}
				    	}
				    	for (int i = 0; i < 11; ++i)
				    	{
				    		for (int j = 0; j < 11; ++j)
				    		{
				    			cout<<map[i][j]<<" ";	
				    		}
				    		cout<<endl;
				    	}
	    			}

				}

			} else 
				auto err = res.error();
		}
		else if (choice == 3){
			if (auto res = cli.Get("/renderMap")) {
				string msg = "";
				int tmp;
				if (res->status == 200) {
			    	//cout << res->body << endl;
			    	msg = res->body;
			    	int k = 0;
			    	for (int i = 0; i < 11; ++i)
			    	{
			    		for (int j = 0; j < 11; ++j)
			    		{
			    			tmp = msg[k];
			    			map[i][j] = tmp - 48;
			    			k++;	
			    		}
			    	}
			    	for (int i = 0; i < 11; ++i)
			    	{
			    		for (int j = 0; j < 11; ++j)
			    		{
			    			cout<<map[i][j]<<" ";	
			    		}
			    		cout<<endl;
			    	}
			    } else 
					auto err = res.error();
			}
		}
		else if (choice == 4){	
			if (auto res = cli.Get("/stop")) {
				if (res->status == 200) {
			    	cout<<"Server has been stoped"<<endl;
			    	return 0;
			    }
			}else
				auto err = res.error();
		}
		if (auto res = cli.Get("/win")) {
			string msg = "";
			if (res->status == 200) {
				if(res->body!= "0"){
					cout<<"Player "+res->body+" has won the game!"<<endl;
					break;
				}
    			
    		}
		}
		if (auto res = cli.Get("/stop")) {
			if (res->status == 200) {
				if(res->body == "1"){
					cout<<"Game has been stopped!"<<endl;
					break;
				}
    		}
		}
	}
}