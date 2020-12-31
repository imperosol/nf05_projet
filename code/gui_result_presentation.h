#include "struct.h"

#ifndef GUIRESULT_H
#define GUIRESULT_H

/********************************************//**
 * \fn void display_top_square(SDL_Renderer* renderer, SDL_Surface* icon, SDL_Color text_color, const int width, const int height)
 * \brief Function that displays the title of the window and the two images right and left of it.
 *
 * \param SDL_Renderer* renderer : the renderer of the window
 * \param SDL_Surface* image : the image to display right and left of the title
 * \param SDL_Color text_color : the colour of the text
 * \param const int width : the width of the window
 * \param const int height : the height of the window
 * \param
 ***********************************************/
void display_top_square(SDL_Renderer* renderer, SDL_Surface* image, SDL_Color text_color, const int width, const int height);

/********************************************//**
 * \fn void display_buttons(SDL_Renderer* renderer, const unsigned short nbrOfButtons, const unsigned short firstButton, const int win_width, const int win_height, SDL_Color text_color, TTF_Font* p_font)
 * \brief Function that displays the navigation buttons.
 *
 * \param SDL_Renderer* renderer : the renderer of the window
 * \param const unsigned short nbrOfButtons : the maximum number of buttons to display. If there is too much buttons to display in the window, all the buttons will not be displayed.
 * \param const unsigned short firstButton : the number that will be written on the first button
 * \param const int width : the width of the window
 * \param const int height : the height of the window
 * \param SDL_Color text_color : the colour of the text
 * \param TTF_Font* p_font : the text font to use
 ***********************************************/
void display_buttons(SDL_Renderer* renderer, const unsigned short nbrOfButtons, const unsigned short firstButton, const int win_width, const int win_height, SDL_Color text_color, TTF_Font* p_font);


/********************************************//**
 * \fn void display_buttons_content(SDL_Renderer* renderer, const unsigned short nbrOfButtons, const unsigned short firstButton, SDL_Color text_color, TTF_Font* p_font)
 * \brief Function that displays the navigation buttons text content, but not their shape.
 *
 * \param SDL_Renderer* renderer : the renderer of the window
 * \param const unsigned short nbrOfButtons : the maximum number of buttons to display. If there is too much buttons to display in the window, all the buttons will not be displayed.
 * \param const unsigned short firstButton : the number that will be written on the first button
 * \param SDL_Color text_color : the colour of the text
 * \param TTF_Font* p_font : the text font to use
 ***********************************************/
void display_buttons_content(SDL_Renderer* renderer, const unsigned short nbrOfButtons, const unsigned short firstButton, SDL_Color text_color, TTF_Font* p_font);

/********************************************//**
 * \fn void hide_buttons_content(SDL_Renderer* renderer, const unsigned short nbrOfButtons, const unsigned short firstButton, const int win_width, const int win_height, SDL_Color text_color, TTF_Font* p_font)
 * \brief Function that hides the navigation buttons text content, but not their shape.
 *
 * \param SDL_Renderer* renderer : the renderer of the window
 * \param const unsigned short nbrOfButtons : the maximum number of buttons to display. If there is too much buttons to display in the window, all the buttons will not be displayed.
 * \param const unsigned short firstButton : the number that will be written on the first button
 * \param SDL_Color text_color : the colour of the text
 * \param TTF_Font* p_font : the text font
 ***********************************************/
void hide_buttons_content(SDL_Renderer* renderer, const unsigned short nbrOfButtons, const unsigned short firstButton, SDL_Color text_color, TTF_Font* p_font);

/********************************************//**
 * \fn void display_down_arrow(SDL_Renderer* renderer, const int win_width)
 * \brief Function that displays the down arrow in the navigation menu.
 *
 * \param SDL_Renderer* renderer : the renderer of the window
 * \param const int win_width : the width of the window
 ***********************************************/
void display_down_arrow(SDL_Renderer* renderer, const int win_width);

