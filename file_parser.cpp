/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*	Nom			:	file_parser.cpp
*	
*	�cris par	:	Tomy Aumont & Xavier Mercure-Gagnon
*	
*	Descritpion	:	Contient toutes les fonctions utiles au pr�-traitement des donn�es
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include "file_parser.h"

/*************************************************************************************/
/*							Fonctions de la classe "ConfigFile"						 */
/*************************************************************************************/

/*-------------------------------------------------------------------------------------
*	Nom			:	ConfigFile
*	�cris par	:	Tomy Aumont
*
*	Description	:	Constructeur de la classe "ConfigFile"
*------------------------------------------------------------------------------------*/
ConfigFile::ConfigFile( void )
{
}
/*-------------------------------------------------------------------------------------
*	Nom			:	ReadConfig
*	�cris par	:	Tomy Aumont
*
*	Description	:	R�cupere les informations contenues dans le fichier de
*					configuration "config.ini"
*------------------------------------------------------------------------------------*/
bool ConfigFile::ReadConfig()
{
	fstream fileConfig;
	string line;

	fileConfig.open( "config.ini", ios::in );
	if( fileConfig.is_open() )
	{
		while( getline(fileConfig, line) )
		{
			/*	R�cupere le chemin vers le fichier contenant la liste des fichiers
				de test � traiter.	*/
			if( string::npos != line.find("infoTestPath") )
			{
				size_t info_pos = line.find("=") +2;
				this->infoTestPath = line.substr( info_pos );
			}
			/*	R�cupere le chemin vers le fichier contenant la liste des fichiers
				d'apprentissage � traiter.	*/
			else if( string::npos != line.find("infoTrainPath") )
			{
				size_t info_pos = line.find("=") +2;
				this->infoTrainPath = line.substr( info_pos );
			}
			/*	R�cupere le chemin vers le fichier contenant la liste des fichiers
				de validation crois�e � traiter.	*/
			else if( string::npos != line.find("infoVCPath") )
			{
				size_t info_pos = line.find("=") +2;
				this->infoVCPath = line.substr( info_pos );
			}
			/*	R�cupere le nombre de donn�es � utiliser comme entr�e du r�seau de
				de neurones pour chaque fichier.	*/
			else if( string::npos != line.find("nbBestData") )
			{
				size_t info_pos = line.find("=") +2;
				this->nbBestData = atoi(line.substr( info_pos ).c_str());
			}
			//	R�cupere l'information qui d�termine si le classement est d�j� fait.
			else if( string::npos != line.find("isSorted") )
			{
				size_t info_pos = line.find("=") +2;
				this->sorted = atoi(line.substr( info_pos ).c_str());
			}
			//	R�cupere le nombre de neurone utilisees pour la couche d'entree
			else if( string::npos != line.find("nbNeuroneIn") )
			{
				size_t info_pos = line.find("=") +2;
				this->nbNeuroneIn = atoi(line.substr( info_pos ).c_str());
			}
			//	R�cupere le nombre de couches cachees a utiliser
			else if( string::npos != line.find("nbHiddenLayers") )
			{
				size_t info_pos = line.find("=") +2;
				this->nbHiddenLayers = atoi(line.substr( info_pos ).c_str());
			}
			//	R�cupere le nombre de neurone par couche cachee a utiliser
			else if( string::npos != line.find("nbNeuroneHiddenLayers") )
			{
				size_t info_pos = line.find("=") +2;
				this->nbNeuroneHiddenLayers = atoi(line.substr( info_pos ).c_str());
			}
			//	R�cupere le nombre de neurone utilisees pour la couche de sortie
			else if( string::npos != line.find("nbNeuroneOut") )
			{
				size_t info_pos = line.find("=") +2;
				this->nbNeuroneOut = atoi(line.substr( info_pos ).c_str());
			}
			// Recupere la fonction d'activation a utiliser
			else if( string::npos != line.find("activationFct") )
			{
				size_t info_pos = line.find("=") +2;
				this->activationFct = line.substr( info_pos ).c_str();
			}
			// Recupere le delai a atteindre pour arreter l'apprentissage
			else if( string::npos != line.find("learnMaxDelay") )
			{
				size_t info_pos = line.find("=") +2;
				this->learnMaxDelay = atoi(line.substr( info_pos ).c_str());
			}
			// Recupere la marge d'erreur a atteindre pour arreter l'apprentissage
			else if( string::npos != line.find("errorMargin") )
			{
				size_t info_pos = line.find("=") +2;
				this->errorMargin = stod(line.substr( info_pos ).c_str());
			}
			// Recupere la marge d'erreur a atteindre pour arreter l'apprentissage
			else if( string::npos != line.find("initWeightMin") )
			{
				size_t info_pos = line.find("=") +2;
				this->initWeightMin = stod(line.substr( info_pos ).c_str());
			}
			// Recupere la marge d'erreur a atteindre pour arreter l'apprentissage
			else if( string::npos != line.find("initWeightMax") )
			{
				size_t info_pos = line.find("=") +2;
				this->initWeightMax = stod(line.substr( info_pos ).c_str());
			}
			// Recupere la marge d'erreur a atteindre pour arreter l'apprentissage
			else if( string::npos != line.find("learnRate") )
			{
				size_t info_pos = line.find("=") +2;
				this->learnRate = stod(line.substr( info_pos ).c_str());
			}
			// Recupere le nombre maximal d'epoque a faire lors de l'apprentissage
			else if( string::npos != line.find("nbEpoch") )
			{
				size_t info_pos = line.find("=") +2;
				this->nbEpoch = atoi(line.substr( info_pos ).c_str());
			}
			// Recupere l'information qui determine si on normalise les theta ou pas
			else if( string::npos != line.find("normTheta") )
			{
				size_t info_pos = line.find("=") +2;
				this->normTheta = atoi(line.substr( info_pos ).c_str());
			}
		}
		return EXIT_SUCCESS;
	}
	else
	{
		PrintDebugMessage( "\tError opening config.ini" );
		return EXIT_FAILURE;
	}
}
/*-------------------------------------------------------------------------------------
*	Nom			:	UserSetConfig
*	�cris par	:	Tomy Aumont
*
*	Description	:	Affiche la derni�re configuration utilis�e. Si l'usager veut la 
*					modifier, modifie le fichier "config.ini" selon ses pr�f�rences.
*------------------------------------------------------------------------------------*/
bool ConfigFile::UserSetConfig( void )
{
	this->PrintConfig();

	if( this->IsModifyingConfig() )
	{
		this->ModifyConfig();
		this->PrintConfig();
	}
	else
		return EXIT_SUCCESS;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	PrintConfig
*	�cris par	:	Tomy Aumont
*
*	Description	:	Affiche la configuration courante dans le terminal.
*------------------------------------------------------------------------------------*/
void ConfigFile::PrintConfig( void )
{
	cout << "Configuration courante :" << endl << endl;
	cout << "\t1. Fichier d'apprentissage \t : " << this->infoTrainPath << endl;
	cout << "\t2. Fichier de test \t\t : " << this->infoTestPath << endl;
	cout << "\t3. Fichier de validation croisee : " << this->infoVCPath << endl;
	cout << "\t4. Nombre de donnees a utilisees \t: " << this->nbBestData << endl;
	cout << "\t5. Donnees deja triees ? \t\t: " << this->sorted << endl;
	cout << "\t6. Nombre de neurones d'entree \t\t: " << this->nbNeuroneIn << endl;
	cout << "\t7. Nombre de couches cachees \t\t: " << this->nbHiddenLayers << endl;
	cout << "\t8. Nombre de neurones par couche cachee : " <<
												this->nbNeuroneHiddenLayers << endl;
	cout << "\t9. Nombre de neurones de sortie \t: " << this->nbNeuroneOut << endl;
	cout << "\tA. Fonction d'activation utilisee\t: " << this->activationFct << endl;
	cout << "\tB. Temps d'apprentissage (seconde) \t: " << this->learnMaxDelay << endl;
	cout << "\tC. Marge d'erreur acceptable \t\t: " << this->errorMargin << endl;
	cout << "\tD. Initialisation des poids minimale \t: " << this->initWeightMin << endl;
	cout << "\tE. Initialisation des poids maximale \t: " << this->initWeightMax << endl;
	cout << "\tF. Taux d'apprentissage \t\t: " << this->learnRate << endl;
	cout << "\tG. Nombre d'epoque d'apprentissage \t: " << this->nbEpoch << endl;
	cout << "\tH. Normalisation des theta? \t\t: " << this->normTheta << endl;

	PrintDashLine();
}
/*-------------------------------------------------------------------------------------
*	Nom			:	IsModifyingConfig
*	�cris par	:	Tomy Aumont
*
*	Description	:	Demande � l'usager s'il veut modifier la configuration
*------------------------------------------------------------------------------------*/
bool ConfigFile::IsModifyingConfig( void )
{
	char answer;

	cout<<"Voulez-vous modifier la configuration? ( O / N ) : ";
	
	answer = toupper( getchar() );

	while( answer != 'O' && answer != 'N' )
	{
		getchar(); // R�cupere la touche "ENTR�"
		cout << "\tVeuillez entrer 'O' ou 'N' : ";
		answer = toupper( getchar() );
	}

	if( 'O' == answer )
		return true;
	else if( 'N' == answer )
		return false;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	ModifyConfig
*	�cris par	:	Tomy Aumont
*
*	Description	:	Permet � l'usager de modifier les param�tres du fichier de
*					configuration "config.ini"
*------------------------------------------------------------------------------------*/
void ConfigFile::ModifyConfig( void )
{
	string tmpStr;
	char parametre = NULL;

	cout << endl << "Quel parametre voulez-vous modifier?" << endl <<
			"\t1. Chemin vers la liste des fichiers d'apprentissage" << endl <<
			"\t2. Chemin vers la liste des fichiers de test" << endl <<
			"\t3. Chemin vers la liste des fichiers de validation croisee" << endl <<
			"\t4. Nombre de donnees a considerer par fichier (40, 50, 60)" << endl <<
			"\t5. Utiliser des fichiers deja triees ? (O/N)" << endl <<
			"\t6. Nombre de neurones d'entree" << endl <<
			"\t7. Nombre de couches cachees" << endl <<
			"\t8. Nombre de neurones par couche cachee" << endl <<
			"\t9. Nombre de neurones de sortie (10)" << endl <<
			"\tA. Fonction d'activation (sigmoide ou tanh)" << endl <<
			"\tB. Temps maximal d'apprentissage (seconde)" << endl <<
			"\tC. Marge d'erreur acceptable" << endl <<
			"\tD. Initialisation des poids minimale" << endl <<
			"\tE. Initialisation des poids maximale" << endl <<
			"\tF. Taux d'apprentissage" << endl <<
			"\tG. Nombre d'epoque d'apprentissage" << endl <<
			"\tH. Nomralisation des theta?" << endl <<
			"\t0. Terminer la modification" << endl <<
			"Votre choix : ";

	while( parametre != '0' )
	{
		cin >> parametre;
		parametre = toupper(parametre);

		switch( parametre )
		{
			// Termine la modification
		case '0':
			{
				cout << "\tModification terminee" << endl;
			break;
			}
			// Pour le fichier d'apprentissage, de test ou de validation crois�e
		case '1': case '2': case '3':
			{
				cout << "Entrez le chemin desire : ";
				cin >> tmpStr;
				if( parametre == '1' )
					this->infoTrainPath = tmpStr;
				else if( parametre == '2' )
					this->infoTestPath = tmpStr;
				else if( parametre == '3' )
					this->infoVCPath = tmpStr ;
				cout << endl << "Quel parametre voulez-vous modifier? : ";
				break;
			} 
		case '4': case '6': case '7': case '8': case '9': case 'B': case 'C': case 'D':
		case 'E': case 'F': case 'G':
			{
				// Pour le nombre de donn�es tri�es � consid�rer par fichier
				cout << "Entrez le nombre desire : ";
				cin >> tmpStr;

				if( parametre == '4' )
					this->nbBestData = atoi(tmpStr.c_str());
				else if( parametre == '6' )
					this->nbNeuroneIn = atoi(tmpStr.c_str());
				else if( parametre == '7' )
					this->nbHiddenLayers = atoi(tmpStr.c_str());
				else if( parametre == '8' )
					this->nbNeuroneHiddenLayers = atoi(tmpStr.c_str());
				else if( parametre == '9' )
					this->nbNeuroneOut = atoi(tmpStr.c_str());
				else if( parametre == 'B' )
					this->learnMaxDelay = atoi(tmpStr.c_str());
				else if( parametre == 'C' )
					this->errorMargin = stod(tmpStr.c_str());
				else if( parametre == 'D' )
					this->initWeightMin = stod(tmpStr.c_str());
				else if( parametre == 'E' )
					this->initWeightMax = stod(tmpStr.c_str());
				else if( parametre == 'F' )
					this->learnRate = stod(tmpStr.c_str());
				else if( parametre == 'G' )
					this->nbEpoch = atoi(tmpStr.c_str());

				cout << endl << "Quel parametre voulez-vous modifier? : ";
				break;
			}
		case '5': case 'H':
			{
				cout << "Entrez oui (O) ou non (N) : ";
				cin >> tmpStr; // Recupere la lettre entree
				transform(tmpStr.begin(), tmpStr.end(), tmpStr.begin(), toupper);
				while( tmpStr!="O" && tmpStr!="N" && tmpStr!="OUI" && tmpStr!="NON" )
				{
					cout << "\tVeuillez entrer 'O' ou 'N' : ";
					cin >> tmpStr;
					transform( tmpStr.begin(), tmpStr.end(), tmpStr.begin(), toupper );
				}

				if( "O" == tmpStr || "OUI" == tmpStr )
				{
					if( parametre == '5' )
						this->sorted = true;
					else if(parametre == 'H' )
						this->normTheta = true;
				}
				else if( "N" == tmpStr || "NON" == tmpStr )
				{
					if( parametre == '5' )
						this->sorted = false;
					else if(parametre == 'H' )
						this->normTheta = false;
				}
				cout << endl << "Quel parametre voulez-vous modifier? : ";
				break;
			}
		case 'A':
			{
				cout << "Entrez la fonction desire, soit sigmoide ou ... : ";
				cin >> tmpStr;
				transform( tmpStr.begin(), tmpStr.end(), tmpStr.begin(), toupper );
				while( tmpStr != "SIGMOIDE" && tmpStr != "TANH")
				{
					cout << "\tVeuillez entrer SIGMOIDE ou TANH : ";
					cin >> tmpStr;
					transform( tmpStr.begin(), tmpStr.end(), tmpStr.begin(), toupper );
				}

				this->activationFct = tmpStr;

				cout << endl << "Quel parametre voulez-vous modifier? : ";
				break;
			}
		default:
			{
				cout <<"Veuillez entrer un chiffre de 0 -> 9 ou une lettre de a->h : ";
				break;
			}	
		}
	}
	cout << endl;

	// Sauvegarde les nouvelles donn�es dans le fichier "config.ini"
	this->WriteConfig();
}
/*-------------------------------------------------------------------------------------
*	Nom			:	WriteConfig
*	�cris par	:	Tomy Aumont
*
*	Description	:	�cris le fichier "config.ini" avc les param�tres actuels.
*------------------------------------------------------------------------------------*/
void ConfigFile::WriteConfig( void )
{
	ofstream ofsConfig("config.ini", ios::out );
	
	ofsConfig << "infoTrainPath = " << this->infoTrainPath << endl <<
				"infoTestPath = " << this->infoTestPath << endl <<
				"infoVCPath = " << this->infoVCPath << endl <<
				"nbBestData = " << this->nbBestData << endl <<
				"isSorted = " << this->sorted << endl <<
				"nbNeuroneIn = " << this->nbNeuroneIn << endl <<
				"nbHiddenLayers = " << this->nbHiddenLayers << endl <<
				"nbNeuroneHiddenLayers = " << this->nbNeuroneHiddenLayers << endl <<
				"nbNeuroneOut = " << this->nbNeuroneOut << endl <<
				"activationFct = " << this->activationFct << endl <<
				"learnMaxDelay = " << this->learnMaxDelay << endl <<
				"errorMargin = " << this->errorMargin << endl <<
				"initWeightMin = " << this->initWeightMin << endl <<
				"initWeightMax = " << this->initWeightMax << endl <<
				"learnRate = " << this->learnRate << endl <<
				"nbEpoch = " << this->nbEpoch << endl <<
				"normTheta = " << this->normTheta;

	ofsConfig.close();
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetInfoTestPath
*	�cris par	:	Tomy Aumont
*
*	Description	:	Assigne le chemin vers le fichier contenant la liste des fichiers
*					d'apprentissage.
*------------------------------------------------------------------------------------*/
void ConfigFile::SetInfoTrainPath( string path )
{
	this->infoTrainPath = path;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetInfoVCPath
*	�cris par	:	Tomy Aumont
*
*	Description	:	Assigne le chemin vers le fichier contenant la liste des fichiers
*					de validation crois�e.
*------------------------------------------------------------------------------------*/
void ConfigFile::SetInfoVCPath( string path )
{
	this->infoVCPath = path;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetInfoTestPath
*	�cris par	:	Tomy Aumont
*
*	Description	:	Assigne le chemin vers le fichier contenant la liste des fichiers
*					de test.
*------------------------------------------------------------------------------------*/
void ConfigFile::SetInfoTestPath( string path )
{
	this->infoTestPath = path;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetNbBestData
*	�cris par	:	Tomy Aumont
*
*	Description	:	Assigne une valeur (nbData) � nbBestData
*------------------------------------------------------------------------------------*/
void ConfigFile::SetNbBestData( int nbData )
{
	this->nbBestData = nbData;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetSorted
*	�cris par	:	Tomy Aumont
*
*	Description	:	Assigne une valeur (val) � Sorted
*------------------------------------------------------------------------------------*/
void ConfigFile::SetSorted( bool val )
{
	this->sorted = val;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetNbHiddenLayers
*	�cris par	:	Tomy Aumont
*
*	Description	:	Assigne une valeur (val) au nombre de couchees cachees du reseau
*------------------------------------------------------------------------------------*/
void ConfigFile::SetNbHiddenLayers( int val )
{
	this->nbHiddenLayers = val;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetNbNeuroneIn
*	�cris par	:	Tomy Aumont
*
*	Description	:	Assigne une valeur (val) au nombre de neurones compris dans la
*					couche d'entree du reseau
*------------------------------------------------------------------------------------*/
void ConfigFile::SetNbNeuroneIn( int val )
{
	this->nbNeuroneIn = val;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetNbNeuroneHiddenLayers
*	�cris par	:	Tomy Aumont
*
*	Description	:	Assigne une valeur (val) au nombre de neurones compris dans les
*					couches cachees du reseau
*------------------------------------------------------------------------------------*/
void ConfigFile::SetNbNeuroneHiddenLayers( int val )
{
	this->nbNeuroneHiddenLayers = val;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetNbNeuroneOut
*	�cris par	:	Tomy Aumont
*
*	Description	:	Assigne une valeur (val) au nombre de neurones compris dans la
*					couche de sortie du reseau
*------------------------------------------------------------------------------------*/
void ConfigFile::SetNbNeuroneOut( int val )
{
	this->nbNeuroneOut = val;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetActivationFct
*	�cris par	:	Tomy Aumont
*
*	Description	:	Assigne la focntion d'activation a utiliser dans le reseau
*------------------------------------------------------------------------------------*/
void ConfigFile::SetActivationFct( string fctName )
{
	this->activationFct = fctName;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetLearnMaxDelay
*	�cris par	:	Tomy Aumont
*
*	Description	:	Assigne le delai maximal a atteindre pour arreter l'apprentissage
*------------------------------------------------------------------------------------*/
void ConfigFile::SetLearnMaxDelay( int val )
{
	this->learnMaxDelay = val;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetErrorMargin
*	�cris par	:	Tomy Aumont
*
*	Description	:	Assigne la marge d'erreur a atteindre pour arreter l'apprentissage
*------------------------------------------------------------------------------------*/
void ConfigFile::SetErrorMargin( double val )
{
	this->errorMargin = val;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetInitWeightMin
*	�cris par	:	Tomy Aumont
*
*	Description	:	Assigne la limite minimale d'initialisation des poids
*------------------------------------------------------------------------------------*/
void ConfigFile::SetInitWeightMin( double val )
{
	this->initWeightMin = val;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetInitWeightMax
*	�cris par	:	Tomy Aumont
*
*	Description	:	Assigne la limite maximale d'initialisation des poids
*------------------------------------------------------------------------------------*/
void ConfigFile::SetInitWeightMax( double val )
{
	this->initWeightMax = val;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetLearnRate
*	�cris par	:	Tomy Aumont
*
*	Description	:	Assigne le taux d'apprentissage a utiliser
*------------------------------------------------------------------------------------*/
void ConfigFile::SetLearnRate( double val )
{
	this->learnRate = val;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetNbEpoch
*	�cris par	:	Tomy Aumont
*
*	Description	:	Assigne le nombre d'epoque maximal a faire lors de l'apprentissage
*------------------------------------------------------------------------------------*/
void ConfigFile::SetNbEpoch( int val )
{
	this->nbEpoch = val;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetNormTheta
*	�cris par	:	Tomy Aumont
*
*	Description	:	Assigne la valeur du parametre qui determine si le reseau fera la
*					normalisation des theta ou pas
*------------------------------------------------------------------------------------*/
void ConfigFile::SetNormTheta( int val )
{
	this->normTheta = val;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	getInfoTestPath
*	�cris par	:	Tomy Aumont
*
*	Description	:	R�cupere le chemin vers le fichier contenant la liste des fichiers
*					de test.
*------------------------------------------------------------------------------------*/
string ConfigFile::GetInfoTestPath()
{
	return this->infoTestPath;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	getInfoTrainPath
*	�cris par	:	Tomy Aumont
*
*	Description	:	R�cupere le chemin vers le fichier contenant la liste des fichiers
*					d'apprentissage.
*------------------------------------------------------------------------------------*/
string ConfigFile::GetInfoTrainPath()
{
	return this->infoTrainPath;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetInfoVCPath
*	�cris par	:	Tomy Aumont
*
*	Description	:	R�cupere le chemin vers le fichier contenant la liste des fichiers
*					de validation croisee.
*------------------------------------------------------------------------------------*/
string ConfigFile::GetInfoVCPath()
{
	return this->infoVCPath;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	getnbBestData
*	�cris par	:	Tomy Aumont
*
*	Description	:	R�cupere le nombre de donn�es par fichier qui sera utilis� comme
*					entr�e du r�seau de neurones.
*------------------------------------------------------------------------------------*/
int ConfigFile::GetNbBestData()
{
	return this->nbBestData;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	isSorted
*	�cris par	:	Tomy Aumont
*
*	Description	:	Retourne 1 si le classement � d�j� �t� fait, sinon retourne 0.
*------------------------------------------------------------------------------------*/
bool ConfigFile::GetSorted()
{
	return this->sorted;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetNbHiddenLayers
*	�cris par	:	Tomy Aumont
*
*	Description	:	Recupere le nombre de couches cachees voulu dans le reseau
*------------------------------------------------------------------------------------*/
int ConfigFile::GetNbHiddenLayers( void )
{
	return this->nbHiddenLayers;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetNbNeuroneIn
*	�cris par	:	Tomy Aumont
*
*	Description	:	Recupere le nombre de neurone voulu dans la couche d'entree
*------------------------------------------------------------------------------------*/
int ConfigFile::GetNbNeuroneIn( void )
{
	return this->nbNeuroneIn;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetNbNeuroneHiddenLayers
*	�cris par	:	Tomy Aumont
*
*	Description	:	Recupere le nombre de neurone voulu dans les couches cachees
*------------------------------------------------------------------------------------*/
int ConfigFile::GetNbNeuroneHiddenLayers( void )
{
	return this->nbNeuroneHiddenLayers;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetNbNeuroneOut
*	�cris par	:	Tomy Aumont
*
*	Description	:	Recupere le nombre de neurone compris dans la couche de sortie
*------------------------------------------------------------------------------------*/
int ConfigFile::GetNbNeuroneOut( void )
{
	return this->nbNeuroneOut;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetNbNeuroneOut
*	�cris par	:	Tomy Aumont
*
*	Description	:	Recupere le nombre de neurone compris dans la couche de sortie
*------------------------------------------------------------------------------------*/
string ConfigFile::GetActivationFct( void )
{
	return this->activationFct;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetLearnMaxDelay
*	�cris par	:	Tomy Aumont
*
*	Description	:	Recupere le delai maximal a atteindre pour arreter l'apprentissage
*------------------------------------------------------------------------------------*/
int ConfigFile::GetLearnMaxDelay( void )
{
	return this->learnMaxDelay;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetErrorMargin
*	�cris par	:	Tomy Aumont
*
*	Description	:	Recupere la marge d'erreur a atteindre pour arreter l'apprentissage
*------------------------------------------------------------------------------------*/
double ConfigFile::GetErrorMargin( void )
{
	return this->errorMargin;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetInitWeightMin
*	�cris par	:	Tomy Aumont
*
*	Description	:	Recupere la limite minimale d'initialisation des poids
*------------------------------------------------------------------------------------*/
double ConfigFile::GetInitWeightMin( void )
{
	return this->initWeightMin;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetInitWeightMax
*	�cris par	:	Tomy Aumont
*
*	Description	:	Recupere la limite maximale d'initialisation des poids
*------------------------------------------------------------------------------------*/
double ConfigFile::GetInitWeightMax( void )
{
	return this->initWeightMax;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetLearnRate
*	�cris par	:	Tomy Aumont
*
*	Description	:	Recupere le taux d'apprentissage a utiliser
*------------------------------------------------------------------------------------*/
double ConfigFile::GetLearnRate( void )
{
	return this->learnRate;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetNbEpoch
*	�cris par	:	Tomy Aumont
*
*	Description	:	Recupere le nombre d,epoque d'apprentissage maximal a faire
*------------------------------------------------------------------------------------*/
int ConfigFile::GetNbEpoch( void )
{
	return this->nbEpoch;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetNormTheta
*	�cris par	:	Tomy Aumont
*
*	Description	:	Recupere la valeur du parametre qui determine si le reseau fera la
*					normalisation des theta ou pas
*------------------------------------------------------------------------------------*/
int ConfigFile::GetNormTheta( void )
{
	return this->normTheta;
}
/*************************************************************************************/
/*							Fonctions de la classe Pathfile							 */
/*************************************************************************************/

/*-------------------------------------------------------------------------------------
*	Nom			:	PathFile
*	�cris par	:	Tomy Aumont
*
*	Description	:	Constructeur de la classe PathFile.
*------------------------------------------------------------------------------------*/
PathFile::PathFile( void )
{	}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetOwnPath
*	�cris par	:	Tomy Aumont
*
*	Description	:	Assigne le chemin vers lui-m�me � pathAndName
*------------------------------------------------------------------------------------*/
void PathFile::SetOwnPath( std::string path )
{
	this->pathAndName = path;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetFilePathAndName
*	�cris par	:	Tomy Aumont
*
*	Description	:	R�cupere le chemin vers la liste de fichier, incluant le nom et
*					l'extension de la liste.
*------------------------------------------------------------------------------------*/
std::string PathFile::GetPathFilePathAndName( void )
{
	return this->pathAndName;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	ParsePathFile
*	�cris par	:	Tomy Aumont
*
*	Description	:	Parse la liste de fichiers dans une structure
-------------------------------------------------------------------------------------*/
bool PathFile::Parse( bool load )
{
	stringstream ssTemp;
	fstream pathFile;

	pathFile.open( this->pathAndName, ios::in );
	if( pathFile.is_open() )
	{
		ssTemp << endl << "Parsing file: " << this->pathAndName;
		PrintDebugMessage( ssTemp.str() );

		PathData_s tmp_data;

		while( !pathFile.eof() )
		{
			if( !load )
				pathFile >> tmp_data.nbOfDataInPath;
			pathFile >> tmp_data.path;
			this->pathFileList.push_back(tmp_data);
		}
		pathFile.close();

		ssTemp.str( DBG_MSG_COMPLETE );
		PrintDebugMessage( ssTemp.str() );
		return EXIT_SUCCESS;
	}
	else
	{
		ssTemp << "\tError opening file : " << this->pathAndName;
		PrintDebugMessage( ssTemp.str() );
		return EXIT_FAILURE;
	}
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetPathX
*	�cris par	:	Tomy Aumont
*
*	Description	:	R�cupere le nombre de fichier dans la liste.
-------------------------------------------------------------------------------------*/
int PathFile::GetNumberOfPath( void )
{
	return this->pathFileList.size();
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetPathX
*	�cris par	:	Tomy Aumont
*
*	Description	:	R�cupere le chemin vers le fichier designer par 'index'. Le premier
*					index est 0.
-------------------------------------------------------------------------------------*/
string PathFile::GetPathX( int index )
{
	return this->pathFileList[index].path;
}
/*************************************************************************************/
/*							Fonctions de la classe FileInfo							 */
/*************************************************************************************/
/*-------------------------------------------------------------------------------------
*	Nom			:	FileInfo
*	�cris par	:	Tomy Aumont
*
*	Description	:	Constructeur de la classe FileInfo
-------------------------------------------------------------------------------------*/
FileInfo::FileInfo( void )
{	}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetFilePath
*	�cris par	:	Tomy Aumont
*
*	Description	:	Assigne le chemin vers le fichier � la variable filePath
-------------------------------------------------------------------------------------*/
void FileInfo::SetFilePath( std::string path )
{
	this->filePath = path;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetRawDataMatrix
*	�cris par	:	Tomy Aumont and Xavier Mercure-Gagnon
*
*	Description	:	Copie chacune des valeurs lues dans la matrice rawDataMatrix sous
*					le format d�cimal et non avec un exponnentielle comme � la lecture
-------------------------------------------------------------------------------------*/
bool FileInfo::SetRawDataMatrix( std::string path )
{
	fstream ifs;	

	ifs.open( path, ios::in );
	if( ifs.is_open() )
	{
		while( !ifs.eof() )
		{
			vector<double> vTemp;
			string sTotalTmp;
			string tmpExp;
			string tmpValue;
			double totalTmp;

			for (int i = 0; i < NB_ELEM_BY_RECORD; i++)
			{
				ifs >> sTotalTmp;
				// Convertis l'exponentiel en double
				tmpExp = sTotalTmp.substr( sTotalTmp.find("e") + 1, sTotalTmp.size() ); //Extraits l'exposant
				tmpValue = sTotalTmp.substr( 0, sTotalTmp.find("e") ); //Extrait mantisse
				if ( !tmpValue.empty() )
				{
					totalTmp = stod(tmpValue)* pow( 10.0, stod(tmpExp) ); //Calcul mantis*10^exposant
					vTemp.push_back( totalTmp ); //Met la donn�es format� dans un vecteur temporaire.
				}
			}
			if( !all_of(vTemp.begin(), vTemp.end(), [](int i) { return i ==0; }) )
				this->rawDataMatrix.push_back( vTemp );
		}
		ifs.close();
		return EXIT_SUCCESS;
	}
	else
	{
		std::stringstream ssTemp;
		ssTemp << "\tError while opening file : " << path;
		PrintDebugMessage( ssTemp.str() );
		return EXIT_FAILURE;
	}
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetFilePath
*	�cris par	:	Tomy Aumont
*
*	Description	:	R�cup�re le chemin vers le fichier
-------------------------------------------------------------------------------------*/
std::string FileInfo::GetFilePath( void )
{
	return this->filePath;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetFileName
*	�cris par	:	Tomy Aumont
*
*	Description	:	R�cup�re le nom et l'extension du fichier
-------------------------------------------------------------------------------------*/
std::string FileInfo::GetFileName( void )
{
	return this->fileName;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetSavePath
*	�cris par	:	Tomy Aumont
*
*	Description	:	R�cup�re le chemin vers le r�pertoire de sauvegarde du fichier
-------------------------------------------------------------------------------------*/
std::string FileInfo::GetSavePath( void )
{
	return this->savePath;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetSavePath
*	�cris par	:	Tomy Aumont
*
*	Description	:	Assigne le chemin vers l'endroit de sauvegarde du fichier � la
*					variable savePath
-------------------------------------------------------------------------------------*/
void FileInfo::SetSavePath( int nbElem )
{
	char buff[100];
	std::stringstream ssTempo;

	for( int i=0; i<10; i++ )
	{
		size_t copy_end = this->filePath.find_last_of( '\\' );
		if( string::npos != copy_end )
		{
			size_t copy_begin = this->filePath.find( "txt_dist" );
			int copy_length = ++copy_end - copy_begin;
			this->filePath.copy( buff, copy_length, copy_begin );
			buff[copy_length] = '\0';
			ssTempo << "Sorted_Files\\" << nbElem << "\\" << buff;
			this->savePath = ssTempo.str();
			
			ssTempo.str("");
		}
	}
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetFileName
*	�cris par	:	Tomy Aumont
*
*	Description	:	Assigne le nom du fichier et son extension � la variable fileName
-------------------------------------------------------------------------------------*/
void FileInfo::SetFileName( void )
{
	for( int i=0; i<10; i++ )
	{
		// Recupere tout ce qui se trouve apres le dernier backslash
		size_t tmp_pos = this->filePath.find_last_of( '\\' );
		if( string::npos != tmp_pos )
			this->fileName = this->filePath.substr( ++tmp_pos );
		// Si ce qui est recuperer commence par un 'o', le changer pour un '0'
		if( this->fileName[0] == 'o' || this->fileName[0] == 'O' )
			this->fileName[0] = '0';
	}
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetStaticEnergy
*	�cris par	:	Tomy Aumont
*
*	Description	:	R�cup�re l'�nergie statique de la donn�e d�sign�e par index.
*					Si l'index est plus grand que la grosseur du vecteur, retourne -1
-------------------------------------------------------------------------------------*/
double FileInfo::GetStaticEnergyX( int index )
{
	if( index <= rawDataMatrix.size() )
		return rawDataMatrix[index][STATIC_ENERGY_POSITION];
	else
		return ERROR;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetDynamicEnergy
*	�cris par	:	Tomy Aumont
*
*	Description	:	R�cup�re l'�nergie dynamique de la donn�e d�sign�e par index.
*					Si l'index est plus grand que la grosseur du vecteur, retourne -1
-------------------------------------------------------------------------------------*/
double FileInfo::GetDynamicEnergyX( int index )
{
	if( index <= rawDataMatrix.size() )
		return rawDataMatrix[index][DYNAMIC_ENERGY_POSITION];
	else
		return ERROR;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetRawDataY_X
*	�cris par	:	Tomy Aumont
*
*	Description	:	Retourne un pointeur vers la donn�e d�sign� par index
*					Si index est plus grand que la grosseur du vecteur, retourne NULL
-------------------------------------------------------------------------------------*/
vector<double>* FileInfo::GetRawDataX( int index )
{
	if( index <= rawDataMatrix.size() )
		return &rawDataMatrix[index];
	else
		return NULL;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetSize
*	�cris par	:	Tomy Aumont
*
*	Description	:	R�cup�re la taille de la matrice de donn�es brute
-------------------------------------------------------------------------------------*/
int FileInfo::GetRawMatrixSize( void )
{
	return this->rawDataMatrix.size();
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SortStaticEnergy
*	�cris par	:	Tomy Aumont
*
*	Description	:	Retourne 1 si l'�nergie statique du vecteur v1 est plus petite que
*					celle du vecteur v2
-------------------------------------------------------------------------------------*/
bool SortStaticEnergy( const std::vector<double>& v1, const std::vector<double>& v2 )
{
  return v1[STATIC_ENERGY_POSITION] < v2[STATIC_ENERGY_POSITION];
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SortDynamicEnergy
*	�cris par	:	Tomy Aumont
*
*	Description	:	Retourne 1 si l'�nergie dynamique du vecteur v1 est plus petite que
*					celle du vecteur v2
-------------------------------------------------------------------------------------*/
bool SortDynamicEnergy( const std::vector<double>& v1, const std::vector<double>& v2 )
{
	if( v1[STATIC_ENERGY_POSITION] == v2[STATIC_ENERGY_POSITION] )
		return v1[DYNAMIC_ENERGY_POSITION] < v2[DYNAMIC_ENERGY_POSITION];
	else
		return false;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SortMatrix
*	�cris par	:	Tomy Aumont
*
*	Description	:	R�arange la matrice de donn�es brute en ordre d�croissant de
*					l'�nergie statique, puis lorsque deux �nergie sont �gales, selon la
*					plus grande �nergie dynamique.
-------------------------------------------------------------------------------------*/
void FileInfo::SortMatrix( void )
{
	// R�arrange seloon l'�nergie statique de chaque donn�e
	std::sort( this->rawDataMatrix.begin(), this->rawDataMatrix.end(), SortStaticEnergy );
	// R�arrange seloon l'�nergie dynamique de chaque donn�e
	std::sort( this->rawDataMatrix.begin(), this->rawDataMatrix.end(), SortDynamicEnergy );
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SetBestData
*	�cris par	:	Tomy Aumont
*
*	Description	:	Pour les nbElem meilleures donnees a utiliser par fichier, rempli
*					un vecteur avec le 12 valeurs statique seulement de chaque donnees.
-------------------------------------------------------------------------------------*/
void FileInfo::SetBestData( int nbElem )
{
	for( int i=0; i < nbElem; i++ )
	{
		for ( int j=0; j<STATIC_ENERGY_POSITION; j++ )
			this->bestData.push_back( this->rawDataMatrix[i][j] );
	}
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetRawDataMatrix
*	�cris par	:	Tomy Aumont
*
*	Description	:	R�cup�re la matrice de donn�es brutes du fichier
-------------------------------------------------------------------------------------*/
vector<vector<double>> FileInfo::GetRawDataMatrix( void )
{
	return this->rawDataMatrix;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SaveSortedFile
*	�cris par	:	Tomy Aumont
*
*	Description	:	Sauvegarde la matrice de donn�es tri�es dans un fichier .txt
*					Inscrit le chemin vers ce fichier dans le fichier correspondant a
*					l'operation effectuee avec ce fichier soit info_test.txt pour un
*					fichier de test, info_train.txt pour un fichier d'entrainement et
*					info_vc.txt pour un fichier de validation croisee.
------------------------------------------------------------------------------------*/
bool FileInfo::SaveSortedFile( void )
{
	std::stringstream ssPath;  
	std::ofstream ofs;

	ssPath << this->GetSavePath() << this->GetFileName();

	/*	�cris toutes les donn�es de la matrice tri�e dans un fichier texte. Chaque
		donn�e est ecrite sur une seule ligne et s�par�e d'un espace.	*/
	ofs.open( ssPath.str(), std::ofstream::out );
	if ( ofs.is_open() )
	{
		for ( int i=0; i < this->bestData.size(); i++ )
		{
			if( i != 0 )
				ofs << " ";
			ofs << this->bestData[i];
		}
		ofs << std::endl;
		ofs.close();

		if( !this->WritePathToFileList( ssPath.str()) )
			return EXIT_SUCCESS;
		else
			return EXIT_FAILURE;
	}
	else
	{
		std::stringstream ssDebug;
		ssDebug << "\tCannot save files at path : " << ssPath.str();
		PrintDebugMessage( ssDebug.str() );
		return EXIT_FAILURE;
	}
}
/*-------------------------------------------------------------------------------------
*	Nom			:	WritePathToFileList
*	�cris par	:	Tomy Aumont
*
*	Description	:	Inscrit le chemin vers un fichier de donnees dans le fichier
*					correspondant a l'operation effectuee avec ce fichier, soit :
*					info_test.txt pour un fichier de test, info_train.txt pour un
*					fichier d'entrainement et info_vc.txt pour un fichier de validation
*					croisee.
-------------------------------------------------------------------------------------*/
bool FileInfo::WritePathToFileList( std::string savePath )
{
	std::ofstream ofs;
	std::string listFileName = "";
	std::stringstream ssDebug;
	
	if( savePath.npos != savePath.find("train") )
		listFileName = "info_train.txt";
	else if( savePath.npos != savePath.find("test") )
		listFileName = "info_test.txt";
	else if( savePath.npos != savePath.find("vc") )
		listFileName = "info_vc.txt";

	ofs.open( listFileName, std::ios::out | std::ios::app );

	if( ofs.is_open() )
	{
		ofs << savePath << std::endl;
		ofs.close();
		return EXIT_SUCCESS;
	}
	else
	{
		ssDebug << "Cannot open save path in : " << listFileName;
		PrintDebugMessage( ssDebug.str() );
		return EXIT_FAILURE;
	}
}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetBestData
*	�cris par	:	Tomy Aumont
*
*	Description	:	Recupere le vecteur de donnees triees
-------------------------------------------------------------------------------------*/
vector<double> FileInfo::GetBestData( void )
{
	return this->bestData;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	ReadBestData
*	�cris par	:	Tomy Aumont
*
*	Description	:	Lis le contenu d'un fichier a charger comme entree dans le reseau
-------------------------------------------------------------------------------------*/
bool FileInfo::ReadBestData( void )
{
	ifstream ifs;

	ifs.open( this->filePath, ios::in );
	if( ifs.is_open() )
	{
		while( !ifs.eof() )
		{
			double tmpData;

			ifs >> tmpData;
			if( ifs.eof() )
				break;
			this->bestData.push_back( tmpData );
		}
		return EXIT_SUCCESS;
	}
	else
		return EXIT_FAILURE;
}
/*************************************************************************************/
/*							Fonctions de la classe Inputfiles						 */
/*************************************************************************************/
/*-------------------------------------------------------------------------------------
*	Nom			:	InputFiles
*	�cris par	:	Tomy Aumont
*
*	Description	:	Constructeur de la classe InputFiles
-------------------------------------------------------------------------------------*/
InputFiles::InputFiles( void )
{	}
/*-------------------------------------------------------------------------------------
*	Nom			:	CreateSortedFiles
*	�cris par	:	Tomy Aumont
*
*	Description	:	Cr�e les fichier de donn�es tri�es ainsi que les fichiers qui
*					contiennent les chemins vers ces fichiers.
-------------------------------------------------------------------------------------*/
bool InputFiles::CreateSortedFiles( std::string pathFileName, int nbDataPerFile )
{
	PathFile fileOfPaths;


	fileOfPaths.SetOwnPath( pathFileName );

	if( fileOfPaths.Parse() )	// R�cup�re les chemins vers tout les fichiers � traiter
	{
		PrintDebugMessage( FAILURE );
		return EXIT_FAILURE;
	}

	// Cree la liste de fichier et de leur donnees
	if( this->CreateFileList(&fileOfPaths, nbDataPerFile) )
	{
		PrintDebugMessage( FAILURE );
		return EXIT_FAILURE;
	}

	// Trie les donnees de chaque fichier en ordre croissant d'energie
	if( this->SortBestInputData(nbDataPerFile) )
	{
		PrintDebugMessage( FAILURE );
		return EXIT_FAILURE;
	}

	// Sauvegarde les meilleures donnees de chaque fichier dans un fichier .txt
	if( this->SaveDataToTxt() )
	{
		PrintDebugMessage( FAILURE );
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	CreateFileList
*	�cris par	:	Tomy Aumont
*
*	Description	:	Cr�e la liste de fichiers � traiter � partir des chemins donn�es
*					lues. La liste contient les FileInfo assign� � chaque fichier.
-------------------------------------------------------------------------------------*/
bool InputFiles::CreateFileList( PathFile* paths, int nbElem )
{
	int nbPath = paths->GetNumberOfPath();
	stringstream ssTemp;

	ssTemp << "Importing the " << nbPath << " files...";
	PrintDebugMessage( ssTemp.str() );

	for( int i=0; i<nbPath; i++ )
	{
		FileInfo tmpData;

		tmpData.SetFilePath( paths->GetPathX(i) );
		tmpData.SetFileName();
		if( nbElem )
		{
			tmpData.SetSavePath( nbElem );
			if( tmpData.SetRawDataMatrix(tmpData.GetFilePath()) )
				return EXIT_FAILURE;
			else
				this->filesList.push_back( tmpData );
		}
		else
		{
			if( tmpData.ReadBestData() )
				return EXIT_FAILURE;
			else
				this->filesList.push_back( tmpData );
		}
	}
	PrintDebugMessage( DBG_MSG_COMPLETE );
	return EXIT_SUCCESS;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	InputFiles
*	�cris par	:	Tomy Aumont
*
*	Description	:	Cr�e l'architecture de r�pertoire de sauvegarde des fichiers de
*					donn�es tri�es.
*
*					Ecris le chemin vers le nouveau fichier cree dans le fichier
*					correspondant au type d'operation fait avec ce fichier, soit :
*					info_train.txt pour un fichier d'entrainement, info_test.txt pour
*					un fichier de test et info_vc.txt pour un fichier de validation
*					croisee.
-------------------------------------------------------------------------------------*/
void InputFiles::CreateDataBaseArchitecture( void )
{	
	std::stringstream ss1;
	char buff[100];


	for ( int i = 0; i < this->filesList.size(); i++ )
	{
		/*	Redirige le buffer 'stderr' dans un fichier bidon pour ne pas imprimer
			d'informations inutiles dans le terminal.	*/
		ss1 << "mkdir " << this->filesList[i].GetSavePath() << " 2> null.dump";
		//PrintDebugMessage( ss1.str() );
		system( ss1.str().c_str() );
		ss1.str( "" );
	}

	PrintDebugMessage( "\tCreation de l'architecture de sauvegarde terminee" );
}
/*-------------------------------------------------------------------------------------
*	Nom			:	SortBestInputData
*	�cris par	:	Tomy Aumont
*
*	Description	:	Tri les donn�e brutes de chaque fichier de la liste (filesList) et
*					assigne la matrice tri�e de chaque fichier.
-------------------------------------------------------------------------------------*/
bool InputFiles::SortBestInputData( int nbElem )
{
	PrintDebugMessage( "Sorting data..." );

	// Loop for all files
	for( int i=0; i < this->filesList.size(); i++ )
	{
		this->filesList[i].SortMatrix();
		this->filesList[i].SetBestData( nbElem );
	}
	PrintDebugMessage( DBG_MSG_COMPLETE );
	return EXIT_SUCCESS;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	OutputDataToTxt
*	�cris par	:	Tomy Aumont et Xavier Mercure-Gagnon
*
*	Description	:	Cr�e l'architecture de sauvegarde des fichier trait�s et
*					sauvegarde les fichiers trait�s dans leur r�pertoire respectif.
-------------------------------------------------------------------------------------*/
bool InputFiles::SaveDataToTxt( void )
{
	PrintDebugMessage( "Saving best data..." );

	this->CreateDataBaseArchitecture();

	// Sauvegarde chaque structure de fichier traitee dans un .txt
	for ( int i=0; i < this->filesList.size(); i++ )
	{
		if( this->filesList[i].SaveSortedFile() )
		{
			std::stringstream ssDebug;
			ssDebug << "Error saving file to : " << this->filesList[i].GetFilePath() <<
						this->filesList[i].GetFileName();

			PrintDebugMessage( ssDebug.str() );
			return EXIT_FAILURE;
		}
	}
	PrintDebugMessage( DBG_MSG_COMPLETE );
	return EXIT_SUCCESS;
}
/*-------------------------------------------------------------------------------------
*	Nom			:	LoadSortedFiles
*	�cris par	:	Xavier Mecure-Gagnon
*
*	Description	:	R�cup�re les fichiers � traiter � partir d'une liste d�j� cr��e.
*					La liste contient les chemins vers les fichiers contenant les
*					donn�es d�j� class�es.
-------------------------------------------------------------------------------------*/
bool InputFiles::LoadSortedFiles( char* pathFileName )
{

	PathFile fileOfPaths;

	fileOfPaths.SetOwnPath( pathFileName );

	// R�cup�re les chemins vers tout les fichiers � traiter
	if ( fileOfPaths.Parse(PARSE_LOAD) )
	{
		PrintDebugMessage(FAILURE);
		return EXIT_FAILURE;
	}

	// Cree la liste de fichier et de leur donnees
	if ( this->CreateFileList(&fileOfPaths) )
	{
		PrintDebugMessage(FAILURE);
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;

}
/*-------------------------------------------------------------------------------------
*	Nom			:	GetFileList
*	�cris par	:	Tomy Aumont
*
*	Description	:	Recupere le vecteur de fichier
-------------------------------------------------------------------------------------*/
vector<FileInfo> InputFiles::GetFileList( void )
{
	return this->filesList;
}

