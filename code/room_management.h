
/********************************************//**
 * \file room_management.h
 * \brief header of room_management.c
 * \author Thomas Girod
 * \version 1.0
 * \date 12.11.2020
 ***********************************************/

#include "struct.h"

#ifndef ROOM_MANAGEMENT_H
#define ROOM_MANAGEMENT_H

 /********************************************//**
 * \fn declare_waiting_room_as_empty(waitingRoom *waitingRoom)
 * \brief Function that sets all the elements of the waitingRoom instance as those of an empty waiting room.
 * \param waitingRoom* waitingRoom : a pointer to the waitingRoom instance that is to be modified
 ***********************************************/
void declare_waiting_room_as_empty(waitingRoom *waitingRoom);

 /********************************************//**
 * \fn set_disponibility_hour(int (*availabilityHour)[],int h,int m)
 * \brief Function that sets the availability hour of a room to a time in hh/mm format
 * \param int (*availabilityHour)[] : a pointer to the element that is to be modified
 * \param int h : hours
 * \param int m : minutes
 ***********************************************/
void set_disponibility_hour(int (*availabilityHour)[],int h,int m);

 /********************************************//**
 * \fn box create_box(int numberOfExamRoom);
 * \brief Function that creates a group of exam rooms. The number of rooms is given as an argument of the function.
 * \param int numberOfExamRoom : the number of room that must be contained in the group of exam rooms.
 * \return box t_box : a box containing the number of rooms given in argument of the function.
 ***********************************************/
box create_box(int numberOfExamRoom);

 /********************************************//**
 * \fn void exam_of_the_patient (patient *patient, waitingRoom *firstRoom, waitingRoom *secondRoom, examRoom *examRoom,int duration)
 * \brief Function that moves a patient from a waiting room to another by passing an exam and modifies his availability hour by setting it to the time he finishes the medical exam
 * \param patient* patient : the pointer to the patient instance that is to be modified
 * \param waitingRoom* firstRoom : the pointer to the waiting room the patient leaves from
 * \param waitingRoom* secondRoom : the pointer to the waiting room the patient arrives to
 * \param examRoom* examRoom : the pointer to the exam room
 * \param int duration : the duration of the exam
 ***********************************************/
void exam_of_the_patient (patient *patient, waitingRoom *firstRoom, waitingRoom *secondRoom, examRoom *examRoom,int duration);

 /********************************************//**
 * \fn void add_patient_in_waiting_room(int patientID, waitingRoom *room)
 * \brief Function that add the index of a patient in the patients[] array in the remainingPatients[] array of a waiting room
 * \param int patientID : the index of the patient in the patients[] array
 * \param waitingRoom *room : the waitingRoom instance containing the remainingPatient[] array to add the patient's index in.
 ***********************************************/
void add_patient_in_waiting_room(int patientID, waitingRoom *room);

#endif // ROOM_MANAGEMENT_H

