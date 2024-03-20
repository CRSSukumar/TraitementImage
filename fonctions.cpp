#include "fonctions.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <xmath.h>
#include "filtre.h"

using namespace std;

/// constructor vide
Image::Image() {
  cout << "::::::: Constructeur Image VIDE :::::::" << endl;
  _longueur = 0;
  _largeur = 0;
}

/// constructor, verifie si les 3 vectors ont la meme taille, puis etabli les valeurs respectives
Image::Image(vector<vector<int>> r, vector<vector<int>> v,
             vector<vector<int>> b) {

  if (r.size() != v.size() || r.size() != b.size() || v.size() != b.size() ||
      r[0].size() != v[0].size() || r[0].size() != b[0].size() ||
      v[0].size() != b[0].size()) {
    throw invalid_argument("The vectors must have the same size");
  };

  _rouge = r;
  _vert = v;
  _bleu = b;
  _longueur = r.size();
  _largeur = r[0].size();
}

///constructor, à partir d'un fichier ppm
Image::Image(string& nomFichier)
{
    loadPicture(nomFichier, _rouge, _vert, _bleu);
    _longueur = _rouge.size();
    _largeur = _rouge[0].size();
}

/// affiche les codes RGB de chaqu'un des 3 vecteurs
void Image::display() const {
  cout << ":: RED Vector ::" << endl;
  for (int i = 0; i < _longueur; i++) {
    for (int j = 0; j < _largeur; j++) {
      cout << _rouge[i][j] << "\t";
    };
    cout << "\n";
  }
  cout << endl;

  cout << ":: GREEN Vector ::" << endl;
  for (int i = 0; i < _longueur; i++) {
    for (int j = 0; j < _largeur; j++) {
      cout << _vert[i][j] << "\t";
    };
    cout << "\n";
  }
  cout << endl;

  cout << ":: BLUE Vector ::" << endl;
  for (int i = 0; i < _longueur; i++) {
    for (int j = 0; j < _largeur; j++) {
      cout << _bleu[i][j] << "\t";
    };
    cout << "\n";
  }
}

/// cree une NOUVELLE composante (rouge) à partir de "Image"
Image Image::composanteRouge() const{

  // mettre _vert et _bleu tout a 0 (une seule boucle car ils ont la même taille)
  Image img(_rouge, _vert, _bleu);
  for (int i = 0; i < img._longueur; i++) {
    for (int j = 0; j < img._largeur; j++) {
      img._vert[i][j] = 0;
      img._bleu[i][j] = 0;
    };
  }
  return img;
}

/// cree une NOUVELLE composante (gris) à partir de "Image"
Image Image::niveauxGris() const{

  int moy; // code gris = r, g et b de la meme valeur (faire la moyenne des 3 pour avoir le bon niveau de gris)
  Image img(_rouge, _vert, _bleu);

  for (int i = 0; i < img._longueur; i++) {
    for (int j = 0; j < img._largeur; j++) {
      moy = (img._rouge[i][j] + img._bleu[i][j] + img._vert[i][j]) / 3;
      img._rouge[i][j] = moy;
      img._bleu[i][j] = moy;
      img._vert[i][j] = moy;
    };
  }
  return img;
}

/// cherche si un pixel d'une tel couleur existe dans l'image
bool Image::detection(int r, int g, int b) const {

  for (int i = 0; i < _longueur; i++) {
    for (int j = 0; j < _largeur; j++) {
      if (_rouge[i][j] == r && _vert[i][j] == g && _bleu[i][j] == b) {
        return true; // return vrai si les valeurs respectives sont égales
      }
    };
  }
  return false;
}

