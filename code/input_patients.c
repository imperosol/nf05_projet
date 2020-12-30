
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "input_patients.h"

/********************************************//**
 * \file input_patients.c
 * \brief File that contains all the functions to modify a patient instance without modification a waitingRoom or examRoom instance.
 * \author Thomas Girod
 * \version 1.0
 * \date 12.11.2020
 ***********************************************/


patient* create_patient_list(short* nbrOfPatients)
{
    bool isArrivalHourRandomlyGenerated, isDurationRandomlyGenerated, isNameRandomlyGenerated;
    isNameRandomlyGenerated = get_random_generation_preference("patient name");
    isDurationRandomlyGenerated = get_random_generation_preference("exam duration");
    isArrivalHourRandomlyGenerated = get_random_generation_preference("arrival hour");
    printf("Number of patients : ");
    scanf("%d",nbrOfPatients);
    patient* patient_list = NULL;
    patient_list = (patient *)malloc((*nbrOfPatients) * sizeof(patient));
    if (patient_list == NULL)
    {
        exit(0);
    }
    for (int i=0;i<(*nbrOfPatients);i++)//Patients registration
    {
        input_patient_informations(&patient_list[i],isDurationRandomlyGenerated,isArrivalHourRandomlyGenerated,isNameRandomlyGenerated);
    }
    return patient_list;
}

int circuit_taken_by_patient()
{
    int randomCircuit;
    /*40% chances to go in short circuit,
    60% * 20% = 12% chances to go in long circuit
    60% * 80% = 48% chances to go in very long circuit*/
    randomCircuit = rand()%100;
    if (randomCircuit<40)
    {
        return SHORT;
    }
    else if (randomCircuit<52)
    {
        return LONG;
    }
    else
    {
        return VERY_LONG;
    }
    return 0;
}

void input_patient_informations(patient *patient, bool isDurationRandom, bool isArrivalHourRandom, bool isNameRandom)
{
    static int timeAfterBeginning = 0;
    patient->circuit = circuit_taken_by_patient();
    if (!isNameRandom || !isDurationRandom || !isArrivalHourRandom)
    {
        puts("\nEnter new patient :\n");
    }
    if (isNameRandom)
    {
        get_random_name_from_file("name_bank/surname.txt",patient->surname);
        get_random_name_from_file("name_bank/name.txt",patient->name);
    }
    else
    {
        printf("Surname : ");
        scanf("%s",patient->surname);
        printf("Name : ");
        scanf("%s",patient->name);
    }
    if (isArrivalHourRandom)
    {
        timeAfterBeginning += generate_time_with_exponential_law(5);
        patient->arrivalHour[HOUR] = 8 + timeAfterBeginning/60;
        patient->arrivalHour[MINUTE] = timeAfterBeginning%60;
    }
    else
    {
        printf("Arrival hour (format : hh mm) : ");
        scanf("%d",&(patient->arrivalHour[HOUR]));
        scanf("%d",&(patient->arrivalHour[MINUTE]));
    }

    patient->availabilityHour[HOUR] = patient->arrivalHour[HOUR];
    patient->availabilityHour[MINUTE] = patient->arrivalHour[MINUTE];

    if (isDurationRandom)
    {
        patient->medicalExamDuration[0] = generate_duration_with_box_muller_method(5,1);
        if (patient->medicalExamDuration[0] < 1){
            patient->medicalExamDuration[0] = 1;
        }
        patient->medicalExamDuration[1] = generate_duration_with_box_muller_method(10,1);
        patient->medicalExamDuration[2] = generate_duration_with_box_muller_method(30,5);
        if (patient->circuit == VERY_LONG)
        {
            patient->medicalExamDuration[3] = generate_duration_with_box_muller_method(30,5);
        }
    }
    else
    {
        printf("registration duration (in minutes) : ");
        scanf("%d",&(patient->medicalExamDuration[0]));
        printf("Duration of the exam by the nurse reception organizer (in minutes) : ");
        scanf("%d",&(patient->medicalExamDuration[1]));
        if (patient->circuit == SHORT)
        {
            printf("Short circuit.\nDuration of the medical exam : ");
            scanf("%d",&(patient->medicalExamDuration[2]));
        }
        if (patient->circuit == LONG)
        {
            printf("Long circuit.\nDuration of the first medical exam : ");
            scanf("%d",&(patient->medicalExamDuration[2]));
            puts("This patient does not need any further exam");
        }
        if (patient->circuit == VERY_LONG)
        {
            printf("Long circuit.\nDuration of the first medical exam : ");
            scanf("%d",&(patient->medicalExamDuration[2]));
            puts("This patient does need one more exam");
            printf("Duration of the second medical exam : ");
            scanf("%d",&(patient->medicalExamDuration[3]));
        }
    }
    patient->examNumber = 0;//The patient has not yet passed any exam
}

bool get_random_generation_preference(char sentence[])
{
    char choice;
    do
    {
        fflush(stdin);
        printf("Do you want the %s to be randomly generated ? (y/n) : ",sentence);
        scanf("%c",&choice);
    }while (choice != 'y' && choice != 'n');
    return (choice == 'y');
}

void get_random_name_from_file(const char* file_to_open, char* word)
{
    /*For this function, .txt files are used. Those files contains n names and n+1 lines. In the first line is indicated the number
    of names the file contains. All the other lines contain a name.
    This function read the first line to know the number of names in the file, generates a random number between 0 and the number of lines
    then takes the name which is in the line corresponding to this number.*/
    int nbrOfWords, wordToTake;
    FILE* file = NULL;
    file = fopen(file_to_open,"r");
    fscanf(file,"%d",&nbrOfWords);
    /*generate a random number number corresponding to the line of the word to take*/
    wordToTake = rand()%nbrOfWords + 1;
    fgets(word,20,file);
    /*Go down in the file until the right line is reached*/
    for (int i=0; i<wordToTake; i++)
    {
        fgets(word,20,file);
    }
    /*Shift the end of the word by one character to the left to delete the character '\n'*/
    word[strlen(word) - 1] = '\0';
    fclose(file);
}

short generate_duration_with_box_muller_method(short mean, short variance)
{
    float a = (float)rand()/(float)(RAND_MAX);
    float b = (float)rand()/(float)(RAND_MAX);
    float randomNbr = sqrt(-2*log(a)) * cos(2*M_PI*b);
    return mean + floor(variance*randomNbr);
}

short generate_time_with_exponential_law(short mean)
{
    float t = (float)rand()/(float)(RAND_MAX);
    return ceil(-mean * log(1-t));
}

