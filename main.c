#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#define prompt '>'

#define RIGHT_END      10
#define LEFT_END        2
#define CURSOR_TOP      1
#define CURSOR_BOTTOM  12

int mult_sum(int x); 

int main() {

	char abacus[13][20] = {
	    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	    {' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' '},
            {' ', '|', '*', '*', '*', '*', '*', '-', '-', '-', '-', '|', '|', '-', '-', '*', '*', '|', ' ', ' '},
            {' ', '|', '*', '*', '*', '*', '*', '-', '-', '-', '-', '|', '|', '-', '-', '*', '*', '|', ' ', ' '},
            {' ', '|', '*', '*', '*', '*', '*', '-', '-', '-', '-', '|', '|', '-', '-', '*', '*', '|', ' ', ' '},
            {' ', '|', '*', '*', '*', '*', '*', '-', '-', '-', '-', '|', '|', '-', '-', '*', '*', '|', ' ', ' '},
            {' ', '|', '*', '*', '*', '*', '*', '-', '-', '-', '-', '|', '|', '-', '-', '*', '*', '|', ' ', ' '},
            {' ', '|', '*', '*', '*', '*', '*', '-', '-', '-', '-', '|', '|', '-', '-', '*', '*', '|', ' ', ' '},
            {' ', '|', '*', '*', '*', '*', '*', '-', '-', '-', '-', '|', '|', '-', '-', '*', '*', '|', ' ', ' '},
            {' ', '|', '*', '*', '*', '*', '*', '-', '-', '-', '-', '|', '|', '-', '-', '*', '*', '|', ' ', ' '},
            {' ', '|', '*', '*', '*', '*', '*', '-', '-', '-', '-', '|', '|', '-', '-', '*', '*', '|', ' ', ' '},
            {' ', '|', '*', '*', '*', '*', '*', '-', '-', '-', '-', '|', '|', '-', '-', '*', '*', '|', ' ', ' '},
            {' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' '}
	};

	WINDOW *p_win;

	int quit_app = 0;
	int pos_y = 11;
	int pos_x = 0;
	int tmp_x;
    int sum_tmp = 0;
    int sum_tot = 0;
	abacus[pos_y][pos_x] = prompt;

	while (!quit_app) {
		p_win = initscr();
		clear();
		printw("SUM:%14d", sum_tot);
		sum_tot = 0;
        for (int i = 0; i < 13; i++) {
            printw("\n");
            for (int j = 0; j < 20; j++) {
                printw("%c", abacus[i][j]);
            }
        }

		timeout(5000);
		if (getch() == 'q') {
			quit_app = 1;
		    endwin();
			continue;
		}
		if (getch() == '\033') {
			getch();
		}

		switch(getch()) {
			case 'A':
				// up arrow
				if (pos_y - 1 != CURSOR_TOP) {
					abacus[pos_y][pos_x] = ' ';
					pos_y--;
					abacus[pos_y][pos_x] = prompt;
				} else {
					// should chirp 
				}
				break;
			case 'B':
				// down arrow
				if (pos_y + 1 != CURSOR_BOTTOM) {
					abacus[pos_y][pos_x] = ' ';
					pos_y++;
					abacus[pos_y][pos_x] = prompt;
				} else {
					// should chirp
				}
				break;
			case 'C':
				// right arrow
				// need to push the * to the right
				tmp_x = pos_x;
				for (int i = 11; i > 1; i--) {
					if (abacus[i][0] == prompt) {
						if (abacus[i][14] == '*') {
							break;
						}
					    for (int j = 0; j < 10; j++) {
						    tmp_x = RIGHT_END - j;
						    if (abacus[i][tmp_x] == '-' && tmp_x - 4 >= 2) {
							    abacus[i][tmp_x] = '*';
							    abacus[i][tmp_x - 4] = '-';
						    } else {
							    continue;
						    }
						    break;
					    }
						if (abacus[i][2] == '-') {
							if (abacus[i][13] == '-') {
								abacus[i][15] =  '-';
								abacus[i][13] = '*';
								abacus[i][10] = '-';
								abacus[i][9]  = '-';
								abacus[i][8]  = '-';
								abacus[i][7]  = '-';
								abacus[i][6]  = '*';
								abacus[i][5]  = '*';
								abacus[i][4]  = '*';
								abacus[i][3]  = '*';
								abacus[i][2]  = '*';
							} else if (abacus[i][13] == '*' && abacus[i][14] == '-') {
								abacus[i][16] = '-';
								abacus[i][14] = '*';
								abacus[i][10] = '-';
								abacus[i][9]  = '-';
								abacus[i][8]  = '-';
								abacus[i][7]  = '-';
								abacus[i][6]  = '*';
								abacus[i][5]  = '*';
								abacus[i][4]  = '*';
								abacus[i][3]  = '*';
								abacus[i][2]  = '*';
							}
						}
					} else {
						continue;
					}
					break;
				}
				break;
			case 'D':
				// left arrow
				// need to push the * to the left
				tmp_x = pos_x;
				for (int i = 11; i > 1; i--) {
					if (abacus[i][0] == prompt) {
						if (abacus[i][13] == '*' && abacus[i][14] == '*' && abacus[i][10] == '-') {
							abacus[i][16] = '*';
							abacus[i][14] = '-';
							abacus[i][10] = '*';
							abacus[i][9]  = '*';
							abacus[i][8]  = '*';
							abacus[i][7]  = '*';
							abacus[i][6]  = '*';
							abacus[i][5]  = '-';
							abacus[i][4]  = '-';
							abacus[i][3]  = '-';
							abacus[i][2]  = '-';
						} else if (abacus[i][13] == '*' && abacus[i][14] == '-' && abacus[i][10] == '-') {
							abacus[i][15] = '*';
							abacus[i][13] = '-';
							abacus[i][10] = '*';
							abacus[i][9]  = '*';
							abacus[i][8]  = '*';
							abacus[i][7]  = '*';
							abacus[i][6]  = '*';
							abacus[i][5]  = '-';
							abacus[i][4]  = '-';
							abacus[i][3]  = '-';
							abacus[i][2]  = '-';
						}
					    for (int j = 0; j < 10; j++) {
						    tmp_x = LEFT_END + j;
						    if (abacus[i][tmp_x] == '-' && tmp_x + 4 <= 10) {
							    abacus[i][tmp_x] = '*';
							    abacus[i][tmp_x + 4] = '-';
						    } else {
							    continue;
						    }
						    break;
					    }
					} else {
						continue;
					}
					break;
				}
				break;
			case 'q':
				quit_app = 0;
		}
		// sum stars
		for (int y = 11; y > 1; y--) {
			sum_tmp = 0;
			if (abacus[y][14] == '*') {
				sum_tmp = sum_tmp + 5;
			}
			if (abacus[y][13] == '*') {
				sum_tmp = sum_tmp + 5;
			}
			if (abacus[y][10] != '-') {
			    for (int x = 10; x > 6; x--) {
				   if(abacus[y][x] == '*') {
					   sum_tmp = sum_tmp + 1;
				   }
			    } 
			}
			sum_tot = sum_tot + (sum_tmp * mult_sum(y));
		}
		endwin();
	}
	return 0;
}

int mult_sum(int x) {
	int m;
	switch(x) {
		case 11:
			m = 1;
			break;
		case 10:
			m = 10;
			break;
		case 9:
			m = 100;
			break;
		case 8:
			m = 1000;
			break;
		case 7:
			m = 10000;
			break;
		case 6:
			m = 100000;
			break;
		case 5:
			m = 1000000;
			break;
		case 4:
			m = 1000000;
			break;
		case 3:
			m = 10000000;
			break;
		case 2:
			m = 100000000;
			break;
	}
	return m;
}
