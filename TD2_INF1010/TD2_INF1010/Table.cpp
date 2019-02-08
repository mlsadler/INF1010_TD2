/*
* Titre : Table.cpp - Travail Pratique #2
* Date : 18 Janvier 2019
* Auteur : Allan BEDDOUK
*/

#include "Table.h"

//constructeurs
Table::Table() {
	///////////capacite_ = MAXCAP;
	//////////commande_ = new Plat*[MAXCAP];
	nbPlats_ = commande_.size();
	id_ = -1;
	nbPlaces_ = 1;
	nbClientsATable_ = 0;
}

Table::Table(int id, int nbPlaces) {
	//////////////capacite_ = MAXCAP;
	/////////////commande_ = new Plat*[capacite_];
	nbPlats_ = commande_.size();
	id_ = id;
	nbPlaces_ = nbPlaces;
	nbClientsATable_ = 0;
}

//destructeur
Table::~Table() {
	//A MODIFIER
	delete[] commande_; ////encore une fois pas sur de destruction dun vecteur
	for (int i = 0; i < nbPlats_; i++) {
		commande_.pop_back();
		////??????
	}
}

//getters
int Table::getId() const {
	return id_;
}

int Table::getNbPlaces() const {
	return nbPlaces_;
}

int Table::getnbClientATable() const
{
	return nbClientsATable_;
}

bool Table::estPleine() const {
	return nbPlaces_==0;
}

bool Table::estOccupee() const
{
	return nbClientsATable_!=0;
}

//setters
void Table::setId(int id) {
	id_ = id;
}

void Table::libererTable() {
	nbPlaces_ += nbClientsATable_;
	nbClientsATable_ = 0;
	//A MODIFIER
	
	for (int i = 0; i < nbPlats_; i++) {
		//commande_[i] = nullptr;
		commande_.pop_back(); //je sais pas si ca va fuck up le for nbPlat (v.size()) pasque lui aussi va modifié quand on va pop bak
	}
	
	nbPlats_ = 0;  ////utile??
	
}

void Table::placerClient(int nbClients) {
	nbClientsATable_ = nbClients;
	nbPlaces_ -= nbClients;
}

//autres methodes
void Table::commander(Plat* plat) {
	// A MODIFIER
	/*
	if (nbPlats_ == capacite_) {
		capacite_ *= 2;
		Plat** temp = new Plat*[capacite_];
		for (int i = 0; i < nbPlats_; i++) {
			temp[i] = commande_[i];
		}

		delete[] commande_;
		commande_ = temp;
	}

	commande_[nbPlats_] = plat;
	nbPlats_++;
	*/
	commande_.push_back(plat);
}

double Table::getChiffreAffaire() const {
	double chiffre = 0;
	for (int i = 0; i < nbPlats_; i++) {
		chiffre += (commande_[i]->getPrix() - commande_[i]->getCout());
	}
	return chiffre;
}

//affichage
void Table::afficher() const {
	cout << "La table numero " << id_;
	if (estOccupee()) {
		cout << " est occupee. ";
		if (nbPlats_ != 0) {
			cout << "Voici la commande passee par les clients : " << endl;
			for (int i = 0; i < nbPlats_; i++) {
				cout << "\t";
				commande_[i]->afficher();
			}
		}
		else
			cout << "Mais ils n'ont rien conmmande pour l'instant. " << endl;
	}
	else {
		cout << " est libre. " << endl;
	}
}
