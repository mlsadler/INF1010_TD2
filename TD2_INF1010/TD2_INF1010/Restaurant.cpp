/*
* Titre : Restaurant.cpp - Travail Pratique #2
* Date : 18 Janvier 2019
* Auteur : Allan BEDDOUK
*/

#include "Restaurant.h"

//constructeurs

/****************************************************************************
 * Description: Constructeur par default
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
Restaurant::Restaurant() {
	nom_ = new string("Inconnu");

	chiffreAffaire_ = 0;

	momentJournee_ = Matin;

	menuMatin_ = new Menu("menu.txt", Matin);
	menuMidi_ = new Menu("menu.txt", Midi);
	menuSoir_ = new Menu("menu.txt",  Soir);
}

/***************************************************************************
 * Description: Constucteur avec l'aide de parametre
 * in: fichier, nom et moment
 * out:
 * in \ out:
 ****************************************************************************/
Restaurant::Restaurant(const string& fichier,  const string& nom, TypeMenu moment) {
	nom_ = new string(nom);

	chiffreAffaire_ = 0;

	momentJournee_ = moment;

	menuMatin_ = new Menu(fichier, Matin);
	menuMidi_ = new Menu(fichier,  Midi);
	menuSoir_ = new Menu(fichier,  Soir);

	lireTable(fichier);
}

/***************************************************************************
 * Description: Constucteur de copie
 * in: restaurantCopie
 * out:
 * in \ out:
 ****************************************************************************/
Restaurant::Restaurant(const Restaurant& restaurantCopie)
{
	nom_ = new string(*(restaurantCopie.nom_));
	menuMatin_ = new Menu(*(restaurantCopie.menuMatin_));
	menuMidi_ = new Menu(*(restaurantCopie.menuMidi_));
	menuSoir_ = new Menu(*(restaurantCopie.menuSoir_));
	chiffreAffaire_ = restaurantCopie.chiffreAffaire_;
	momentJournee_ = restaurantCopie.momentJournee_;
	
	for (int i = 0; i < restaurantCopie.tables_.size(); i++){
		Table* tablePtr = new Table(*restaurantCopie.tables_[i]);
		tables_.push_back(tablePtr);
	}
		
}

//destructeur


/***************************************************************************
 * Description: Destructeur de la classe Restaurant
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
Restaurant::~Restaurant() {
	delete nom_;
	delete menuMatin_;
	delete menuMidi_;
	delete menuSoir_;
}


//setter

/***************************************************************************
 * Description: Fonction qui set la variable au moment voulu
 * in: moment
 * out:
 * in \ out:
 ****************************************************************************/
void Restaurant::setMoment(TypeMenu moment) {
	momentJournee_ = moment;
}
//getters

/***************************************************************************
 * Description: Fonction qui retourne le nomdu restaurant
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
string Restaurant::getNom() const {
	return *nom_;
}

/***************************************************************************
 * Description: Fonction qui retourne le moment de la journee
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
TypeMenu Restaurant::getMoment() const {
	return momentJournee_;
}

//autres methodes

/***************************************************************************
 * Description: Fonction qui libere un table et calcul le chiffre d'affaire
 * in: id
 * out:
 * in \ out:
 ****************************************************************************/
void Restaurant::libererTable(int id) {
	for (int i = 0; i < tables_.size(); i++) {
		if (id == tables_[i]->getId()) {
			chiffreAffaire_ += tables_[i]->getChiffreAffaire();
			tables_[i]->libererTable();
		}
	}
}

/***************************************************************************
 * Description: Fonction pour commander des plats
 * in: nom et idTable
 * out:
 * in \ out:
 ****************************************************************************/
void Restaurant::commanderPlat(const string& nom, int idTable) {
	Plat* plat = nullptr;
	int index;
	for (int i = 0; i < tables_.size(); i++) {
		if (idTable == tables_[i]->getId()) {
			index = i;
			switch (momentJournee_) {
			case Matin :
				plat = menuMatin_->trouverPlat(nom);
				break;
			case Midi :
				plat = menuMidi_->trouverPlat(nom);
				break;
			case Soir :
				plat = menuSoir_->trouverPlat(nom);
				break;
			}
		}
	}
	if (plat != nullptr && tables_[index]->estOccupee()) {
		tables_[index]->commander(plat);
	}
	else cout << "Erreur : table non occupee ou plat introuvable" << endl;
}

/***************************************************************************
 * Description: Fonction qui lira le document et cree un variable table
 * in: fichier
 * out:
 * in \ out:
 ****************************************************************************/
