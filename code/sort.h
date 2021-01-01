/********************************************//**
 * \file sort.h
 * \brief Header of sort.c
 * \author Thomas Girod
 * \version 1.0
 * \date 12.11.2020
 ***********************************************/

#include "struct.h"

#ifndef SORT_H
#define SORT_H

 /********************************************//**
 * \fn int sort_by_arrival_hour (const void *a,const void *b)
 * \brief Function that sorts the elements of a patient array.
 * \param const void *a
 * \param const void *b
 ***********************************************/
int sort_by_arrival_hour (const void *a,const void *b);//applies to patients

 /********************************************//**
 * \fn int sort_by_disponibility_hour(const void *a,const void *b)
 * \brief Function that sorts the elements of an examRoom array.
 * \param const void *a
 * \param const void *b
 ***********************************************/
int sort_by_disponibility_hour(const void *a,const void *b);//applies to exam rooms

#endif // SORT_H
