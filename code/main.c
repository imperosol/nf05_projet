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
#include "gui_result_presentation.h"


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


int main (int argc, char *argv[])
{
    srand ((int)time (NULL));
    puts ("Welcome in our hospital management program in C for NF05.\nPlease write in the shell the informations which you shall be asked for\n\n");

    /*Creation of the list which contains all the patient instances*/
    short numberOfPatients;
    patient* patients = create_patient_list (&numberOfPatients);
    /*Initialisation of all room structures*/
    examRoom registrationRoom;
    examRoom examNRO;
    box boxShortCircuit = create_box (2);
    box boxLongCircuit = create_box (3);
    box boxVeryLongCircuit = create_box (2);
    waitingRoom hospitalExit;//The hospital exit is considered as a waiting room with no following exam
    waitingRoom waitingRoom[5];
    //for the sake of the program, it will be considered that there is a waiting room between the two exam boxes of the long circuit

    for (int i = 0; i < 5; i++)//All the waiting rooms are declared as empty
    {
        declare_waiting_room_as_empty(&waitingRoom[i]);
    }
    declare_waiting_room_as_empty(&hospitalExit);
    qsort(patients,numberOfPatients,sizeof(*patients),sort_by_arrival_hour);//sort patient by arrival hour

    /*set all rooms as disposable from 00h00*/
    set_availability_hour(&(registrationRoom.endOfExamHour), 0,0);
    set_availability_hour(&(examNRO.endOfExamHour),0,0);

    waitingRoom[0].numberOfPatients = numberOfPatients;

    for (int i=0;waitingRoom[0].numberOfPatients>0;i++)//first registration (is considered as an exam)
    {
        exam_of_the_patient (&patients[i],&waitingRoom[0],&waitingRoom[1],&registrationRoom,patients[i].medicalExamDuration[0]);
    }
    for (int i=0;waitingRoom[1].numberOfPatients>0;i++)//NRO exam in which patients are separated between short and long circuit
    {
        if (patients[i].circuit==SHORT)
        {
            exam_of_the_patient (&patients[i], &waitingRoom[1], &waitingRoom[3], &examNRO, patients[i].medicalExamDuration[1]);
            add_patient_in_waiting_room (i, &waitingRoom[3]);
        }
        else
        {
            exam_of_the_patient (&patients[i], &waitingRoom[1], &waitingRoom[2], &examNRO, patients[i].medicalExamDuration[1]);
            add_patient_in_waiting_room (i, &waitingRoom[2]);
        }
    }

    for (int i=0;waitingRoom[3].numberOfPatients>0;i++)//medical exam of the short circuit
    {
        /*Only patients in the short circuit are here, so circuit tests are useless*/
        exam_of_the_patient (&(patients[waitingRoom[3].remainingPatients[i]]), &waitingRoom[3], &hospitalExit, &(boxShortCircuit.examRoom[1]), patients[waitingRoom[3].remainingPatients[i]].medicalExamDuration[2]);
        /*sort the exam rooms to make the next room to be available the first element of the list*/
        qsort (boxShortCircuit.examRoom, 3, sizeof(*boxShortCircuit.examRoom), sort_by_disponibility_hour);
    }
    /*freeing of memory space for the patient list in the waiting room*/
    free(waitingRoom[3].remainingPatients);

    for (int i=0;waitingRoom[2].numberOfPatients>0;i++)//first medical exam of the long circuit
    {
        qsort(boxLongCircuit.examRoom, 3, sizeof(*boxLongCircuit.examRoom), sort_by_disponibility_hour);
        if (patients[waitingRoom[2].remainingPatients[i]].circuit==LONG)
        {
            exam_of_the_patient(&patients[waitingRoom[2].remainingPatients[i]], &waitingRoom[2], &hospitalExit, &boxLongCircuit.examRoom[0], patients[waitingRoom[2].remainingPatients[i]].medicalExamDuration[2]);
        }
        else
        {
            exam_of_the_patient (&patients[waitingRoom[2].remainingPatients[i]], &waitingRoom[2], &waitingRoom[4], &boxLongCircuit.examRoom[1], patients[waitingRoom[2].remainingPatients[i]].medicalExamDuration[2]);
            add_patient_in_waiting_room (waitingRoom[2].remainingPatients[i], &waitingRoom[4]);
        }
    }
    /*freeing of memory space for the patient list in the waiting room*/
    free(waitingRoom[2].remainingPatients);

    for (int i=0 ; waitingRoom[4].numberOfPatients > 0 ; i++)//Last exam of the very long circuit
    {
        qsort (boxVeryLongCircuit.examRoom, 3, sizeof(*boxVeryLongCircuit.examRoom), sort_by_disponibility_hour);
        exam_of_the_patient (&patients[waitingRoom[4].remainingPatients[i]], &waitingRoom[4], &hospitalExit, &boxVeryLongCircuit.examRoom[0], patients[waitingRoom[4].remainingPatients[i]].medicalExamDuration[3]);
    }
    /*freeing of memory space for the patient list in the waiting room*/
    free(waitingRoom[4].remainingPatients);

    /***************************************** - GUI FOR RESULT PRESENTATION START - *****************************************/

    if (SDL_Init(SDL_INIT_EVERYTHING) ==-1)/*Initialisation SDL*/{
       printf("window initialization failure due to : %s",SDL_GetError());  exit(EXIT_FAILURE);
    }if (SDL_Init(TTF_Init()) == -1){
        printf("window initialization failure due to : %s",SDL_GetError());  exit(EXIT_FAILURE);
    }

    SDL_Window* pWindow = NULL;
    pWindow = SDL_CreateWindow("Hospital management", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_UNDEFINED, 1200, 900, SDL_WINDOW_FULLSCREEN_DESKTOP|SDL_WINDOW_ALLOW_HIGHDPI|SDL_WINDOW_OPENGL);/*screen Initialisation*/
    if (pWindow == NULL){
        printf("window initialization failure due to : %s",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_SetWindowFullscreen(pWindow, 0);
    SDL_SetWindowSize(pWindow, 1200, 900);

    /*pointers definition*/
    SDL_Renderer* renderer = SDL_CreateRenderer (pWindow,-1,SDL_RENDERER_TARGETTEXTURE);//renderer
    SDL_Surface* icon = NULL;
    SDL_Surface* pageText = NULL;//page text surface
    SDL_Texture* texture = NULL;//The same texture is used and redefined all along the program
    TTF_Font* p_font = TTF_OpenFont("./font/SEGOEUI.ttf",17);
    TTF_Font* button_font = TTF_OpenFont("./font/SEGOEUI.ttf",20);



    /*Variables definition*/
    int height, width;
    unsigned short scroll = 0;
    short patientToPrint = -5;
    mouse mouse;
    SDL_Color text_color = {240,240,240};//Text color : white
    SDL_GetWindowSize(pWindow,&width,&height);
    icon = SDL_LoadBMP("./img/icon.bmp");

    display_icon(pWindow);


    /*background colour definition*/
    SDL_SetRenderDrawColor(renderer,40,40,40,255);
    SDL_RenderClear(renderer);

    display_top_square (renderer, icon, text_color, width, height);
    display_buttons (renderer, numberOfPatients, 1, width, height, text_color, button_font);

    display_patient_panel (renderer, width, height, text_color, button_font);
    display_patient_constant_informations(renderer, width, height, text_color, p_font);

    display_global_statistics (renderer, patients, numberOfPatients, height, width, p_font, text_color);

    SDL_SetRenderDrawColor (renderer,40,40,40,255);

    /****Start of the event loop****/
    SDL_Event event;
    SDL_bool run = SDL_TRUE;
    while (run){
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(pageText);
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
                        if (mouse.y > 85 && mouse.y < 105 && scroll)
                        {
                            scroll = event_click_on_up_arrow (renderer, numberOfPatients, scroll, patientToPrint, width, text_color, button_font);
                        }

                        /*event click on the down arrow*/
                        else if (mouse.y > 875 && mouse.y < 895 && scroll+17 < numberOfPatients)
                        {
                            scroll = event_click_on_down_arrow (renderer, numberOfPatients, scroll, patientToPrint, width, text_color, button_font);
                        }

                        /*event click on a button*/
                        else
                        {
                            for (int i=0;i<numberOfPatients;i++)
                            {
                                if (i == 17)
                                {
                                    break;
                                }
                                if (mouse.y>110+45*i && mouse.y<150+45*i)//Test if the cursor is on a button when the user left clicks
                                {
                                    if (patientToPrint!=i + scroll)//The program does not execute this part if the user push the same button than previously
                                    {
                                        /*clear the button highlighting from the last patient*/
                                        highlight_button (renderer, patientToPrint-scroll, width);
                                        hide_patient_individual_top_panel (renderer, patients[patientToPrint], width, text_color, button_font);
                                        hide_patient_individual_informations (renderer, width, text_color, p_font);

                                        patientToPrint = i + scroll;

                                        /*Highlight the button which have been pushed*/
                                        SDL_SetRenderDrawColor (renderer, 240, 240, 240, 255);
                                        highlight_button (renderer, patientToPrint-scroll, width);
                                        SDL_SetRenderDrawColor (renderer, 40, 40, 40, 255);

                                        display_patient_individual_top_panel (renderer, patients[patientToPrint], width, text_color, button_font);
                                        display_patient_individual_informations (renderer, patients[patientToPrint], width, text_color, p_font);
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
        SDL_RenderPresent(renderer);
    }
    /****End of the event loop****/

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
