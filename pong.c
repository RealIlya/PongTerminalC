#include <stdio.h>

#define clear() printf("\033[H\033[J")

#define BALL_SIGN '@'
#define BOUNDARY_SIGN '='
#define GAP_SIGN ' '
#define NET_SIGN '#'
#define PLATFORM_SIGN '|'

const int START_SCORE = 0;
const int WIN_SCORE = 21;

const int WIDTH = 80;
const int HEIGHT = 25;
const int BOUNDARIES = HEIGHT + 2;

const int BALL_GAP_1 = 30;
const int BALL_GAP_2 = WIDTH - 30;
const int SCORE_GAP = WIDTH - 34;

const int PLATFORM_POS_1_X_DEF = 0;
const int PLATFORM_POS_2_X_DEF = WIDTH - 1;

const int MIDDLE = BOUNDARIES / 2;

void start_game();
void play_game();

void print_score(int score1, int score2);
void print_field(int platform_y_1, int platform_y_2, int ball_x, int ball_y);

int update_ball_position_platform(int ball_x, int ball_y, int platform_pos_1_y, int platform_pos_2_y);
int update_ball_position_boudaries(int ball_y);

int main() {
    start_game();
    return 0;
}

void start_game() {
    printf("Welcome to Pong Game, Stangers!\n");
    printf("You're looking sooooo tired, I think maybe you wanna playyy?\n");
    printf("(y, n) > ");

    char input;
    while (1) {
        scanf("%c", &input);

        if (input == '\n') continue;

        if (input == 'y') {
            printf("Let's Play!");
            play_game();
            break;
        } else if (input == 'n') {
            printf("Okey... :(\n");
            printf("See you later!");
            break;
        } else
            printf("What did you say?\n");

        printf("(y, n) > ");
    }
}

// to play game
void play_game() {
    int score1 = START_SCORE, score2 = START_SCORE;
    int platform_last_pos_1_y = MIDDLE, platform_last_pos_2_y = MIDDLE;
    int ball_x = BALL_GAP_1, ball_y = MIDDLE;
    int ball_direction_x = -1, ball_direction_y = 1;
    char input = 'y';
    while (input != 'q' && score1 != 21 && score2 != 21) {
        int unknown_char = 0;  // stores correct input
        if (input == 'a' || input == 'A') {
            if (platform_last_pos_1_y - 2 > 0) platform_last_pos_1_y--;  // move platform 1 decreasing y
        } else if (input == 'z' || input == 'Z') {
            if (platform_last_pos_1_y + 1 < HEIGHT) platform_last_pos_1_y++;  // move platform 1 increasing y
        } else if (input == 'k' || input == 'K') {
            if (platform_last_pos_2_y - 2 > 0) platform_last_pos_2_y--;  // move platform 2 decreasing y
        } else if (input == 'm' || input == 'M') {
            if (platform_last_pos_2_y + 1 < HEIGHT) platform_last_pos_2_y++;  // move platform 2 increasing y
        } else if (input == ' ') {
        } else
            unknown_char = 1;  // if input character does not exist
        if (!unknown_char) {
            ball_direction_x *=
                update_ball_position_platform(ball_x, ball_y, platform_last_pos_1_y, platform_last_pos_2_y);
            ball_direction_y *= update_ball_position_boudaries(ball_y);
            if (ball_x <= PLATFORM_POS_1_X_DEF) {
                score2++;
                ball_x = BALL_GAP_2;
                ball_direction_x = 1;
                ball_y = MIDDLE;
                ball_direction_y = 1;
            } else if (ball_x >= PLATFORM_POS_2_X_DEF) {
                score1++;
                ball_x = BALL_GAP_1;
                ball_direction_x = -1;
                ball_y = MIDDLE;
                ball_direction_y = 1;
            }
            ball_x += ball_direction_x;
            ball_y += ball_direction_y;
        }
        print_score(score1, score2);
        print_field(platform_last_pos_1_y, platform_last_pos_2_y, ball_x, ball_y);
        printf("Moving: ");
        scanf("%c", &input);
        clear();
    }
    if (input != 'q') {
        printf("Game Over!\n");
        printf(score1 == 21 ? "Player 1 won!" : "Player 2 won!");
    }
}

// print players score
void print_score(int score1, int score2) {
    printf("\nPlayer 1");
    for (int i = 0; i < SCORE_GAP; i++) {
        if (SCORE_GAP / 2 - 3 == i) printf((score1 < 10 ? "Score:  %d" : "Score: %d"), score1);
        if (SCORE_GAP / 2 + 3 == i) printf((score2 < 10 ? "Score:  %d" : "Score: %d"), score2);
        printf(" ");
    }

    printf("Player 2\n");
}

// print the game field
void print_field(int platform_y_1, int platform_y_2, int ball_x, int ball_y) {
    for (int y = 0; y < BOUNDARIES; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (y == 0 || y == BOUNDARIES - 1)
                printf("%c", BOUNDARY_SIGN);
            else if (x == ball_x && y == ball_y)
                printf("%c", BALL_SIGN);
            else if (x == WIDTH / 2 || x == WIDTH / 2 - 1)
                printf("%c", NET_SIGN);
            else if (x == PLATFORM_POS_1_X_DEF && (y >= platform_y_1 - 1 && y <= platform_y_1 + 1) &&
                     (platform_y_1 - 1 > 0 && platform_y_1 + 1 <= HEIGHT))
                printf("%c", PLATFORM_SIGN);
            else if (x == PLATFORM_POS_2_X_DEF && (y >= platform_y_2 - 1 && y <= platform_y_2 + 1) &&
                     (platform_y_2 - 1 > 0 && platform_y_2 + 1 <= HEIGHT))
                printf("%c", PLATFORM_SIGN);
            else
                printf("%c", GAP_SIGN);
        }

        printf("\n");
    }
}

// update ball position relative to the platforms
int update_ball_position_platform(int ball_x, int ball_y, int platform_pos_1_y, int platform_pos_2_y) {
    return (ball_x - 1 == PLATFORM_POS_1_X_DEF &&
            (ball_y >= platform_pos_1_y - 1 && ball_y <= platform_pos_1_y + 1)) ||
                   (ball_x + 1 == PLATFORM_POS_2_X_DEF && ball_y >= platform_pos_2_y - 1 &&
                    ball_y <= platform_pos_2_y + 1)
               ? -1
               : 1;
}

// update ball position relative to the boundaries
int update_ball_position_boudaries(int ball_y) { return (ball_y > 1 && ball_y < BOUNDARIES - 2) ? 1 : -1; }