/*
* Titre : main.cpp - Travail Pratique #1
* Date : 18 Janvier 2019 
* Auteur : Allan BEDDOUK
*/

#include "Restaurant.h"

using namespace std; 

/*
R�ponse aux questions:
		1. L'utilit� de l'op�rateur = et du constructeur par copie est  d'assign� 
		   les attributs d'un objet a un autre objet de la m�me classe.
		2. La diff�rence entre les deux est que l'op�rateur = sert � assign� les 
		   attributs d'un objet � un autre qui existe d�j�, tandis que le constructeur 
		   par copie sert � initialiser un nouvel objet de la meme classe avec les 
		   m�mes attributs de l'autre objet
*/

int main() {

	//creation du restaurant 
	Restaurant poly("polyFood.txt", "PolyFood", Soir); 

	///creer plusieurs clients 
	int nbclient1 = 1; 
	int nbclient2 = 5; 
	int nbclient3 = 15; 
	int nbclient4 = 3; 
	int nbclient5 = 2; 


	//placer les clients 
	poly.placerClients(nbclient1);
	poly.placerClients(nbclient2);
	poly.placerClients(nbclient3); 
	poly.placerClients(nbclient4); 
	poly.placerClients(nbclient5); 

	// commander des plats 
	poly.commanderPlat("Poisson", 1);
	poly.commanderPlat("Poulet", 2);
	poly.commanderPlat("Pizza", 2); 
	poly.commanderPlat("Poulet", 4); 
	poly.commanderPlat("Muffin", 4); 
	poly.commanderPlat("Oeuf", 4); 


	//Creation d'une copie du poly restaurant 
	Restaurant poly2(poly);
	poly2.setNom("PolyFood2");

	//Affichage du restaurant poly 
	cout << poly;

	cout << "--------------------------------------------------------------------------------------------------" << endl; 


	//liberer les tables et calcule du chiffre d'affaire
	poly.libererTable(1);
	poly.libererTable(2);
	poly.libererTable(3);
	poly.libererTable(4);

	cout << poly;

	cout << "====================================================================================================" << endl;

	// Le restaurant Poly2 ne doit pas encore avoir liberer ses tables
	cout << poly2;

	poly2 = poly;
	

	cout << "--------------------------------------------------------------------------------------------------" << endl;
	// Le restaurant Poly2 doit maintenant avoir toutes ses tables lib�r�es
	cout << poly2;
	return 0;
}