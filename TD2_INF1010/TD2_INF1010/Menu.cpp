/*
* Titre : Menu.cpp - Travail Pratique #2
* Date : 18 Janvier 2019
* Auteur : Allan BEDDOUK
*/

#include "Menu.h"

//constructeurs

/****************************************************************************
  * Description: Constructeur par default
  * in:
  * out:
  * in \ out:
  ****************************************************************************/

Menu::Menu() {
	type_ = Matin;
}

/****************************************************************************
  * Description: Constructeur avec parametre
  * in: fichier et type
  * out:
  * in \ out:
  ****************************************************************************/
Menu::Menu(string fichier, TypeMenu type) {
	type_ = type;

	//lecture du fichier -- creation du menu
	lireMenu(fichier);
}

/****************************************************************************
  * Description: Constructeur de copie
  * in: menu
  * out:
  * in \ out:
  ****************************************************************************/
Menu::Menu(const Menu& menu) {
	
	for (int i = 0; i < menu.listePlats_.size(); i++) {
		Plat* platPtr = new Plat(*menu.listePlats_[i]);
		listePlats_.push_back(platPtr);
	}
		
	type_ = menu.type_;
	
}
//destructeur

/****************************************************************************
  * Description: Destructeur de menu
  * in:
  * out:
  * in \ out:
  ****************************************************************************/
Menu::~Menu() {
	// A MODIFIER
	for (int i = 0; i < listePlats_.size(); i++)
		delete listePlats_[i];
}

//getters

/****************************************************************************
  * Description: Retourne le nombre de plats dans la liste
  * in:
  * out:
  * in \ out:
  ****************************************************************************/
int Menu::getNbPlats() const {
	return listePlats_.size();
}

/****************************************************************************
  * Description: Retourne la listePlats_
  * in:
  * out:
  * in \ out:
  ****************************************************************************/
vector<Plat*> Menu::getListePlats(){
	return listePlats_;
}

//autres methodes

/****************************************************************************
 * Description: Fonction qui assigne a l'operateur << a une fonction d'affichage d'un menu
 * in: menu
 * out:
 * in \ out: o
 ****************************************************************************/
ostream& operator<<(ostream& o, const Menu& menu)
{
	for (int i = 0; i < menu.listePlats_.size(); i++) {
		o << "\t" << *menu.listePlats_[i];
	}
	return o;
}

/****************************************************************************
 * Description: Fonction qui assigne a l'operateur += a une fonction pour ajouter un plat a un menu
 * in: plat
 * out:
 * in \ out:
 ****************************************************************************/
Menu& Menu::operator+=(const Plat& plat) {
	Plat* platPtr = new Plat(plat);
	listePlats_.push_back(platPtr);
	return *this;
}

/****************************************************************************
 * Description: Fonction qui assigne a l'operateur = a une fonction qui permet de copier les attributs d'un menu a un autre
 * in: menu
 * out:
 * in \ out:
 ****************************************************************************/
Menu& Menu::operator=(const Menu& menu) {

	if (this != &menu) {
		listePlats_.clear();
		for (int i = 0; i < menu.listePlats_.size(); i++)
			listePlats_.push_back(menu.listePlats_[i]);
		
		type_ = menu.type_;
	}

	return *this;
}

/****************************************************************************
  * Description: Fonction qui le lit un fichier et cree un menu
  * in: fichier
  * out:
  * in \ out:
  ****************************************************************************/
bool Menu::lireMenu(const string& fichier) {
	ifstream file(fichier, ios::in);

	if (!file) {
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

/****************************************************************************
  * Description: Fonction qui trouve le un plat le moins cher dans une liste de plat
  * in:
  * out:
  * in \ out:
  ****************************************************************************/
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

/****************************************************************************
  * Description: Fonction qui trouve le un plat avec l'aide d'un nom dans la liste et retourne le pointeur du plat
  * in: nom
  * out:
  * in \ out:
  ****************************************************************************/
Plat* Menu::trouverPlat(const string& nom) const {
	for (int i = 0; i < listePlats_.size(); i++) {
		if (listePlats_[i]->getNom() == nom)
			return listePlats_[i];
	}
	return nullptr;
}
