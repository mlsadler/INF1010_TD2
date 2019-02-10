/*
* Titre : Table.cpp - Travail Pratique #2
* Date : 18 Janvier 2019
* Auteur : Allan BEDDOUK
*/

#include "Table.h"

//constructeurs

/****************************************************************************
  * Description: Constructeur par default
  * in:
  * out:
  * in \ out:
  ****************************************************************************/
Table::Table() {
	id_ = -1;
	nbPlaces_ = 1;
	nbClientsATable_ = 0;
}

/****************************************************************************
 * Description: Constructeur avec parametre
 * in: id et nbPlaces
 * out:
 * in \ out:
 ****************************************************************************/
Table::Table(int id, int nbPlaces) {
	id_ = id;
	nbPlaces_ = nbPlaces;
	nbClientsATable_ = 0;
}

//getters

/****************************************************************************
 * Description: Fonction qui retourne le id de la table
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
int Table::getId() const {
	return id_;
}

/****************************************************************************
 * Description: Fonction qui retourne le nombre de place que la table offre
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
int Table::getNbPlaces() const {
	return nbPlaces_;
}

/****************************************************************************
 * Description: Fonction qui retourne le nombre de clients à la table
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
int Table::getnbClientATable() const
{
	return nbClientsATable_;
}

/****************************************************************************
 * Description: Fonction qui retourne si la table est pleine ou non avec le nombre de places restant soit 0
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
bool Table::estPleine() const {
	return nbPlaces_==0;
}

/****************************************************************************
 * Description: Fonction qui retourne si la table est occupee ou non
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
bool Table::estOccupee() const
{
	return nbClientsATable_!=0;
}

//setters

/****************************************************************************
 * Description: Fonction qui met le id a une valeur voulu
 * in: id
 * out:
 * in \ out:
 ****************************************************************************/
void Table::setId(int id) {
	id_ = id;
}

/****************************************************************************
 * Description: Fonction qui effacera les commandes de la table et la rendera valide pour de nouveau client
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
void Table::libererTable() {
	nbPlaces_ += nbClientsATable_;
	nbClientsATable_ = 0;
	commande_.clear();
	
}

/****************************************************************************
 * Description: Fonction qui rend la table occcupee
 * in: nbClients
 * out:
 * in \ out:
 ****************************************************************************/
void Table::placerClient(int nbClients) {
	nbClientsATable_ = nbClients;
	nbPlaces_ -= nbClients;
}

//autres methodes

/****************************************************************************
 * Description: Fonction qui recoit un plat et qui la place dans une liste de plat commander pour une table
 * in: Plat
 * out:
 * in \ out:
 ****************************************************************************/
void Table::commander(Plat* plat) {
	commande_.push_back(plat);
}

/****************************************************************************
 * Description: Fonction qui calcul le chiffre d'affaire
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
double Table::getChiffreAffaire() const {
	double chiffre = 0;
	for (int i = 0; i < commande_.size(); i++) {
		chiffre += (commande_[i]->getPrix() - commande_[i]->getCout());
	}
	return chiffre;
}

//affichage

/****************************************************************************
 * Description: Fonction qui assigne a l'operateur << a une fonction d'affichage d'une table
 * in: table
 * out:
 * in \ out: o
 ****************************************************************************/
ostream& operator<<(ostream& o, const Table& table)
{
	o << "La table numero " << table.id_;
	if (table.estOccupee()) {
		o << " est occupee. ";
		if (table.commande_.size() != 0) {
			cout << "Voici la commande passee par les clients : " << endl;
			for (int i = 0; i < table.commande_.size(); i++) {
				o << "\t" << *table.commande_[i];
			}
		}
		else
			o << "Mais ils n'ont rien conmmande pour l'instant. " << endl;
	}
	else {
		o << " est libre. " << endl;
	}
	return o;

}