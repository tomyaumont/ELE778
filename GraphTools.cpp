#include "GraphTools.h"

void PrintDashLine( void )
{
	std::cout << "----------------------------------------"
				 "----------------------------------------" << std::endl;
}

void PrintDebugMessage( std::string message )
{
	std::cout << message << std::endl;
}

void PrintIntroHeader( void )
{
	PrintDashLine();
	std::cout << "Programme de reconnaissance vocale (chiffres de 0 a 9)" << std::endl;
	std::cout << std::endl << "Auteurs : Tomy Aumont & Xavier Mercure-Gagnon" << std::endl;
	std::cout << std::endl << "\tCe programme se deroule en 3 etapes. Premierement "
								"l'apprentissage, \n\tdeuxiemement le test et troisiemement la"
								" validation croisee." << std::endl << std::endl;
	PrintDashLine();
}
