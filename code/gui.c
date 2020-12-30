#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include "gui.h"


 void display_top_square(SDL_Renderer* renderer, SDL_Surface* image, SDL_Color text_color, const int width, const int height)
{
    SDL_Surface* title = NULL;//title surface
    TTF_Font* title_font = TTF_OpenFont("./font/SEGOEUI.ttf",50);
    SDL_Texture* texture = NULL;
    SDL_Rect r;

     /*Title diplay*/
    title = TTF_RenderText_Solid(title_font,"Patients infos",text_color);
    texture = SDL_CreateTextureFromSurface(renderer,title);
    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
    r.x=width/2-r.w/2;
    r.y=5;
    SDL_RenderCopy(renderer,texture,NULL,&r);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(title);

    /*Display images on both sides of main title*/
    r.x=width/4-70;r.w=60;r.h=60;r.y = 10;
    texture = SDL_CreateTextureFromSurface(renderer,image);
    SDL_RenderCopy(renderer,texture,NULL,&r);
    r.x += width/2 + 80;
    SDL_RenderCopy(renderer,texture,NULL,&r);

    /*Lines and squares on top of the window*/
    r.x = width/4;r.y = 10;r.w = width/2;r.h = 60;
    SDL_SetRenderDrawColor(renderer,250,250,250,255);
    SDL_RenderDrawLine(renderer,5,80,width-5,80);
    SDL_RenderDrawRect(renderer,&r);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
 }

void display_icon(SDL_Window* window)
{
    /*Icon of the window*/
    SDL_Surface *surface;
    Uint16 pixels[16*16] = {
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
        0x0fff, 0x0fff, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0x0fff, 0x0fff,
        0x0fff, 0x0fff, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0x0fff, 0x0fff,
        0x0fff, 0x0fff, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0x0fff, 0x0fff,
        0x0fff, 0x0fff, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0x0fff, 0x0fff,
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0xcc00, 0xcc00, 0xcc00, 0xcc00, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff
    };
    surface = SDL_CreateRGBSurfaceFrom(pixels,16,16,16,16*2,0x0f00,0x00f0,0x000f,0xf000);

    SDL_SetWindowIcon(window, surface);
    SDL_FreeSurface(surface);
}

void display_buttons(SDL_Renderer* renderer, const unsigned short nbrOfButtons, const unsigned short firstButton, const int win_width, const int win_height, SDL_Color text_color, TTF_Font* button_font)
{
    SDL_Rect r;

    SDL_RenderDrawLine(renderer,win_width/4,90,win_width/4,win_height-5);
    r.x = 10; r.y = 110;
    r.h = 40; r.w = win_width/4 - 20;
    for (int i = 1;i < nbrOfButtons+1;i++) //Draw buttons
    {
        SDL_RenderDrawRect(renderer,&r);
        r.y += 45;
        if (i == 17)
        {
            display_down_arrow(renderer, win_width);
            break;
        }
    }

    display_buttons_content(renderer, nbrOfButtons, firstButton, text_color, button_font);
}

void display_buttons_content(SDL_Renderer* renderer, const unsigned short nbrOfButtons, const unsigned short firstButton, SDL_Color text_color, TTF_Font* button_font)
{
    char buttonPatient[] = "Patient n°  ";
    SDL_Rect r;
    r.x = 30;r.y = 116;
    for (int i = firstButton; i < nbrOfButtons+1; i++) //Display buttons content
    {
        buttonPatient[11] = (i%10) + '0';
        buttonPatient[10] = (i/10) + '0';
        display_text(renderer, buttonPatient, button_font, text_color, r.x, r.y);
        r.y += 45;
        if (i == 16+firstButton){
            break;
        }
    }
}

