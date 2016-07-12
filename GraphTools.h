/*
*	Name: GraphTools.h
*	
*	Written by: Tomy Aumont
*	
*	Descritpion:	Liste les constantes et les fonctions utilisé dans l'affichage sur le terminal
*/
#ifndef __GRAPHTOOLS_H_INCLUDED__
#define __GRAPHTOOLS_H_INCLUDED__

#include <iostream>
#include <string>

#define SUCCESS "\nSucces!!!! :D"	// Message pour souligné si l'application s'est bien terminée
#define FAILURE "\tEchec!!!! :'("	// Message pour souligné si l'application s'est bien terminée
#define DBG_MSG_COMPLETE "\tTerminee"	// Message pour souligné la complétion de chaue étape

void PrintDashLine( void );
void PrintDebugMessage( std::string );
void PrintIntroHeader();

#endif