void Restaurant::lireTable(const string& fichier) {
	ifstream file(fichier, ios::in);

	if (file) {
		string ligne;

		string idString;
		int id;

		string nbPersonnesString;
		int nbPersonnes;

		int curseur;
		while (!file.eof()) {
			getline(file, ligne);
			if (ligne == "-TABLES") {
				while (!file.eof()) {
					getline(file, ligne);
					for (int i = 0; i < ligne.size(); i++) {
						if (ligne[i] == ' ') {
							curseur = i;
							break;
						}
						idString += ligne[i];
					}

					id = stoi(idString);

					nbPersonnesString = ligne.substr(curseur + 1);
					nbPersonnes = stoi(nbPersonnesString);

					//ajouter
					Table table = Table(id, nbPersonnes);
					*this += table;
					nbPersonnesString = "";
					idString = "";
				}
			}
		}
		file.close();
	}
}

/****************************************************************************
 * Description: Fonction qui assigne a l'operateur += a une fonction pour ajouter une table
 * in: table
 * out:
 * in \ out:
 ****************************************************************************/
void Restaurant::operator+=(const Table& table)
{
	return tables_.push_back(new Table(table));
}

/****************************************************************************
 * Description: Fonction qui assigne a l'operateur = a une fonction qui permet de copier les attributs d'un restaurant a un autre
 * in: menu
 * out:
 * in \ out:
 ****************************************************************************/
Restaurant& Restaurant::operator= (const Restaurant& restaurant)
{
	if (this != &restaurant){
		delete nom_;
		nom_ = new string(*(restaurant.nom_));
		delete menuMatin_;
		menuMatin_ = new Menu(*(restaurant.menuMatin_));
		delete menuMidi_;
		menuMidi_ = new Menu(*(restaurant.menuMidi_));
		delete menuSoir_;
		menuSoir_ = new Menu(*(restaurant.menuSoir_));
		chiffreAffaire_ = restaurant.chiffreAffaire_;
		momentJournee_ = restaurant.momentJournee_;
		tables_.clear();
		for (int i = 0; i < restaurant.tables_.size(); i++) 
			tables_.push_back(restaurant.tables_[i]);
		

	}

	return *this;
}

/****************************************************************************
 * Description: Fonction qui assigne a l'operateur << a une fonction d'affichage d'un restaurant
 * in: restaurant
 * out:
 * in \ out: o
 ****************************************************************************/
ostream& operator<< (ostream& o, const Restaurant& restaurant){

	o << "Le restaurant " << *restaurant.nom_;
	if (restaurant.chiffreAffaire_ != 0)
		o << " a fait un chiffre d'affaire de : " << restaurant.chiffreAffaire_ << "$" << endl;
	else
		o << " n'a pas fait de benefice ou le chiffre n'est pas encore calcule." << endl;
	o << "-Voici les tables : " << endl;
	for (int i = 0; i < restaurant.tables_.size(); i++) {
		cout << "\t" << *restaurant.tables_[i];
		cout << endl;
	}
	cout << endl;


	o << "-Voici son menu : " << endl;
	o << "Matin : " << *restaurant.menuMatin_ << endl;

	o << "Midi : " << *restaurant.menuMidi_ << endl;

	o << "Soir : " << *restaurant.menuSoir_ << endl;

	return o;
}

/****************************************************************************
 * Description: Fonction qui assigne a l'operateur < une fonction de comparaison entre 2 chiffres d'affaire de restaurants
 * in: restaurant
 * out:
 * in \ out:
 ****************************************************************************/
bool Restaurant::operator<(const Restaurant& restaurant) {
	if (chiffreAffaire_ < restaurant.chiffreAffaire_) {
		return true;
	}
	else {
		return false;
	}

}

/***************************************************************************
 * Description: Fonction qui set la variable au nom voulue
 * in: nom
 * out:
 * in \ out:
 ****************************************************************************/
void Restaurant::setNom(string nom) {

	*nom_ = nom;
}

/***************************************************************************
 * Description: Fonction pour placer les clients a une table
 * in: nbClients
 * out:
 * in \ out:
 ****************************************************************************/
void Restaurant::placerClients(int nbClients) {
	int indexTable = -1;
	int minimum = 100;


	for (int i = 0; i < tables_.size(); i++) {
		if (tables_[i]->getNbPlaces() >= nbClients && !tables_[i]->estOccupee() && tables_[i]->getNbPlaces() < minimum) {
			indexTable = i;
			minimum = tables_[i]->getNbPlaces();
		}
	}
	if (indexTable == -1) {
		cout << "Erreur : il n'y a plus/pas de table disponible pour le client. " << endl;
	}else
	tables_[indexTable]->placerClient(nbClients);
}
