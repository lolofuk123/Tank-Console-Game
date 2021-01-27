#define _CRT_SECURE_NO_WARNINGS	// for visual studio
// Important constants
#define _USE_MATH_DEFINES
#define DEGREE_IN_RADIANS 0.01745329252
#define KM_ZA_H_V_M_ZA_S 0.27778
#define G 9.81

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>

// ================= FUNCTIONS DECLARATIONS ===================
double deg_to_rad(double angle);					
double km_h_to_m_s(double velocity);				
double generate_random_shot_power(int max, int min);
double calculate_shot_landing(double projectileVelocity, double angle_in_rad, int startingCoorinate);
int generate_random_coordinates();					
void print_starting_position(int player_x, int pc_x);	
void main_game_function(int player_x, int pc_x);
void print_game(int hrac_x, int pc_x, double landing);


int main() {
	srand((unsigned int)time(NULL));
	int player_x = generate_random_coordinates();
	int pc_x = generate_random_coordinates();

	print_starting_position(player_x, pc_x);
	main_game_function(player_x, pc_x);

	return 0;
}

// ================= FUNCTIONS DEFINITIONS ===================

void print_game(int player_x, int pc_x, double landing) {
	printf("\n\n\n");

	for (int i = 0; i <= 119; ++i) {		// console width is 120
		if (player_x == i)
			printf("P");				// mark players position
		else if (pc_x == i)
			printf("C");				// mark PC position
		else  if ((landing - 2 <= i && landing + 2 >= i))	// impact of shot landing is 2 to sides
			printf("x");									// mark the impact of shot
		else
			printf("_");
	}
	printf("\n\n\n");
}

void main_game_function(int player_x, int pc_x) {
	double angle = 0.0, power = 0.0, shotLanding = 0.0;
	int gameEnd = 1, playerTurn = 1, max = 120, min = 20, pcLives = 2;
	int playerPosition = player_x;
	int pcPosition = pc_x;

	do {
		if (playerTurn % 2 == 1) {					// players turn
			printf("Enter angle(in degrees):");
			scanf("%lf", &angle);					// enter angle in degrees
			printf("Enter shot velocity(in km/h):");
			scanf("%lf", &power);					// enter shot power in km/h
			// CALCULATING
			angle = deg_to_rad(angle);
			power = km_h_to_m_s(power);
			shotLanding = calculate_shot_landing(power, angle, player_x);

			print_game(playerPosition, pcPosition, shotLanding);
			if (((shotLanding + 2 >= pc_x) && (shotLanding - 2 <= pc_x)) || shotLanding == pc_x) {	// if PC position is within the impact of shot
				pcLives -= 1;
				if (pcLives == 0) {
					gameEnd = 0;
					printf("\t\t\t\t\tCongrats you have beaten my SUPERINTELIGENT COMPUTER\n\n");
				}
				else
					printf("\t\t\t\t\tYou hit PC. It has one life remaining.\n\n");

			}
			else if (((shotLanding + 2 >= player_x) && (shotLanding - 2 <= player_x)) || shotLanding == player_x) {
				printf("\t\t\t\t\tWell.. I have never seen this.. You killed yourself.\n\n");
				gameEnd = 0;
			}
			else
				gameEnd = 1;
		}
		else {									//  PC is on turn
			if (pc_x < player_x)			// if PC is left to player sets angle to 45 or to 135 otherwise
				angle = deg_to_rad(45.0);
			else
				angle = deg_to_rad(135.0);

			power = generate_random_shot_power(max, min);
			power = km_h_to_m_s(power);		// konverzia na m/s
			shotLanding = calculate_shot_landing(power, angle, pc_x);
			printf("\t\t\t\t\tWATCH OUT! My SUPERINTELLIGENT PC focused on you and shoots!!!\n\n");
			print_game(player_x, pc_x, shotLanding);    //nakreslenie hry
			if ((shotLanding + 2 >= player_x) && (shotLanding - 2 <= player_x)) {	// ak zasah tak koniec hry
				printf("\t\t\t\t\tMy SUPERINTELLIGENT PC has wiped you out!\n\n");
				gameEnd = 0;
			}
			else {
				if (shotLanding + 40 < player_x)
					min += 40;
				else if (shotLanding - 30 > player_x)
					max -= 30;
				else if (shotLanding + 30 < player_x)
					min += 30;
				else if (shotLanding - 20 > player_x)
					max -= 20;
				else if (shotLanding + 20 < player_x)
					min += 20;
				else if (shotLanding - 10 > player_x)
					max -= 10;
				else if (shotLanding + 10 < player_x)
					min += 10;
				else if (shotLanding - 5 > player_x)
					max -= 5;
				else
					min += 2;
			}
		}
		playerTurn += 1;
	} while (gameEnd != 0);

	return;
}

int generate_random_coordinates() {
	int num = (rand() % (110 - 10 + 1)) + 10;

	return num;
}

void print_starting_position(int player_x, int pc_x) {

	for (int i = 0; i < 120; ++i) { printf("="); }
	for (int i = 0; i < 52; ++i) { printf("*"); }
	printf(" W E L C O M E ");
	for (int i = 0; i < 53; ++i) { printf("*"); }
	for (int i = 0; i < 120; ++i) { printf("="); }
	printf("\n\n");
	printf("Your mark is P - player C is computer.\nIf you want to shoot left make angle > 90 deg.\n\n\n");

	for (int i = 0; i <= 119; ++i) {
		if (i == player_x)
			printf("P");
		else if (i == pc_x)
			printf("C");			// computer
		else
			printf("_");
	}
	printf("\n\n\n");
}

double km_h_to_m_s(double velocity) {
	return (velocity / 3.6);
}

double deg_to_rad(double angle) {
	double result = 2.0* M_PI*(angle / 360.0);

	return result;
}

double calculate_shot_landing(double projectileVelocity, double angleInRad, int startingCoordinate) {
	double result = startingCoordinate + ((pow(projectileVelocity, 2) / G) * sin(2 * angleInRad));

	return result;
}

double generate_random_shot_power(int max, int min) {		// generates random number from interval min to max
	double result = (rand() % (max - min + 1)) + min;

	return result;
}