/// une méthode noirEtBlanc de la classe Image permettant de créer une nouvelle image à partir de l’image cible dont chaque pixel est ou noir, ou blanc
Image Image::noirEtBlanc( int seuil) const{
    Image inb(_rouge, _vert, _bleu);
    inb = inb.niveauxGris();
    for (int i=0; i < _longueur; i++){
        for (int j=0; j < _largeur; j++){
            if(seuil > inb._vert[i][j]){
                inb._vert[i][j]=0;
                inb._bleu[i][j]=0;
                inb._rouge[i][j]=0;
            }
            else{
                inb._vert[i][j]=255;
                inb._bleu[i][j]=255;
                inb._rouge[i][j]=255;
            }
        }
    }
    return inb;
}

/// une méthode histogrammeGris retournant un vecteur d’entiers représentant l’histogramme de l’image en niveau de gris
vector<int> Image::histogrammeGris() const{
    Image Ihg(_rouge, _vert, _bleu);
    Ihg = Ihg.niveauxGris();
    vector<int> HG(256,0);
    int index;
    for(int i=0;i<_longueur;i++){
        for(int j=0;j<_largeur;j++){
            index=Ihg._vert[i][j];
            HG[index]++;
        }
    }
    return HG;
}
///méthodes luminosityUp de la classe Image permettant de créer une nouvelle image à partir de l’image cible dont la luminosité a été augmentée
Image Image::luminosityUp()const
{
    float x;
    do{
        cout<<"\n Enter a number bigger than 1: ";
        cin>>x;
    }while(x<1);
    Image img(_rouge, _vert, _bleu);

    for (int i = 0; i < _longueur; i++)
    {
        for (int j = 0; j < _largeur; j++)
        {
            floor(img._rouge[i][j] *= x);
            floor(img._vert[i][j] *= x);
            floor(img._bleu[i][j] *= x);
            if (img._rouge[i][j] > 255) img._rouge[i][j] = 255;
            if (img._vert[i][j] > 255) img._vert[i][j] = 255;
            if (img._bleu[i][j] > 255) img._bleu[i][j] = 255;
        }
    }

    return img;
}
///méthodes luminosityDown de la classe Image permettant de créer une nouvelle image à partir de l’image cible dont la luminosité a été diminuée
Image Image::luminosityDown()const
{
    float x;
    do{
        cout<<"\nEnter a number smaller than 1: ";
        cin>>x;
    }while(x>1);

    Image img(_rouge, _vert, _bleu);

    for (int i = 0; i < _longueur; i++)
    {
        for (int j = 0; j < _largeur; j++)
        {
            floor(img._rouge[i][j] *= x);
            floor(img._vert[i][j] *= x);
            floor(img._bleu[i][j] *= x);
        }
    }

    return img;
}
///méthodes contrasteUp de la classe Image permettant de créer une nouvelle image à partir de l’image cible dont le contraste a été augmenté
Image Image::contrasteUp()const
{
    float x;
    do{
        cout<<"\nEnter a number bigger than 1: ";
        cin>>x;
    }while(x<1);

    Image img(_rouge, _vert, _bleu);


    for (int i = 0; i < _longueur; i++)
    {
        for (int j = 0; j < _largeur; j++)
        {
            img._rouge[i][j] = (img._rouge[i][j] - 128)*x + img._rouge[i][j];
            img._vert[i][j] = (img._vert[i][j] -128)*x + img._vert[i][j];
            img._bleu[i][j] = (img._bleu[i][j] -128)*x + img._bleu[i][j];

            if (img._rouge[i][j] > 255) img._rouge[i][j] = 255;
            if (img._vert[i][j] > 255) img._vert[i][j] = 255;
            if (img._bleu[i][j] > 255) img._bleu[i][j] = 255;

            if (img._rouge[i][j] < 0) img._rouge[i][j] = 0;
            if (img._vert[i][j] < 0) img._vert[i][j] = 0;
            if (img._bleu[i][j] < 0) img._bleu[i][j] = 0;
        }
    }

    return img;
}

