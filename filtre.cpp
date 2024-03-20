#include "fonctions.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <xmath.h>
#include "filtre.h"

using namespace std;

Filtre::Filtre(const vector<vector<float>>& action){
    _action= action;
    _rayon=action.size()/2;

}
///Méthode le la classe Filtre pour créer une nouvelle image flou
Image Filtre::application(const Image& img) const{
    vector<vector<int>> rouge = img.getRouge();
    vector<vector<int>> vert= img.getVert();
    vector<vector<int>> bleu= img.getBleu();

    vector<vector<int>> rougen = img.getRouge();
    vector<vector<int>> vertn= img.getVert();
    vector<vector<int>> bleun= img.getBleu();

    int cfr;
    int cfv;
    int cfb;

    for (int i = 0; i < img.getLongueur(); i++) {
        for (int j = 0; j < img.getLargeur(); j++) {
            cfr=0;
            cfv=0;
            cfb=0;
            for (int k= -(_rayon); k <= _rayon; k++){
                for(int l=-(_rayon); l <= _rayon; l++){
                   if(i-k>0 && i-k<img.getLongueur() && j-l>0 && j-l<img.getLargeur()){
                    cfr+=(rouge[i-k][j-l])*(_action[k+_rayon][l+_rayon]);
                    cfv+=(vert[i-k][j-l])*(_action[k+_rayon][l+_rayon]);
                    cfb+=(bleu[i-k][j-l])*(_action[k+_rayon][l+_rayon]);
                   }
                }
            }
            rougen[i][j] = cfr;
            vertn[i][j] = cfv;
            bleun[i][j] = cfb;
        };
    }
    Image x(rougen, vertn, bleun);
  return x;
}
