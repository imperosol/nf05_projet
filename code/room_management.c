
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "room_management.h"

/********************************************//**
 * \file room_management.c
 * \brief File that contains all the functions to modify the state of a room instance (waitingRoom or examRoom) and of any patient instance that interact with a room.
 * the functions are used to set the time a room will be available, to set the variables of a waitingRoom instance as those of an empty waiting room
 * \author Thomas Girod
 * \version 1.0
 * \date 12.11.2020
 ***********************************************/


void declare_waiting_room_as_empty(waitingRoom* waitingRoom)
{
    waitingRoom->numberOfPatients = 0;
    waitingRoom->remainingPatients = NULL;
}

void set_availability_hour(int availabilityHour[],int h,int m)
{
    availabilityHour[HOUR] = h;
    availabilityHour[MINUTE] = m;
}

box create_box(int numberOfExamRoom)
{
    box t_box;
    t_box.examRoom = (examRoom*) malloc(numberOfExamRoom * sizeof(examRoom));
    if (t_box.examRoom == NULL)
    {
        exit(0);
    }
    for (int i=0; i<numberOfExamRoom; i++)
    {
        set_availability_hour(t_box.examRoom[i].endOfExamHour, 0, 0);
    }
    return t_box;
}

void exam_of_the_patient (patient* patient, waitingRoom* firstRoom, waitingRoom* secondRoom, examRoom* examRoom,int duration)
{
    /*conditions to test if the next patient will have to wait before enter the room
    If the availability hour the patient is posterior to the freeing hour of the room, the availability hour
    of both the patient and the room are set to the freeing hour of the room plus the exam duration
    else they are set to the availability hour of the patient plus the exam duration.*/
    if ((patient->availabilityHour[HOUR]>examRoom->endOfExamHour[HOUR]) || ((patient->availabilityHour[HOUR]==examRoom->endOfExamHour[HOUR]) && (patient->availabilityHour[MINUTE]>examRoom->endOfExamHour[MINUTE])) )
    {
        patient->examStart[patient->examNumber].hour[HOUR] = patient->availabilityHour[HOUR];
        patient->examStart[patient->examNumber].hour[MINUTE] = patient->availabilityHour[MINUTE];
        patient->availabilityHour[HOUR] = patient->availabilityHour[HOUR] + duration/60;
        patient->availabilityHour[MINUTE] = patient->availabilityHour[MINUTE] + duration%60;
    }
    else
    {
        patient->examStart[patient->examNumber].hour[HOUR] = examRoom->endOfExamHour[HOUR];
        patient->examStart[patient->examNumber].hour[MINUTE] = examRoom->endOfExamHour[MINUTE];
        patient->availabilityHour[HOUR] = examRoom->endOfExamHour[HOUR] + duration/60;
        patient->availabilityHour[MINUTE] = examRoom->endOfExamHour[MINUTE] + duration%60;
    }
    if (patient->availabilityHour[MINUTE]>=60)//Update to the next hour if the number of minutes exceeds 59.
    {
        patient->availabilityHour[HOUR] += (patient->availabilityHour[MINUTE])/60;
        patient->availabilityHour[MINUTE] = (patient->availabilityHour[MINUTE])%60;
    }
    examRoom->endOfExamHour[HOUR] = patient->availabilityHour[HOUR];
    examRoom->endOfExamHour[MINUTE] = patient->availabilityHour[MINUTE];
    patient->examEnd[patient->examNumber].hour[HOUR] = patient->availabilityHour[HOUR];
    patient->examEnd[patient->examNumber].hour[MINUTE] = patient->availabilityHour[MINUTE];
    (firstRoom->numberOfPatients)--;
    (secondRoom->numberOfPatients)++;
    (patient->examNumber)++;
}


void add_patient_in_waiting_room(int patientID, waitingRoom* room)
{
    if (room->remainingPatients == NULL)
    {
        (room->remainingPatients) = malloc(sizeof(int));
    }
    else
    {
        (room->remainingPatients) = realloc(room->remainingPatients, room->numberOfPatients * sizeof(int));
    }
    (room->remainingPatients[room->numberOfPatients - 1]) = patientID;
}