///méthodes contrasteDown de la classe Image permettant de créer une nouvelle image à partir de l’image cible dont le contraste a été diminué
Image Image::contrasteDown()const
{
    float x;
    do {
        cout << "Enter a number smaller than 1: ";
        cin >> x;
    } while (x >= 1);

    Image img(_rouge, _vert, _bleu);

    for (int i = 0; i < _longueur; i++)
    {
        for (int j = 0; j < _largeur; j++)
        {
            img._rouge[i][j] = (img._rouge[i][j] - 128)*x + 128;
            img._vert[i][j] = (img._vert[i][j] -128)*x + 128;
            img._bleu[i][j] = (img._bleu[i][j] -128)*x + 128;
        }
    }

    return img;
}
///méthodes visionDeuteranopie de la classe Image permettant de se rendre compte de ce que voient les gens atteints de Deuteranopie
Image Image::visionDeuteranopie()const{

    Image img(_rouge, _vert, _bleu);
    for (int i = 0; i < img._longueur; i++) {
      for (int j = 0; j < img._largeur; j++) {
       // img._vert[i][j] = 0;
  img._vert[i][j] = int(0.567 * _rouge[i][j] + 0.433 * _bleu[i][j]);
      };
    }
    return img;
  }


///méthodes visionProtanopie de la classe Image permettant de se rendre compte de ce que voient les gens atteints de Protanopie
Image Image::visionProtanopie()const{

  Image img(_rouge, _vert, _bleu);
  for (int i = 0; i < img._longueur; i++) {
    for (int j = 0; j < img._largeur; j++) {
     // img._rouge[i][j] = 0;
  img._rouge[i][j] = int(0.621 * _vert[i][j] + 0.379 * _bleu[i][j]);
    };
  }
  return img;
}

///méthodes visionTritanopie de la classe Image permettant de se rendre compte de ce que voient les gens atteints de Tritanopie
Image Image::visionTritanopie()const{

  Image img(_rouge, _vert, _bleu);
  for (int i = 0; i < img._longueur; i++) {
    for (int j = 0; j < img._largeur; j++) {
     // img._bleu[i][j] = 0;
  img._bleu[i][j] = int(0.95 * _rouge[i][j] + 0.05 * _vert[i][j]);
    };
  }
  return img;
}

//MENU FICHIERS
///pour saisir le nom du fichier et le retourne avec "images/"
string saisirNomImage(const vector<string>& IMAGES)
{
    string image;

    cout<<":::::::: FICHIERS IMAGES EXISTANTS ::::::::::"<<endl;
    for (int i = 0; i<IMAGES.size(); i++)
    {
        cout<<IMAGES[i]<<"\n";
    }
    cout<<":::::::::::::::::::::::::::::::::::::::::::::\n"<<endl;

    cout<<"\nChoisir Fichier .PPM : "; cin>>image;
    image = "images/" + image;
    cout<<"\nCHARGEMENT...\n";
    return image;
}

///pour afficher les fonctions.
void afficherFonctions(const vector<string>& MENU)
{
    cout<<":::::::::::: OPTIONS LOGICIEL :::::::::::::::"<<endl;
    for (int i = 0; i<MENU.size(); i++)
    {
        cout<<MENU[i]<<"\n";
    }
    cout<<":::::::::::::::::::::::::::::::::::::::::::::\n"<<endl;
}
///Pour saisir la fonction et retourner le choix
int saisirFonction()
{
    int choix;
    cout<<"\nEntrer le nombre de l'option correspendante(999 pour sortir): "; cin>>choix;

    return choix;
}