/********************************************//**
 * \fn void display_up_arrow(SDL_Renderer* renderer, const int win_width)
 * \brief Function that displays the up arrow in the navigation menu.
 *
 * \param SDL_Renderer* renderer : the renderer of the window
 * \param const int win_width : the width of the window
 ***********************************************/
void display_up_arrow(SDL_Renderer* renderer, const int win_width);

/********************************************//**
 * \fn void display_patient_panel (SDL_Renderer* renderer, const int win_width, const int win_height, SDL_Color text_color, TTF_Font* p_font)
 * \brief Function that displays the patient panel
 *
 * \param SDL_Renderer* renderer : the renderer of the window
 * \param const int win_width : the width of the window
 * \param const int win_height : the height of the window
 * \param SDL_Color text_color : the colour of the text
 * \param TTF_Font* p_font : the text font
 ***********************************************/
void display_patient_panel (SDL_Renderer* renderer, const int win_width, const int win_height, SDL_Color text_color, TTF_Font* p_font);


/********************************************//**
 * \fn void display_patient_constant_informations(SDL_Renderer* renderer, const int win_width, const int win_height, SDL_Color text_color, TTF_Font* p_font)
 * \brief Function that displays the structure for the hour informations of the patients
 *
 * \param SDL_Renderer* renderer : the renderer of the window
 * \param const int win_width : the width of the window
 * \param const int win_height : the height of the window
 * \param SDL_Color text_color : the colour of the text
 * \param TTF_Font* p_font : the text font
 ***********************************************/
void display_patient_constant_informations(SDL_Renderer* renderer, const int win_width, const int win_height, SDL_Color text_color, TTF_Font* p_font);

/********************************************//**
 * \fn void display_global_statistics(SDL_Renderer* renderer, patient patient_list[], const short numberOfPatients, const int win_height, const int win_width, TTF_Font* p_font, SDL_Color text_color)
 * \brief Function that displays the structure for the hour informations of the patients
 *
 * \param SDL_Renderer* renderer : the renderer of the window
 * \param patient patient_list[] : the list of all the patients
 * \param const short numberOfPatients : the number of patients
 * \param const int win_height : the height of the window
 * \param const int win_width : the width of the window
 * \param TTF_Font* p_font : the text font
 * \param SDL_Color text_color : the colour of the text
 ***********************************************/
void display_global_statistics(SDL_Renderer* renderer, patient patient_list[], const short numberOfPatients, const int win_height, const int win_width, TTF_Font* p_font, SDL_Color text_color);

/********************************************//**
 * \fn void highlight_button(SDL_Renderer* renderer, const unsigned short buttonNumber, const int win_width)
 * \brief Function that highlights a button. The highlighting color must be set before the call of the procedure.
 *
 * \param SDL_Renderer* renderer : the renderer of the window
 * \param const unsigned short buttonNumber : the button to highlight
 * \param const int win_width : the width of the window
 ***********************************************/
void highlight_button(SDL_Renderer* renderer, const unsigned short buttonNumber, const int win_width);

/********************************************//**
 * \fn void display_patient_individual_top_panel(SDL_Renderer* renderer, patient patientToPrint, const int win_width, SDL_Color text_color, TTF_Font* panel_font)
 * \brief Function that displays the individual infos in the top panel
 *
 * \param SDL_Renderer* renderer : the renderer of the window
 * \param patient patientToPrint : the patient whose the informations are to be displayed
 * \param const int win_width : the width of the window
 * \param SDL_Color text_color : the colour of the text
 * \param TTF_Font* panel_font : the text font
 ***********************************************/
void display_patient_individual_top_panel(SDL_Renderer* renderer, patient patientToPrint, const int win_width, SDL_Color text_color, TTF_Font* panel_font);

/********************************************//**
 * \fn void display_patient_individual_informations(SDL_Renderer* renderer, patient patientToPrint, const int win_width, SDL_Color text_color, TTF_Font* p_font)
 * \brief Function that displays the individual hour informations
 *
 * \param SDL_Renderer* renderer : the renderer of the window
 * \param patient patientToPrint : the patient whose the informations are to be displayed
 * \param const int win_width : the width of the window
 * \param SDL_Color text_color : the colour of the text
 * \param TTF_Font* p_font : the text font
 ***********************************************/
