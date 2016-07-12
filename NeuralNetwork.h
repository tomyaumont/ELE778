/*
*	Name: NeuralNetwork.h
*
*	Written by: Tomy Aumont
*
*	Descritpion:	Fichier qui contient toutes les fonctions et constantes utilisées
*					dans le réseau de neurones
*/
#ifndef __NeuralNetwork_H
#define __NeuralNetwork_H

#include <vector>
#include <time.h>

#include "file_parser.h"

using namespace std;

#define NB_INPUT_PER_DATA 12

/*-----------------------------------------------------------------------------------*/
// Genere un double de maniere aleatoire entre minLimit et maxLimit
inline double fRand(double minLimit, double maxLimit)
{
    double tmp = (double)rand() / RAND_MAX;
    return minLimit + tmp * (maxLimit - minLimit);
}

/*-----------------------------------------------------------------------------------*/
// Genere un double de maniere aleatoire entre minLimit et maxLimit
typedef struct PosID_s
{
    int layer;
	int rang;
} PosID_s;

/*-----------------------------------------------------------------------------------*/
// Objet qui représente une neurone
class Neurone
{
private:
	double data;
	double activation;
	double delta;	// erreur
	double theta;	// ??? je me souviens plus ce que c'est mais il doit etre a zero
	double alpha;	// taux d'apprentissage
	vector<double> weights;	// vecteur de poids du neurone
	vector<double> delatW;	// vecteur de variation des poids en fonction de l'erreur
	PosID_s id;		// position du neurone dans le reseau

public:
	Neurone( void );
	~Neurone( void );

	void InitDelatW( int val );
	void AddWeight( double val );
	void UpdateDeltaW( int val, vector<Neurone> inputs );

	void SetData( double val );
	void SetTheta( double val );
	void SetDelta( double val );
	void SetAlpha( double val );
	void SetActivation( double val );
	void CalcData( vector<double> inputs );
	void CalcActivation( string activationFct );
	void CalcDelta( void );
	void SetID( PosID_s val );
	

	double GetData( void );
	double GetTheta( void );
	double GetDelta( void );
	double GetAlpha( void );
	vector<double> GetWeights( void );
	double GetActivation( void );
	PosID_s GetID( void );
};
/*-----------------------------------------------------------------------------------*/
// Objet qui représente une couche
class Layer
{
private:
	vector<Neurone> neurones;	// liste de neurone de la couche
	vector<double> activations; /* vecteur contenant la valeur d'activation de chaque
								neurone de la couche	*/

public:
	Layer( void );
	~Layer( void );

	void InitWeight( double min, double max, int nbWeigh );

	void AddNeurone( int layer, double data = 0, double theta = 0, double delta = 0
																, double alpha = 0);
	bool RmvNeurone( PosID_s ID );

	void InitActivations( int nbNeuronesInLayer );
	void SetActivations( void );

	vector<Neurone> GetNeurones( void );
	vector<double> GetActivations( void );

	void CalcNeuroneXData( int neuroneIt, vector<double> bestData );
	void CalcNeuroneXActivation( int neuroneIt, string function );

	int GetNeuronesSize( void );
	PosID_s GetNeuroneXID( int x );
};
/*-----------------------------------------------------------------------------------*/
// Objet qui représente le réseau de neurones
class NeuralNetwork
{
private:
	vector<Layer> layers;	// liste de couches du reseau
	int nbInput;			// nombre d'entrees du reseau
	double alpha;		// je pense que le alpha irait mieux ici que dans un neurone mais il faut verifier dans nos notes de cours
	double learnRate;
	int out;

	// Calcul la donnee et l'activaiton de chaque neurone
	void PhaseOne( FileInfo trainFile, string activFct );
	void PhaseTwo( void );		// Calcul l'erreur (delta) de chaque neurone
	void PhaseThree( void );	// Calcul et actualise les poids
	void CrossValidation( vector<FileInfo> vcFiles );

public:
	NeuralNetwork( void );
	~NeuralNetwork( void );
	
	void InitNetwork( ConfigFile* config );
	void InitLayers(int nbNeuronesIn, int nbHiddenLayers, int nbNeuroneHiddenLayer,
																	int nbNeuroneOut);
	void InitWeight( double min, double max );

	//L'entrainement est arrete par le delai ou la validation croisee
	bool Train( vector<FileInfo> inputs, int learnDelay, double errorMargin,
																	string activFct ); 
	bool Test( void );


	void SetNbInput( int nbDataInput );
	int GetNbInput( void );


	bool IDExist( PosID_s );
};
/*-----------------------------------------------------------------------------------*/

#endif
