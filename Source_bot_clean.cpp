#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <string>
using namespace std;



double cdistance(int xp, int yp, int xc, int yc) {
	double cd;
	cd = sqrt(pow((xp - xc), 2) + pow((yp - yc), 2));

	return cd;
}

string nextmove1(int xp, int yp, int xc, int yc) { // evaluating the direction to reach target
	struct move {
		double distofmove;
		string direction;
	};
	string outdirection;
	move decision;
	move movedir[4];
	movedir[0].direction = "UP";
	movedir[0].distofmove = cdistance(xp, yp, xc - 1, yc);


	movedir[1].direction = "DOWN";
	movedir[1].distofmove = cdistance(xp, yp, xc + 1, yc);


	movedir[2].direction = "LEFT";
	movedir[2].distofmove = cdistance(xp, yp, xc, yc - 1);


	movedir[3].direction = "RIGHT";
	movedir[3].distofmove = cdistance(xp, yp, xc, yc + 1);




	decision = movedir[0];

	double mdistance;

	for (int i = 0; i < 4; i++) {
		if (movedir[i].distofmove < decision.distofmove) {
			decision = movedir[i];
			mdistance = movedir[i].distofmove;
		}
	}


	return decision.direction;

}


void next_move(int posr, int posc, vector <string> board) {

	vector <int> drx; vector <int> dry; vector <double> dcdistance;
	vector <int> drxo; vector <int> dryo; vector <double> ocdistance;
	int curx, cury;
	int n = 5; int no_of_dirtycells; int no_of_notobscells;
	curx = posr; cury = posc; int choice;
	struct dirtycells {
		int xco;
		int yco;
		double distancetotarget;
	};
	dirtycells target;
	string result; int turns = 1;
	




	for (int ii = 0; ii < n; ii++) {
		for (int jj = 0; jj < n; jj++) {
			if (board[ii][jj] == 'd') {
				drx.push_back(ii);
				dry.push_back(jj);
				dcdistance.push_back(cdistance(ii, jj, curx, cury));
			}
			else if (board[ii][jj] == 'o') {
				drxo.push_back(ii);
				dryo.push_back(jj);
				ocdistance.push_back(cdistance(ii, jj, curx, cury));
			}

		}

	}
	
	no_of_dirtycells = drx.size();
	no_of_notobscells = drxo.size();
	 	  
	if (no_of_dirtycells>0)
	{
		target.distancetotarget = dcdistance[0];
		target.xco = drx[0];
		target.yco = dry[0];
		choice = 1;
	}
	else if (no_of_dirtycells == 0 && no_of_notobscells > 0) {
		target.distancetotarget = ocdistance[0];
		target.xco = drxo[0];
		target.yco = dryo[0];
		choice = 0;
	}



	if (choice == 1) {
		for (int i = 0; i < no_of_dirtycells; i++) {
			if (dcdistance[i] < target.distancetotarget) {
				target.distancetotarget = dcdistance[i];
				target.xco = drx[i];
				target.yco = dry[i];
			}
		}
	}
	else
	{
		for (int i = 0; i < no_of_notobscells; i++) {
			if (ocdistance[i] < target.distancetotarget) {
				target.distancetotarget = ocdistance[i];
				target.xco = drxo[i];
				target.yco = dryo[i];
			}
		}
	}
	
	
	while (target.distancetotarget > 0 && turns > 0)
	{
		result = nextmove1(target.xco, target.yco, curx, cury);
		cout << result << endl;

		if (result == "RIGHT") {
			cury = cury + 1;
		}
		else if (result == "UP") {
			curx = curx - 1;
		}
		else if (result == "LEFT") {
			cury = cury - 1;
		}
		else if (result == "DOWN") {
			curx = curx + 1;
		}
		turns = turns - 1;

	}

	if (target.distancetotarget == 0 && choice == 1) {
		result = "CLEAN";
		cout << result << endl;
	}
	



}


int main(void) {
	int pos[2]; int c;
	vector <string> board;
	cin >> pos[0] >> pos[1];
	for (int i = 0; i < 5; i++) {
		string s; cin >> s;
		board.push_back(s);
	}
	next_move(pos[0], pos[1], board);
	cin >> c;
	return 0;
}