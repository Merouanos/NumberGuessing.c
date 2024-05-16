#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
typedef struct
{
    short pos, cor;
} information;
typedef struct
{
    short *player, *cpu;
} Player;
void wait(short time)
{
    printf("\n");
    for (short i = 0; i < time; i++)
    {
        printf(".");
        Sleep(500);
    }
    printf("\n");
}
void Display(short *player, short digits)
{
    wait(5);
    for (int i = 0; i < digits; i++)
        printf("%d", player[i]);
    printf("\n");
}
void FreePlayers(Player players)
{
    free(players.cpu);
    free(players.player);
}
void DisplayInfo(information info)
{
    printf("\nCorrect Position : %d         Correct Numbers : %d", info.pos, info.cor);
}
short pow_10(short degree)
{
    short s=1;
    while(degree>0)
    {
    s*=10;
    degree--;
    }
    return s;


}
bool IsRightDigits(short number, short digits)
{
    short i = 0;
    while (number > 0)
    {
        i++;
        number /= 10;
    }
    if (digits == i)
        return true;
    else
        return false;
}
bool IsRepeated(short guess, short digits)
{
    short i = 0, x;
    while (digits > 1)
    {
        x = guess;
        i = 1;
        while (i < digits)
        {
            x /= 10;
            i++;
        }
        if (x == guess % 10)
            return true;
        else
        {
            guess = guess % pow_10(digits-1);
            digits--;
        }
    }
    return false;
}
void CheckInfo(short *player, short guessing, short digits, information *info)
{
    short x, j;
    bool finished;
    info->cor = 0;
    info->pos = 0;
    for (short i = 0; i < digits; i++)
    {
        finished=false;
        x = guessing;
        j = digits - 1;
        while (x > 0 && !finished)
        {
            if (player[digits - 1 - i] == guessing % 10)
            {
                info->cor++;
                if (j == i)
                    info->pos++;
                finished=true;
            }
            else
            {
            j--;
            x /= 10;
            }
        }
    }
}
/*--------------------------------Complexe fonctions -----------------------------------------------------------*/
void ReadDigits(short *digits)
{
    scanf("%d", digits);
    while (*digits > 4 || *digits < 3)
    {
        printf("\nPlease enter the right number 3 or 4 :");
        scanf("%d", digits);
    }
}
void CpGenerate(short **Cpu, short digits)
{
    short guess = 0;
    srand(time(0));
    *Cpu = (short *)malloc(digits * sizeof(short));
    for (int i = 0; i < digits; i++)
    {
        do
        {
            (*Cpu)[i] = 1 + rand() % 9;

        } while (IsRepeated(guess, i + 1));
        guess = guess * 10 + (*Cpu)[i];
    }
}
void GeneratePlayer(short **player, short digits)
{
    short guess;
    scanf("%d", &guess);
    while (!IsRightDigits(guess, digits) || IsRepeated(guess, digits))
    {
        printf("\nPlease make sure to enter %d digit number that are not repeated :", digits);
        scanf("%d", &guess);
    }
    *player = (short *)malloc(sizeof(short) * digits);
    for (int i = 0; i < digits; i++)
    {
        (*player)[digits - 1 - i] = guess % 10;
        guess /= 10;
    }
}
void ReadPlayerInput(short *cpu, short digits)
{
    information info;
    short guess;
    scanf("%d", &guess);
    while (!IsRightDigits(guess, digits) || IsRepeated(guess, digits))
    {
        printf("\nPlease make sure to enter %d digit number that are not repeated:", digits);
        scanf("%d", &guess);
    }
    CheckInfo(cpu, guess, digits, &info);
    wait(5);
    DisplayInfo(info);
}
void ReadCpuInput(short *player, short digits)
{
    information info;
    short guess;
    CheckInfo(player, guess, digits, &info);
    wait(5);
    DisplayInfo(info);
}
int main()
{
    information info;
    Player players;
    short digits;
    bool GameFinished = false;
    printf("Welcome to the number guessing game!!\nPlease choose the number of digits 3 or 4 : ");
    ReadDigits(&digits);
    CpGenerate(&players.cpu, digits);
    printf("The Computer has generated a %d digit number , now it's your turn to enter a number for the computer to guess it :\n");
    GeneratePlayer(&players.player, digits);
    Display(players.cpu, digits);
    while (!GameFinished)
    {
        printf("\nNow Please guess a number :\n");
        ReadPlayerInput(players.cpu, digits);
    }
    FreePlayers(players);
}
