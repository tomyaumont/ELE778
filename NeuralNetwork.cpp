
#include "NeuralNetwork.h"
#include "GraphTools.h"

/*************************************************************************************/
/*							Fonctions de la classe Neurone							 */
/*************************************************************************************/
/*-------------------------------------------------------------------------------------
*	Nom			:	Neurone
*	Écris par	:	Tomy Aumont
*
*	Description	:	Constructeur de la classe Neurone. Initialise theta à 0.0.
-------------------------------------------------------------------------------------*/
Neurone::Neurone( void ) : theta(0.0), delta(0.0)
{
}
/*-------------------------------------------------------------------------------------
*	Nom			:	~Neurone
*	Écris par	:	Tomy Aumont
*
*	Description	:	Destructeur de la classe Neurone
-------------------------------------------------------------------------------------*/
Neurone::~Neurone( void )
{

}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetData
*	Écris par	:	Tomy Aumont
*
*	Description	:	Assigne une donnee a ce neurone
-------------------------------------------------------------------------------------*/
void Neurone::SetData( double val )
{
	this->data = val;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetTheta
*	Écris par	:	Tomy Aumont
*
*	Description	:	Assigne la valeur 'val' au champs 'theta' du neurone
-------------------------------------------------------------------------------------*/
void Neurone::SetTheta( double val )
{
	this->theta = val;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetDelta
*	Écris par	:	Tomy Aumont
*
*	Description	:	Assigne la valeur de l'erreur de ce neurone
-------------------------------------------------------------------------------------*/
void Neurone::SetDelta( double val )
{
	this->delta = val;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetAlpha
*	Écris par	:	Tomy Aumont
*
*	Description	:	Assigne la valeur 'val' au champs 'alpha' du neurone
-------------------------------------------------------------------------------------*/
void Neurone::SetAlpha( double val )
{
	this->alpha = val;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetActivation
*	Écris par	:	Tomy Aumont
*
*	Description	:	Assigne la valeur 'val' au champs 'activation' du neurone
-------------------------------------------------------------------------------------*/
void Neurone::SetActivation( double val )
{
	this->activation = val;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	CalcData
*	Écris par	:	Tomy Aumont
*
*	Description	:	Calcul la donnee d'un neurone a travers chaque entree et poids.
*					Inputs est soit l'entree du reseau, soit l'activation de la couche
*					precedente.
-------------------------------------------------------------------------------------*/
void Neurone::CalcData( vector<double> inputs )
{
	double newData = 0;

	for( int neuroneIt = 0; neuroneIt < inputs.size(); neuroneIt++ )
	{
		newData += inputs[neuroneIt] * this->weights[neuroneIt];
	}
	this->data = newData + this->GetTheta();
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetActivation
*	Écris par	:	Tomy Aumont
*
*	Description	:	Calcul l'activation du neurone en utilisant la fonction recu en
*					parametre et l'assigne au champs activation du neurone
-------------------------------------------------------------------------------------*/
void Neurone::CalcActivation( string activationFct )
{
	if( !strcmp( activationFct.c_str(), "SIGMOIDE") )
		this->activation = ( 1 / ( 1 + exp(this->data) ) );

	else
		cout << "Fonction d'activation invalide! Verifier config.ini..." << endl;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	UpdateDeltaW
*	Écris par	:	Tomy Aumont
*
*	Description	:	Destructeur de la classe Neurone
-------------------------------------------------------------------------------------*/
void Neurone::UpdateDeltaW( int val, vector<Neurone> inputs )
{
	//this->delatW = this->alpha * this->delta * input;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetTag
*	Écris par	:	Tomy Aumont
*
*	Description	:	Assigne un numéro d'identification au neurone
-------------------------------------------------------------------------------------*/
void Neurone::SetID( PosID_s val )
{
	this->id = val;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	AddWeight
*	Écris par	:	Tomy Aumont
*
*	Description	:	Ajoute un poids a la liste de poids du neurone
-------------------------------------------------------------------------------------*/
void Neurone::AddWeight( double val )
{
	this->weights.push_back( val );
}
/*-------------------------------------------------------------------------------------
*	Nom			:	InitDelatW
*	Écris par	:	Tomy Aumont
*
*	Description	:	Initialise le vecteur de variations de poids au nombre de poids
*					compris dans le reseau de neurone
-------------------------------------------------------------------------------------*/
void Neurone::InitDelatW( int val )
{
	this->delatW.resize( val );
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetData
*	Écris par	:	Tomy Aumont
*
*	Description	:	Récupère la donnee de ce neurone
-------------------------------------------------------------------------------------*/
double Neurone::GetData( void )
{
	return this->data;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetTheta
*	Écris par	:	Tomy Aumont
*
*	Description	:	Récupère la valeur de theta pour ce neurone
-------------------------------------------------------------------------------------*/
double Neurone::GetTheta( void )
{
	return this->theta;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetDelta
*	Écris par	:	Tomy Aumont
*
*	Description	:	Recupere la valeur de l'erreur (delta)
-------------------------------------------------------------------------------------*/
double Neurone::GetDelta( void )
{
	return this->delta;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetAlpha
*	Écris par	:	Tomy Aumont
*
*	Description	:	Récupère le taux d'apprentissage du neurone
-------------------------------------------------------------------------------------*/
double Neurone::GetAlpha( void )
{
	return this->alpha;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetTag
*	Écris par	:	Tomy Aumont
*
*	Description	:	Récupère le numéro d'identificaiton de ce neurone
-------------------------------------------------------------------------------------*/
PosID_s Neurone::GetID( void )
{
	return this->id;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetWeights
*	Écris par	:	Tomy Aumont
*
*	Description	:	Recupere le vecteur de poids du neurone
-------------------------------------------------------------------------------------*/
vector<double> Neurone::GetWeights( void )
{
	return this->weights;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetActivation
*	Écris par	:	Tomy Aumont
*
*	Description	:	Recupere la valeur de l'activation du neurone
-------------------------------------------------------------------------------------*/
double Neurone::GetActivation( void )
{
	return this->activation;
}
/*************************************************************************************/
/*							Fonctions de la classe Layer							 */
/*************************************************************************************/
/*-------------------------------------------------------------------------------------
*	Nom			:	Layer
*	Écris par	:	Tomy Aumont
*
*	Description	:	Constructeur de l'objet layer
------------------------------------------------------------------------------------*/
Layer::Layer( void )
{

}
/*-------------------------------------------------------------------------------------
*	Nom			:	~Layer
*	Écris par	:	Tomy Aumont
*
*	Description	:	Destructeur de l'objet layer
------------------------------------------------------------------------------------*/
Layer::~Layer( void )
{

}
/*-------------------------------------------------------------------------------------
*	Nom			:	InitWeight
*	Écris par	:	Tomy Aumont
*
*	Description	:	Initialise les poids de toutes les connexions avec des valeurs
*					aleatoire entre [ min, max ]
-------------------------------------------------------------------------------------*/
void Layer::InitWeight( double min, double max, int nbWeight )
{
	for( int neuroneIt = 0; neuroneIt < this->neurones.size(); neuroneIt++ )
	{
		for( int weightIt = 0; weightIt < nbWeight; weightIt++ )
		{
			this->neurones[neuroneIt].AddWeight( fRand(min, max) );
		}
		this->neurones[neuroneIt].InitDelatW( nbWeight );
	}
}
/*-------------------------------------------------------------------------------------
*	Nom			:	AddNeurone
*	Écris par	:	Tomy Aumont
*
*	Description	:	Ajoute un neurone au réseau
------------------------------------------------------------------------------------*/
void Layer::AddNeurone( int layer, double data, double theta, double delta, double alpha )
{
	Neurone tmpNeurone;
	PosID_s tmpID;

	tmpID.layer = layer;
	tmpID.rang = this->neurones.size();

	// Assigne des valeur aux champs  du neurone
	tmpNeurone.SetData( data );
	tmpNeurone.SetTheta( theta );
	tmpNeurone.SetID( tmpID );
	tmpNeurone.SetDelta( delta );
	tmpNeurone.SetAlpha( alpha );
	tmpNeurone.SetActivation( 0.0 );

	// Ajoute le neurone a la liste
	this->neurones.push_back( tmpNeurone );

}
/*-------------------------------------------------------------------------------------
*	Nom			:	RmvNeurone
*	Écris par	:	Tomy Aumont
*
*	Description	:	Détruit le neurone possédant le ID recu en parametre
-------------------------------------------------------------------------------------*/
bool Layer::RmvNeurone( PosID_s ID )
{
	for( int i = 0; i < this->neurones.size(); i++ )
	{
		if( this->neurones[i].GetID().layer == ID.layer )
		{
			if( this->neurones[i].GetID().rang == ID.rang )
			{
				this->neurones.erase( this->neurones.begin() + i );
				return EXIT_SUCCESS;
			}
		}
	}
	return EXIT_FAILURE;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	InitActivations
*	Écris par	:	Tomy Aumont
*
*	Description	:	Initialise la grandeur du vecteur d'activiation
-------------------------------------------------------------------------------------*/
void Layer::InitActivations( int nbNeuronesInLayer )
{
	this->activations.resize( nbNeuronesInLayer );
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetActiVector
*	Écris par	:	Tomy Aumont
*
*	Description	:	Cree un vecteur contenant la valeur d'activation de chaque neurone
*					de la couche
-------------------------------------------------------------------------------------*/
void Layer::SetActivations( void )
{
	for( int neuroneIt = 0; neuroneIt < this->neurones.size(); neuroneIt++ )
	{
		this->activations[neuroneIt] =  this->neurones[neuroneIt].GetActivation();
	}
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetNeurones
*	Écris par	:	Tomy Aumont
*
*	Description	:	Recupere le vecteur de neurone de cette couche
-------------------------------------------------------------------------------------*/
vector<Neurone> Layer::GetNeurones( void )
{
	return this->neurones;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetActiVector
*	Écris par	:	Tomy Aumont
*
*	Description	:	Recupere le vecteur d'activation de la couche
-------------------------------------------------------------------------------------*/
vector<double> Layer::GetActivations( void )
{
	return this->activations;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetNeuronesSize
*	Écris par	:	Tomy Aumont
*
*	Description	:	Recupere le nombre de neurones dans la couche
-------------------------------------------------------------------------------------*/
int Layer::GetNeuronesSize( void )
{
	return this->neurones.size();
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetNeuroneXID
*	Écris par	:	Tomy Aumont
*
*	Description	:	Recupere l'ID du neurone au rang x de la couche
-------------------------------------------------------------------------------------*/
PosID_s Layer::GetNeuroneXID( int x )
{
	return this->neurones[x].GetID();
}
/*-------------------------------------------------------------------------------------
*	Nom			:	CalcNeuroneXData
*	Écris par	:	Tomy Aumont
*
*	Description	:	Permet de faire le calcul de la donnee du neurone neuroneIt de la
*					couche
-------------------------------------------------------------------------------------*/
void Layer::CalcNeuroneXData( int neuroneIt, vector<double> bestData )
{
	this->neurones[neuroneIt].CalcData( bestData );
}
/*-------------------------------------------------------------------------------------
*	Nom			:	CalcNeuroneXActivation
*	Écris par	:	Tomy Aumont
*
*	Description	:	Permet de faire le calcul de l'activation du neurone 'neuroneIt' de
*					la couche avec le type de fonction defini dans 'function'
-------------------------------------------------------------------------------------*/
void Layer::CalcNeuroneXActivation( int neuroneIt, string function )
{
	this->neurones[neuroneIt].CalcActivation( function );
}
/*************************************************************************************/
/*						Fonctions de la classe NeuralNetwork						 */
/*************************************************************************************/
/*-------------------------------------------------------------------------------------
*	Nom			:	NeuralNetwork
*	Écris par	:	Tomy Aumont
*
*	Description	:	Constructeur de la classe NeuralNetwork
-------------------------------------------------------------------------------------*/
NeuralNetwork::NeuralNetwork( void ) : layers(0)
{
	this->layers.resize(0);
	this->layers.shrink_to_fit();
}
/*-------------------------------------------------------------------------------------
*	Nom			:	~NeuralNetwork
*	Écris par	:	Tomy Aumont
*
*	Description	:	Destructeur de la classe NeuralNetwork
-------------------------------------------------------------------------------------*/
NeuralNetwork::~NeuralNetwork()
{

}
/*-------------------------------------------------------------------------------------
*	Nom			:	InitNetwork
*	Écris par	:	Tomy Aumont
*
*	Description	:	Initialise la structure du reseau, les couches, les connexions et
*					les neurones avec des valeurs aleatoires de poids et 0 comme theta
-------------------------------------------------------------------------------------*/
void NeuralNetwork::InitNetwork( ConfigFile* config )
{
	// Assigne le nombre d'input =  nombre de bestData * 12 donnees par data
	this->nbInput = config->GetNbBestData() * NB_INPUT_PER_DATA;
	this->learnRate = config->GetLearnRate();

	this->InitLayers(config->GetNbNeuroneIn(), config->GetNbHiddenLayers(),
		config->GetNbNeuroneHiddenLayers(), config->GetNbNeuroneOut());

	this->InitWeight( config->GetInitWeightMin(), config->GetInitWeightMax() );

}
/*-------------------------------------------------------------------------------------
*	Nom			:	Initneurones
*	Écris par	:	Tomy Aumont
*
*	Description	:	Cree le nombre necessaire de neurones pour chaque couche. Les
*					neurones cree sont initialisees avec un data, theta et delta egal
*					a 0 et leur position (couche + rang) respective
-------------------------------------------------------------------------------------*/
void NeuralNetwork::InitLayers(int nbNeuronesIn, int nbHiddenLayers, 
	int nbNeuroneHiddenLayer, int nbNeuroneOut)
{
	for( int i=0; i <= (nbHiddenLayers +1); i++ )
	{
		Layer tmpLayer;
		int j;
		if( i == 0 )
		{
			// Cree les neurones de la couche d'entree
			for( j=0; j < nbNeuronesIn; j++ )
			{
				tmpLayer.AddNeurone(i);
			}
			this->layers.push_back(tmpLayer);
		}
		else if( i > 0 && i < (nbHiddenLayers +1) )
		{
			// Cree les neurones des couches cachees
			for( j=0; j < nbNeuroneHiddenLayer; j++ )
			{
				tmpLayer.AddNeurone(i);
			}
			this->layers.push_back(tmpLayer);
		}
		else if( i == (nbHiddenLayers +1) )
		{
			// Cree les neurones de la couche de sortie
			for( j=0; j < nbNeuroneOut; j++ )
			{
				tmpLayer.AddNeurone(i);
			}
			this->layers.push_back(tmpLayer);
		}
		this->layers[i].InitActivations( j );
	}
}
/*-------------------------------------------------------------------------------------
*	Nom			:	Train
*	Écris par	:	Tomy Aumont
*
*	Description	:	Fait l'apprentissage de tous les chiffres de 0 a 9 a partir des
*					fichiers recu dans trainFiles.
*					Termine la fonction quand le delai learnDelay est atteint ou que
*					la validation croisee est satisfaisante.
-------------------------------------------------------------------------------------*/
bool NeuralNetwork::Train( vector<FileInfo> trainFiles, int learnDelay,
							double errorMargin, string activFct )
{
	char buffer [2];
	string learnNumItStr = "";

	// Pour tout les chiffres a apprendre
	for( int learnNumIt = 0; learnNumIt < 10; learnNumIt++ )
	{
		// Pour tout les fichier d'entrainement
		for( int fileIt = 0; fileIt < trainFiles.size(); fileIt++ )
		{
			/*	Si le fichier d'entrainement correspond au chiffre a apprendre, fait
				une epoque	*/
			learnNumItStr = itoa( learnNumIt, buffer, 10 );
			if( trainFiles[fileIt].GetFileName()[0] == learnNumItStr[0] )
			{
				/*	Calcul la donnees et l'activations des neurones etmet a jour le
					vecteur d'activation des couches.	*/
				this->PhaseOne( trainFiles[fileIt], activFct );
				//	Calcul l'erreur (delta) de chaque neurone
				this->PhaseTwo();
				//	Calcul et actualise les poids de tout le reseau
				this->PhaseThree();
		//		Si la validation croisee est acceptable, quitte la boucle
		//		d'apprentissage de ce chiffre
		//		if( this->CrossValidation(vcFiles[fileIt]) );
		//			break;
			}
		}
	}
	return EXIT_SUCCESS;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	PhaseOne
*	Écris par	:	Tomy Aumont
*
*	Description	:	Calcul la donnee et l'activation de chaque neurone
-------------------------------------------------------------------------------------*/
void NeuralNetwork::PhaseOne( FileInfo trainFile, string activFct )
{

	for( int layerIt = 0; layerIt < this->layers.size(); layerIt++ )
	{
		if( layerIt == 0 )
		{
			for( int neuroneIt = 0;
				neuroneIt < this->layers[layerIt].GetNeurones().size(); neuroneIt++ )
			{
				this->layers[layerIt].CalcNeuroneXData( neuroneIt,
															trainFile.GetBestData() );
				this->layers[layerIt].CalcNeuroneXActivation( neuroneIt, activFct );
			}
		}
		else
		{
			for( int neuroneIt = 0;
				neuroneIt < this->layers[layerIt].GetNeuronesSize(); neuroneIt++ )
			{
				this->layers[layerIt].CalcNeuroneXData( neuroneIt,
											this->layers[layerIt-1].GetActivations() );
				this->layers[layerIt].CalcNeuroneXActivation( neuroneIt, activFct );
			}
		}
		this->layers[layerIt].SetActivations();
	}
}
/*-------------------------------------------------------------------------------------
*	Nom			:	PhaseTwo
*	Écris par	:	Tomy Aumont
*
*	Description	:	Calcul l'erreur (delta) de chaque neurone
-------------------------------------------------------------------------------------*/
void NeuralNetwork::PhaseTwo( void )
{

}
/*-------------------------------------------------------------------------------------
*	Nom			:	PhaseThree
*	Écris par	:	Tomy Aumont
*
*	Description	:	Calcul et actualise les poids de tout le reseau en fonction de
*					l'erreur (delta) trouvee durant le phase 2
-------------------------------------------------------------------------------------*/
void NeuralNetwork::PhaseThree( void )
{
	for( int layIt = 0; layIt < this->layers.size(); layIt++ )
	{
		for( int neuIt = 0; neuIt < this->layers[layIt].GetNeuronesSize(); neuIt++ )
		{
			for( int wIt = 0;
				 wIt < this->layers[layIt].GetNeurones()[neuIt].GetWeights().size();
				 wIt++ )
			{
				this->layers[layIt].GetNeurones()[neuIt].UpdateDeltaW( wIt, this->layers[layIt-1].GetNeurones() );
			}
		}
	}
}
/*-------------------------------------------------------------------------------------
*	Nom			:	CrossValidation
*	Écris par	:	Tomy Aumont
*
*	Description	:	Effectue la validation croisee
-------------------------------------------------------------------------------------*/
void NeuralNetwork::CrossValidation( vector<FileInfo> vcFiles )
{

}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetNbInput
*	Écris par	:	Tomy Aumont
*
*	Description	:	Assigne le nombre d'entree du reseau de neurones
-------------------------------------------------------------------------------------*/
void NeuralNetwork::SetNbInput( int val )
{
	this->nbInput = val;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetNbInput
*	Écris par	:	Tomy Aumont
*
*	Description	:	Recupere le nombre d'entree du reseau de neurones
-------------------------------------------------------------------------------------*/
int NeuralNetwork::GetNbInput( void )
{
	return this->nbInput;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	InitWeight
*	Écris par	:	Tomy Aumont
*
*	Description	:	Initialise tous les poids du reseau aleatoirement entre min et max
-------------------------------------------------------------------------------------*/
void NeuralNetwork::InitWeight( double min, double max )
{
	int nbWeight;

	for( int layerIt = 0; layerIt < this->layers.size(); layerIt++)
	{
		if( layerIt == 0 )
			nbWeight = this->nbInput;
		else
			nbWeight = this->layers[layerIt-1].GetNeuronesSize();

		this->layers[layerIt].InitWeight( min, max, nbWeight );
	}
}
/*-------------------------------------------------------------------------------------
*	Nom			:	IDExist
*	Écris par	:	Tomy Aumont
*
*	Description	:	Retourne vrai si un neurone existe a la position defini par pos,
*					sinon retourne faux
-------------------------------------------------------------------------------------*/
bool NeuralNetwork::IDExist( PosID_s pos )
{
	for( int i=0; i < this->layers.size(); i++ )
	{
		for( int j=0; j < this->layers[i].GetNeuronesSize(); j++ )
		{
			if( this->layers[i].GetNeuroneXID(j).rang == pos.rang )
				return true;
		}
	}
	return false;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	Test
*	Écris par	:	Tomy Aumont
*
*	Description	:	Retourne 0 si le reseau de neurones a bien apprit les donnees
*					sinon, s'il n'a pas reconnu les donnees retourn 1
-------------------------------------------------------------------------------------*/
bool NeuralNetwork::Test(  )
{
	return EXIT_SUCCESS;
}
