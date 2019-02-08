/*
* Titre : Restaurant.cpp - Travail Pratique #2
* Date : 18 Janvier 2019
* Auteur : Allan BEDDOUK
*/

#include "Restaurant.h"

//constructeurs
Restaurant::Restaurant() {
	nom_ = new string("Inconnu");

	chiffreAffaire_ = 0;

	momentJournee_ = Matin;

	menuMatin_ = new Menu("menu.txt", Matin);
	menuMidi_ = new Menu("menu.txt", Midi);
	menuSoir_ = new Menu("menu.txt",  Soir);

	////capaciteTables_ = INTTABLES;
	/////nbTables_ = tables_.size();
	//////tables_ = new Table*[capaciteTables_];


}

Restaurant::Restaurant(const string& fichier,  const string& nom, TypeMenu moment) {
	nom_ = new string(nom);

	chiffreAffaire_ = 0;

	momentJournee_ = moment;

	menuMatin_ = new Menu(fichier, Matin);
	menuMidi_ = new Menu(fichier,  Midi);
	menuSoir_ = new Menu(fichier,  Soir);


	///////capaciteTables_ = INTTABLES;
	///////nbTables_ = tables_.size();
	////////tables_ = new Table*[capaciteTables_];

	lireTable(fichier);
}

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
Restaurant::~Restaurant() {
	delete nom_;
	delete menuMatin_;
	delete menuMidi_;
	delete menuSoir_;

	//A MODIFIER
	for (int i = 0; i < tables_.size(); i++)
		delete tables_[i];
		///delete tables_[i];
	////delete[] tables_;////??????????
}


//setter

void Restaurant::setMoment(TypeMenu moment) {
	momentJournee_ = moment;
}
//getters
string Restaurant::getNom() const {
	return *nom_;
}

TypeMenu Restaurant::getMoment() const {
	return momentJournee_;
}

//autres methodes


void Restaurant::libererTable(int id) {
	for (int i = 0; i < tables_.size(); i++) {
		if (id == tables_[i]->getId()) {
			chiffreAffaire_ += tables_[i]->getChiffreAffaire();
			tables_[i]->libererTable();
		}
	}
}
/*/
void Restaurant::afficher() const {
	cout << "Le restaurant " << *nom_;
	if (chiffreAffaire_ != 0)
		cout << " a fait un chiffre d'affaire de : " << chiffreAffaire_ << "$" << endl;
	else
		cout << " n'a pas fait de benefice ou le chiffre n'est pas encore calcule." << endl;
	cout << "-Voici les tables : " << endl;
	for (int i = 0; i < nbTables_; i++) {
		cout << "\t" << tables_[i];
		cout << endl;
	}
	cout << endl;


	cout << "-Voici son menu : " << endl;
	cout << "Matin : " << menuMatin_ << endl;

	cout << "Midi : " << menuMidi_ << endl;
	
	cout << "Soir : " << menuSoir_ << endl;
	
}
*/

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

/*
void Restaurant::ajouterTable(int id, int nbPlaces) {
	// A MODIFIER
	/*
	if (nbTables_ == capaciteTables_) {
		capaciteTables_ *= 2;
		Table** temp = new Table*[capaciteTables_];

		for (int i = 0; i < nbTables_; i++) {
			temp[i] = tables_[i];
		}

		delete[] tables_;
		tables_ = temp;

	}

	tables_[nbTables_] = new Table(id, nbPlaces);
	nbTables_++;
	
	tables_.push_back(id, nbPlaces);/////pas sur qu on peut en mettre 2
}
*/

void Restaurant::operator+=(const Table& table)
{
	return tables_.push_back(new Table(table));
}

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
	//delete restaurant.nom_;
	//delete restaurant.momentJournee_;
	//delete restaurant;

	return *this;
}

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

bool Restaurant::operator<(const Restaurant& restaurant) {
	if (chiffreAffaire_ < restaurant.chiffreAffaire_) {
		return true;
	}
	else {
		return false;
	}

}

void Restaurant::setNom(string nom) {

	*nom_ = nom;
}

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
