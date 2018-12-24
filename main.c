#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
//#include <conio.h>
#include <time.h>
//#include <conio.h>

//#define num 6 //количество команд

int i;
struct football//структура команды
{
    int number;//порядковый номер, для рандома
    char name[25];//название
    int score;//количество очков в последнем туре
    int sum_score;//количество очков за все проведенные туры
};
/*
 struct tour
 {//структура матча
 struct football team_1;//команда 1
 struct football team_2;//команда 2
 };*/

struct Score
{
    int team1;
    int team2;
    char name1[25];
    char name2[25];
};

struct Score* tabl;

void tur(struct football[], int);//функция подбора соперников на матч
void output(struct football[], int);//вывод итогово турнирной таблицы
void sort_sum_score(struct football[], int);//сортировка по количеству очков за туры
void output_tur(int);//вывод результатов тура
void input_score(struct football*, struct football*, struct Score*);//ввод очков за матч

int main()
{
    int count_tur = 0;
    int a, j = 0, num;
    struct football* turnir = (struct football*) malloc(1 * sizeof(struct football));//массив команд
    FILE *file;
    
    
    
    file = fopen("/Users/art.fek/Desktop/kursachfinal2/kursachfinal2/team.txt", "r");
    if (file != NULL)
    {
        fscanf(file, "%i", &num);
        turnir = (struct football*) realloc(turnir, num * sizeof(struct football));
        while (j < num)//ввод названий
        {
            fscanf(file, "%s", &turnir[j].name);
            turnir[j].sum_score = 0;
            turnir[j].number = j;
            j++;
        }
    }
    j++;
    fclose(file);
    if (j % 32 != 0 && j % 16 != 0 && j % 8 != 0 && j % 4 != 0 && j % 2 != 0 && j == 0)
    {
        printf("%i Kolichestvo komand nevernoe!!!", j);
        system("pause");
        return 1;
    }
    
    tabl = (struct Score*) malloc((num-1) * sizeof(struct Score));
    for (i = 0; i < num; i++)
    {
        tabl[i].team1 = 0;
        tabl[i].team2 = 0;
    }
    
    do{
        printf("\n Viberite deistvie:\n\n\n");
        printf("1. Provedenie tura\n\n");
        printf("2. Vivod sceta komand\n\n");
        printf("3. Vivod resul'tata igr\n\n");
        printf("4. Exit\n\n\n");
        scanf("%i", &a);
        
        switch (a)
        {
            case 1:
                tur(turnir, num);
                break;
            case 2:
                printf("Vivod komand\n\n");
                output(turnir, num);
                break;
            case 3:
                output_tur(num);
                system("pause");
                break;
            case 4:
                break;
            default:
                printf("\n\nERROR!!! Please enter number 1-4...\n\n");
        }
        
    } while (a != 4);
    system("pause");
    free(turnir);
    free(tabl);
    return 0;
}

void game(struct football turnir[], int num, int antirepet[], int a)
{
    struct football r;
    int n = 0, m = 0, j, k;
    for (i = 0; i < num - 1; i++)
        for (j = i + 1; j < num; j++)
            if (turnir[j].number < turnir[i].number)
            {
                r = turnir[i];
                turnir[i] = turnir[j];
                turnir[j] = r;
            }
    for (i = 0; i < num; i++)
        antirepet[i] = -1;
    k = 0;
    while (k < num)
    {
        //printf("i = %d\n\n", k);
        do{//подбор первой команды в матч
            srand(time(NULL));
            n = rand() % num;
            if (antirepet[n] == -1)//если эта команда еще не учавствовала, то выбираем ее и выходим из цикла
            {
                antirepet[n] = 1;//и присваиваем соответсвующему элементу массива 0
                //printf("i = %d\n\n", k);
                ++k;
                break;
            }
        } while (1);//в противном случае цикл будет продолжаться, пока не найдется не участвующая команда
        //такой же принцип для подбора соперника
        //printf("i = %d\n\n", k);
        do{
            srand(time(NULL));
            m = rand() % num;
            if (antirepet[m] == -1)
            {
                antirepet[m] = 1;
                //printf("i = %d\n\n", k);
                ++k;
                break;
            }
        } while (1);
        //printf("i = %d\n\n", k);
        input_score(&turnir[n], &turnir[m], &tabl[a]);
        a++;
        //input_score(&turnir[m], &turnir[n], &tabl[m][n]);
    }
    
    for (i = 0; i < num-1; i++)
        for (j = i+1; j < num; j++)
            if (turnir[j].sum_score > turnir[i].sum_score)
            {
                r = turnir[i];
                turnir[i] = turnir[j];
                turnir[j] = r;
            }
    printf("\n\n");
    //for (i = 0; i < num; i++)
    //printf(" %i ", turnir[i].sum_score);
    if (num / 2 > 1)
    {
        printf("\n-----------------------------\n\n");
        game(turnir, num / 2, antirepet, a);//рекурсия
    }
}