void loadPicture(string &picture, vector<vector<int>> &red,
                                        vector<vector<int>> &green,
                                        vector <vector<int>> &blue)
{
    string line; // pour recuperer les lignes du fichier image au format .ppm, qui est code en ASCII.
    string format; //pour recuperer le format de l'image : celui-ci doit être de la forme P3
    //string name; // au cas où l'utilisateur se trompe dans le nom de l'image a charger, on redemande le nom.
    int taille;
    vector <int> mypixels; // pour recuperer les donnees du fichier de maniere lineaire. On repartira ensuite ces donnees dans les tableaux correspondants
    ifstream entree; // Declaration d'un "flux" qui permettra ensuite de lire les donnees de l'image.
    int hauteur;
    //name = picture;
    entree.open(picture);
    while (!entree){
        //cin.rdbuf(oldbuf);
        cerr << "\n[ERROR] Impossible de lire de fichier " << picture << " ! " << endl;
        cerr << "[ATTENTION] Redonnez le nom du fichier. Ce fichier doit avoir un nom du type nom.ppm :" << endl;
        cin >> picture;
        picture = "images/" + picture;
        entree.open(picture); // relance
    }
    entree >> format;
    getline(entree, line);
    getline(entree, line);
    entree >> taille >> hauteur;
    getline(entree, line);
    while (format != "P3"){
        if (format != "P3"){
            cerr << "Erreur! L'image que vous nous avez donnee a un format ne verifiant pas les conditions requises." << endl;
            cerr << "L'image que vous nous avez donnee doit etre codee en ASCII et non en brut." << endl;
        }
  entree.close();
        do{
            cerr << "Veuillez redonner un nom de fichier qui respecte les conditions de format et de taille. Attention, ce nom doit etre de la forme nom.ppm." << endl;
            cin >> picture;
            entree.open(picture); // relance
        }while(!entree);
         entree >> format;
         getline(entree, line); // on finit de lire la ligne (caractere d'espacement)
        getline(entree, line);
        entree >> taille >> hauteur; // relance
        getline(entree, line); // on finit de lire la ligne (caractere d'espacement)
    }
    getline(entree, line);
    int pix;
    mypixels.resize(3*taille*hauteur); // taille fixe : on alloue une fois pour toutes
    for (int i = 0; i < 3*taille*hauteur; i++){
      entree >> pix;
      mypixels[i]=pix;
    }
    int val;
    red.resize(hauteur);
    green.resize(hauteur);
    blue.resize(hauteur);
    for (int i = 0; i < hauteur; i++){
      vector <int> ligneR(taille);
      vector <int> ligneB(taille);  // les lignes ont toutes la même taille
      vector <int> ligneG(taille);
      for (int j = 0; j < taille; j++){
            val =  mypixels[3*j + 3*taille*i];
            ligneR[j]=val;
            val = mypixels[3*j + 1 + 3*taille*i];
            ligneG[j]=val;
            val = mypixels[3*j + 2 + 3*taille*i];
            ligneB[j]=val;
        }
        red[i]=ligneR;
        green[i]=ligneG;
        blue[i]=ligneB;
    }
    cout << "[REUSSI] L'image " << picture << " a bien ete chargee dans les tableaux.\n" << endl;
     entree.close();
 }
///un switch qui applique la fonctions du choix demandé sur l'image et la retourne
Image appliquerFonction(const Image& imga, int choix)
{
    Image imgn = imga;
    int nb;
    int facteur;
    int seuil;
    switch(choix)
    {
    case 1:
        imgn = imga.composanteRouge();
        break;
    case 2:
        imgn = imga.niveauxGris();
        break;
    case 3:
        cout << "Donnez le seuil: ";
        cin >> seuil;
        imgn = imga.noirEtBlanc(seuil);
        break;
    case 4:
        imgn = imga.luminosityUp();
        break;
    case 5:
        imgn = imga.luminosityDown();
        break;
    case 6:
        imgn = imga.contrasteUp();
        break;
    case 7:
        imgn = imga.contrasteDown();
        break;
    case 8:
        imgn = imga.visionDeuteranopie();
        break;
    case 9:
        imgn = imga.visionProtanopie();
        break;
    case 10:
        imgn = imga.visionTritanopie();
        break;
    case 11:
        cout << "Donnez un nombre: ";
        cin >> nb;
        imgn= imga.rognerD(nb);
        break;
    case 12:
        cout << "Donnez un nombre: ";
        cin >> nb;
        imgn= imga.rognerG(nb);
        break;
    case 13:
        cout << "Donnez un nombre: ";
        cin >> nb;
        imgn = imga.rognerH(nb);
        break;
    case 14:
        cout << "Donnez un nombre: ";
        cin >> nb;
        imgn = imga.rognerB(nb);
        break;
    case 15:
        imgn = imga.rotationD();
        break;
    case 16:
        imgn = imga.rotationG();
        break;
    case 17:
        imgn = imga.retournementH();
        break;
    case 18:
        imgn = imga.retournementV();
        break;
    case 19:
        cout << "Donnez un facteur: ";
        cin >> facteur;
        imgn = imga.agrandissement(facteur);
        break;
    case 20:
        cout << "Donnez un facteur: ";
        cin >> facteur;
        imgn = imga.retrecissement(facteur);
        break;
    case 21:
    vector<vector<float>> fG3 = {{1/16.0, 1/8.0, 1/16.0},
                               {1/8.0, 1/4.0, 1/8.0},
                               {1/16.0, 1/8.0, 1/16.0}};
    Filtre flouG3(fG3);
    imgn = flouG3.application(imga);
    break;

    return imgn;
    }
}

