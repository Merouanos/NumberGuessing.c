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
typedef struct
{
    short number, IfExist, pos, IsCertain;
} Ai;
typedef struct
{

    Ai *data;
    information CpuInfo;

} structure;
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
    Sleep(500);
    printf("\nCorrect Numbers : %d         Correct Position : %d", info.cor, info.pos);
}
void IntializeData(Ai *data, short i)
{
    data[i].number = i;
    data[i].IsCertain = 0;
    data[i].IfExist = 1;
    data[i].pos = -1;
}
void DeleteDataNum(Ai *data, short pos, short *Numbers)
{
    for (short i = pos; i < *Numbers - 1; i++)
        data[i] = data[i + 1];
    (*Numbers)--;
}
void CheckStatus(structure cpu, short *guess, short *max, short digits)
{
    short i = 0, j;
    while (i < *max)
    {
        if (cpu.data[i].IfExist == 0)
            DeleteDataNum(cpu.data, i, max);
        else if (cpu.data[i].IsCertain == 1 && cpu.data[i].pos != i + 1)
        {
            Ai temp;
            temp = cpu.data[i];
            cpu.data[i] = cpu.data[temp.pos - 1];
            cpu.data[temp.pos - 1] = cpu.data[i];
        }
        i++;
    }
    if (cpu.CpuInfo.cor == 0)
    {
        for (i = 0; i < digits; i++)
        {
            j = 0;
            while (j < *max)
                if (guess[i] == cpu.data[j].number)
                    DeleteDataNum(cpu.data, j, max);
        }
    }
    else if (cpu.CpuInfo.cor == digits)
    {
        for (i = 0; i < digits; i++)
        {
            j = 0;
            while (j < *max)
                if (guess[i] != cpu.data[j].number)
                    DeleteDataNum(cpu.data, j, max);
        }
    }
}
void GenerateGuess(structure cpu, short *guess, short max)
{
    short i;
    for(i=0;i<max;i++)
    {
        if(cpu.data[i].IsCertain==1)
        guess[i]=cpu.data[i].number;
        else
            if(cpu.data[i].IfExist==2)




    }
}

bool IsRightDigits(short number, short digits)
{
    if (number == digits)
        return true;
    else
        return false;
}
bool ConvertStrToArray(char *str, short *array, short max)
{
    for (int i = 0; i < max; i++)
        if (str[i] < '1' || str[i] > '9')
            return false;
        else
            array[i] = str[i] - '0';
    return true;
}
bool IsZero(short *guess, short digits)
{
    int i = 0;
    while (i < 0)
        if (guess[i] == 0)
            return true;
        else
            i++;
    return false;
}
bool IsRepeated(short *guess, short digits)
{
    int i = 0, j;
    while (i < digits - 1)
    {
        j = i + 1;
        while (j < digits)
        {
            if (guess[i] == guess[j])
                return true;
            else
                j++;
        }
        i++;
    }
    return false;
}
void CheckInfo(short *player, short *guessing, short digits, information *info)
{
    bool finished;
    info->cor = 0;
    info->pos = 0;
    for (short i = 0; i < digits; i++)
    {
        finished = false;
        short j = 0;
        while (j < digits && !finished)
        {
            if (player[i] == guessing[j])
            {
                info->cor++;
                if (i == j)
                    info->pos++;
                finished = true;
            }
            else
                j++;
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
    Sleep(500);
    srand(time(0));
    *Cpu = (short *)malloc(digits * sizeof(short));
    for (int i = 0; i < digits; i++)

        do
        {
            (*Cpu)[i] = 1 + rand() % 9;

        } while (IsRepeated(*Cpu, i + 1));
}
void GeneratePlayer(short **player, short digits)
{
    short l;
    char input[digits + 1];
    *player = (short *)malloc(sizeof(short) * digits);
    getchar();
    gets(input);
    l = strlen(input);
    while (!ConvertStrToArray(input, *player, digits) || !IsRightDigits(l, digits) || IsZero(*player, digits) || IsRepeated(*player, digits))
    {
        printf("\nPlease make sure to enter %d digit number that are not repeated and doesn't include zero : ", digits);
        gets(input);
        l = strlen(input);
    }
}
void ReadPlayerInput(short *cpu, short digits, information *info)
{
    short *guessing, l;
    char guess[digits + 1];
    guessing = (short *)malloc(sizeof(short) * digits);
    gets(guess);
    l = strlen(guess);
    while (!ConvertStrToArray(guess, guessing, digits) || !IsRightDigits(l, digits) || IsZero(guessing, digits) || IsRepeated(guessing, digits))
    {
        printf("\nPlease make sure to enter %d digit number that are not repeated and doesn't include zero : ", digits);
        gets(guess);
        l = strlen(guess);
    }
    CheckInfo(cpu, guessing, digits, info);
    DisplayInfo(*info);
    free(guessing);
}
void ReadCpuInput(short *player, short digits, structure cpu)
{
    short *guess, i;
    if (cpu.data = NULL)
    {
        guess = (short *)malloc(sizeof(short) * digits);
        for (i = 0; i < digits; i++)

            do
            {
                guess[i] = (rand() % 9) + 1;

            } while (IsRepeated(guess, i + 1));
        cpu.data = (Ai *)malloc(sizeof(Ai) * 9);
        for (int i = 0; i < 9; i++)
            IntializeData(cpu.data, i);
    }
    CheckInfo(player, guess, digits, &cpu.CpuInfo);
    printf("\nThe Cpu has guessed a number :\n");
    Display(guess, digits);
    DisplayInfo(cpu.CpuInfo);
}

void CheckGameFinished(information info, short player, bool *finished, short digits)
{
    if (info.cor == digits && info.pos == digits)
    {
        *finished = true;
        printf("\nThe game has finished");
        Sleep(500);
        printf("\nPlayer %d has won!!!!!!!!!", player);
    }
}
int main()
{
    information info;
    Player players;
    structure cpu;
    short digits, AiNumbers;
    bool GameFinished = false;
    cpu.data = NULL;
    printf("Welcome to the number guessing game!!\nPlease choose the number of digits 3 or 4 : ");
    ReadDigits(&digits);
    CpGenerate(&players.cpu, digits);
    printf("The Computer has generated a %d digit number , now it's your turn to enter a number for the computer to guess it :\n");
    GeneratePlayer(&players.player, digits);
    while (!GameFinished)
    {
        printf("\nNow Please guess a number :\n");
        ReadPlayerInput(players.cpu, digits, &info);
        CheckGameFinished(info, 1, &GameFinished, digits);
        if (!GameFinished)
        {
            Sleep(500);
            ReadCpuInput(players.player, digits, &info);
            CheckGameFinished(info, 2, &GameFinished, digits);
        }
    }
    FreePlayers(players);
}
