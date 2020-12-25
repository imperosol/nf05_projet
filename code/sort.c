
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "input_patients.h"
#include "sort.h"


/********************************************//**
 * \file sort.c
 * \brief File that contains all the functions that are used in the program to sort an array
 * \author Thomas Girod
 * \version 1.0
 * \date 12.11.2020
 ***********************************************/
int sort_by_arrival_hour(const void *a,const void *b)//applies to patients
{
    patient* pa = a;
    patient* pb = b;
    if (pa->arrivalHour[HOUR] != pb->arrivalHour[HOUR])
    {
        return pa->arrivalHour[HOUR] - pb->arrivalHour[HOUR];
    }
    else
    {
        return pa->arrivalHour[MINUTE] - pb->arrivalHour[MINUTE];
    }
}
int sort_by_disponibility_hour(const void *a,const void *b)//applies to exam rooms
{
    examRoom* pa = a;
    examRoom* pb = b;
    if (pa->endOfExamHour[HOUR] != pb->endOfExamHour[HOUR])
    {
        return pa->endOfExamHour[HOUR] - pb->endOfExamHour[HOUR];
    }
    else
    {
        return pa->endOfExamHour[MINUTE] - pb->endOfExamHour[MINUTE];
    }
}