///la métode que va permettre de choisir les fonctions et les appliquer sur image creé
void menu(){

    string nomf = saisirNomImage(IMAGES);
    Image img(nomf);
    int choix;
    afficherFonctions(MENU);
    while(choix!=999){
        choix=saisirFonction();
        img = appliquerFonction(img,choix);
    }
    img.toppm(nomf);
}


///metode pour creer une image ppm a partir de l'image de base
void Image::toppm(const string& nomf) const
{
    string nfichier = nomf;
    ofstream ecrit;
    for (int i = 0; i < 4; i++)
        nfichier.pop_back();
    nfichier = nfichier + "(1).ppm";
    ecrit.open(nfichier);

    ecrit<<"P3\n";
    ecrit<<"#"<<nfichier<<"\n";
    ecrit<<_largeur<<" "<<_longueur<<"\n";
    ecrit<<"255\n";
    for(int i=0; i<_longueur;i++){
        for(int j=0; j<_largeur;j++){
            ecrit<<_rouge[i][j]<<" "<<_vert[i][j]<<" "<<_bleu[i][j]<<"\n";
        }
    }
    ecrit.close();
}
///méthodes rognerD de la classe image permettant de créer une nouvelle image à partir de l’image cible qui supprime nb des colonnes de pixel de l’image respectivement à droite, où nb est un entier passé en paramètre
Image Image::rognerD(int nb) const {

    if (nb <= 0 || nb >= _largeur) {
        cout << "Rogner impossible: NB invalide" << endl;
        return Image(_rouge, _vert, _bleu);
    }
    Image img(_rouge, _vert, _bleu);
    for (int i = 0; i < _longueur; i++) {
        for (int j = 0; j < nb; j++) {
            img._vert[i].pop_back();
            img._bleu[i].pop_back();
            img._rouge[i].pop_back();
        }
    }
    img._largeur=img._largeur-nb;
    return img;
}

///méthodes rognerG de la classe image permettant de créer une nouvelle image à partir de l’image cible qui supprime nb des colonnes de pixel de l’image où respectivement à gauche, où nb est un entier passé en paramètre

Image Image::rognerG(int nb) const{
    if (nb <= 0 || nb >= _longueur)
    {
        cout << "Rogner impossible: NB invalide" << endl;
        return Image(_rouge, _vert, _bleu);
    }
    vector<vector<int>> vert(_longueur);
    vector<vector<int>> bleu(_longueur);
    vector<vector<int>> rouge(_longueur);
    for(int i=0; i<_longueur; i++){
        for(int j=nb; j<_largeur; j++){
            vert[i].push_back(_vert[i][j]);
            bleu[i].push_back(_bleu[i][j]);
            rouge[i].push_back(_rouge[i][j]);
        }
    }
    Image img(rouge, vert, bleu);
    return img;
}
///méthodes rognerH de la classe image permettant de créer une nouvelle image à partir de l’image cible qui supprime nb des lignes de pixel de l’image où respectivement en haut,où nb est un entier passé en paramètre

