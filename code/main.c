#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "struct.h"
#include "input_patients.h"
#include "sort.h"
#include "room_management.h"
#include "gui.h"


/********************************************//**
 * \file main.c
 * \brief Main file of the project
 * \authors Thomas Girod
 * \authors Kevin Hernandez
 * \version 1.0
 * \date 12.11.2020
 *
 * Main file of the project, containing the main instructions for back-end and all instructions for GUI. Contains no other function
 * or procedure than `int main(int argc, char *argv[])`\n
 * The first part, from line 24 to 115, manages only the operations to achieve the simulation\n
 * The second part, from line 117 to the end, manages the output of the final results in the graphical user interface.
 ***********************************************/


/********************************************//**
 * \fn int main(int argc, char *argv[])
 * \brief main function : calls the functions to initialize the structures of the simulation, then call the functions to simulate the exam
 * and finally manages the GUI to display the results of the simulation.
 *
 * \return EXIT_SUCCESS : no error during the execution
 ***********************************************/


int main(int argc, char *argv[])
{
    srand((int)time (NULL));
    puts("Welcome in our hospital management program in C for NF05.\nPlease write in the shell the informations which you shall be asked for\n\n");

    /*Creation of the list which contains all the patient instances*/
    short numberOfPatients;
    patient* patients = create_patient_list(&numberOfPatients);
    /*Initialisation of all room structures*/
    examRoom registrationRoom;
    examRoom examNRO;
    box boxShortCircuit = create_box(2);
    box boxLongCircuit = create_box(3);
    box boxVeryLongCircuit = create_box(2);
    waitingRoom hospitalExit;//The hospital exit is considered as a waiting room with no following exam
    waitingRoom waitingRoom[5];
    //for the sake of the program, it will be considered that there is a waiting room between the two exam boxes of the long circuit

    for (int i=0;i<5;i++)//All the waiting rooms are declared as empty
    {
        declare_waiting_room_as_empty(&waitingRoom[i]);
    }
    declare_waiting_room_as_empty(&hospitalExit);
    qsort(patients,numberOfPatients,sizeof(*patients),sort_by_arrival_hour);//sort patient by arrival hour

    //set all rooms as disposable from 00h00
    set_disponibility_hour(&(registrationRoom.endOfExamHour), 0,0);
    set_disponibility_hour(&(examNRO.endOfExamHour),0,0);

    waitingRoom[0].numberOfPatients = numberOfPatients;

    for (int i=0;waitingRoom[0].numberOfPatients>0;i++)//first registration (is considered as an exam)
    {
        exam_of_the_patient(&patients[i],&waitingRoom[0],&waitingRoom[1],&registrationRoom,patients[i].medicalExamDuration[0]);
    }
    for (int i=0;waitingRoom[1].numberOfPatients>0;i++)//NRO exam in which patients are separated between short and long circuit
    {
        if (patients[i].circuit==SHORT)
        {
            exam_of_the_patient(&patients[i],&waitingRoom[1],&waitingRoom[3],&examNRO,patients[i].medicalExamDuration[1]);
            add_patient_in_waiting_room(i,&waitingRoom[3]);
        }
        else
        {
            exam_of_the_patient(&patients[i],&waitingRoom[1],&waitingRoom[2],&examNRO,patients[i].medicalExamDuration[1]);
            add_patient_in_waiting_room(i,&waitingRoom[2]);
        }
    }

    for (int i=0;waitingRoom[3].numberOfPatients>0;i++)//medical exam of the short circuit
    {
        /*Only patients in the short circuit are here, so circuit tests are useless*/
        exam_of_the_patient(&(patients[waitingRoom[3].remainingPatients[i]]),&waitingRoom[3],&hospitalExit,&(boxShortCircuit.examRoom[1]),patients[waitingRoom[3].remainingPatients[i]].medicalExamDuration[2]);
        /*sort the exam rooms to make the next room to be available the first element of the list*/
        qsort(boxShortCircuit.examRoom,3,sizeof(*boxShortCircuit.examRoom),sort_by_disponibility_hour);
    }
    /*freeing of memory space for the patient list in the waiting room*/
    free(waitingRoom[3].remainingPatients);

    for (int i=0;waitingRoom[2].numberOfPatients>0;i++)//first medical exam of the long circuit
    {
        qsort(boxLongCircuit.examRoom,3,sizeof(*boxLongCircuit.examRoom),sort_by_arrival_hour);
        if (patients[waitingRoom[2].remainingPatients[i]].circuit==LONG)
        {
            exam_of_the_patient(&patients[waitingRoom[2].remainingPatients[i]],&waitingRoom[2],&hospitalExit,&boxLongCircuit.examRoom[0],patients[waitingRoom[2].remainingPatients[i]].medicalExamDuration[2]);
        }
        else
        {
            exam_of_the_patient(&patients[waitingRoom[2].remainingPatients[i]],&waitingRoom[2],&waitingRoom[4],&boxLongCircuit.examRoom[1],patients[waitingRoom[2].remainingPatients[i]].medicalExamDuration[2]);
            add_patient_in_waiting_room(waitingRoom[2].remainingPatients[i],&waitingRoom[4]);
        }
    }
    /*freeing of memory space for the patient list in the waiting room*/
    free(waitingRoom[2].remainingPatients);

    for (int i=0;waitingRoom[4].numberOfPatients>0;i++)//Last exam of the very long circuit
    {
        qsort(boxVeryLongCircuit.examRoom,3,sizeof(*boxVeryLongCircuit.examRoom),sort_by_disponibility_hour);
        exam_of_the_patient(&patients[waitingRoom[4].remainingPatients[i]],&waitingRoom[4],&hospitalExit,&boxVeryLongCircuit.examRoom[0],patients[waitingRoom[4].remainingPatients[i]].medicalExamDuration[3]);
    }
    /*freeing of memory space for the patient list in the waiting room*/
    free(waitingRoom[4].remainingPatients);

    /***************************************** - GUI START - *****************************************/

    if (SDL_Init(SDL_INIT_EVERYTHING) ==-1)/*Initialisation SDL*/{
        printf("window initialization failure due to : %s",SDL_GetError());  exit(EXIT_FAILURE);
    }if (SDL_Init(TTF_Init()) == -1){
        printf("window initialization failure due to : %s",SDL_GetError());  exit(EXIT_FAILURE);
    }

    SDL_Window* pWindow = NULL;
    pWindow = SDL_CreateWindow("Hospital management", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);/*Initialisation cran*/
    if (pWindow == NULL){
        printf("window initialization failure due to : %s",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /*pointers definition*/
    SDL_Renderer* renderer = SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_ACCELERATED);//renderer
    SDL_Surface* icon = NULL;
    SDL_Surface* pageText = NULL;//page text surface
    SDL_Texture* texture = NULL;//The same texture is used and redefined all along the program
    TTF_Font* p_font = TTF_OpenFont("./font/SEGOEUI.ttf",14);


    /*Variables definition*/
    int height, width;
    int tempHeure,tempMinute;
    unsigned short scroll = 0;
    short patientToPrint = -5;
    char buttonPatient[] = "Patient n°  ";
    char heure[] = "  h  ";
    char nbr[] = "  ";
    mouse mouse;
    SDL_Color text_color = {240,240,240};//Text color : white
    SDL_GetWindowSize(pWindow,&width,&height);
    icon = SDL_LoadBMP("./img/icon.bmp");
    SDL_Rect r;

    display_icon(pWindow);

    /*background colour definition*/
    SDL_SetRenderDrawColor(renderer,40,40,40,255);
    SDL_RenderClear(renderer);

    display_top_square(renderer, icon, text_color, width, height);

    /*Button display*/
    SDL_RenderDrawLine(renderer,width/4,55,width/4,height-5);
    r.x = 10; r.y = 80;
    r.h = 30; r.w = width/4 - 20;
    for (int i=0;i<numberOfPatients;i++) //Draw buttons
    {
        SDL_RenderDrawRect(renderer,&r);
        r.y += 35;
        if (i == 13)
        {
            r.h = 20;
            SDL_RenderDrawRect(renderer, &r);
            SDL_RenderDrawLine(renderer,width/8-5, r.y+7, width/8+5, r.y+7);
            SDL_RenderDrawLine(renderer,width/8-5, r.y+7, width/8, r.y+15);
            SDL_RenderDrawLine(renderer,width/8, r.y+15, width/8+5, r.y+7);
            break;
        }
    }
    r.x = 20;r.y = 50;
    for (int i=1; i <= numberOfPatients; i++) //Display buttons content
    {
        r.y += 35;
        buttonPatient[11] = (i%10) + '0';
        buttonPatient[10] = (i/10) + '0';
        pageText = TTF_RenderText_Solid(p_font,buttonPatient,text_color);
        texture = SDL_CreateTextureFromSurface(renderer,pageText);
        SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
        SDL_RenderCopy(renderer,texture,NULL,&r);
        if (i == 14){
            break;
        }
    }

    /*Creation of the display structure for patient file*/
    r.x = 5*(width/16);//Les fractions bizarres, c'est normal, j'ai fait des schemas pour arriver à ça
    r.y = 80;
    r.h = 41; r.w = 7*(width/16);
    SDL_RenderDrawRect(renderer,&r);//surname rectangle
    r.y = 120;
    SDL_RenderDrawRect(renderer,&r);//name rectangle
    r.y = 80; r.x += r.w-1;
    r.h = 81; r.w = 3*(width/16);
    SDL_RenderDrawRect(renderer,&r);//circuit rectangle
    r.x = 5*(width/16); r.y = 160;
    r.h = 41; r.w = 10*(width/16)-1;
    SDL_RenderDrawLine(renderer,5*width/8,215,5*width/8,height);//Line which cuts the patient information page in two parts
    SDL_RenderDrawLine(renderer,5*width/16 + 5*width/24-10,160,5*width/16 + 5*width/24-10,200);
    SDL_RenderDrawRect(renderer,&r);

    /*Display of the permanent content of the patient file*/
    {
    {//top pannel
    pageText = TTF_RenderText_Solid(p_font,"Circuit :",text_color);
    texture = SDL_CreateTextureFromSurface(renderer,pageText);
    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
    r.x = 3*width/4 + 5;
    r.y = 93;
    SDL_RenderCopy(renderer,texture,NULL,&r);

    pageText = TTF_RenderText_Solid(p_font,"Surname :",text_color);
    texture = SDL_CreateTextureFromSurface(renderer,pageText);
    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
    r.x = 5*width/16 + 5;
    SDL_RenderCopy(renderer,texture,NULL,&r);
    pageText = TTF_RenderText_Solid(p_font,"Name :",text_color);
    texture = SDL_CreateTextureFromSurface(renderer,pageText);
    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
    r.y = 133;
    SDL_RenderCopy(renderer,texture,NULL,&r);
    pageText = TTF_RenderText_Solid(p_font,"Nbr of exams :",text_color);
    texture = SDL_CreateTextureFromSurface(renderer,pageText);
    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
    r.y = 173;
    SDL_RenderCopy(renderer,texture,NULL,&r);
    pageText = TTF_RenderText_Solid(p_font,"Mean waiting time :             |exam time :",text_color);
    texture = SDL_CreateTextureFromSurface(renderer,pageText);
    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
    r.x = 5*width/16 + 5*width/24;
    SDL_RenderCopy(renderer,texture,NULL,&r);
    }
    {//Patient registration
    pageText = TTF_RenderText_Solid(p_font,"Arrival hour :",text_color);
    texture = SDL_CreateTextureFromSurface(renderer,pageText);
    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
    r.x = 5*width/16;
    r.y = 218;
    SDL_RenderCopy(renderer,texture,NULL,&r);
    pageText = TTF_RenderText_Solid(p_font,"Registration start :",text_color);
    texture = SDL_CreateTextureFromSurface(renderer,pageText);
    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
    r.y = 238;
    SDL_RenderCopy(renderer,texture,NULL,&r);
    pageText = TTF_RenderText_Solid(p_font,"Registration end :",text_color);
    texture = SDL_CreateTextureFromSurface(renderer,pageText);
    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
    r.y = 258;
    SDL_RenderCopy(renderer,texture,NULL,&r);
    pageText = TTF_RenderText_Solid(p_font,"Registration duration :",text_color);
    texture = SDL_CreateTextureFromSurface(renderer,pageText);
    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
    r.y = 278;
    SDL_RenderCopy(renderer,texture,NULL,&r);}
    {//NRO exam
    pageText = TTF_RenderText_Solid(p_font,"NRO exam",text_color);
    texture = SDL_CreateTextureFromSurface(renderer,pageText);
    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
    r.x = 5*width/8 + 5;
    r.y = 218;
    SDL_RenderDrawLine(renderer,r.x, r.y+r.h, r.x + r.w, r.y+r.h);
    SDL_RenderCopy(renderer,texture,NULL,&r);
    pageText = TTF_RenderText_Solid(p_font,"Exam start :",text_color);
    texture = SDL_CreateTextureFromSurface(renderer,pageText);
    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
    r.y = 238;
    SDL_RenderCopy(renderer,texture,NULL,&r);
    pageText = TTF_RenderText_Solid(p_font,"Exam end :",text_color);
    texture = SDL_CreateTextureFromSurface(renderer,pageText);
    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
    r.y = 258;
    SDL_RenderCopy(renderer,texture,NULL,&r);
    pageText = TTF_RenderText_Solid(p_font,"Exam duration :",text_color);
    texture = SDL_CreateTextureFromSurface(renderer,pageText);
    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
    r.y = 278;
    SDL_RenderCopy(renderer,texture,NULL,&r);}
    {//First and second exam
    pageText = TTF_RenderText_Solid(p_font,"First exam",text_color);
    texture = SDL_CreateTextureFromSurface(renderer,pageText);
    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
    r.x = 5*width/16;
    r.y = 333;
    SDL_RenderDrawLine(renderer, r.x, r.y+r.h, r.x + r.w, r.y+r.h);
    SDL_RenderCopy(renderer,texture,NULL,&r);
    pageText = TTF_RenderText_Solid(p_font,"Second exam",text_color);
    texture = SDL_CreateTextureFromSurface(renderer,pageText);
    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
    r.x = 5*width/8 + 5;
    r.y = 333;
    SDL_RenderDrawLine(renderer, r.x, r.y+r.h, r.x + r.w, r.y+r.h);
    SDL_RenderCopy(renderer,texture,NULL,&r);
    for (int i = 0;i<2;i++)
    {
        pageText = TTF_RenderText_Solid(p_font,"Exam start :",text_color);
        texture = SDL_CreateTextureFromSurface(renderer,pageText);
        SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
        r.x = 5*width/16 + i*5 + i*5*width/16;
        r.y = 353;
        SDL_RenderCopy(renderer,texture,NULL,&r);
        pageText = TTF_RenderText_Solid(p_font,"Exam End :",text_color);
        texture = SDL_CreateTextureFromSurface(renderer,pageText);
        SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
        r.y = 373;
        SDL_RenderCopy(renderer,texture,NULL,&r);
        pageText = TTF_RenderText_Solid(p_font,"Exam duration :",text_color);
        texture = SDL_CreateTextureFromSurface(renderer,pageText);
        SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
        r.y = 393;
        SDL_RenderCopy(renderer,texture,NULL,&r);
    }}
    {//Total
    pageText = TTF_RenderText_Solid(p_font,"Overall results",text_color);
    texture = SDL_CreateTextureFromSurface(renderer,pageText);
    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
    r.x = 5*width/8 + 5;
    r.y = 448;
    SDL_RenderDrawLine(renderer,5*width/8 + 5,r.y+r.h,5*width/8 + 5 + r.w,r.y+r.h);
    SDL_RenderCopy(renderer,texture,NULL,&r);
    pageText = TTF_RenderText_Solid(p_font,"Exam time :",text_color);
    texture = SDL_CreateTextureFromSurface(renderer,pageText);
    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
    r.y = 468;
    SDL_RenderCopy(renderer,texture,NULL,&r);
    pageText = TTF_RenderText_Solid(p_font,"Waiting time :",text_color);
    texture = SDL_CreateTextureFromSurface(renderer,pageText);
    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
    r.y = 488;
    SDL_RenderCopy(renderer,texture,NULL,&r);
    pageText = TTF_RenderText_Solid(p_font,"Exit hour :",text_color);
    texture = SDL_CreateTextureFromSurface(renderer,pageText);
    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
    r.y = 508;
    SDL_RenderCopy(renderer,texture,NULL,&r);
    }
    }

    /*Display of the global time statistics*/
    {SDL_RenderDrawLine(renderer, width/4, height-140, 5*width/8, height-140);
    r.x = width/4;
    r.y = height - 135;
    r.w = 3*width/8 - 5;
    r.h = 146;
    SDL_RenderDrawRect(renderer, &r);
    pageText = TTF_RenderText_Solid(p_font,"Global time statistics", text_color);
    texture = SDL_CreateTextureFromSurface(renderer, pageText);
    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
    r.x = 5*width/16;
    r.y = height-123;
    SDL_RenderCopy(renderer,texture,NULL,&r);
    SDL_RenderDrawLine(renderer, r.x, r.y+r.h, r.x+r.w, r.y+r.h);//Underline the text

    pageText = TTF_RenderText_Solid(p_font, "Mean waiting time :", text_color);
    texture = SDL_CreateTextureFromSurface(renderer, pageText);
    SDL_QueryTexture(texture, NULL, NULL, &r.w, &r.h);
    r.y = height-103;
    SDL_RenderCopy(renderer, texture, NULL, &r);

    pageText = TTF_RenderText_Solid(p_font,"Mean exam time :",text_color);
    texture = SDL_CreateTextureFromSurface(renderer,pageText);
    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
    r.y = height-83;
    SDL_RenderCopy(renderer,texture,NULL,&r);

    pageText = TTF_RenderText_Solid(p_font,"Mean time in hospital :",text_color);
    texture = SDL_CreateTextureFromSurface(renderer,pageText);
    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
    r.y = height-63;
    SDL_RenderCopy(renderer,texture,NULL,&r);

    /*Calculation of the average waiting time*/
    tempMinute = 0;
    for (int i = 0; i < numberOfPatients; i++)
    {
        tempMinute += patients[i].disponibilityHour[MINUTE] - patients[i].arrivalHour[MINUTE];
        tempMinute += (patients[i].disponibilityHour[HOUR] - patients[i].arrivalHour[HOUR]) * 60;
        tempMinute -= patients[i].medicalExamDuration[0] + patients[i].medicalExamDuration[1] + patients[i].medicalExamDuration[2] + (patients[i].medicalExamDuration[3]*(patients[i].circuit==VERY_LONG));
    }
    tempMinute = tempMinute/numberOfPatients;
    tempHeure = tempMinute/60;
    tempMinute = tempMinute%60;
    heure[0] = tempHeure/10 + '0';
    heure[1] = tempHeure%10 + '0';
    heure[3] = tempMinute/10 + '0';
    heure[4] = tempMinute%10 + '0';
    pageText = TTF_RenderText_Solid(p_font, heure, text_color);
    texture = SDL_CreateTextureFromSurface(renderer, pageText);
    SDL_QueryTexture(texture, NULL, NULL, &r.w, &r.h);
    r.x = 5*width/16 + 126;
    r.y = height - 103;
    SDL_RenderCopy(renderer, texture, NULL, &r);

    /*Calculation of the average exam time*/
    tempMinute = 0;
    for (int i = 0; i < numberOfPatients; i++)
    {
        tempMinute += patients[i].medicalExamDuration[0] + patients[i].medicalExamDuration[1] + patients[i].medicalExamDuration[2] + (patients[i].medicalExamDuration[3]*(patients[i].circuit==VERY_LONG));
    }
    tempMinute = tempMinute / numberOfPatients;
    tempHeure = tempMinute/60;
    tempMinute = tempMinute%60;
    heure[0] = tempHeure/10 + '0';
    heure[1] = tempHeure%10 + '0';
    heure[3] = tempMinute/10 + '0';
    heure[4] = tempMinute%10 + '0';
    pageText = TTF_RenderText_Solid(p_font,heure,text_color);
    texture = SDL_CreateTextureFromSurface(renderer,pageText);
    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
    r.x = 5*width/16 + 115;
    r.y = height - 83;
    SDL_RenderCopy(renderer,texture,NULL,&r);

    /*Calculation of the average total time in hospital*/
    tempMinute = 0;
    for (int i = 0; i < numberOfPatients; i++)
    {
        tempMinute += patients[i].disponibilityHour[MINUTE] - patients[i].arrivalHour[MINUTE];
        tempMinute += (patients[i].disponibilityHour[HOUR] - patients[i].arrivalHour[HOUR]) * 60;
    }
    tempMinute = tempMinute/numberOfPatients;
    tempHeure = tempMinute/60;
    tempMinute = tempMinute%60;
    heure[0] = tempHeure/10 + '0';
    heure[1] = tempHeure%10 + '0';
    heure[3] = tempMinute/10 + '0';
    heure[4] = tempMinute%10 + '0';
    pageText = TTF_RenderText_Solid(p_font, heure, text_color);
    texture = SDL_CreateTextureFromSurface(renderer, pageText);
    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
    r.x = 5*width/16 + 147;
    r.y = height - 63;
    SDL_RenderCopy(renderer,texture,NULL,&r);}

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(pageText);
    SDL_SetRenderDrawColor(renderer,40,40,40,255);

    /*Start of the event loop*/
    SDL_Event event;
    SDL_bool run = SDL_TRUE;
    while (run){
        while (SDL_PollEvent(&event)){
            switch (event.type)
            {
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_CLOSE){
                    run = SDL_FALSE;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_GetMouseState(&mouse.x,&mouse.y);
                    if (mouse.x>10 && mouse.x<width/4-20)
                    {
                        /*event click on the up arrow*/
                        if (mouse.y > 55 && mouse.y < 75 && scroll)
                        {
                            if (numberOfPatients - 15 - scroll < 0)//if the down arrow was not displayed previously
                            {
                                r.x = 10;
                                r.y = 570;
                                r.h = 20;
                                r.w = width/4 - 20;
                                SDL_SetRenderDrawColor(renderer,240,240,240,255);
                                SDL_RenderDrawRect(renderer,&r);
                                SDL_RenderDrawLine(renderer,width/8-5, r.y+7, width/8+5, r.y+7);
                                SDL_RenderDrawLine(renderer,width/8-5, r.y+7, width/8, r.y+15);
                                SDL_RenderDrawLine(renderer,width/8, r.y+15, width/8+5, r.y+7);
                                SDL_SetRenderDrawColor(renderer,40,40,40,255);
                            }
                            scroll--;
                            if (!scroll)//if the up arrow has to be hidden
                            {
                                r.y = 55;r.x = 10;
                                r.h = 20;
                                r.w = width/4 - 20;
                                SDL_RenderFillRect(renderer, &r);
                            }
                            r.x = 20;r.y = 50;
                            for (int i = 1; i < 15; i++)
                            {
                                r.y += 35;
                                buttonPatient[11] = ((i+scroll)%10) + '0';
                                buttonPatient[10] = ((i+scroll)/10) + '0';
                                pageText = TTF_RenderText_Solid(p_font,buttonPatient,text_color);
                                texture = SDL_CreateTextureFromSurface(renderer,pageText);
                                SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
                                SDL_RenderFillRect(renderer, &r);
                                SDL_RenderCopy(renderer,texture,NULL,&r);
                            }
                            /*Make the button highlighting move with the scroll*/
                            if (patientToPrint != -5)
                            {
                                SDL_SetRenderDrawColor(renderer,40,40,40,255);
                                r.x = 12;
                                r.y = 47 + 35*(patientToPrint - scroll);
                                if(r.y < 538 && r.y > 35){
                                    r.h = 26;
                                    r.w = width/4 - 24;
                                    SDL_RenderDrawRect(renderer, &r);
                                    SDL_SetRenderDrawColor(renderer,240,240,240,255);
                                }if (r.y < 535 && r.y > 30){
                                    r.y +=35;
                                    SDL_RenderDrawRect(renderer, &r);
                                }
                                SDL_SetRenderDrawColor(renderer,40,40,40,255);
                            }
                        }
                        /*event click on the down arrow*/
                        else if (mouse.y > 570 && mouse.y < 590 && scroll+14 < numberOfPatients)
                        {
                            if (!scroll)//if the up arrow was not displayed previously
                            {
                                r.x = 10;
                                r.y = 55;
                                r.h = 20;
                                r.w = width/4 - 20;
                                SDL_SetRenderDrawColor(renderer,240,240,240,255);
                                SDL_RenderDrawRect(renderer,&r);
                                SDL_RenderDrawLine(renderer,width/8-5, r.y+15, width/8+5, r.y+15);
                                SDL_RenderDrawLine(renderer,width/8-5, r.y+15, width/8, r.y+7);
                                SDL_RenderDrawLine(renderer,width/8, r.y+7, width/8+5, r.y+15);
                                SDL_SetRenderDrawColor(renderer,40,40,40,255);
                            }
                            scroll++;
                            if (numberOfPatients - 15 - scroll < 0)//if the down arrow has to be hidden
                            {
                                r.y = 570;r.x = 10;
                                r.h = 20;
                                r.w = width/4 - 20;
                                SDL_RenderFillRect(renderer, &r);
                            }
                            r.x = 20;r.y = 50;
                            for (int i = 1; i < 15; i++)
                            {
                                r.y += 35;
                                buttonPatient[11] = ((i+scroll)%10) + '0';
                                buttonPatient[10] = ((i+scroll)/10) + '0';
                                pageText = TTF_RenderText_Solid(p_font,buttonPatient,text_color);
                                texture = SDL_CreateTextureFromSurface(renderer,pageText);
                                SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
                                SDL_RenderFillRect(renderer, &r);
                                SDL_RenderCopy(renderer,texture,NULL,&r);
                            }
                            if (patientToPrint != -5)
                            {
                                SDL_SetRenderDrawColor(renderer,40,40,40,255);
                                r.x = 12;
                                r.y = 117 + 35*(patientToPrint - scroll);
                                if(r.y > 81 && r.y < 602){
                                    r.h = 26;
                                    r.w = width/4 - 24;
                                    SDL_RenderDrawRect(renderer, &r);
                                    SDL_SetRenderDrawColor(renderer,240,240,240,255);
                                }if (r.y > 85 && r.y < 600){
                                    r.y -=35;
                                    SDL_RenderDrawRect(renderer, &r);
                                }
                                SDL_SetRenderDrawColor(renderer,40,40,40,255);
                            }
                        }
                        else{
                        for (int i=0;i<numberOfPatients;i++)
                        {
                            if (i == 14){break;}
                            if (mouse.y>80+35*i && mouse.y<105+35*i)//Test if the cursor is on a button when the user left click
                            {
                                if (patientToPrint!=i + scroll)//The program does not execute this part if the user push the same button than previously
                                {
                                    /*clear the button highlighting from the last patient*/
                                    r.x = 12;
                                    r.y = 82 + 35*(patientToPrint - scroll);
                                    r.h = 26;
                                    r.w = width/4 - 24;
                                    SDL_RenderDrawRect(renderer, &r);

                                    patientToPrint = i + scroll;

                                    /*Highlight the button which have been pushed*/
                                    SDL_SetRenderDrawColor(renderer,240,240,240,255);
                                    r.y = 82 + 35*(patientToPrint - scroll);
                                    SDL_RenderDrawRect(renderer, &r);
                                    SDL_SetRenderDrawColor(renderer,40,40,40,255);
                                    {//personnal infos
                                    {pageText = TTF_RenderText_Solid(p_font,patients[patientToPrint].surname,text_color);//surname
                                    texture = SDL_CreateTextureFromSurface(renderer,pageText);
                                    SDL_QueryTexture(texture,NULL,NULL,NULL,&r.h);
                                    r.x = 5*width/16 + 68;
                                    r.y = 93;
                                    r.w = 280;
                                    SDL_RenderFillRect(renderer,&r);//hide previous content
                                    SDL_QueryTexture(texture,NULL,NULL,&r.w,NULL);
                                    SDL_RenderCopy(renderer,texture,NULL,&r);
                                    }
                                    {pageText = TTF_RenderText_Solid(p_font,patients[patientToPrint].name,text_color);//nom
                                    texture = SDL_CreateTextureFromSurface(renderer,pageText);
                                    SDL_QueryTexture(texture,NULL,NULL,NULL,&r.h);
                                    r.x = 5*width/16 + 51;
                                    r.y = 133;
                                    r.w = 290;
                                    SDL_RenderFillRect(renderer,&r);//Hide previous content
                                    SDL_QueryTexture(texture,NULL,NULL,&r.w,NULL);
                                    SDL_RenderCopy(renderer,texture,NULL,&r);}
                                    {nbr[1] = 3+(patients[patientToPrint].circuit == VERY_LONG) + '0';//number of exams
                                    pageText = TTF_RenderText_Solid(p_font,nbr,text_color);
                                    texture = SDL_CreateTextureFromSurface(renderer,pageText);
                                    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
                                    r.x = 5*width/16 + 105;
                                    r.y = 173;
                                    SDL_RenderFillRect(renderer,&r);//Hide previous content
                                    SDL_RenderCopy(renderer,texture,NULL,&r);}
                                    {if(patients[patientToPrint].circuit == SHORT)//circuit
                                    {
                                        pageText = TTF_RenderText_Solid(p_font,"court",text_color);
                                    }
                                    else
                                    {
                                        pageText = TTF_RenderText_Solid(p_font,"long",text_color);
                                    }
                                    texture = SDL_CreateTextureFromSurface(renderer,pageText);
                                    SDL_QueryTexture(texture,NULL,NULL,NULL,&r.h);
                                    r.x = 3*width/4 + 5;
                                    r.y = 113;
                                    r.w = 70;
                                    SDL_RenderFillRect(renderer,&r);//Hide previous content
                                    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
                                    SDL_RenderCopy(renderer,texture,NULL,&r);}
                                    {//mean exam duration
                                    tempMinute = ((patients[patientToPrint].medicalExamDuration[0]+patients[patientToPrint].medicalExamDuration[1]+patients[patientToPrint].medicalExamDuration[2]+(patients[patientToPrint].medicalExamDuration[3]*(patients[patientToPrint].circuit==VERY_LONG)))/(3+(patients[patientToPrint].circuit==VERY_LONG)));
                                    tempHeure = tempMinute/60;//exam duration
                                    tempMinute = tempMinute%60;
                                    heure[0] = tempHeure/10 + '0';
                                    heure[1] = tempHeure%10 + '0';
                                    heure[3] = tempMinute/10 + '0';
                                    heure[4] = tempMinute%10 + '0';
                                    pageText = TTF_RenderText_Solid(p_font,heure,text_color);
                                    texture = SDL_CreateTextureFromSurface(renderer,pageText);
                                    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
                                    r.x = 5*width/16 + 5*width/24 + 250;
                                    r.y = 173;
                                    SDL_RenderFillRect(renderer,&r);//display previous content
                                    SDL_RenderCopy(renderer,texture,NULL,&r);}
                                    {//mean waiting time
                                    tempMinute = patients[patientToPrint].medicalExamDuration[0] + patients[patientToPrint].medicalExamDuration[1] + patients[patientToPrint].medicalExamDuration[2] + (patients[patientToPrint].medicalExamDuration[3]*(patients[patientToPrint].circuit==VERY_LONG));
                                    tempHeure = patients[patientToPrint].disponibilityHour[HOUR] - patients[patientToPrint].arrivalHour[HOUR] - tempMinute/60;
                                    tempMinute = patients[patientToPrint].disponibilityHour[MINUTE] - patients[patientToPrint].arrivalHour[MINUTE] - tempMinute%60;
                                    tempMinute = (tempMinute + (60*tempHeure)) / (3+(patients[patientToPrint].circuit == VERY_LONG));
                                    tempHeure = tempMinute/60;
                                    tempMinute = tempMinute%60;
                                    heure[0] = tempHeure/10 + '0';
                                    heure[1] = tempHeure%10 + '0';
                                    heure[3] = tempMinute/10 + '0';
                                    heure[4] = tempMinute%10 + '0';
                                    pageText = TTF_RenderText_Solid(p_font,heure,text_color);
                                    texture = SDL_CreateTextureFromSurface(renderer,pageText);
                                    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
                                    r.x = 5*width/16 + 5*width/24 + 127;
                                    r.y = 173;
                                    SDL_RenderFillRect(renderer,&r);//Hide previous content
                                    SDL_RenderCopy(renderer,texture,NULL,&r);}
                                    }
                                    {//Arrival hour
                                    heure[0] = (patients[patientToPrint].arrivalHour[HOUR])/10 + '0';
                                    heure[1] = (patients[patientToPrint].arrivalHour[HOUR])%10 + '0';
                                    heure[3] = (patients[patientToPrint].arrivalHour[MINUTE])/10 + '0';
                                    heure[4] = (patients[patientToPrint].arrivalHour[MINUTE])%10 + '0';
                                    pageText = TTF_RenderText_Solid(p_font,heure,text_color);
                                    texture = SDL_CreateTextureFromSurface(renderer,pageText);
                                    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
                                    r.x = 5*width/16 + 82;
                                    r.y = 218;
                                    SDL_RenderFillRect(renderer,&r);//Hide previous content
                                    SDL_RenderCopy(renderer,texture,NULL,&r);}
                                    {heure[0] = (patients[patientToPrint].examStart[0].hour[HOUR])/10 + '0';//exam start
                                    heure[1] = (patients[patientToPrint].examStart[0].hour[HOUR])%10 + '0';
                                    heure[3] = (patients[patientToPrint].examStart[0].hour[MINUTE])/10 + '0';
                                    heure[4] = (patients[patientToPrint].examStart[0].hour[MINUTE])%10 + '0';
                                    pageText = TTF_RenderText_Solid(p_font,heure,text_color);
                                    texture = SDL_CreateTextureFromSurface(renderer,pageText);
                                    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
                                    r.x = 5*width/16 + 115;
                                    r.y = 238;
                                    SDL_RenderFillRect(renderer,&r);//Hide previous content
                                    SDL_RenderCopy(renderer,texture,NULL,&r);}
                                    {heure[0] = (patients[patientToPrint].examEnd[0].hour[HOUR])/10 + '0';//exam end
                                    heure[1] = (patients[patientToPrint].examEnd[0].hour[HOUR])%10 + '0';
                                    heure[3] = (patients[patientToPrint].examEnd[0].hour[MINUTE])/10 + '0';
                                    heure[4] = (patients[patientToPrint].examEnd[0].hour[MINUTE])%10 + '0';
                                    pageText = TTF_RenderText_Solid(p_font,heure,text_color);
                                    texture = SDL_CreateTextureFromSurface(renderer,pageText);
                                    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
                                    r.x = 5*width/16 + 115;
                                    r.y = 258;
                                    SDL_RenderFillRect(renderer,&r);//hide previous content
                                    SDL_RenderCopy(renderer,texture,NULL,&r);}
                                    {heure[0] = ((patients[patientToPrint].medicalExamDuration[0])/60)/10 + '0';//exam duration
                                    heure[1] = ((patients[patientToPrint].medicalExamDuration[0])/60)%10 + '0';
                                    heure[3] = ((patients[patientToPrint].medicalExamDuration[0])%60)/10 + '0';
                                    heure[4] = ((patients[patientToPrint].medicalExamDuration[0])%60)%10 + '0';
                                    pageText = TTF_RenderText_Solid(p_font,heure,text_color);
                                    texture = SDL_CreateTextureFromSurface(renderer,pageText);
                                    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
                                    r.x = 5*width/16 + 138;
                                    r.y = 278;
                                    SDL_RenderFillRect(renderer,&r);//hide previous content
                                    SDL_RenderCopy(renderer,texture,NULL,&r);}
                                    {//NRO
                                    {heure[0] = (patients[patientToPrint].examStart[1].hour[HOUR])/10 + '0';//début exam
                                    heure[1] = (patients[patientToPrint].examStart[1].hour[HOUR])%10 + '0';
                                    heure[3] = (patients[patientToPrint].examStart[1].hour[MINUTE])/10 + '0';
                                    heure[4] = (patients[patientToPrint].examStart[1].hour[MINUTE])%10 + '0';
                                    pageText = TTF_RenderText_Solid(p_font,heure,text_color);
                                    texture = SDL_CreateTextureFromSurface(renderer,pageText);
                                    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
                                    r.x = 5*width/8 + 78;
                                    r.y = 238;
                                    r.w += 20;
                                    SDL_SetRenderDrawColor(renderer,40,40,40,255);
                                    SDL_RenderFillRect(renderer,&r);r.w -= 20;//hide previous content
                                    SDL_RenderCopy(renderer,texture,NULL,&r);}
                                    {heure[0] = (patients[patientToPrint].examEnd[1].hour[HOUR])/10 + '0';//fin exam
                                    heure[1] = (patients[patientToPrint].examEnd[1].hour[HOUR])%10 + '0';
                                    heure[3] = (patients[patientToPrint].examEnd[1].hour[MINUTE])/10 + '0';
                                    heure[4] = (patients[patientToPrint].examEnd[1].hour[MINUTE])%10 + '0';
                                    pageText = TTF_RenderText_Solid(p_font,heure,text_color);
                                    texture = SDL_CreateTextureFromSurface(renderer,pageText);
                                    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
                                    r.x = 5*width/8 + 73;
                                    r.y = 258;
                                    r.w += 20;
                                    SDL_SetRenderDrawColor(renderer,40,40,40,255);
                                    SDL_RenderFillRect(renderer,&r);r.w -= 20;//hide previous content
                                    SDL_RenderCopy(renderer,texture,NULL,&r);}
                                    {heure[0] = ((patients[patientToPrint].medicalExamDuration[1])/60)/10 + '0';//tps exam
                                    heure[1] = ((patients[patientToPrint].medicalExamDuration[1])/60)%10 + '0';
                                    heure[3] = ((patients[patientToPrint].medicalExamDuration[1])%60)/10 + '0';
                                    heure[4] = ((patients[patientToPrint].medicalExamDuration[1])%60)%10 + '0';
                                    pageText = TTF_RenderText_Solid(p_font,heure,text_color);
                                    texture = SDL_CreateTextureFromSurface(renderer,pageText);
                                    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
                                    r.x = 5*width/8 + 103;
                                    r.y = 278;
                                    r.w += 20;
                                    SDL_SetRenderDrawColor(renderer,40,40,40,255);
                                    SDL_RenderFillRect(renderer,&r);r.w -= 20;//hide previous content
                                    SDL_RenderCopy(renderer,texture,NULL,&r);
                                    }}
                                    {//Second exam
                                    {tempHeure = patients[patientToPrint].examEnd[3].hour[HOUR]-((patients[patientToPrint].medicalExamDuration[3])/60);//début examen
                                    tempMinute = tempHeure*60 + patients[patientToPrint].examEnd[3].hour[MINUTE]-((patients[patientToPrint].medicalExamDuration[3])%60);
                                    tempHeure = tempMinute/60;
                                    tempMinute = tempMinute%60;
                                    heure[0] = tempHeure/10 + '0';
                                    heure[1] = tempHeure%10 + '0';
                                    heure[3] = tempMinute/10 + '0';
                                    heure[4] = tempMinute%10 + '0';
                                    pageText = TTF_RenderText_Solid(p_font,heure,text_color);
                                    texture = SDL_CreateTextureFromSurface(renderer,pageText);
                                    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
                                    r.x = 5*width/8 + 78;
                                    r.y = 353;
                                    r.w += 20;
                                    SDL_SetRenderDrawColor(renderer,40,40,40,255);
                                    SDL_RenderFillRect(renderer,&r);r.w -= 20;//hide previous content
                                    if (patients[patientToPrint].circuit==VERY_LONG)
                                        {SDL_RenderCopy(renderer,texture,NULL,&r);}}
                                    {heure[0] = (patients[patientToPrint].disponibilityHour[HOUR])/10 + '0';//exam end
                                    heure[1] = (patients[patientToPrint].disponibilityHour[HOUR])%10 + '0';
                                    heure[3] = (patients[patientToPrint].disponibilityHour[MINUTE])/10 + '0';
                                    heure[4] = (patients[patientToPrint].disponibilityHour[MINUTE])%10 + '0';
                                    pageText = TTF_RenderText_Solid(p_font,heure,text_color);
                                    texture = SDL_CreateTextureFromSurface(renderer,pageText);
                                    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
                                    r.x = 5*width/8 + 73;
                                    r.y = 373;
                                    r.w += 20;
                                    SDL_SetRenderDrawColor(renderer,40,40,40,255);
                                    SDL_RenderFillRect(renderer,&r);r.w -= 20;//Hide previous content
                                    if (patients[patientToPrint].circuit==VERY_LONG)
                                        {SDL_RenderCopy(renderer,texture,NULL,&r);}}
                                    {heure[0] = ((patients[patientToPrint].medicalExamDuration[3])/60)/10 + '0';//tps exam
                                    heure[1] = ((patients[patientToPrint].medicalExamDuration[3])/60)%10 + '0';
                                    heure[3] = ((patients[patientToPrint].medicalExamDuration[3])%60)/10 + '0';
                                    heure[4] = ((patients[patientToPrint].medicalExamDuration[3])%60)%10 + '0';
                                    pageText = TTF_RenderText_Solid(p_font,heure,text_color);
                                    texture = SDL_CreateTextureFromSurface(renderer,pageText);
                                    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
                                    r.x = 5*width/8 + 103;
                                    r.y = 393;
                                    r.w += 20;
                                    SDL_SetRenderDrawColor(renderer,40,40,40,255);
                                    SDL_RenderFillRect(renderer,&r);r.w -= 20;//Hide previous content
                                    if (patients[patientToPrint].circuit==VERY_LONG)
                                        {SDL_RenderCopy(renderer,texture,NULL,&r);}
                                    }
                                    }
                                    //Display first exam
                                    {heure[0] = (patients[patientToPrint].examStart[2].hour[HOUR])/10 + '0';//début exam
                                    heure[1] = (patients[patientToPrint].examStart[2].hour[HOUR])%10 + '0';
                                    heure[3] = (patients[patientToPrint].examStart[2].hour[MINUTE])/10 + '0';
                                    heure[4] = (patients[patientToPrint].examStart[2].hour[MINUTE])%10 + '0';
                                    pageText = TTF_RenderText_Solid(p_font,heure,text_color);
                                    texture = SDL_CreateTextureFromSurface(renderer,pageText);
                                    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
                                    r.x = 5*width/16 + 76;
                                    r.y = 353;
                                    SDL_RenderFillRect(renderer,&r);//Hide previous content
                                    SDL_RenderCopy(renderer,texture,NULL,&r);}
                                    {heure[0] = (patients[patientToPrint].examEnd[2].hour[HOUR])/10 + '0';//fin exam
                                    heure[1] = (patients[patientToPrint].examEnd[2].hour[HOUR])%10 + '0';
                                    heure[3] = (patients[patientToPrint].examEnd[2].hour[MINUTE])/10 + '0';
                                    heure[4] = (patients[patientToPrint].examEnd[2].hour[MINUTE])%10 + '0';
                                    pageText = TTF_RenderText_Solid(p_font,heure,text_color);
                                    texture = SDL_CreateTextureFromSurface(renderer,pageText);
                                    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
                                    r.x = 5*width/16 + 71;
                                    r.y = 373;
                                    SDL_RenderFillRect(renderer,&r);//Hide previous content
                                    SDL_RenderCopy(renderer,texture,NULL,&r);}
                                    {heure[0] = ((patients[patientToPrint].medicalExamDuration[2])/60)/10 + '0';//tps exam
                                    heure[1] = ((patients[patientToPrint].medicalExamDuration[2])/60)%10 + '0';
                                    heure[3] = ((patients[patientToPrint].medicalExamDuration[2])%60)/10 + '0';
                                    heure[4] = ((patients[patientToPrint].medicalExamDuration[2])%60)%10 + '0';
                                    pageText = TTF_RenderText_Solid(p_font,heure,text_color);
                                    texture = SDL_CreateTextureFromSurface(renderer,pageText);
                                    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
                                    r.x = 5*width/16 + 101;
                                    r.y = 393;
                                    SDL_RenderFillRect(renderer,&r);//Hide previous content
                                    SDL_RenderCopy(renderer,texture,NULL,&r);}
                                    {//Overall results display
                                    {tempHeure = ((patients[patientToPrint].medicalExamDuration[0]+patients[patientToPrint].medicalExamDuration[1]+patients[patientToPrint].medicalExamDuration[2]+(patients[patientToPrint].medicalExamDuration[3]*(patients[patientToPrint].circuit==VERY_LONG)))/60);//tps examen
                                    tempMinute = ((patients[patientToPrint].medicalExamDuration[0]+patients[patientToPrint].medicalExamDuration[1]+patients[patientToPrint].medicalExamDuration[2]+(patients[patientToPrint].medicalExamDuration[3]*(patients[patientToPrint].circuit==VERY_LONG)))%60);
                                    heure[0] = tempHeure/10 + '0';//exam duration
                                    heure[1] = tempHeure%10 + '0';
                                    heure[3] = tempMinute/10 + '0';
                                    heure[4] = tempMinute%10 + '0';
                                    pageText = TTF_RenderText_Solid(p_font,heure,text_color);
                                    texture = SDL_CreateTextureFromSurface(renderer,pageText);
                                    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
                                    r.x = 5*width/8 + 78;
                                    r.y = 468;
                                    SDL_RenderFillRect(renderer,&r);//Hide previous content
                                    SDL_RenderCopy(renderer,texture,NULL,&r);}
                                    {tempHeure = patients[patientToPrint].disponibilityHour[HOUR]-patients[patientToPrint].arrivalHour[HOUR]-tempHeure;//tps d'attente
                                    tempMinute = patients[patientToPrint].disponibilityHour[MINUTE]-patients[patientToPrint].arrivalHour[MINUTE]-tempMinute + tempHeure*60;
                                    /*The total examination time in hours and minutes has already been retrieved in the previous step, so it can be reused here to simplify the calculations.*/
                                    tempHeure = tempMinute/60;
                                    tempMinute = tempMinute%60;
                                    heure[0] = tempHeure/10 + '0';//tps d'attente
                                    heure[1] = tempHeure%10 + '0';
                                    heure[3] = tempMinute/10 + '0';
                                    heure[4] = tempMinute%10 + '0';
                                    pageText = TTF_RenderText_Solid(p_font,heure,text_color);
                                    texture = SDL_CreateTextureFromSurface(renderer,pageText);
                                    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
                                    r.x = 5*width/8 + 93;
                                    r.y = 488;
                                    SDL_RenderFillRect(renderer,&r);//Hide previous content
                                    SDL_RenderCopy(renderer,texture,NULL,&r);}
                                    {heure[0] = (patients[patientToPrint].disponibilityHour[HOUR])/10 + '0';//heure de sortie
                                    heure[1] = (patients[patientToPrint].disponibilityHour[HOUR])%10 + '0';
                                    heure[3] = (patients[patientToPrint].disponibilityHour[MINUTE])/10 + '0';
                                    heure[4] = (patients[patientToPrint].disponibilityHour[MINUTE])%10 + '0';
                                    pageText = TTF_RenderText_Solid(p_font,heure,text_color);
                                    texture = SDL_CreateTextureFromSurface(renderer,pageText);
                                    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
                                    r.x = 5*width/8 + 69;
                                    r.y = 508;
                                    SDL_RenderFillRect(renderer,&r);//Hide previous content
                                    SDL_RenderCopy(renderer,texture,NULL,&r);}
                                    }
                                }
                                break;
                            }
                        }
                        }
                    }
                }
                break;

            default:
                break;
            }
        }
        //SDL_RenderCopy(renderer,texture,NULL,&r);
        SDL_RenderPresent(renderer);
    }
    //End of the event loop

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(pWindow);

    TTF_Quit();
    SDL_Quit();

    free(patients);
    free(boxLongCircuit.examRoom);
    free(boxShortCircuit.examRoom);
    free(boxVeryLongCircuit.examRoom);
    return (EXIT_SUCCESS);
}
