#define W 80
#define H 25

#include <fcntl.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

void menu(char menu_field[H][W], int contin, int kursor, int speed);
int switchmenu(int *kursor, int contin, char menu_field[H][W]);
int kbhit();
int getch();
int generate(int menu_field[H][W], int nfile);
void print_menu_field(char menu_field[H][W]);
void print_field(int prev_field[H][W]);
int checkExit(int prev_field[H][W], int next_field[H][W], int speed);
int getSpeed(int *speed, int prev_field[H][W], int next_field[H][W]);
void check_rules(int prev_field[H][W], int next_field[H][W], int i, int j);

int main() {
    int contin = 1, kursor = 2, speed = 1, exit = 0;
    int prev_field[H][W] = {0}, next_field[H][W] = {0};
    char menu_field[H][W];
    while (!exit) {
        menu(menu_field, contin, kursor, speed);
        print_menu_field(menu_field);
        while (switchmenu(&kursor, contin, menu_field) != 1) {
            print_menu_field(menu_field);
        }
        if (kursor > 1 && kursor < 7) {
            if (generate(prev_field, kursor - 1) == 0) {
                while (getSpeed(&speed, prev_field, next_field) != 1) {  // если остановлена игра
                }
                contin = 0;
            } else {
                printf("Файл %d.txt отсутствует.\n", (kursor - 1));
                exit++;
            }
        } else if (kursor == 1) {
            while (getSpeed(&speed, prev_field, next_field) != 1) {  // если остановлена игра
            }
        } else {
            exit = 1;
        }
    }
    return 0;
}

void menu(char menu_field[H][W], int contin, int kursor, int speed) {
    char *menu_item_1 = "CONTINUE", *menu_item_2 = "START GAME";
    char *menu_item_3 = "EXIT", *menu_item_4 = "G A M E  O F  L I F E";
    char *menu_item_5 = "A - Up / Z - Down / Space - Break|Enter / 0~9 - Speed [ ]";
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            menu_field[i][j] = ' ';
        }
    }
    for (int j = 0; j < W; j++) {
        menu_field[0][j] = '#';
        menu_field[H - 1][j] = '#';
    }
    for (int i = 1; i < H - 1; i++) {
        menu_field[i][0] = '#';
        menu_field[i][W - 1] = '#';
    }
    for (int i = 0; i < 57; i++) {
        menu_field[H - 3][12 + i] = menu_item_5[i];
    }
    menu_field[22][67] = speed + 48;
    for (int j = 0; j < 21; j++) {
        menu_field[3][29 + j] = menu_item_4[j];
    }
    if (contin == 0) {
        for (int j = 0; j < 8; j++) {
            menu_field[6][35 + j] = menu_item_1[j];
        }
    }
    for (int i = 1; i < 6; i++) {
        for (int j = 0; j < 10; j++) {
            menu_field[6 + i * 2][35 + j] = menu_item_2[j];
        }
        menu_field[6 + i * 2][46] = i + 48;
    }
    for (int j = 0; j < 4; j++) {
        menu_field[18][35 + j] = menu_item_3[j];
    }
    menu_field[4 + kursor * 2][32] = '>';
}

int switchmenu(int *kursor, int contin, char menu_field[H][W]) {
    int start = 0;
    char key;
    key = getch();
    if ((key == 'a' || key == 'A') && (*kursor > (1 + contin))) {
        menu_field[4 + *kursor * 2][32] = ' ';
        *kursor = *kursor - 1;
        menu_field[4 + *kursor * 2][32] = '>';
    } else if ((key == 'z' || key == 'Z') && (*kursor < 7)) {
        menu_field[4 + *kursor * 2][32] = ' ';
        *kursor = *kursor + 1;
        menu_field[4 + *kursor * 2][32] = '>';
    } else if (key == 32) {
        start++;
    }
    return start;
}

int generate(int prev_field[H][W], int nfile) {
    int err = 0;
    char str[] = "1.txt";
    str[0] = nfile + 48;
    FILE *pfile;
    if ((pfile = fopen(str, "r")) == NULL) {
        err++;
    } else {
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                fscanf(pfile, "%d", &prev_field[i][j]);
            }
        }
        fclose(pfile);
    }
    return err;
}

int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

void print_menu_field(char menu_field[H][W]) {
    printf("\e[2J\e[H");  // system("clear"); printf("\x1B[1;1H\x1B[2J"); system("cls");
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            printf("%c", menu_field[i][j]);
        }
        printf("\n");
    }
}

int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ICANON;
    newt.c_lflag &= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void print_field(int prev_field[H][W]) {
    printf("\e[2J\e[H");  // system("clear");
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (prev_field[i][j] == 1)
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }
}

int getSpeed(int *speed, int prev_field[H][W], int next_field[H][W]) {
    int res = 0;
    while (res != 1) {
        int key;
        key = checkExit(prev_field, next_field, *speed);
        if (key == 10) {         // это любая клавиша
            res = -1;            // не имеет смысла
        } else if (key == -1) {  // это пробел
            res = 1;
        } else {
            *speed = key;
            // printf("speed is %d\n", *speed); нужно печатать в интерфейс
            res = -1;
        }
        // сюда заходит после проверки клавиш
    }
    return res;
}

int checkExit(int prev_field[H][W], int next_field[H][W], int speed) {
    int res = 10;
    while (!kbhit()) {
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                check_rules(prev_field, next_field, i, j);
            }
        }
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                prev_field[i][j] = next_field[i][j];
            }
        }
        print_field(prev_field);
        usleep(1000000 / (speed + 1));
    }
    char key = getchar();
    if (key - '0' >= 0 && key - '0' <= 9) {
        res = key - '0';
    } else if (key == ' ') {
        res = -1;
    }
    return res;
}

void check_rules(int prev_field[H][W], int next_field[H][W], int i, int j) {
    int sum = 0;
    if (prev_field[(i - 1 + H) % H][(j - 1 + W) % W] == 1) {
        sum++;
    }
    if (prev_field[(i - 1 + H) % H][j] == 1) {
        sum++;
    }
    if (prev_field[(i - 1 + H) % H][(j + 1 + W) % W] == 1) {
        sum++;
    }
    if (prev_field[i][(j - 1 + W) % W] == 1) {
        sum++;
    }
    if (prev_field[i][(j + 1 + W) % W] == 1) {
        sum++;
    }
    if (prev_field[(i + 1 + H) % H][(j - 1 + W) % W] == 1) {
        sum++;
    }
    if (prev_field[(i + 1 + H) % H][j] == 1) {
        sum++;
    }
    if (prev_field[(i + 1 + H) % H][(j + 1 + W) % W] == 1) {
        sum++;
    }
    if ((prev_field[i][j] == 1) && (sum > 1 && sum < 4)) {
        next_field[i][j] = 1;
    } else if ((prev_field[i][j] == 0) && (sum == 3)) {
        next_field[i][j] = 1;
    } else {
        next_field[i][j] = 0;
    }
}
