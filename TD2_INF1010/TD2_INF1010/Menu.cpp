/*
* Titre : Menu.cpp - Travail Pratique #2
* Date : 18 Janvier 2019
* Auteur : Allan BEDDOUK
*/

#include "Menu.h"

//constructeurs

Menu::Menu() {
	/////////capacite_ = MAXPLAT;
	/////////listePlats_ = new Plat*[capacite_];

	//////////nbPlats_ = listePlats_.size(); ///
	type_ = Matin;
}

Menu::Menu(string fichier, TypeMenu type) {
	//////////capacite_ = MAXPLAT;
	//////////listePlats_ = new Plat*[capacite_];
	/////////nbPlats_ = listePlats_.size(); ////
	type_ = type;

	//lecture du fichier -- creation du menu
	lireMenu(fichier);
}

Menu::Menu(const Menu& menu) {
	
	for (int i = 0; i < menu.listePlats_.size(); i++) {
		Plat* platPtr = new Plat(*menu.listePlats_[i]);
		listePlats_.push_back(platPtr);
	}
		
	type_ = menu.type_;
	
}
//destructeur
Menu::~Menu() {
	// A MODIFIER
	for (int i = 0; i < listePlats_.size(); i++)
		delete listePlats_[i];
	/////////delete[] listePlats_; /////pas sur si faut delete vector
}

//getters

int Menu::getNbPlats() const {
	return listePlats_.size();
}

vector<Plat*> Menu::getListePlats(){
	return listePlats_;
}

//autres methodes
ostream& operator<<(ostream& o, const Menu& menu)
{
	for (int i = 0; i < menu.listePlats_.size(); i++) {
		o << "\t" << *menu.listePlats_[i];
	}
	return o;
}

/*
void Menu::afficher() const {

	for (int i = 0; i < listePlats_.size(); i++) {
		cout << "\t" << listePlats_[i];

	}
}


void Menu::ajouterPlat(const Plat &  plat) {
	// A MODIFIER

	
	if (nbPlats_ == capacite_) {
		if (capacite_ == 0) {
			capacite_ = 1;
			delete[] listePlats_;
			listePlats_ = new Plat*[1];

		}
		else {
			capacite_ *= 2;
			Plat** listeTemp = new Plat*[capacite_];
			for (int i = 0; i < nbPlats_; i++) {
				listeTemp[i] = listePlats_[i];
			}

			delete[] listePlats_;
			listePlats_ = listeTemp;

		}
	}
	
	listePlats_[nbPlats_] = new Plat(plat);
	
	///////////////listePlats_.push_back(plat);
	////nbPlats_++;
}
*/

Menu& Menu::operator+=(const Plat& plat) {
	Plat* platPtr = new Plat(plat);
	listePlats_.push_back(platPtr);
	return *this;
}

Menu& Menu::operator=(const Menu& menu) {

	if (this != &menu) {
		listePlats_.clear();
		for (int i = 0; i < menu.listePlats_.size(); i++)
			listePlats_.push_back(menu.listePlats_[i]);
		
		type_ = menu.type_;
	}

	return *this;
}

bool Menu::lireMenu(const string& fichier) {
	ifstream file(fichier, ios::in);

	if (!file) {
		//cout << "ERREUR : le fichier n'a pas pu etre ouvert" << endl;
		return false;
	}
	else {
		string type;
		switch (type_) {
		case Matin :
			type = "-MATIN";
			break;
		case Midi :
			type = "-MIDI";
			break;
		case Soir :
			type = "-SOIR";
			break;
		}
		string ligne;

		string nom;

		string prixString;
		double prix;

		string coutString;
		int cout;


		// lecture
		while (!file.eof()) {
			getline(file, ligne);
			//trouver le bon type de menu (section)
			if (ligne == type){
				//commencer a lire -- s'arrete si fin du fichier ou encore si on arrive a une nouvelle section du menu
				getline(file, ligne);
				int curseur;
				while (ligne[0] != '-' && !file.eof()) {
					//trouver le nom
					for (int i = 0; i < int(ligne.size()); i++) {
						if (ligne[i] == ' ') {
							curseur = i;
							break;
						}
						nom += ligne[i];
					}
					//trouver le prix

					for (int i = curseur + 1; i < int(ligne.size()); i++) {
						if (ligne[i] == ' ') {
							curseur = i;
							break;
						}
						prixString += ligne[i];

					}
					//passer le prixString en double --- indice dans l'enonce
					prix = stof(prixString.c_str());

					for (int i = curseur + 1; i < int(ligne.size()); i++) {
						if (ligne[i] == ' ')
							break;
						coutString += ligne[i];
					}

					cout =int( stof(coutString.c_str()));

					
					*this+= Plat(nom, prix, cout);
					nom = "";
					prixString = "";
					coutString = "";

					getline(file, ligne);
				}
			}
		}

		file.close();
		return true;
	}
}

Plat * Menu::trouverPlatMoinsCher() const
{
	Plat minimum(*listePlats_[0]);
	int found = -1;

	for (unsigned i = 0; i < listePlats_.size(); ++i)
	{
		if (*listePlats_[i] < minimum)
		{
			minimum = *listePlats_[i];
			found = i;
		}
	}

	return listePlats_[found];

}

Plat* Menu::trouverPlat(const string& nom) const {
	for (int i = 0; i < listePlats_.size(); i++) {
		if (listePlats_[i]->getNom() == nom)
			return listePlats_[i];
	}
	return nullptr;
}