void hide_buttons_content(SDL_Renderer* renderer, const unsigned short nbrOfButtons, const unsigned short firstButton, SDL_Color text_color, TTF_Font* button_font)
{
    SDL_Rect r;
    r.x = 30;r.y = 116;
    SDL_Surface* surface = TTF_RenderText_Solid(button_font, "Patient n°88", text_color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(texture, NULL, NULL, &r.w, &r.h);
    for (int i = firstButton; i < nbrOfButtons+1; i++)
    {
        SDL_RenderFillRect(renderer, &r);
        if (i == 16+firstButton){
            break;
        }
        r.y += 45;
    }
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void display_down_arrow(SDL_Renderer* renderer, const int win_width)
{
    SDL_Rect r;
    r.h = 20;
    r.y = 875;
    r.x = 10;
    r.w = win_width/4 - 20;
    SDL_RenderDrawRect(renderer, &r);
    SDL_RenderDrawLine(renderer,win_width/8-5, r.y+7, win_width/8+5, r.y+7);
    SDL_RenderDrawLine(renderer,win_width/8-5, r.y+7, win_width/8, r.y+15);
    SDL_RenderDrawLine(renderer,win_width/8, r.y+15, win_width/8+5, r.y+7);
}

void display_up_arrow(SDL_Renderer* renderer, const int win_width)
{
    SDL_Rect r;
    r.h = 20;
    r.y = 85;
    r.x = 10;
    r.w = win_width/4 - 20;
    SDL_RenderDrawRect(renderer, &r);
    SDL_RenderDrawLine(renderer,win_width/8-5, r.y+15, win_width/8+5, r.y+15);
    SDL_RenderDrawLine(renderer,win_width/8-5, r.y+15, win_width/8, r.y+7);
    SDL_RenderDrawLine(renderer,win_width/8, r.y+7, win_width/8+5, r.y+15);
}

void display_text(SDL_Renderer* renderer, const char textToDisplay[], TTF_Font* p_font, SDL_Color text_color, const unsigned int positionX, const unsigned int positionY)
{
    SDL_Rect r;
    r.x = positionX;
    r.y = positionY;
    SDL_Surface* pageText = TTF_RenderText_Solid(p_font, textToDisplay, text_color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,pageText);
    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);
    //printf("%s\t: %d\n", textToDisplay, r.w);

    SDL_RenderCopy(renderer,texture,NULL,&r);

    SDL_FreeSurface(pageText);
    SDL_DestroyTexture(texture);
}

void display_underlined_text(SDL_Renderer* renderer, const char textToDisplay[], TTF_Font* p_font, SDL_Color text_color, const unsigned int positionX, const unsigned int positionY)
{
    SDL_Rect r;
    r.x = positionX;
    r.y = positionY;
    SDL_Surface* pageText = TTF_RenderText_Solid(p_font, textToDisplay, text_color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,pageText);
    SDL_QueryTexture(texture,NULL,NULL,&r.w,&r.h);

    SDL_RenderCopy(renderer,texture,NULL,&r);
    SDL_RenderDrawLine(renderer,r.x, r.y+r.h, r.x + r.w, r.y+r.h);

    SDL_FreeSurface(pageText);
    SDL_DestroyTexture(texture);
}

void display_patient_panel (SDL_Renderer* renderer, const int win_width, const int win_height, SDL_Color text_color, TTF_Font* p_font)
{
    SDL_Rect r;
    int xPosition;
    /*Creation of the display structure for patient file*/
    r.x = 5*(win_width/16);//Les fractions bizarres, c'est normal, j'ai fait des schemas pour arriver à ça
    r.y = 100;
    r.h = 41; r.w = 7*(win_width/16);
    SDL_RenderDrawRect(renderer,&r);//surname rectangle
    r.y = 140;
    SDL_RenderDrawRect(renderer,&r);//name rectangle
    r.y = 100; r.x += r.w-1;
    r.h = 81; r.w = 3*(win_width/16);
    SDL_RenderDrawRect(renderer,&r);
    //SDL_RenderDrawLine(renderer,3*win_width/4, 140, 15*win_width/16, 140);

    SDL_RenderDrawLine(renderer,5*win_width/8,230,5*win_width/8,win_height-230);//Line which cuts the patient information page in two parts

    /*Display of the permanent content of the patient file*/

    xPosition = 3*win_width/4 + 5;
    display_text(renderer, "Circuit :", p_font, text_color, xPosition, 108);
    display_text(renderer, "Number of exams :", p_font, text_color, xPosition, 148);

    xPosition = 5*win_width/16 + 5;
    display_text(renderer, "Surname :", p_font, text_color, xPosition, 108);
    display_text(renderer, "Name :", p_font, text_color, xPosition, 148);
}

void display_patient_constant_informations(SDL_Renderer* renderer, const int win_width, const int win_height, SDL_Color text_color, TTF_Font* p_font)
{
    int xPosition;
    /*patient registration*/
    xPosition = 5*win_width/16;
    display_underlined_text(renderer, "First registration :", p_font, text_color, xPosition, 238);
    display_text(renderer, "Registration start :", p_font, text_color, xPosition, 262);
    display_text(renderer, "Registration end :", p_font, text_color, xPosition, 284);
    display_text(renderer, "Registration duration :", p_font, text_color, xPosition, 306);
    display_text(renderer, "Waiting time :", p_font, text_color, xPosition, 328);

    /*NRO exam*/
    xPosition = 5*win_width/8 + 10;
    display_underlined_text(renderer, "NRO exam", p_font, text_color, xPosition, 238);
    display_text(renderer, "Exam start :", p_font, text_color, xPosition, 262);
    display_text(renderer, "Exam end :", p_font, text_color, xPosition, 284);
    display_text(renderer, "Exam duration :", p_font, text_color, xPosition, 306);
    display_text(renderer, "Waiting time :", p_font, text_color, xPosition, 328);

    /*First exam*/
    xPosition = 5*win_width/16;
    display_underlined_text(renderer, "First exam", p_font, text_color, xPosition, 388);
    display_text(renderer, "Exam start :", p_font, text_color, xPosition, 412);
    display_text(renderer, "Exam end :", p_font, text_color, xPosition, 434);
    display_text(renderer, "Exam duration :", p_font, text_color, xPosition, 456);
    display_text(renderer, "Waiting time :", p_font, text_color, xPosition, 478);

    /*Second exam*/
    xPosition = 5*win_width/8 + 10;
    display_underlined_text(renderer, "Second exam :", p_font, text_color, xPosition, 388);
    display_text(renderer, "Exam start :", p_font, text_color, xPosition, 412);
    display_text(renderer, "Exam end :", p_font, text_color, xPosition, 434);
    display_text(renderer, "Exam duration :", p_font, text_color, xPosition, 456);
    display_text(renderer, "Waiting time :", p_font, text_color, xPosition, 478);

    /*Overall*/
    xPosition = 5*win_width/8 + 10;
    display_underlined_text(renderer, "Overall results of this patient :", p_font, text_color, xPosition, 538);
    display_text(renderer, "Total exam time :", p_font, text_color, xPosition, 563);
    display_text(renderer, "Total waiting time :", p_font, text_color, xPosition, 588);
    display_text(renderer, "Arrival hour :", p_font, text_color, xPosition, 613);
    display_text(renderer, "Exit hour :", p_font, text_color, xPosition, 638);
}

void display_global_statistics(SDL_Renderer* renderer, patient patient_list[], const short numberOfPatients, const int win_height, const int win_width, TTF_Font* p_font, SDL_Color text_color)
{
    int xPosition;
    short patientsInCircuit;
    int tempMinute;
    char str_time[] = "  h  ";
    /*Display of the separators between individual and global infos*/
    SDL_RenderDrawLine(renderer, win_width/4, win_height-370, 5*win_width/8, win_height-370);
    SDL_RenderDrawLine(renderer, win_width/4, win_height-365, (5*win_width/8)-5, win_height-365);
    SDL_RenderDrawLine(renderer, (5*win_width/8)-5, win_height-365, (5*win_width/8)-5, win_height-225);
    SDL_RenderDrawLine(renderer,(5*win_width/8)-5, win_height-225,win_width, win_height-225);
    SDL_RenderDrawLine(renderer,(5*win_width/8), win_height-230,win_width, win_height-230);

    xPosition = 5*win_width/16;

    display_underlined_text(renderer, "Global time statistics", p_font, text_color, xPosition, win_height - 358);
    display_text(renderer, "Mean waiting time :", p_font, text_color, xPosition, win_height - 324);
    display_text(renderer, "Mean exam time :", p_font, text_color, xPosition, win_height - 300);
    display_text(renderer, "Mean time in hospital :", p_font, text_color, xPosition, win_height - 276);

    /*average waiting time*/
    tempMinute = 0;
    for (int i = 0; i < numberOfPatients; i++)
    {
        tempMinute += patient_list[i].disponibilityHour[MINUTE] - patient_list[i].arrivalHour[MINUTE];
        tempMinute += (patient_list[i].disponibilityHour[HOUR] - patient_list[i].arrivalHour[HOUR]) * 60;
        tempMinute -= (patient_list[i].medicalExamDuration[0]
                       + patient_list[i].medicalExamDuration[1]
                       + patient_list[i].medicalExamDuration[2]
                       + (patient_list[i].medicalExamDuration[3]*(patient_list[i].circuit==VERY_LONG)));
    }
    tempMinute/=numberOfPatients;
    convert_minutes_to_displayable_hour(tempMinute, str_time);
    display_text(renderer, str_time, p_font, text_color, xPosition+156, win_height - 324);

    /*average exam time*/
    tempMinute = 0;
    for (int i = 0; i < numberOfPatients; i++)
    {
        tempMinute += (patient_list[i].medicalExamDuration[0]
                       + patient_list[i].medicalExamDuration[1]
                       + patient_list[i].medicalExamDuration[2]
                       + (patient_list[i].medicalExamDuration[3]*(patient_list[i].circuit==VERY_LONG)));
    }
    tempMinute/=numberOfPatients;
    convert_minutes_to_displayable_hour(tempMinute, str_time);
    display_text(renderer, str_time, p_font, text_color, xPosition+142, win_height - 300);

    /*average total time*/
    tempMinute = 0;
    for (int i = 0; i < numberOfPatients; i++)
    {
        tempMinute += patient_list[i].disponibilityHour[MINUTE] - patient_list[i].arrivalHour[MINUTE];
        tempMinute += (patient_list[i].disponibilityHour[HOUR] - patient_list[i].arrivalHour[HOUR]) * 60;
    }
    tempMinute/=numberOfPatients;
    convert_minutes_to_displayable_hour(tempMinute, str_time);
    display_text(renderer, str_time, p_font, text_color, xPosition+180, win_height - 276);

    display_text(renderer, "Mean time in waiting room 1 :", p_font, text_color, xPosition, win_height - 216);
    tempMinute = 0;
    for (int i = 0; i < numberOfPatients; i++)
    {
        tempMinute += patient_list[i].examStart[0].hour[MINUTE] - patient_list[i].arrivalHour[MINUTE];
        tempMinute += (patient_list[i].examStart[0].hour[HOUR] - patient_list[i].arrivalHour[HOUR]) * 60;
    }
    tempMinute/=numberOfPatients;
    convert_minutes_to_displayable_hour(tempMinute, str_time);
    display_text(renderer, str_time, p_font, text_color, xPosition+235, win_height - 216);

    display_text(renderer, "Mean time in registration room :", p_font, text_color, xPosition, win_height - 186);
    tempMinute = 0;
    for (int i = 0; i < numberOfPatients; i++)
    {
        tempMinute += patient_list[i].medicalExamDuration[0];
    }
    tempMinute/=numberOfPatients;
    convert_minutes_to_displayable_hour(tempMinute, str_time);
    display_text(renderer, str_time, p_font, text_color, xPosition + 252, win_height - 186);

    display_text(renderer, "Mean time in waiting room 2 :", p_font, text_color, xPosition, win_height - 156);
    tempMinute = 0;
    for (int i = 0; i < numberOfPatients; i++)
    {
        tempMinute += patient_list[i].examStart[1].hour[MINUTE] - patient_list[i].examEnd[0].hour[MINUTE];
        tempMinute += (patient_list[i].examStart[1].hour[HOUR] - patient_list[i].examEnd[0].hour[HOUR]) * 60;
    }
    tempMinute/=numberOfPatients;
    convert_minutes_to_displayable_hour(tempMinute, str_time);
    display_text(renderer, str_time, p_font, text_color, xPosition+235, win_height - 156);

    display_text(renderer, "Mean time with NRO :", p_font, text_color, xPosition, win_height - 126);
    tempMinute = 0;
    for (int i = 0; i < numberOfPatients; i++)
    {
        tempMinute += patient_list[i].medicalExamDuration[1];
    }
    tempMinute/=numberOfPatients;
    convert_minutes_to_displayable_hour(tempMinute, str_time);
    display_text(renderer, str_time, p_font, text_color, xPosition + 174, win_height - 126);

    display_text(renderer, "Mean time in waiting room 4 :", p_font, text_color, xPosition, win_height - 96);
    tempMinute = 0;
    patientsInCircuit = 0;
    for (int i = 0; i < numberOfPatients; i++)
    {
        if (patient_list[i].circuit == SHORT)
        {
            patientsInCircuit++;
            tempMinute += patient_list[i].examStart[2].hour[MINUTE] - patient_list[i].examEnd[1].hour[MINUTE];
            tempMinute += (patient_list[i].examStart[2].hour[HOUR] - patient_list[i].examEnd[1].hour[HOUR]) * 60;
        }
    }
    tempMinute = (patientsInCircuit) ? tempMinute/patientsInCircuit : 0;
    convert_minutes_to_displayable_hour(tempMinute, str_time);
    display_text(renderer, str_time, p_font, text_color, xPosition+235, win_height - 96);

    display_text(renderer, "Mean time of exam (short circuit) :", p_font, text_color, xPosition, win_height - 66);
    tempMinute = 0;
    patientsInCircuit = 0;
    for (int i = 0; i < numberOfPatients; i++)
    {
        if (patient_list[i].circuit == SHORT)
        {
            tempMinute += patient_list[i].medicalExamDuration[2];
            patientsInCircuit++;
        }
    }
    tempMinute = (patientsInCircuit) ? tempMinute/patientsInCircuit : 0;
    convert_minutes_to_displayable_hour(tempMinute, str_time);
    display_text(renderer, str_time, p_font, text_color, xPosition + 267, win_height - 66);

    xPosition = 5*win_width/8 + 10;

    display_text(renderer, "Mean time in waiting room 3 :", p_font, text_color, xPosition, win_height - 156);
    tempMinute = 0;
    patientsInCircuit = 0;
    for (int i = 0; i < numberOfPatients; i++)
    {
        if (patient_list[i].circuit!=SHORT)
        {
            patientsInCircuit++;
            tempMinute += patient_list[i].examStart[2].hour[MINUTE] - patient_list[i].examEnd[1].hour[MINUTE];
            tempMinute += (patient_list[i].examStart[2].hour[HOUR] - patient_list[i].examEnd[1].hour[HOUR]) * 60;
        }
    }
    tempMinute = (patientsInCircuit) ? tempMinute/patientsInCircuit : 0; // To avoid division by 0
    convert_minutes_to_displayable_hour(tempMinute, str_time);
    display_text(renderer, str_time, p_font, text_color, xPosition+235, win_height - 156);

    display_text(renderer, "Mean time of first exam (long circuit) :", p_font, text_color, xPosition, win_height - 126);
    tempMinute = 0;
    patientsInCircuit = 0;
    for (int i = 0; i < numberOfPatients; i++)
    {
        if (patient_list[i].circuit != VERY_LONG)
        {
            tempMinute += patient_list[i].medicalExamDuration[2];
            patientsInCircuit++;
        }
    }
    tempMinute = (patientsInCircuit) ? tempMinute/patientsInCircuit : 0;
    convert_minutes_to_displayable_hour(tempMinute, str_time);
    display_text(renderer, str_time, p_font, text_color, xPosition + 295, win_height - 126);

    display_text(renderer, "Mean time in waiting room 5 :", p_font, text_color, xPosition, win_height - 96);
    tempMinute = 0;
    patientsInCircuit = 0;
    for (int i = 0; i < numberOfPatients; i++)
    {
        if (patient_list[i].circuit == VERY_LONG)
        {
            patientsInCircuit++;
            tempMinute += patient_list[i].examStart[3].hour[MINUTE] - patient_list[i].examEnd[2].hour[MINUTE];
            tempMinute += (patient_list[i].examStart[3].hour[HOUR] - patient_list[i].examEnd[2].hour[HOUR]) * 60;
        }
    }
    tempMinute = (patientsInCircuit) ? tempMinute/patientsInCircuit : 0;
    convert_minutes_to_displayable_hour(tempMinute, str_time);
    display_text(renderer, str_time, p_font, text_color, xPosition+235, win_height - 96);

    display_text(renderer, "Mean time of second exam (long circuit) :", p_font, text_color, xPosition, win_height - 66);
    tempMinute = 0;
    patientsInCircuit = 0;
    for (int i = 0; i < numberOfPatients; i++)
    {
        if (patient_list[i].circuit == VERY_LONG)
        {
            tempMinute += patient_list[i].medicalExamDuration[3];
            patientsInCircuit++;
        }
    }
    tempMinute = (patientsInCircuit) ? tempMinute/patientsInCircuit : 0;
    convert_minutes_to_displayable_hour(tempMinute, str_time);
    display_text(renderer, str_time, p_font, text_color, xPosition + 321, win_height - 66);
}

void highlight_button(SDL_Renderer* renderer, const unsigned short buttonNumber, const int win_width)
{
    SDL_Rect r;
    r.x = 12;
    r.y = 112 + 45*buttonNumber;
    r.h = 36;
    r.w = win_width/4 - 24;
    SDL_RenderDrawRect(renderer, &r);
}

void display_patient_individual_top_panel(SDL_Renderer* renderer, patient patientToPrint, const int win_width, SDL_Color text_color, TTF_Font* panel_font)
{
    char nbr[] = "  ";

    display_text(renderer, patientToPrint.surname, panel_font, text_color, 5*win_width/16 + 96, 108);
    display_text(renderer, patientToPrint.name, panel_font, text_color, 5*win_width/16 + 71, 148);

    nbr[1] = 3+(patientToPrint.circuit == VERY_LONG) + '0';//number of exams
    display_text(renderer, nbr, panel_font, text_color, 3*win_width/4 + 168, 148);

    if(patientToPrint.circuit == SHORT)//circuit
    {
        display_text(renderer, "short", panel_font, text_color, 3*win_width/4 + 75, 108);
    }
    else
    {
        display_text(renderer, "long", panel_font, text_color, 3*win_width/4 + 75, 108);
    }
}

void display_patient_individual_informations(SDL_Renderer* renderer, patient patientToPrint, const int win_width, SDL_Color text_color, TTF_Font* p_font)
{
    int xPosition;
    char str_time[] = "  h  ";
    int minutes_duration, hours_duration;
    int totalWaitingTime = 0;

    xPosition = 5*win_width/16;

    /*exam start*/
    convert_hh_mm_to_displayable_hour(patientToPrint.examStart[0].hour[HOUR], patientToPrint.examStart[0].hour[MINUTE], str_time);
    display_text(renderer, str_time, p_font, text_color, xPosition + 144, 262);
    /*Exam end*/
    convert_hh_mm_to_displayable_hour(patientToPrint.examEnd[0].hour[HOUR], patientToPrint.examEnd[0].hour[MINUTE], str_time);
    display_text(renderer, str_time, p_font, text_color, xPosition + 139, 284);
    /*exam duration*/
    convert_minutes_to_displayable_hour(patientToPrint.medicalExamDuration[0], str_time);
    display_text(renderer, str_time, p_font, text_color, xPosition + 175, 306);
    /*Waiting time*/
    hours_duration = patientToPrint.examStart[0].hour[HOUR] - patientToPrint.arrivalHour[HOUR];
    minutes_duration = patientToPrint.examStart[0].hour[MINUTE] - patientToPrint.arrivalHour[MINUTE];
    minutes_duration += hours_duration*60;
    totalWaitingTime = minutes_duration;
    convert_minutes_to_displayable_hour(minutes_duration, str_time);
    display_text(renderer, str_time, p_font, text_color, xPosition + 112, 328);

    xPosition = 5*win_width/8 + 10;

    /****NRO, first and second exam****/
    /*exam start*/
    convert_hh_mm_to_displayable_hour(patientToPrint.examStart[1].hour[HOUR], patientToPrint.examStart[1].hour[MINUTE], str_time);
    display_text(renderer, str_time, p_font, text_color, xPosition + 94, 262);
    /*Exam end*/
    convert_hh_mm_to_displayable_hour(patientToPrint.examEnd[1].hour[HOUR], patientToPrint.examEnd[1].hour[MINUTE], str_time);
    display_text(renderer, str_time, p_font, text_color, xPosition + 89, 284);
    /*exam duration*/
    convert_minutes_to_displayable_hour(patientToPrint.medicalExamDuration[1], str_time);
    display_text(renderer, str_time, p_font, text_color, xPosition + 125, 306);
    /*Waiting time*/
    hours_duration = patientToPrint.examStart[1].hour[HOUR] - patientToPrint.examEnd[0].hour[HOUR];
    minutes_duration = patientToPrint.examStart[1].hour[MINUTE] - patientToPrint.examEnd[0].hour[MINUTE];
    minutes_duration += hours_duration*60;
    totalWaitingTime += minutes_duration;
    convert_minutes_to_displayable_hour(minutes_duration, str_time);
    display_text(renderer, str_time, p_font, text_color, xPosition + 112, 328);

    xPosition = 5*win_width/16;
    for (int i = 2; i < 4; i++)
    {
        if (i == 3)
        {
            xPosition = 5*win_width/8 + 10;
            if (!(patientToPrint.circuit==VERY_LONG)){break;}
        }
        /*exam start*/
        convert_hh_mm_to_displayable_hour(patientToPrint.examStart[i].hour[HOUR], patientToPrint.examStart[i].hour[MINUTE], str_time);
        display_text(renderer, str_time, p_font, text_color, xPosition + 94, 412);
        /*Exam end*/
        convert_hh_mm_to_displayable_hour(patientToPrint.examEnd[i].hour[HOUR], patientToPrint.examEnd[i].hour[MINUTE], str_time);
        display_text(renderer, str_time, p_font, text_color, xPosition + 89, 434);
        /*exam duration*/
        convert_minutes_to_displayable_hour(patientToPrint.medicalExamDuration[i], str_time);
        display_text(renderer, str_time, p_font, text_color, xPosition + 125, 456);
        /*Waiting time*/
        hours_duration = patientToPrint.examStart[i].hour[HOUR] - patientToPrint.examEnd[i-1].hour[HOUR];
        minutes_duration = patientToPrint.examStart[i].hour[MINUTE] - patientToPrint.examEnd[i-1].hour[MINUTE];
        minutes_duration += hours_duration*60;
        totalWaitingTime += minutes_duration;
        convert_minutes_to_displayable_hour(minutes_duration, str_time);
        display_text(renderer, str_time, p_font, text_color, xPosition + 112, 478);
    }

    /****Overall Results****/
    xPosition = 5*win_width/8 + 10;
    /*total exam time*/
    minutes_duration = (patientToPrint.medicalExamDuration[0]
                      + patientToPrint.medicalExamDuration[1]
                      + patientToPrint.medicalExamDuration[2]
                      + (patientToPrint.medicalExamDuration[3] * patientToPrint.circuit == VERY_LONG));
    convert_minutes_to_displayable_hour(minutes_duration, str_time);
    display_text(renderer, str_time, p_font, text_color, xPosition + 135, 564);
    /*total waiting time*/
    convert_minutes_to_displayable_hour(totalWaitingTime, str_time);
    display_text(renderer, str_time, p_font, text_color, xPosition + 150, 588);
    /*Arrival hour*/
    convert_hh_mm_to_displayable_hour(patientToPrint.arrivalHour[HOUR], patientToPrint.arrivalHour[MINUTE], str_time);
    display_text(renderer, str_time, p_font, text_color, xPosition + 103, 613);
    /*Exit hour*/
    convert_hh_mm_to_displayable_hour(patientToPrint.disponibilityHour[HOUR], patientToPrint.disponibilityHour[MINUTE], str_time);
    display_text(renderer, str_time, p_font, text_color, xPosition + 83, 638);
}

void hide_patient_individual_top_panel(SDL_Renderer* renderer, patient patientToHide, const int win_width, SDL_Color text_color, TTF_Font* panel_font)
{
    int xPosition = 5*win_width/16;

    hide_text(renderer, patientToHide.surname, xPosition + 96, 108, text_color, panel_font);
    hide_text(renderer, patientToHide.name, xPosition + 71 , 148, text_color, panel_font);

    xPosition = 3*win_width/4;
    hide_text(renderer, "33", xPosition + 168 , 148, text_color, panel_font);
    hide_text(renderer, "short",xPosition  + 75, 108, text_color, panel_font);
}

void hide_patient_individual_informations(SDL_Renderer* renderer, const int win_width, SDL_Color text_color, TTF_Font* p_font)
{
    int xPosition;
    char str_time[] = "00h00";

    xPosition = 5*win_width/16;
    hide_text(renderer, str_time, xPosition + 144, 262, text_color, p_font);
    hide_text(renderer, str_time, xPosition + 139, 284, text_color, p_font);
    hide_text(renderer, str_time, xPosition + 175, 306, text_color, p_font);
    hide_text(renderer, str_time, xPosition + 112, 328, text_color, p_font);

    xPosition = 5*win_width/8 + 10;

    hide_text(renderer, str_time, xPosition + 94, 262, text_color, p_font);
    hide_text(renderer, str_time, xPosition + 89, 284, text_color, p_font);
    hide_text(renderer, str_time, xPosition + 125, 306, text_color, p_font);
    hide_text(renderer, str_time, xPosition + 112, 328, text_color, p_font);

    xPosition = 5*win_width/16;
    hide_text(renderer, str_time, xPosition + 94, 412, text_color, p_font);
    hide_text(renderer, str_time, xPosition + 89, 434, text_color, p_font);
    hide_text(renderer, str_time, xPosition + 125, 456, text_color, p_font);
    hide_text(renderer, str_time, xPosition + 112, 478, text_color, p_font);

    xPosition = 5*win_width/8 + 10;
    hide_text(renderer, str_time, xPosition + 94, 412, text_color, p_font);
    hide_text(renderer, str_time, xPosition + 89, 434, text_color, p_font);
    hide_text(renderer, str_time, xPosition + 125, 456, text_color, p_font);
    hide_text(renderer, str_time, xPosition + 112, 478, text_color, p_font);

    hide_text(renderer, str_time, xPosition + 135, 564, text_color, p_font);
    hide_text(renderer, str_time, xPosition + 150, 588, text_color, p_font);
    hide_text(renderer, str_time, xPosition + 103, 613, text_color, p_font);
    hide_text(renderer, str_time, xPosition + 83, 638, text_color, p_font);
}

void hide_text(SDL_Renderer* renderer, const char textToHide[], const int xPosition, const int yPosition, SDL_Color text_color, TTF_Font* font)
{
    SDL_Rect rect;
    rect.x = xPosition;
    rect.y = yPosition;
    SDL_Surface* pageText = TTF_RenderText_Solid(font, textToHide, text_color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,pageText);
    SDL_QueryTexture(texture,NULL,NULL,&rect.w,&rect.h);

    SDL_RenderFillRect(renderer, &rect);
}

void convert_minutes_to_displayable_hour(int minutes, char str_time[])
{
    int hours;
    hours = minutes/60;
    minutes = minutes%60;
    convert_hh_mm_to_displayable_hour(hours, minutes, str_time);
}

void convert_hh_mm_to_displayable_hour(int hours, int minutes, char str_time[])
{
    str_time[0] = hours/10 + '0';
    str_time[1] = hours%10 + '0';
    str_time[3] = minutes/10 + '0';
    str_time[4] = minutes%10 + '0';
}

short event_click_on_up_arrow(SDL_Renderer* renderer, const unsigned short numberOfPatients, unsigned short scroll, const short patientToPrint, const int win_width, SDL_Color text_color, TTF_Font* button_font)
{
    SDL_Rect r;
    if (numberOfPatients - 18 - scroll < 0)//if the down arrow was not displayed previously
    {
        SDL_SetRenderDrawColor(renderer,240,240,240,255);
        display_down_arrow(renderer, win_width);
        SDL_SetRenderDrawColor(renderer,40,40,40,255);
    }
    scroll--;
    if (!scroll)//if the up arrow has to be hidden
    {
        r.y = 85;r.x = 10;
        r.h = 20;
        r.w = win_width/4 - 20;
        SDL_RenderFillRect(renderer, &r);
    }
    hide_buttons_content(renderer, numberOfPatients, scroll, text_color, button_font);
    display_buttons_content(renderer, numberOfPatients, scroll + 1, text_color, button_font);
    /*Make the button highlighting move with the scroll*/
    if (patientToPrint != -5)
    {
        SDL_SetRenderDrawColor(renderer,40,40,40,255);
        if(patientToPrint - scroll < 18 && patientToPrint - scroll > 0)
        {
            highlight_button(renderer, patientToPrint - scroll - 1, win_width);
        }if (patientToPrint - scroll < 17 && patientToPrint - scroll > -1){
            SDL_SetRenderDrawColor(renderer,240,240,240,255);
            highlight_button(renderer, patientToPrint - scroll, win_width);
            SDL_SetRenderDrawColor(renderer,40,40,40,255);
        }
    }
    return scroll;
}

short event_click_on_down_arrow(SDL_Renderer* renderer, const unsigned short numberOfPatients, unsigned short scroll, const short patientToPrint, const int win_width, SDL_Color text_color, TTF_Font* button_font)
{
    SDL_Rect r;
    if (!scroll)//if the up arrow was not displayed previously
    {
        SDL_SetRenderDrawColor(renderer,240,240,240,255);
        display_up_arrow(renderer, win_width);
        SDL_SetRenderDrawColor(renderer,40,40,40,255);
    }
    scroll++;
    if (numberOfPatients - 18 - scroll < 0)//if the down arrow has to be hidden
    {
        r.y = 875;r.x = 10;
        r.h = 20;
        r.w = win_width/4 - 20;
        SDL_RenderFillRect(renderer, &r);
    }
    hide_buttons_content(renderer, numberOfPatients, scroll, text_color, button_font);
    display_buttons_content(renderer, numberOfPatients, 1+scroll, text_color, button_font);

    if (patientToPrint != -5)//Applies only if a patient has already been selected
    {
        SDL_SetRenderDrawColor(renderer,40,40,40,255);
        if(patientToPrint - scroll < 18 && patientToPrint - scroll > -2)
        {
            highlight_button(renderer, patientToPrint - scroll + 1, win_width);
        }if (patientToPrint - scroll < 17 && patientToPrint - scroll > -1){
            SDL_SetRenderDrawColor(renderer,240,240,240,255);
            highlight_button(renderer, patientToPrint - scroll, win_width);
            SDL_SetRenderDrawColor(renderer,40,40,40,255);
        }
    }
    return scroll;
}
