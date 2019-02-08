/*
* Titre : Menu.h - Travail Pratique #2
* Date : 18 Janvier 2019
* Auteur : Allan BEDDOUK
*/

#ifndef MENU_H
#define MENU_H

#include "Plat.h"
#include <fstream>

enum TypeMenu{Matin, Midi, Soir};
const int MAXPLAT = 5;
class Menu {
public:
	// constructeurs
	Menu();
	Menu(string fichier, TypeMenu type);
	Menu(const Menu& menu);

	//destructeur
	~Menu();

	//getters
	int getNbPlats() const;
	vector<Plat*> getListePlats();
	//affichage
	//////////void afficher() const; //A MODIFIER
	friend ostream& operator<<(ostream& o, const Menu& menu);

	//methodes en plus
	Plat* trouverPlat(const string& nom) const; // A MODIFIER
	Plat * trouverPlatMoinsCher() const; // Utilise les vecteurs (NE PAS MODIFIER)
	//////////////void ajouterPlat(const Plat & plat); // A MODIFIER
	Menu& operator+=(const Plat& plat);
	Menu& operator=(const Menu& menu);
	bool lireMenu(const string& fichier);

private :
	// A MODIFIER
	//////int capacite_;
	vector <Plat*> listePlats_;
	/////int nbPlats_;
	TypeMenu type_;

};

#endif // !MENU_H
