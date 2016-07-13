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
Neurone::Neurone(void) : theta(0.0), delta(0.0)
{
}
/*-------------------------------------------------------------------------------------
*	Nom			:	~Neurone
*	Écris par	:	Tomy Aumont
*
*	Description	:	Destructeur de la classe Neurone
-------------------------------------------------------------------------------------*/
Neurone::~Neurone(void)
{

}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetData
*	Écris par	:	Tomy Aumont
*
*	Description	:	Assigne une donnee a ce neurone
-------------------------------------------------------------------------------------*/
void Neurone::SetData(double val)
{
	this->data = val;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetTheta
*	Écris par	:	Tomy Aumont
*
*	Description	:	Assigne la valeur 'val' au champs 'theta' du neurone
-------------------------------------------------------------------------------------*/
void Neurone::SetTheta(double val)
{
	this->theta = val;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetDelta
*	Écris par	:	Tomy Aumont
*
*	Description	:	Assigne la valeur de l'erreur de ce neurone
-------------------------------------------------------------------------------------*/
void Neurone::SetDelta(double val)
{
	this->delta = val;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetAlpha
*	Écris par	:	Tomy Aumont
*
*	Description	:	Assigne la valeur 'val' au champs 'alpha' du neurone
-------------------------------------------------------------------------------------*/
void Neurone::SetAlpha(double val)
{
	this->alpha = val;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	CalcData
*	Écris par	:	Tomy Aumont
*
*	Description	:	Calcul la donnee d'un neurone a travers chaque entree et poids.
*					Inputs est soit l'entree du reseau, soit l'activation de la couche
*					precedente.
-------------------------------------------------------------------------------------*/
void Neurone::CalcData(vector<double> inputs)
{
	double newData = 0;

	for (int neuroneIt = 0; neuroneIt < inputs.size(); neuroneIt++)
	{
		newData += inputs[neuroneIt] * this->weights[neuroneIt];
	}
	this->data = newData + this->GetTheta();
}
/*-------------------------------------------------------------------------------------
*	Nom			:	CalcDelta
*	Écris par	:	Xavier Mercure-Gagnon
*
*	Description	:	Calcul la valeur Delta d'un neurone à partir du taux d'apprentissage,
*					de la données activées et de la fonction d'activation dérivée.
*					L'entrée
-------------------------------------------------------------------------------------*/
void Neurone::CalcDelta(vector<double> inputs, string activFct, double learnRate, bool isLastLayer)
{
	if (isLastLayer)
	{
		this->delta = (learnRate - (this->activation)) * ((this->CalcActivationDerivee(this->data, activFct)));
	}
	else
	{
		double totalDelta = 0;

		for (int neuroneIt = 0; neuroneIt < inputs.size(); neuroneIt++)
		{
			totalDelta += inputs[neuroneIt];
		}
		this->delta = totalDelta * ((this->CalcActivationDerivee(this->data, activFct)));
	}
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetActivation
*	Écris par	:	Tomy Aumont
*
*	Description	:	Calcul l'activation du neurone en utilisant la fonction recu en
*					parametre et l'assigne au champs activation du neurone
-------------------------------------------------------------------------------------*/
void Neurone::CalcActivation(string activationFct)
{
	if (!strcmp(activationFct.c_str(), "SIGMOIDE"))
		this->activation = (1 / (1 + exp(this->data)));

	else
		cout << "Fonction d'activation invalide! Verifier config.ini..." << endl;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	CalcActivationDerivee
*	Écris par	:	xavier Mercure-Gagnon
*
*	Description	:	Calcul la dérivee de l'activation du neurone en utilisant la fonction
*					recu en parametre et l'assigne au champs activation du neurone
-------------------------------------------------------------------------------------*/
double Neurone::CalcActivationDerivee(double data, string activationFct)
{
	if (!strcmp(activationFct.c_str(), "SIGMOIDE"))
	{
		double lnEuler = log(exp(1.0));
		activationDerivee = (lnEuler / (4 * pow(cosh(lnEuler*(this->data) / 2), 2.0)));
		return activationDerivee;
	}
	else
		cout << "Fonction d'activation invalide! Verifier config.ini..." << endl;
	return ERROR;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetTag
*	Écris par	:	Tomy Aumont
*
*	Description	:	Assigne un numéro d'identification au neurone
-------------------------------------------------------------------------------------*/
void Neurone::SetID(PosID_s val)
{
	this->id = val;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	AddWeight
*	Écris par	:	Tomy Aumont
*
*	Description	:	Ajoute un poids a la liste de poids du neurone
-------------------------------------------------------------------------------------*/
void Neurone::AddWeight(double val)
{
	this->weights.push_back(val);
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetData
*	Écris par	:	Tomy Aumont
*
*	Description	:	Récupère la donnee de ce neurone
-------------------------------------------------------------------------------------*/
double Neurone::GetData(void)
{
	return this->data;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetTheta
*	Écris par	:	Tomy Aumont
*
*	Description	:	Récupère la valeur de theta pour ce neurone
-------------------------------------------------------------------------------------*/
double Neurone::GetTheta(void)
{
	return this->theta;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetDelta
*	Écris par	:	Tomy Aumont
*
*	Description	:	Recupere la valeur de l'erreur (delta)
-------------------------------------------------------------------------------------*/
double Neurone::GetDelta(void)
{
	return this->delta;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetAlpha
*	Écris par	:	Tomy Aumont
*
*	Description	:	Récupère le taux d'apprentissage du neurone
-------------------------------------------------------------------------------------*/
double Neurone::GetAlpha(void)
{
	return this->alpha;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetTag
*	Écris par	:	Tomy Aumont
*
*	Description	:	Récupère le numéro d'identificaiton de ce neurone
-------------------------------------------------------------------------------------*/
PosID_s Neurone::GetID(void)
{
	return this->id;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetWeight
*	Écris par	:	Tomy Aumont
*
*	Description	:	Recupere le poids a l'indice ind du neurone
-------------------------------------------------------------------------------------*/
double Neurone::GetWeight(int ind)
{
	return this->weights[ind];
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetActivation
*	Écris par	:	Tomy Aumont
*
*	Description	:	Recupere la valeur de l'activation du neurone
-------------------------------------------------------------------------------------*/
double Neurone::GetActivation(void)
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
Layer::Layer(void)
{

}
/*-------------------------------------------------------------------------------------
*	Nom			:	~Layer
*	Écris par	:	Tomy Aumont
*
*	Description	:	Destructeur de l'objet layer
------------------------------------------------------------------------------------*/
Layer::~Layer(void)
{

}
/*-------------------------------------------------------------------------------------
*	Nom			:	InitWeight
*	Écris par	:	Tomy Aumont
*
*	Description	:	Initialise les poids de toutes les connexions avec des valeurs
*					aleatoire entre [ min, max ]
-------------------------------------------------------------------------------------*/
void Layer::InitWeight(double min, double max, int nbWeight)
{
	for (int neuroneIt = 0; neuroneIt < this->neurones.size(); neuroneIt++)
	{
		for (int weightIt = 0; weightIt < nbWeight; weightIt++)
		{
			this->neurones[neuroneIt].AddWeight(fRand(min, max));
		}
	}
}
/*-------------------------------------------------------------------------------------
*	Nom			:	AddNeurone
*	Écris par	:	Tomy Aumont
*
*	Description	:	Ajoute un neurone au réseau
------------------------------------------------------------------------------------*/
void Layer::AddNeurone(int layer, double data, double theta, double delta, double alpha)
{
	Neurone tmpNeurone;
	PosID_s tmpID;

	tmpID.layer = layer;
	tmpID.rang = this->neurones.size();

	// Assigne des valeur aux champs  du neurone
	tmpNeurone.SetData(data);
	tmpNeurone.SetTheta(theta);
	tmpNeurone.SetID(tmpID);
	tmpNeurone.SetDelta(delta);
	tmpNeurone.SetAlpha(alpha);

	// Ajoute le neurone a la liste
	this->neurones.push_back(tmpNeurone);

}
/*-------------------------------------------------------------------------------------
*	Nom			:	RmvNeurone
*	Écris par	:	Tomy Aumont
*
*	Description	:	Détruit le neurone possédant le ID recu en parametre
-------------------------------------------------------------------------------------*/
bool Layer::RmvNeurone(PosID_s ID)
{
	for (int i = 0; i < this->neurones.size(); i++)
	{
		if (this->neurones[i].GetID().layer == ID.layer)
		{
			if (this->neurones[i].GetID().rang == ID.rang)
			{
				this->neurones.erase(this->neurones.begin() + i);
				return EXIT_SUCCESS;
			}
		}
	}
	return EXIT_FAILURE;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetActiVector
*	Écris par	:	Tomy Aumont
*
*	Description	:	Cree un vecteur contenant la valeur d'activation de chaque neurone
*					de la couche
-------------------------------------------------------------------------------------*/
void Layer::SetActivations(void)
{
	for (int neuroneIt = 0; neuroneIt < this->neurones.size(); neuroneIt++)
	{
		this->activations.push_back(this->neurones[neuroneIt].GetActivation());
	}
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetDeltas
*	Écris par	:	Xavier Mercure-Gagnon
*
*	Description	:	Cree un vecteur contenant le delta de chaque neurone de la couche
-------------------------------------------------------------------------------------*/
void Layer::SetDeltas(void)
{
	for (int neuroneIt = 0; neuroneIt < this->neurones.size(); neuroneIt++)
	{
		this->deltas.push_back(this->neurones[neuroneIt].GetDelta());
	}
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetNeurones
*	Écris par	:	Tomy Aumont
*
*	Description	:	Recupere le vecteur de neurone de cette couche
-------------------------------------------------------------------------------------*/

vector<Neurone> Layer::GetNeurones(void)
{
	return this->neurones;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetActiVector
*	Écris par	:	Tomy Aumont
*
*	Description	:	Recupere le vecteur d'activation de la couche
-------------------------------------------------------------------------------------*/
vector<double> Layer::GetActivations(void)
{
	return this->activations;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetDeltas
*	Écris par	:	Xavier Mercure-Gagnon
*
*	Description	:	Recupere le vecteur de deltas de la couche
-------------------------------------------------------------------------------------*/
vector<double> Layer::GetDeltas(void)
{
	return this->deltas;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetNeuronesSize
*	Écris par	:	Tomy Aumont
*
*	Description	:	Recupere le nombre de neurones dans la couche
-------------------------------------------------------------------------------------*/
int Layer::GetNeuronesSize(void)
{
	return this->neurones.size();
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetNeuroneXID
*	Écris par	:	Tomy Aumont
*
*	Description	:	Recupere l'ID du neurone au rang x de la couche
-------------------------------------------------------------------------------------*/
PosID_s Layer::GetNeuroneXID(int x)
{
	return this->neurones[x].GetID();
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
NeuralNetwork::NeuralNetwork(void) : layers(0)
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
void NeuralNetwork::InitNetwork(ConfigFile* config)
{
	// Assigne le nombre d'input =  nombre de bestData * 12 donnees par data
	this->nbInput = config->GetNbBestData() * NB_INPUT_PER_DATA;
	this->learnRate = config->GetLearnRate();

	this->InitLayers(config->GetNbNeuroneIn(), config->GetNbHiddenLayers(),
		config->GetNbNeuroneHiddenLayers(), config->GetNbNeuroneOut());

	this->InitWeight(config->GetInitWeightMin(), config->GetInitWeightMax());

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
	for (int i = 0; i <= (nbHiddenLayers + 1); i++)
	{
		Layer tmpLayer;

		if (i == 0)
		{
			// Cree les neurones de la couche d'entree
			for (int j = 0; j < nbNeuronesIn; j++)
			{
				tmpLayer.AddNeurone(i);
			}
			this->layers.push_back(tmpLayer);
		}
		else if (i > 0 && i < (nbHiddenLayers + 1))
		{
			// Cree les neurones des couches cachees
			for (int j = 0; j < nbNeuroneHiddenLayer; j++)
			{
				tmpLayer.AddNeurone(i);
			}
			this->layers.push_back(tmpLayer);
		}
		else if (i == (nbHiddenLayers + 1))
		{
			// Cree les neurones de la couche de sortie
			for (int j = 0; j < nbNeuroneOut; j++)
			{
				tmpLayer.AddNeurone(i);
			}
			this->layers.push_back(tmpLayer);
		}
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
bool NeuralNetwork::Train(vector<FileInfo> trainFiles, int learnDelay,
	double errorMargin, string activFct)
{
	char learnNumIt_ch;

	for (int learnNumIt = 0; learnNumIt < 10; learnNumIt++)
	{
		for (int fileIt = 0; fileIt < trainFiles.size(); fileIt++)
		{
			itoa(learnNumIt, &learnNumIt_ch, 10);
			if (trainFiles[fileIt].GetFileName()[0] == learnNumIt_ch)
			{
				// Calcul les donnees et les activations des neurones
				this->PhaseOne(trainFiles[fileIt], activFct);
				this->PhaseTwo(trainFiles[fileIt], activFct);
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
*
*	Probleme	:	Quand on passe au 2e fichier, on se retrouve avec plus d'activation
*					que de neurones donc le calcul du data plante
*	Solution possible	:	Faire la validation croisee apres le premier fichier et
*							overwritter les donner pour la deuxieme iteration
-------------------------------------------------------------------------------------*/
void NeuralNetwork::PhaseOne(FileInfo trainFile, string activFct)
{

	for (int layerIt = 0; layerIt < this->layers.size(); layerIt++)
	{
		if (layerIt == 0)
		{
			for (int neuroneIt = 0;
				neuroneIt < this->layers[layerIt].GetNeuronesSize(); neuroneIt++)
			{
				this->layers[layerIt].GetNeurones()[neuroneIt].CalcData(
					trainFile.GetBestData());
				this->layers[layerIt].GetNeurones()[neuroneIt].CalcActivation(
					activFct);
			}
		}
		else
		{
			for (int neuroneIt = 0;
				neuroneIt < this->layers[layerIt].GetNeuronesSize(); neuroneIt++)
			{
				this->layers[layerIt].GetNeurones()[neuroneIt].CalcData(
					this->layers[layerIt - 1].GetActivations());
				this->layers[layerIt].GetNeurones()[neuroneIt].CalcActivation(
					activFct);
			}
		}
		this->layers[layerIt].SetActivations();
	}
}
/*-------------------------------------------------------------------------------------
*	Nom			:	PhaseTwo
*	Écris par	:	Xavier Mercure-Gagnon
*
*	Description	:	Calcul l'erreur (delta) de chaque neurone
-------------------------------------------------------------------------------------*/
void NeuralNetwork::PhaseTwo(FileInfo trainFiles, string activFct)
{
	int layerMaxSize = this->layers.size();

	for (signed int layerIt = layerMaxSize; layerIt > 0; layerIt -= 1)
		//Dernière à la première couche
	{

		for (int neuroneIt = 0;
			neuroneIt < this->layers[layerIt].GetNeuronesSize(); neuroneIt++)
		{
			if (layerIt == layerMaxSize) //Dernière couche
			{
				this->layers[layerIt].GetNeurones()[neuroneIt].CalcDelta
				(this->layers[layerIt + 1].GetDeltas(), activFct,
					this->alpha, true);
			}
			else //Autres couches
			{
				this->layers[layerIt].GetNeurones()[neuroneIt].CalcDelta
				(this->layers[layerIt + 1].GetDeltas(), activFct,
					this->alpha, false);
			}
		}
		this->layers[layerIt].SetDeltas();
	}
}
/*-------------------------------------------------------------------------------------
*	Nom			:	PhaseThree
*	Écris par	:	Tomy Aumont
*
*	Description	:	Calcul et actualise les poids de tout le reseau
-------------------------------------------------------------------------------------*/
void NeuralNetwork::PhaseThree(void)
{

}
/*-------------------------------------------------------------------------------------
*	Nom			:	CrossValidation
*	Écris par	:	Tomy Aumont
*
*	Description	:	Effectue la validation croisee
-------------------------------------------------------------------------------------*/
void NeuralNetwork::CrossValidation(vector<FileInfo> vcFiles)
{

}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetNbInput
*	Écris par	:	Tomy Aumont
*
*	Description	:	Assigne le nombre d'entree du reseau de neurones
-------------------------------------------------------------------------------------*/
void NeuralNetwork::SetNbInput(int val)
{
	this->nbInput = val;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetNbInput
*	Écris par	:	Tomy Aumont
*
*	Description	:	Recupere le nombre d'entree du reseau de neurones
-------------------------------------------------------------------------------------*/
int NeuralNetwork::GetNbInput(void)
{
	return this->nbInput;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	InitWeight
*	Écris par	:	Tomy Aumont
*
*	Description	:	Initialise tous les poids du reseau aleatoirement entre min et max
-------------------------------------------------------------------------------------*/
void NeuralNetwork::InitWeight(double min, double max)
{
	int nbWeight;

	for (int layerIt = 0; layerIt < this->layers.size(); layerIt++)
	{
		if (layerIt == 0)
			nbWeight = this->nbInput;
		else
			nbWeight = this->layers[layerIt - 1].GetNeuronesSize();

		this->layers[layerIt].InitWeight(min, max, nbWeight);
	}
}
/*-------------------------------------------------------------------------------------
*	Nom			:	IDExist
*	Écris par	:	Tomy Aumont
*
*	Description	:	Retourne vrai si un neurone existe a la position defini par pos,
*					sinon retourne faux
-------------------------------------------------------------------------------------*/
bool NeuralNetwork::IDExist(PosID_s pos)
{
	for (int i = 0; i < this->layers.size(); i++)
	{
		for (int j = 0; j < this->layers[i].GetNeuronesSize(); j++)
		{
			if (this->layers[i].GetNeuroneXID(j).rang == pos.rang)
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
bool NeuralNetwork::Test()
{
	return EXIT_SUCCESS;
}