Image Image::rognerH(int nb) const{
    if (nb <= 0 || nb >= _longueur)
    {
        cout << "Rogner impossible: NB invalide" << endl;
        return Image(_rouge, _vert, _bleu);
    }
    vector<vector<int>> vert(0);
    vector<vector<int>> bleu(0);
    vector<vector<int>> rouge(0);
    for(int i=nb; i<_longueur; i++){
        vert.push_back(_vert[i]);
        bleu.push_back(_bleu[i]);
        rouge.push_back(_rouge[i]);

    }
    Image img(rouge, vert, bleu);
    return img;
}
///méthodes rognerB de la classe image permettant de créer une nouvelle image à partir de l’image cible qui supprime nb des lignes de pixel de l’image où respectivement en bas, où nb est un entier passé en paramètre

Image Image::rognerB(int nb) const {
    if (nb <= 0 || nb >= _longueur) {
        cout << "Rogner impossible: NB invalide" << endl;
        return Image(_rouge, _vert, _bleu);
    }
    Image img(_rouge, _vert, _bleu);
    for (int j = 0; j < _largeur; j++) {
        for (int i = _longueur; i < nb; i--) {
            img._vert[i].pop_back();
            img._bleu[i].pop_back();
            img._rouge[i].pop_back();
        }
    }
    img._longueur=img._longueur-nb;
    return img;
}

///méthode rotationD de la classe Image permettant de créer une nouvelle image à partir de l’image cible qui effectue une rotation de l’image de 90° vers la droite
Image Image::rotationD() const{
    vector<vector<int>> vert(_longueur);
    vector<vector<int>> bleu(_longueur);
    vector<vector<int>> rouge(_longueur);
    Image img(rouge, vert, bleu);
    img._largeur = _longueur;
    for (int j=0; j < _largeur; j++){
        for (int i=_longueur-1; i>=0; i--){
            img._vert[j].push_back(_vert[i][j]);
            img._bleu[j].push_back(_bleu[i][j]);
            img._rouge[j].push_back(_rouge[i][j]);
        }
    }
    return img;
}


///méthode rotationG de la classe Image permettant de créer une nouvelle image à partir de l’image cible qui effectue une rotation de l’image de 90° vers la gauche

Image Image::rotationG() const{
    vector<vector<int>> vert(_longueur);
    vector<vector<int>> bleu(_longueur);
    vector<vector<int>> rouge(_longueur);
    Image img(rouge, vert, bleu);
    img._largeur = _largeur;
    for (int j=_largeur-1; j >=0; j--){
        for (int i=0; i< _longueur; i++){
            img._vert[_largeur - j - 1].push_back(_vert[i][j]);
            img._bleu[_largeur - j - 1].push_back(_bleu[i][j]);
            img._rouge[_largeur - j - 1].push_back(_rouge[i][j]);
        }
    }
    return img;
}
///méthode retournementH de la classe Image permettant de créer une nouvelle image à partir de l’image cible qui effectue une symétrie de l’image d’axe vertical
Image Image::retournementH() const{
    vector<vector<int>> vert(_longueur);
    vector<vector<int>> bleu(_longueur);
    vector<vector<int>> rouge(_longueur);
    Image img(rouge, vert, bleu);
    img._largeur = _largeur;
    for (int i=0; i < _longueur; i++){
        for(int j=_largeur-1; j >=0; j--){
           img._vert[i].push_back(_vert[i][j]);
           img._rouge[i].push_back(_rouge[i][j]);
           img._bleu[i].push_back(_bleu[i][j]);
        }
    }
    return img;
}
///méthodes retournementV de la classe Image permettant de créer une nouvelle image à partir de l’image cible qui effectue une symétrie de l’image d’axe horizontal
Image Image::retournementV() const{
    vector<vector<int>> vert(0);
    vector<vector<int>> bleu(0);
    vector<vector<int>> rouge(0);
    for (int i=_longueur-1; i >= 0; i--){
       vert.push_back(_vert[i]);
       rouge.push_back(_rouge[i]);
       bleu.push_back(_bleu[i]);
    }
    Image img(rouge, vert, bleu);
    return img;
}

