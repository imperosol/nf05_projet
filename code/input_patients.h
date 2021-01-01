#include "struct.h"

/********************************************//**
 * \file input_patients.h
 * \brief Header of input_patients.c
 * \author Thomas Girod
 * \version 1.0
 * \date 12.11.2020
 ***********************************************/

#ifndef INPUT_PATIENTS_H
#define INPUT_PATIENTS_H


 /********************************************//**
 * \fn patient* create_patient_list(short* nbrOfPatients)
 * \brief Function that creates the patients list. During its execution, the function calls the input_patient_informations function
 * for each element of the list
 * \return patient* patient_list : list of all the patients that have been input by the user
 ***********************************************/
patient* create_patient_list(short* nbrOfPatients);


 /********************************************//**
 * \fn int circuit_taken_by_patient()
 * \brief Function that randomly determines which circuit the patient will go on
 * \return 0 if short circuit, 1 if long circuit with no complementary exam, 2 if long circuit with complementary exam
 ***********************************************/
int circuit_taken_by_patient();


 /********************************************//**
 * \fn void input_patient_informations(patient* patient, bool isDurationRandom, bool isArrivalHourRandom, bool isNameRandom)
 * \brief Function that asks the user informations about a patient, and modifies the patient instance according to these informations.
 * Those informations can be randomly generated if the boolean arguments of the function are set to true.
 * \param patient* patient : the patient instance that is to be modified
 * \param bool isDurationRandom : indicates if the exams durations must be randomly generated or not.
 * \param bool isArrivalHourRandom : indicates if the arrival hours must be randomly generated or not.
 * \param bool isNameRandom : indicates if the patient name and surname must be randomly generated or not.
 ***********************************************/
void input_patient_informations(patient* patient, bool isDurationRandom, bool isArrivalHourRandom, bool isNameRandom);

/********************************************//**
 * \fn get_random_generation_preference(char sentence[])
 * \brief Function that asks the user if he wants a specific data in the program to be randomly generated
 *
 * \param char sentence[] : a few words that are to be included in the question that will be asked to the user. For example, if sentence[] = "question", the program will ask to user
 * the following question : "Do you want the question to be randomly generated".
 * \return a boolean which value is true if the user answered 'y' (yes) to the question and false else.
 ***********************************************/
bool get_random_generation_preference(char sentence[]);

/********************************************//**
 * \fn generate_duration_with_box_muller_method(short mean, short variance);
 * \brief Function that generates a random number number following the normal law with a given mean and variance. The Box-Muller method is used for this purpose.
 * This randomly generated number is used to determine the duration of the exams. This duration is in minutes.
 * For example, the registration has a mean of 5 and a variance of 1. The NRO exam has a mean of 10 and a variance of 1. The medical exams have a mean of 30 and a variance of 15.
 *
 * \param short mean : the mean of the normal law that number that is to be generated follows
 * \param short variance : the variance of the normal law that number that is to be generated follows
 * \return a short number corresponding to the randomly generated number following the normal law of the given mean and variance
 ***********************************************/
short generate_duration_with_box_muller_method(short mean, short variance);

/********************************************//**
 * \fn generate_time_with_exponential_law(short mean);
 * \brief Function that generates a random number following the exponential law with a given mean. This randomly generated number is used to determine
 * the time between the arrival of two patients (and thus, by knowing the arrival hour of the first patient, to determine the arrival hour of the other patients. This time is in minutes.
 *
 * \param short mean : the mean of the normal law that number that is to be generated follows
 * \return a short number corresponding to the randomly generated number following the exponential law of the given mean.
 ***********************************************/
short generate_time_with_exponential_law(short mean);

/********************************************//**
 * \fn get_random_name_from_file(const char* file_to_open, char* word);
 * \brief Function that takes a randomly chosen word in a file and assigns it the address of the string given to the function.
 * The file that is given to the function must be organized on this way : the first line indicates the number of words, and the next lines contains the words to be taken. There must
 * one word by line.
 * This function is used in the program to generate the names and surnames of the patients.
 *
 * \param const char* file_to_open : the name of the file which contains the words, in which one will be randomly be taken.
 * \param char* word : the address where the randomly taken word will be stored.
 ***********************************************/
void get_random_name_from_file(const char* file_to_open, char* word);

#endif // INPUT_PATIENTS_H
