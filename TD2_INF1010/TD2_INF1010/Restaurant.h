/*
* Titre : Restaurant.h - Travail Pratique #2
* Date : 18 Janvier 2019
* Auteur : Allan BEDDOUK
*/

#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "Table.h"
#include "Menu.h"
const int INTTABLES = 6;
class Restaurant {
public:
	//constructeurs
	Restaurant();
	Restaurant(const string& fichier, const string& nom,  TypeMenu moment);
	Restaurant(const Restaurant& restaurantCopie);
	

	//destructeur
	~Restaurant();

	//setters
	void setMoment(TypeMenu moment);

	//getters
	string getNom() const;
	TypeMenu getMoment() const;

	//Autres methodes
	void lireTable(const string& fichier);
	void operator+=(const Table& table);
	void libererTable(int id);
	Restaurant& operator= (const Restaurant& restaurant);
	void commanderPlat(const string& nom, int idTable); 
	friend ostream& operator<< (ostream& o, const Restaurant& restaurant);
	bool operator<(const Restaurant& restaurant);
	void setNom(string nom);

	void placerClients(int nbClients);

private:
	string* nom_;

	double chiffreAffaire_;
	TypeMenu momentJournee_;

	//differents menus en fonction du moment de la journee
	Menu* menuMatin_;
	Menu* menuMidi_;
	Menu* menuSoir_;

	//liste des tables
	vector <Table*> tables_;
};
#endif // !RESTAURANT_H
