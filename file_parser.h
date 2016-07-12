/*
*	Name: file_parser.h
*
*	Written by: Tomy Aumont
*
*	Descritpion:
*/
#ifndef __FILE_PARSER_H_INCLUDED__
#define __FILE_PARSER_H_INCLUDED__

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <math.h>

#include "GraphTools.h"

using namespace std;

#define STATIC_ENERGY_POSITION 12		// indexe de l'�nergie statique d'une donn�e
#define DYNAMIC_ENERGY_POSITION 25		// indexe de l'�nergie dynamique d'une donn�e
#define NB_ELEM_BY_RECORD 26			// le nombre d'�l�ment dans une donn�e
#define ERROR -1						/*	Erreur retourn�e si la lecture d'une �nergie
											� �chou�e.	*/
#define PARSE_LOAD 1					/*	Constante utiliser pour savoir si les
											fichiers de de chemin de donnees sont
											utiliser pour creer ou charger un liste de
											donnees triees	*/
static const char* TRAIN_LOAD_PATH = "info_train.txt";
static const char* TEST_LOAD_PATH = "info_test.txt";
static const char* VC_LOAD_PATH = "info_vc.txt";

/*-----------------------------------------------------------------------------------*/
class ConfigFile
{
private:
	string infoTrainPath;
	string infoTestPath;
	string infoVCPath;
	int	nbBestData;
	bool sorted;	// 0 si l'usager veut effectuer l'�tape de classement, sinon 0

	int nbNeuroneIn;
	int nbHiddenLayers;
	int nbNeuroneHiddenLayers;
	int nbNeuroneOut;
	string activationFct;
	int learnMaxDelay;
	double errorMargin;
	double initWeightMin;
	double initWeightMax;
	double learnRate;

public:
	ConfigFile( void );		// Constructeur

	bool ReadConfig( void );	// Lis les param�tres du fichier "config.ini"
	bool UserSetConfig( void );	// Permet � l'usager de changer la configuration
	bool IsModifyingConfig( void );// D�termine si l'usage veut modifier la configuration
	void ModifyConfig( void );	// Modifie la configuration du programme
	void WriteConfig( void );	// �cris la configuration actuel dans "config.ini"

	// Les assignateurs pour les information concernant les fichier d'entree
	void SetInfoTrainPath( string );
	void SetInfoTestPath( string );
	void SetInfoVCPath( string );
	void SetNbBestData( int );
	void SetSorted( bool );

	// Les assignateurs pour les information concernant le reseau de neurones
	void SetNbNeuroneIn( int );
	void SetNbHiddenLayers( int );
	void SetNbNeuroneHiddenLayers( int );
	void SetNbNeuroneOut( int );
	void SetActivationFct( string );
	void SetLearnMaxDelay( int );
	void SetErrorMargin( double );
	void SetInitWeightMin( double );
	void SetInitWeightMax( double );
	void SetLearnRate( double );

	// Les recuperateurs pour les information concernant les fichier d'entree
	string GetInfoTrainPath( void );
	string GetInfoTestPath( void );
	string GetInfoVCPath( void );
	int GetNbBestData( void );
	bool GetSorted( void );
	
	// Les recuperateurs pour les information concernant le reseau de neurones
	int GetNbNeuroneIn( void );
	int GetNbHiddenLayers( void );
	int GetNbNeuroneHiddenLayers( void );
	int GetNbNeuroneOut( void );
	string GetActivationFct( void );
	int GetLearnMaxDelay( void );
	double GetErrorMargin( void );
	double GetInitWeightMin( void );
	double GetInitWeightMax( void );
	double GetLearnRate( void );

	void PrintConfig( void );
};
/*-----------------------------------------------------------------------------------*/
typedef struct PathData_s
{
	int nbOfDataInPath;
	string path;

}PathData_s;
/*-----------------------------------------------------------------------------------*/
class PathFile
{
private:
	string pathAndName;
	vector<PathData_s> pathFileList;

public:
	PathFile( void );				// Constructeur

	void SetOwnPath( string );		// Assigne son propre chemin de donnee
	bool Parse( bool load = 0 );	/*	Si load = 0, lis le fichier de chemin vers les
										fichier a pretraiter, sinon lis le fichier de
										chemin vers les donnees d'entrees	*/

	// Les recuperateurs
	string GetPathFilePathAndName( void );
	int GetNumberOfPath( void );
	string GetPathX( int index );
};
/*-----------------------------------------------------------------------------------*/
class FileInfo // Represente un fichier
{
private:
	string savePath;
	string fileName;
	string filePath;
	vector< vector<double> > rawDataMatrix;// Les donn�es brutes du fichier
	vector< double > bestData;		// Les meilleures donnees du fichier en une ligne

public:
	FileInfo( void );		// Constructeur

	bool ReadBestData( void );

	// Les asignateurs
	void SetFilePath( string pathName );
	bool SetRawDataMatrix( string path );
	void SetSavePath( int nbElem );
	void SetFileName( void );
	void SetBestData( int nbElem );

	// Les recuperateurs
	string GetFilePath( void );
	string GetFileName( void );
	string GetSavePath( void );
	double GetStaticEnergyX( int index );		// Not used
	double GetDynamicEnergyX( int index );		// Not used
	vector<vector<double>> GetRawDataMatrix( void );	// Not used
	vector<double>* GetRawDataX( int index );
	int GetRawMatrixSize( void );
	vector<double> GetBestData( void );

	void SortMatrix( void );// R�arrange la matrice de donn�es brute selon les �nergies
	bool SaveSortedFile( void );// Sauvegarde les matrice tri�es dans des fichier .txt
	bool WritePathToFileList( string savePath);

	
};
/*-----------------------------------------------------------------------------------*/
class InputFiles
{
private:
	vector<FileInfo> filesList;					// Liste des fichier � traiter

	void CreateDataBaseArchitecture( void );// Cr�e l'architecture de sauvegarde

public:
	InputFiles( void );	// Constructeur
	bool CreateSortedFiles( string pathFileName, int nbDataPerFile );
	bool CreateFileList( PathFile* paths, int nbElem = 0 ); // Cr�e la liste de fichier � traiter
	bool LoadSortedFiles( char* pathFileName );
	bool SortBestInputData( int nbElem );
	bool SaveDataToTxt( void );

	vector<FileInfo> GetFileList( void );
};

#endif