void tur(struct football turnir[], int num)
{
    struct football r;
    int j;
    int *antirepet = (int*)malloc (num * sizeof(int));//массив сохраняющий игравшие в туре команды для избежания повторов
    
    game(turnir, num, antirepet, 0);
    for (i = 0; i < num - 1; i++)
        for (j = i + 1; j < num; j++)
            if (turnir[j].number < turnir[i].number)
            {
                r = turnir[i];
                turnir[i] = turnir[j];
                turnir[j] = r;
            }
    free(antirepet);
}

void input_score(struct football* team1, struct football* team2, struct Score* sc)
{
    do{
        printf("Igra \n");
        
        printf("Komanda %s: ", team1->name);
        scanf("%i", &team1->score);
        sc->team1 = team1->score;
        strncpy(sc->name1, team1->name, 25);
        
        printf("Komanda %s: ", team2->name);
        scanf("%i", &team2->score);
        sc->team2 = team2->score;
        strncpy(sc->name2, team2->name, 25);
        
        if (team1->score == team2->score)
            printf("\nNich'ya\n\n Povtor igri\n");
        
    } while (team1->score == team2->score);
    if (team1->score > team2->score)
    {
        team1->sum_score += 3;
        team2->sum_score += 0;
    }
    else
    {
        team1->sum_score += 0;
        team2->sum_score += 3;
    }
}

void output_tur(int num)
{
    system("cls");
    printf("Final\n");
    printf("%s - %s\t", tabl[num - 2].name1, tabl[num - 2].name2);
    printf("\n");
    printf("%i - %i\t", tabl[num - 2].team1, tabl[num - 2].team2);
    printf("\n\n");
    
    if (num-1 >= 3)
    {
        printf("1/2 final\n");
        for (i = num - 3; i > num - 5; i--)
            printf("%s - %s\t", tabl[i].name1, tabl[i].name2);
        printf("\n");
        for (i = num - 3; i > num - 5; i--)
            printf("%i - %i\t", tabl[i].team1, tabl[i].team2);
        printf("\n\n");
    }
    
    if (num-1 >= 7)
    {
        printf("1/4 final\n");
        for (i = num - 5; i > num - 9; i--)
            printf("%s - %s\t", tabl[i].name1, tabl[i].name2);
        printf("\n");
        for (i = num - 5; i > num - 9; i--)
            printf("%i - %i\t", tabl[i].team1, tabl[i].team2);
        printf("\n\n");
    }
    
    if (num-1 >= 15)
    {
        printf("1/8 final\n");
        for (i = num - 9; i > num - 17; i--)
            printf("%s - %s\t", tabl[i].name1, tabl[i].name2);
        printf("\n");
        for (i = num - 9; i > num - 17; i--)
            printf("%i - %i\t", tabl[i].team1, tabl[i].team2);
        printf("\n\n");
    }
    
    if (num-1 >= 31)
    {
        printf("1/16 final\n");
        for (i = num - 17; i > num - 31; i--)
            printf("%s - %s\t", tabl[i].name1, tabl[i].name2);
        printf("\n");
        for (i = num - 17; i > num - 31; i--)
            printf("%i - %i\t", tabl[i].team1, tabl[i].team2);
        printf("\n\n");
    }
}

void output(struct football team[], int num)//вывод команд в соответсвии с набранными очками
{
    sort_sum_score(team, num);//сортировка по количеству набранных очков
    system("cls");
    printf("\tItogovay talblica\n\n");
    for (i = 0; i<num; i++)
    {
        printf("%i - %s\n", team[i].sum_score, team[i].name);
    }
    system("pause");
}

void sort_sum_score(struct football team[], int num)//сортировка по убыванию методом "шейкера"
{
    struct football R;
    int leftMark = 1;
    int rightMark = num - 1;
    while (leftMark <= rightMark)
    {
        for (i = rightMark; i >= leftMark; i--)
            if (team[i - 1].sum_score < team[i].sum_score)
            {
                R = team[i];
                team[i] = team[i - 1];
                team[i - 1] = R;
            }
        leftMark++;
        for (i = leftMark; i <= rightMark; i++)
            if (team[i - 1].sum_score <
                team[i].sum_score)
            {
                R = team[i];
                team[i] = team[i - 1];
                team[i - 1] = R;
            }
        rightMark--;
    }
}
