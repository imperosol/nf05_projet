#include "struct.h"

/********************************************//**
 * \file gui.h
 * \brief Header of gui.c
 * \author Thomas Girod
 * \version 1.0
 * \date 25.11.2020
 ***********************************************/

#ifndef GUI_H
#define GUI_H

/********************************************//**
 * \fn void display_icon (SDL_Window* window)
 * \brief Function that sets the icon of the window. The icon is generated during the procedure and cannot be given as an argument.
 *
 * \param SDL_Window* window : the window that is to be given an icon.
 ***********************************************/
void display_icon(SDL_Window* window);

/********************************************//**
 * \fn void display_text (SDL_Renderer* renderer, const char textToDisplay[], TTF_Font* p_font, SDL_Color text_color, const unsigned int positionX, const unsigned int positionY)
 * \brief Function that displays a text in a position chosen by the user, with a given police and text colour.
 *
 * \param SDL_Renderer* renderer : the renderer of the window
 * \param char textToDisplay[] : the text to display
 * \param SDL_Color text_color : the colour of the text
 * \param TTF_Font* p_font : the text font
 * \param const unsigned int positionX : distance in pixels from the left border of the window
 * \param const unsigned int positionY : distance in pixels from the top border of the window
 ***********************************************/
void display_text (SDL_Renderer* renderer, const char textToDisplay[], TTF_Font* p_font, SDL_Color text_color, const unsigned int positionX, const unsigned int positionY);

/********************************************//**
 * \fn void display_underlined_text(SDL_Renderer* renderer, const char textToDisplay[], TTF_Font* p_font, SDL_Color text_color, const unsigned int positionX, const unsigned int positionY)
 * \brief Function that displays an underlined text in a position chosen by the user, with a given police and text colour.
 *
 * \param SDL_Renderer* renderer : the renderer of the window
 * \param char textToDisplay[] : the text to display
 * \param SDL_Color text_color : the colour of the text
 * \param TTF_Font* p_font : the text font
 * \param const unsigned int positionX : distance in pixels from the left border of the window
 * \param const unsigned int positionY : distance in pixels from the top border of the window
 ***********************************************/
void display_underlined_text(SDL_Renderer* renderer, const char textToDisplay[], TTF_Font* p_font, SDL_Color text_color, const unsigned int positionX, const unsigned int positionY);

/********************************************//**
 * \fn void hide_text (SDL_Renderer* renderer, const char textToHide[], const int xPosition, const int yPosition, SDL_Color text_color, TTF_Font* font)
 * \brief Function that hides a text in a specific position
 *
 * \param SDL_Renderer* renderer : the renderer of the window
 * \param const char textToHide[] : the text to hide
 * \param const int xPosition : distance in pixels from the left border of the window
 * \param const int yPosition : distance in pixels from the top border of the window
 * \param SDL_Color text_color : the colour of the text
 * \param TTF_Font* font : the text font
 ***********************************************/
void hide_text(SDL_Renderer* renderer, const char textToHide[], const int xPosition, const int yPosition, SDL_Color text_color, TTF_Font* font);

/********************************************//**
 * \fn void convert_minutes_to_displayable_hour(int minutes, char str_time[])
 * \brief Function that converts a time in minutes in a hh:mm format and stores it in a characters array given by the user
 *
 * \param int minutes : the number of minutes to convert and store
 * \param char str_time[] : the string in which the hour will be stored. This string must have 5 characters and str_time[2] must be equal to 'h'
 ***********************************************/
void convert_minutes_to_displayable_hour(int minutes, char str_time[]);

/********************************************//**
 * \fn void convert_hh_mm_to_displayable_hour(int hours, int minutes, char str_time[])
 * \brief Function that stores a time in a hh:mm format in a characters array given by the user without converting it.
 *
 * \param int hours : the number of hours to store
 * \param int minutes : the number of minutes to store
 * \param char str_time[] : the string in which the hour will be stored. This string must have 5 characters and str_time[2] must be equal to 'h'
 ***********************************************/
void convert_hh_mm_to_displayable_hour(int hours, int minutes, char str_time[]);

#endif // GUI_H
