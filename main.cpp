/**************************************************************************************
*	Name: main.cpp
*
*	Written by: Tomy Aumont
*				Xavier Mercure-Gagnon
*
*	Descritpion:
*		1ère partie:	Fait le pré-traitement des données. Termine avec un vecteur de
*						de données prêtes à être apprises par le réseau de neurones.
*
*	Probleme a regler:	Eventuellemet il va falloir gerer les erreur de plusieurs fonctions qui retourne void pour l'instant
*
*	Chose a faire :		Vérifier les résultat du train avec des calculs fait a la main et comment arreter en fonciton de l'erreur (VC), c'est quoi l'erreur?
*
*	Lien pour fonction activation a faire (tangeant hyperbolique) : http://www.statsoft.fr/concepts-statistiques/reseaux-de-neurones-automatises/reseaux-de-neurones-automatises.php
*						OBLIGATOIRE:
*							Coder les deux activations, choix deja present ( sigmoide + autre )
*							Validation croisee plus temps max d'apprentissage comme critere arret learning
*							Posibilite de voir les donnees des neurone des couches cachees et les sauvegarder
*
*						FACULTATIF:
*							InitWeigth() de plusieurs maniere
*							Initialisation du reseau (creation des neurones, connexions)
*							Implementer de la fonction d'activation sigmoide
*							Implementer du choix de la fonction d'activation
*							Implementer une 2e fonction d'activation
*							Implementer une sauvegarde des donnees + poids(connexions) apres execution
*						???	Attention au doublon de lien pour 2 neurones, vecteur a mettre dans le network ???
*							(optionnel) Choix du nom sauvegarde
*							(optionnel) Choix du nom de load
*							Deep learning ( initialisation des poids 1 couches a la fois )( long a faire )
**************************************************************************************/

#include "file_parser.h"
#include "GraphTools.h"
#include "NeuralNetwork.h"

using namespace std;

bool main( void )
{
	// Objet qui va contenir toutes les information du fichier config.ini
	ConfigFile settings;
	/*	Objet qui va contenir une liste de fichiers et toutes les informations
		concernant ces fichiers		*/
	InputFiles trainFiles;	
	/*	Objet qui va contenir une liste de fichiers et toutes les informations
		concernant ces fichiers.	*/		
	InputFiles testFiles;	
	/*	Objet qui va contenir une liste de fichiers et toutes les informations
		concernant ces fichiers.	*/
	InputFiles vcFiles;
	//	Objet qui va representer tout le reseau de neurone
	NeuralNetwork neuralNetwork;

	srand( time(NULL) );	// Initialise le random avec le temps actuel

	PrintIntroHeader();		//	Imprime une en-tete en debut
	settings.ReadConfig();	//	Recupere les information lu dans le fichier config.ini
	settings.UserSetConfig();	// Si l'usager le veut, modifie la configuration

	// Si l'usager veut utiliser des fichier déjàa triées, charge la liste de fichiers
	int nbData = settings.GetNbBestData();
	int isSorted = settings.GetSorted();

	if( isSorted )
	{
		cout << endl << "Chargement des fichiers triees en cours..." << endl;

		// Recupere le contenu des fichiers d'entrainement
		trainFiles.LoadSortedFiles( (char*)TRAIN_LOAD_PATH );
		// Recupere le contenu des fichiers de test
		testFiles.LoadSortedFiles( (char*)TEST_LOAD_PATH );
		// Recupere le contenu des fichiers de validation croisee
		vcFiles.LoadSortedFiles( (char*)VC_LOAD_PATH );
	}
	else
	{
		cout << endl << "Triage des fichiers d'entrees en cours..." << endl;

		trainFiles.CreateSortedFiles( settings.GetInfoTrainPath() , nbData );
		testFiles.CreateSortedFiles( settings.GetInfoTestPath() , nbData );
		vcFiles.CreateSortedFiles( settings.GetInfoVCPath() , nbData );

		cout << "Triage terminee" << endl;
	}

	//	Initialise le reseau
	neuralNetwork.InitNetwork( &settings );
	//	Effectue l'apprentissage selon les fichier lu et les parametres du config.ini
	neuralNetwork.Train( trainFiles.GetFileList(), vcFiles.GetFileList(),
							settings.GetLearnMaxDelay(), settings.GetErrorMargin(),
							settings.GetActivationFct(), settings.GetNbEpoch() );
	//	Demande et sauvegarde au besoin les parametre de l'apprentissage
	neuralNetwork.SaveTrainParam( settings );
	// Test le reseau de neurone avec des fichiers differents de l'apprentissage
	neuralNetwork.Test( testFiles.GetFileList(), settings.GetActivationFct() );


	PrintDebugMessage( SUCCESS );
	system( "pause" );
	return EXIT_SUCCESS;
}
