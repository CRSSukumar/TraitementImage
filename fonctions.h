#ifndef _FONCTIONS_H_
#define _FONCTIONS_H_

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

const vector<string> IMAGES = {"Ara_ararauna.ppm", "Couleur.ppm", "Flowerbed-large.ppm", "Flowerbed-small.ppm", "Mandel.ppm", "Procyon_lotor.ppm"};

const int FONCTIONS = 10;

///un vécteur qui va nous permettre d'afficher les fonctionnalitées proposées
const vector<string> MENU = {"[1] composanteRouge", "[2] niveauxGris", "[3] noirEtBlanc",
                            "[4] luminosityUp", "[5] luminosityDown", "[6] constrastUp", "[7] constrastDown", "[8] visionDeuteranopie",
                            "[9] visionProtanopie", "[10] visionTritanopie","[11] rognerD","[12] rognerG","[13] rognerH","[14] rognerB",
                            "[15] rotationD","[16] rotationG","[17] retournementH","[18] retournementV","[19] agrandissement",
                            "[20] retrecissement","[21] flou"};

class Image {

  vector<vector<int>> _rouge;
  vector<vector<int>> _vert;
  vector<vector<int>> _bleu;
  int _longueur;
  int _largeur;

public:

  //Images
  Image();
  Image(vector<vector<int>>, vector<vector<int>>, vector<vector<int>>);
  Image(string&);

  // Getters
  vector<vector<int>> getRouge() const;
  vector<vector<int>> getVert() const;
  vector<vector<int>> getBleu() const;
  int getLongueur() const;
  int getLargeur() const;

  // Fonctions
  void display() const;
  Image composanteRouge()const;
  bool detection(int, int, int) const;
  Image niveauxGris()const;
  Image noirEtBlanc(int) const;
  vector<int> histogrammeGris() const;
  Image luminosityUp()const;
  Image luminosityDown()const;
  Image contrasteUp()const;
  Image contrasteDown()const;
  Image visionDeuteranopie()const;
  Image visionProtanopie()const;
  Image visionTritanopie()const;
  void toppm(const string&) const;
  Image rognerD(int) const;
  Image rognerG(int) const;
  Image rognerH(int) const;
  Image rognerB(int) const;
  Image rotationD() const;
  Image rotationG() const;
  Image retournementH() const;
  Image retournementV() const;
  Image agrandissement(int) const;
  Image retrecissement(int) const;
};

//Operateurs
bool operator==(Image, Image);

//MENU FICHIERS
string saisirNomImage(const vector<string>&);
void afficherFonctions(const vector<string>&);
int saisirFonction();
Image appliquerFonction(const Image&, int);
void loadPicture(string &, vector<vector<int>> &, vector<vector<int>> &, vector <vector<int>> &);
void menu();

#endif