void display_patient_individual_informations(SDL_Renderer* renderer, patient patientToPrint, const int win_width, SDL_Color text_color, TTF_Font* p_font);

/********************************************//**
 * \fn void hide_patient_individual_top_panel(SDL_Renderer* renderer, patient patientToHide, const int win_width, const int win_height, SDL_Color text_color, TTF_Font* panel_font)
 * \brief Function that hides the individual infos in the top panel
 *
 * \param SDL_Renderer* renderer : the renderer of the window
 * \param patient patientToPrint : the patient whose the informations are to be hidden
 * \param const int win_width : the width of the window
 * \param SDL_Color text_color : the colour of the text
 * \param TTF_Font* panel_font : the text font
 ***********************************************/
void hide_patient_individual_top_panel(SDL_Renderer* renderer, patient patientToHide, const int win_width, SDL_Color text_color, TTF_Font* panel_font);

/********************************************//**
 * \fn void hide_patient_individual_informations(SDL_Renderer* renderer, const int win_width, const int win_height, SDL_Color text_color, TTF_Font* p_font)
 * \brief Function that hides the individual hour informations
 *
 * \param SDL_Renderer* renderer : the renderer of the window
 * \param const int win_width : the width of the window
 * \param SDL_Color text_color : the colour of the text
 * \param TTF_Font* p_font : the text font
 ***********************************************/
void hide_patient_individual_informations(SDL_Renderer* renderer, const int win_width, SDL_Color text_color, TTF_Font* p_font);


/********************************************//**
 * \fn short event_click_on_up_arrow(SDL_Renderer* renderer, const unsigned short numberOfPatients, unsigned short scroll, const short patientToPrint, const int win_width, SDL_Color text_color, TTF_Font* button_font)
 * \brief function which manages the display of the modifications generated by the event of the click on the up arrow.
 *
 * \param SDL_Renderer* renderer : the renderer of the window
 * \param const unsigned short numberOfPatients : the number of patients
 * \param unisgned short scroll : a number which describes the position of the navigation buttons compared to the start. Each increment of the variable corresponds to a downward movement, and each decrement to an upward movement
 * \param const short patientToPrint : the patient to display
 * \param const int win_width : the width of the window
 * \param SDL_Color text_color : the colour of the text
 * \param TTF_Font* button_font : the text font
 *
 * \return short scroll : the new value of the scroll variable
 ***********************************************/
short event_click_on_up_arrow(SDL_Renderer* renderer, const unsigned short numberOfPatients, unsigned short scroll, const short patientToPrint, const int win_width, SDL_Color text_color, TTF_Font* button_font);

/********************************************//**
 * \fn short event_click_on_down_arrow(SDL_Renderer* renderer, const unsigned short numberOfPatients, unsigned short scroll, const short patientToPrint, const int win_width, SDL_Color text_color, TTF_Font* button_font)
 * \brief function which manages the display of the modifications generated by the event of the click on the down arrow.
 *
 * \param SDL_Renderer* renderer : the renderer of the window
 * \param const unsigned short numberOfPatients : the number of patients
 * \param unisgned short scroll : a number which describes the position of the navigation buttons compared to the start. Each increment of the variable corresponds to a downward movement, and each decrement to an upward movement
 * \param const short patientToPrint : the patient to display
 * \param const int win_width : the width of the window
 * \param SDL_Color text_color : the colour of the text
 * \param TTF_Font* button_font : the text font
 *
 * \return short scroll : the new value of the scroll variable
 ***********************************************/
short event_click_on_down_arrow(SDL_Renderer* renderer, const unsigned short numberOfPatients, unsigned short scroll, const short patientToPrint, const int win_width, SDL_Color text_color, TTF_Font* button_font);


#endif // GUIRESULT_H
