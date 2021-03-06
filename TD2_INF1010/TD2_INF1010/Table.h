/*
* Titre : Table.h - Travail Pratique #2
* Date : 11 Fevrier 2019
* Auteur : Allan BEDDOUK
* Modifier par : Mark Weber-Sadler (1947609) et Felix Dumont (1954787)
*/

#ifndef TABLE_H
#define TABLE_H

#include "Plat.h"

const  int MAXCAP = 5;
class Table {
public:
	///constructeurs
	Table();
	Table(int id, int nbPlaces);

	///destructeur
	~Table();

	///getters
	int getId() const;
	int getNbPlaces() const;
	int getnbClientATable() const;
	bool estPleine() const;
	bool estOccupee() const;

	///setters
	void libererTable(); // A MODIFIER
	void placerClient(int nbClients);
	void setId(int id);

	///autres methodes
	void commander(Plat* plat); // A MODIFIER
	double getChiffreAffaire() const;

	///affichage
	friend ostream& operator<<(ostream& o, const Table& table);

private :
	//A MODIFIER
	vector <Plat*> commande_;
	int id_;
	int nbPlaces_;
	int nbClientsATable_;
};
#endif // !TABLE_H
