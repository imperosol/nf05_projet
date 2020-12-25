/********************************************//**
 * \file struct.h
 * \brief file containing all structures of the program
 * \author Thomas Girod
 * \date 12.11.2020
 * \version 1.0
 *
 * This file contains all data from structures and enumerations. The major structures are <b>patient</b> (which describes a patient), <b>waitingRoom</b> (which describes a waiting room)
 * and <b>examRoom</b> (which describes a waiting room).
 * <b>mouse</b> describes the cursor position by x and y on the GUI screen.
 * In all structures, time is described by arrays of two elements : the first for hours, the second for minutes. Simple durations (like exam duration) are just described
 * in minutes, even in case they last more than 60 minutes.
 ***********************************************/

#ifndef STRUCTURE_H
#define STRUCTURE_H

/********************************************//**
 * \struct hourStartEnd
 * \brief substructure which is used by other structures to store time with format hh/mm
 ***********************************************/
typedef struct
{
    int hour[2];/**< Two elements integer array ; hour[0] represents hours and hour[1] represents minutes */
}hourStartEnd;

/********************************************//**
 * \struct patient
 * \brief structure that contains all the necessary infos about a patient
 * the <b>patient</b> structure stores all informations about a patient : name and surnam, arrival hour, starting and ending hour for each one of his exams
 * duration of each exam, circuit taken (short, long without complementary exam or long with complementary exam). The variable disponibilityHour describes the moment when a patient
 * can pass the next exam of the exam room is free and is updated after every exam. examNumber is incremented after every exam.
 ***********************************************/
typedef struct
{
    char name[20];/**< The patient's name */
    char surname[20];/**< The patient's surname */
    int arrivalHour[2];/**< Patient arrival time */
    int disponibilityHour[2];/**< time the patient is available for the next exam */
    int medicalExamDuration[4];/**< exam duration array */
    short circuit;/**< circuit taken by the patient */
    hourStartEnd examStart[4];/**< Starting time of each exam */
    hourStartEnd examEnd[4];/**< Ending time of each exam */
    short examNumber;/**< the nth exam */
}patient;

/********************************************//**
 * \struct examRoom
 * \brief structure that describes an exam room
 * the <b>examRoom</b> structure stores a single int array which describes when will the current exam end. The value of the table is updated each time a new exam begins and
 * depends on the duration of the exam (information stored in the <b>patient</b> structure. The program set endOfExamHour as {0,0} in order to make the room available whenever the
 * first patient arrives, with some exceptions for groups of two exam rooms.
 ***********************************************/
typedef struct
{
    int endOfExamHour[2];
}examRoom;

/********************************************//**
 * \struct box
 * \brief structure that describes a group of exam room.
 * The <b>box</b> structure contains an array of three structures <b>examRoom</b>. When a patient arrives, this array is sorted by end of exam hour (so the first room to be
 * available is the first element. When only two rooms are actually usable, the third element of the array is set with an arbitrary high hour, so it will be never in first position.
 ***********************************************/
typedef struct
{
    examRoom* examRoom;
}box;

/********************************************//**
 * \struct waitingRoom
 * \brief structure that describes a waiting room.
 * The <b>waitingRoom</b> structure describes a waitingRoom by the number of patients who are still in and the patient number of each patient.\n
 * Is considered as a waiting room anything before and after a medical exam where the patient does not have to wait. The exit of the service is considered as waiting room
 * with no exam after
 ***********************************************/
typedef struct
{
    int* remainingPatients;/**< Integer array which contains the indexes of the elements of the "patient" array which are in the waiting room */
    int numberOfPatients;/**< The number of patients remaining in the waiting room */
}waitingRoom;

/********************************************//**
 * \struct mouse
 * \brief structure that describes the position of the cursor.
 * The <b>mouse</b> structure describes the position of the cursor in the GUI window by its distance (in pixels) from the up-left corner
 ***********************************************/
typedef struct
{
    int x;/**< Distance of the cursor from the left border (in pixels) */
    int y;/**< Distance of the cursor from the upper border (in pixels) */
}mouse;


/********************************************//**
 * \enum time
 * \brief enumeration for time representation
 * The <b>time</b> enumeration is used to make all references to time clearer. The time in hh/mm format is represented by an integer array of two elements of which the first
 * represents hours and the second represents minutes
 ***********************************************/
enum time
{
    HOUR,MINUTE
};//used to describe time by hours an minutes

/********************************************//**
 * \enum circuit
 * \brief numeration for representation of the circuit taken by a patient
 * The <b>circuit</b> enumeration is used to make all references to the circuit taken by patient clearer. The short circuit is represented by SHORT, the long circuit without
 * complementary exam by LONG and the long circuit with complementary exam by VERY_LONG
 ***********************************************/
enum circuit
{
    SHORT,LONG,VERY_LONG
};//used to describe the circuit taken by a patient
/*Nobody expects the Spanish Inquisition or this commentary.*/
#endif // STRUCTURE_H
