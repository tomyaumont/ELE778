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
#define OP_TRAIN	0
#define OP_VC		1
#define OP_TEST		2

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
	double dataVC;
	double dataTest;

	double activation;
	double activationVC;
	double activationTest;

	double activationDerivee; //Xavier
	double activationDeriveeVC;
	double activationDeriveeTest;

	double delta;	// erreur
	double deltaVC;
	double deltaTest;

	double theta;	// ??? je me souviens plus ce que c'est mais il doit etre a zero
	double alpha;	// taux d'apprentissage - Pas utilise pour le moment, plus value le modifier dynamiquement
	vector<double> weights;	// vecteur de poids du neurone
	vector<double> delatW;
	PosID_s id;		// position du neurone dans le reseau

public:
	Neurone(void);
	~Neurone(void);

	void AddWeight(double val);
	void InitDelatW( int val );

	void SetData( double val );
	void SetTheta( double val );
	void SetDelta( double val );
	void SetAlpha( double val );
	void SetActivation( double val );
	void CalcData( vector<double> inputs, int opType );
	void CalcActivation( string activationFct, int opType );
	double CalcActivationDerivee( double data, string activationFct ); //Xavier
	void CalcDelta(  bool isLastLayer, string activFct,
							vector<double> nextLayerDeltas,
							vector<Neurone> nextLayerNeurones,
							int opType, bool desiredOut = 0 ); //Xavier & Tomy
	
	void SetID(PosID_s val);
	void UpdateWeigts( int val, vector<double> inputs );

	double GetData( void );
	double GetTheta( void );
	double GetDelta( int opType );
	double GetAlpha( void );
	double GetWeight( int ind );
	vector<double> GetWeights( void );
	double GetActivation( int opType );
	PosID_s GetID( void) ;
};
/*-----------------------------------------------------------------------------------*/
// Objet qui représente une couche
class Layer
{
private:
	vector<Neurone> neurones;	// liste de neurone de la couche
	vector<double> activations; /* vecteur contenant la valeur d'activation de chaque
								neurone de la couche pour l'entrainement	*/
	vector<double> activationsVC;  /* vecteur contenant la valeur d'activation de
									chaque neurone de la couche pour la validation
									croisee*/
	vector<double> activationsTest;  /* vecteur contenant la valeur d'activation de
										chaque neurone de la couche pour le test	*/
	vector<double> deltas;
	vector<double> deltasVC;
	vector<double> deltasTest;	//Xavier
								/* vecteur contenant le delta de chaque neurone de la couche	*/

public:
	Layer( void );
	~Layer( void );

	void InitWeight( double min, double max, int nbWeigh );
	void InitLayer( int nbNeuronesInLayer );

	void AddNeurone( int layer, double data = 0, double theta = 0, double delta = 0
																, double alpha = 0 );
	bool RmvNeurone( PosID_s ID );

	void CalcNeuroneXData( int neuroneIt, vector<double> bestData, int opType );
	void CalcNeuroneXActivation( int neuroneIt, string function, int opType );

	void SetActivations( int opType );
	void SetDeltas( int opType ); //Xavier

	vector<Neurone>* GetNeurones( void );
	vector<double> GetActivations( int opType );
	vector<double> GetDeltas( int opType ); //Xavier


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
	int out;
	double trainAccErr;
	int outVC;
	double vcAccErr;
	int outTest;
	double testAccErr;

	double trainErrPercent;
	double vcErrPercent;
	double testErrPercent;

	// Calcul la donnee et l'activaiton de chaque neurone
	void PhaseOne( FileInfo trainFile, string activFct, int opType );
	void PhaseTwo( FileInfo trainFile, string activFct, int opType );	//Xavier	// Calcul l'erreur (delta) de chaque neurone
	void PhaseThree( FileInfo trainFile, int opType );	// Calcul et actualise les poids
	void NormaliseThetas(FileInfo trainFile, string activFct, int opType); //Normalise les thetas, eliminant les extremes
	bool CrossValidation( vector<FileInfo> vcFiles, string activFct,
																double errorMargin );

	int FindRandomFile( vector<FileInfo> vcFiles );

	bool AskSaveTrain( void );
	void WriteTrainParam( ConfigFile settings, ofstream* ofs );

public:
	NeuralNetwork( void );
	~NeuralNetwork( void );

	void InitNetwork( ConfigFile* config );
	void InitLayers( int nbNeuronesIn, int nbHiddenLayers, int nbNeuroneHiddenLayer,
					int nbNeuroneOut );
	void InitWeight( double min, double max );

	//L'entrainement est arrete par le delai ou la validation croisee
	bool Train( vector<FileInfo> inputs, vector<FileInfo> trainFiles, int learnDelay,
				double errorMargin, string activFct, int nbEpoch, int normTheta );
	bool Test( vector<FileInfo> trainFiles, string activFct );

	void UpdateErrorAcc( char fileNum, int opType );

	void SetNbInput( int nbDataInput );
	int GetNbInput( void );
	void SetOut( int opType, vector<double> activ );
	void IncOutError( int opType );


	bool SaveTrainParam( ConfigFile settings );
	void SaveTestResult( void );

	bool IDExist( PosID_s );
};
/*-----------------------------------------------------------------------------------*/

#endif