/// méthode agrandissement de la classe image permettant de créer une nouvelle image à partir de l’image cible qui agrandit l’image d’un facteur entier
Image Image::agrandissement(int facteur) const{
    vector<vector<int>> vert(0);
    vector<vector<int>> bleu(0);
    vector<vector<int>> rouge(0);

    for (int i=0; i < _longueur*facteur; i+=facteur){
        vert.push_back(vector<int>(0));
        rouge.push_back(vector<int>(0));
        bleu.push_back(vector<int>(0));
        for(int j=0; j < _largeur; j++){
            for (int k = 0; k < facteur; k++)
            {
                vert[i].push_back(_vert[i/facteur][j]);
                bleu[i].push_back(_bleu[i/facteur][j]);
                rouge[i].push_back(_rouge[i/facteur][j]);
            }
        }
        for (int k = 0; k < facteur-1; k++)
        {
            vert.push_back(vert.back());
            rouge.push_back(rouge.back());
            bleu.push_back(bleu.back());
        }
    }

    Image img(rouge, vert, bleu);
    return img;
}

///une méthode retrecissement de la classe image permettant de créer une nouvelle image à partir de l’image cible et qui rétrécit l’image d’un facteur entier
Image Image::retrecissement(int facteur) const{

    vector<vector<int>> vert(_longueur/facteur, vector<int>(_largeur/facteur));
    vector<vector<int>> bleu(_longueur/facteur, vector<int>(_largeur/facteur));
    vector<vector<int>> rouge(_longueur/facteur, vector<int>(_largeur/facteur));
    Image img(rouge, vert, bleu);
    int moyr;
    int moyv;
    int moyb;
    for (int i=0; i < _longueur; i+=facteur){
        for(int j=0; j < _largeur; j+=facteur){
            moyr=0;
            moyv=0;
            moyb=0;
            for (int k=0; k < facteur; k++){
                for(int l=0; l < facteur; l++){
                    moyr+=_rouge[i+k][j+l];
                    moyv+=_vert[i+k][j+l];
                    moyb+=_bleu[i+k][j+l];
                }
            }
            moyr=moyr/(facteur*facteur);
            moyv=moyv/(facteur*facteur);
            moyb=moyb/(facteur*facteur);

            img._rouge[i/facteur][j/facteur]=moyr;
            img._vert[i/facteur][j/facteur]=moyv;
            img._bleu[i/facteur][j/facteur]=moyb;
        }
    }
    return img;
}

//Getteur vecteur rouge
vector<vector<int>> Image::getRouge() const{
    return _rouge;
}

//Getteur vecteur bleu
vector<vector<int>> Image::getBleu() const{
    return _bleu;
}

//Getteur vecteur vert
vector<vector<int>> Image::getVert() const{
    return _vert;
}

//Getteur largeur
int Image::getLargeur() const{
    return _largeur;
}

//Getteur largeur
int Image::getLongueur() const{
    return _longueur;
}

//Fonction comparaison égalité de deux images
bool operator==(Image img1, Image img2)
{
    bool good = true;

    for (int i = 0; i < img1.getLongueur() && good; i++)
    {
        for (int j = 0; j < img1.getLargeur() && good; j++)
        {
            if(img1.getRouge()[i][j] != img2.getRouge()[i][j] || img1.getVert()[i][j] != img2.getVert()[i][j] || img1.getBleu()[i][j] != img2.getBleu()[i][j]){
                good = false;
            }
        }
    }
    return good;
}
