/*
* Titre : Plat.cpp - Travail Pratique #2
* Date : 18 Janvier 2019
* Auteur : Allan BEDDOUK
* Modifier par : Mark Weber-Sadler (1947609) et Felix Dumont (1954787)
*/

#include "Plat.h"

//constructeurs

 /****************************************************************************
 * Description: Constructeur par default
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
Plat::Plat() {
	nom_ = "Inconnu";
	prix_ = 0;
	cout_ = 0;
}

/****************************************************************************
 * Description: Constructeur par parametre
 * in: nom, prix et cout
 * out:
 * in \ out:
 ****************************************************************************/
Plat::Plat(string nom, double prix, double cout) {
	nom_ = nom;
	prix_ = prix;
	cout_ = cout;
}
//getters

/****************************************************************************
 * Description: Fonction qui retourne le nom du plat
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
string Plat::getNom() const {
	return nom_;
}

/****************************************************************************
 * Description Fonction qui retourne le prix du plat
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
double Plat::getPrix() const {
	return prix_;
}

/****************************************************************************
 * Description: Fonction qui retourne le prix
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
double Plat::getCout() const {
	return cout_;
}
//setters

/****************************************************************************
 * Description: Fonction qui met le nom du plat a un nom voulu
 * in: nom
 * out:
 * in \ out:
 ****************************************************************************/
void Plat::setNom(string nom) {
	nom_ = nom;
}

/****************************************************************************
 * Description: Fonction qui met le prix a un prix voulu
 * in: prix
 * out:
 * in \ out:
 ****************************************************************************/
void Plat::setPrix(double prix) {
	prix_ = prix;
}


//methodes en plus

/****************************************************************************
 * Description: Fonction qui assigne a l'operateur < une fonction de comparaison entre 2 prix de plat
 * in: plat
 * out:
 * in \ out:
 ****************************************************************************/
bool Plat::operator<(const Plat& plat)
{
	if (prix_ < plat.prix_)
		return true;
	else
		return false;
}

/****************************************************************************
 * Description: Fonction qui assigne a l'operateur << a

 une fonction d'affichage d'un plat
 * in: plat
 * out:
 * in \ out: o
 ****************************************************************************/
ostream& operator<<(ostream& o, const Plat& plat)
{
	return o << plat.nom_ << " - " << plat.prix_ << " $ (" << plat.cout_ << "$ pour le restaurant)" << endl;
}