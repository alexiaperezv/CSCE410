// C file for all functions used in main code, including algorithm-specific functions
// By Alexia Perez, 127008512 - All code references included in README.md file

#include "pagingSystem.h"

void newInputFile()
{
    FILE *fptr; // file pointer
    fptr = fopen("PerezA_proj2_input.txt", "w"); // create file with specified name
    if(fptr == NULL)
    {
        printf("Error creating file.\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < 100; i++) // generate 100 random integers
    {
        int number = rand() % (15 + 1); // NOLINT(cert-msc50-cpp)
        if(i != 99)
        {
            fprintf(fptr, "%d\n", number); // add random integer to file + a new line
        }
        else
        {
            fprintf(fptr, "%d", number); // if on last iteration of loop, do not add new line in file
        }
    }
    fclose(fptr); // closes the file
}

void getRefs(int *references, char * filename)
{
    FILE *f = fopen(filename, "r");
    int i = 0;
    int val;
    while(fscanf(f, "%d", &val) > 0)
    {
        references[i] = val;
        i++;
    }
    fclose(f);
}

void makeTable(int *tableName, int size)
{
    for(int i = 0; i < size; i++)
        tableName[i] = -1;
}

void printTime()
{
    time_t t = time(NULL);
    struct tm *current = localtime(&t);
    printf("%s", asctime(current));
}

void printTable(int table[], int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%d ", table[i]);
    }
}

int getAlgChoice()
{
    int choice;
    printf("Choose a page replacement algorithm from the following list:\n1.FIFO\n2.LRU\n3.Second Chance\n");
    scanf("%d", &choice);
    if(choice < 1 || choice > 3)
    {
        printf("Invalid choice entered, please try again.\n");
        getAlgChoice();
    }
    return choice;
}

int getNumFrames()
{
    int choice;
    printf("Choose between:\n1.4-page frames\tor\n2.8-page frames\n");
    scanf("%d", &choice);
    if(choice < 1 || choice > 2)
    {
        printf("Invalid choice entered, please try again.\n");
        getNumFrames();
    }
    if(choice == 1)
        choice = 4;
    if(choice == 2)
        choice = 8;

    return choice;
}

int FIFO(int frames, int references[])
{
    int FIFOtable[frames];
    makeTable(FIFOtable, frames);

    int pageFaults = 0;
    for(int i = 0; i < 100; i++)
    {
        printf("\n\nPage ref: %d | ", references[i]);
        printTime();
        int s = 0;
        for(int j = 0; j < frames; j++)
        {
            if(references[i] == FIFOtable[j])
            {
                s += 1;
                pageFaults -= 1;
                printf("Hit! Page table ->");
            }
        }

        pageFaults += 1;
        if((pageFaults <= frames) && (s == 0))
        {
            FIFOtable[pageFaults-1] = references[i];
            printf("Page fault! Page table ->");
        }
        else if(s == 0)
        {
            FIFOtable[(pageFaults - 1) % frames] = references[i];
            printf("Page fault! Page table ->");
        }
        printTable(FIFOtable, frames);
    }
    printf("\n\nTotal FIFO Page Faults:\t%d\n", pageFaults);
    return pageFaults;
}

int findLRU(const int *timeTable, int size)
{
    int min = timeTable[0];
    int index = 0;
    for(int i = 0; i < size; i++)
    {
        if(timeTable[i] < min)
        {
            min = timeTable[i];
            index = i;
        }
    }
    return index;
}

int LRU(int frames, int references[])
{
    int LRUtable[frames];
    makeTable(LRUtable, frames);

    int pageFaults = 0, counter = 0, flag1, flag2, index, timeTable[frames];

    for(int i = 0; i < 100; i++)
    {
        printf("\n\nPage ref: %d | ", references[i]);
        printTime();
        flag1 = 0;
        flag2 = 0;
        for(int j = 0; j < frames; j++)
        {
            if(LRUtable[j] == references[i])
            {
                counter += 1;
                timeTable[j] = counter;
                flag1 = 1;
                flag2 = 1;
                printf("Hit! Page table ->");
                break;
            }
        }
        if(flag1 == 0)
        {
            for(int j = 0; j < frames; j++)
            {
                if(LRUtable[j] == -1)
                {
                    counter += 1;
                    pageFaults += 1;
                    LRUtable[j] = references[i];
                    timeTable[j] = counter;
                    flag2 = 1;
                    printf("Page fault! Page table ->");
                    break;
                }
            }
        }
        if(flag2 == 0)
        {
            index = findLRU(timeTable, frames);
            counter += 1;
            pageFaults += 1;
            LRUtable[index] = references[i];
            timeTable[index] = counter;
            printf("Page fault! Page table ->");
        }
        printTable(LRUtable, frames);
    }
    printf("\n\nTotal LRU Page Faults:\t%d\n", pageFaults);
    return pageFaults;
}

int findPage (int page, const int secondChanceTable[], int refBits[], int frames)
{
    for(int i = 0; i < frames; i++)
    {
        if(secondChanceTable[i] == page)
        {
            refBits[i] = true;
            return true;
        }
    }
    return false;
}

int replacePage (int page, int secondChanceTable[], int refBits[], int frames, int location)
{
    while(1)
    {
        if(refBits[location] == 0)
        {
            secondChanceTable[location] = page;
            return (location + 1) % frames;
        }
        refBits[location] = false;
        location = (location + 1) % frames;
    }
}

int secondChance(int frames, int references[])
{
    int secChanceTable[frames];
    makeTable(secChanceTable, frames);
    int refBits[frames];
    for(int i = 0; i < frames; i++)
    {
        refBits[i] = 0;
    }
    int index = 0, pageFaults = 0, pageRef;
    for(int i = 0; i < 100; i++)
    {
        pageRef = references[i];
        printf("\n\nPage ref: %d | ", pageRef);
        printTime();
        if(!findPage(pageRef, secChanceTable, refBits, frames))
        {
            index = replacePage(pageRef, secChanceTable, refBits, frames, index);
            pageFaults += 1;
            printf("Page fault! Page table ->");
        }
        else
        {
            printf("Hit! Page table ->");
        }
        printTable(secChanceTable, frames);
    }
    printf("\n\nTotal Second Chance Faults:\t%d\n", pageFaults);
    return pageFaults;
}