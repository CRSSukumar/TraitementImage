/*#include "fonctions.h"
#include <iostream>
#include <ostream>
#include <vector>

using namespace std;

int main() {

    vector<vector<int>> rouge{
                            {100, 150, 200, 250},
                            {50, 100, 150, 200},
                            {25, 75, 125, 175},
                            {75, 145, 255, 255}};

    vector<vector<int>> vert{
                            {25, 75, 255, 150},
                            {0, 235, 50, 175},
                            {105, 25, 75, 100},
                            {50, 75, 0, 0}};

    vector<vector<int>> bleu{
                            {255, 255, 10, 0},
                            {25, 10, 20, 100},
                            {85, 240, 40, 25},
                            {255, 100, 50, 175}};

    Image testImage(rouge, vert, bleu);

    /// TEST AUTOMATIC NiveauxGris()

    cout<<"::::::::::::: TEST AUTOMATIQUES :::::::::::::\n";

    vector<vector<int>> rouge_nivGris{
                            {126, 160,155,133},
                            {25, 115, 73, 158},
                            {71, 113, 80, 100},
                            {126, 106, 101, 143}};

    vector<vector<int>> vert_nivGris{
                            {126, 160,155,133},
                            {25, 115, 73, 158},
                            {71, 113, 80, 100},
                            {126, 106, 101, 143}};

    vector<vector<int>> bleu_nivGris{
                            {126, 160,155,133},
                            {25, 115, 73, 158},
                            {71, 113, 80, 100},
                            {126, 106, 101, 143}};

    Image exepted_NivGris(rouge_nivGris, vert_nivGris, bleu_nivGris);
    Image result_NivGris = testImage.niveauxGris();

    if (exepted_NivGris == result_NivGris) cout<<"Test NiveauxGris :::::\tREUSSI !"<<endl;
    else cout <<"Test NiveauxGris :::::\tECHEC !"<<endl;

    /// TEST AUTOMATIC rognerG()

    vector<vector<int>> rouge_rognerG{
                            {200, 250},
                            {150, 200},
                            {125, 175},
                            {255, 255}};

    vector<vector<int>> vert_rognerG{
                            {255, 150},
                            {50, 175},
                            {75, 100},
                            {0, 0}};

    vector<vector<int>> bleu_rognerG{
                            {10, 0},
                            {20, 100},
                            {40, 25},
                            {50, 175}};

    Image exepted_rognerG(rouge_rognerG, vert_rognerG, bleu_rognerG);
    Image result_rognerG = testImage.rognerG(2);

    if (exepted_rognerG == result_rognerG) cout<<"Test rognerG :::::\tREUSSI !"<<endl;
    else cout <<"Test rognerG :::::\tECHEC !"<<endl;

    /// TEST AUTOMATIC aggrandissement()

    vector<vector<int>> rouge_aggr{
                            {100, 100, 150, 150, 200, 200, 250, 250},
                            {100, 100, 150, 150, 200, 200, 250, 250},
                            {50, 50, 100, 100, 150, 150, 200, 200},
                            {50, 50, 100, 100, 150, 150, 200, 200},
                            {25, 25, 75, 75, 125, 125, 175, 175},
                            {25, 25, 75, 75, 125, 125, 175, 175},
                            {75, 75, 145, 145, 255, 255, 255, 255},
                            {75, 75, 145, 145, 255, 255, 255, 255}};

    vector<vector<int>> vert_aggr{
                            {25, 25, 75, 75, 255, 255, 150, 150},
                            {25, 25,75, 75, 255, 255, 150, 150},
                            {0, 0, 235, 235, 50, 50, 175, 175},
                            {0, 0,  235, 235, 50, 50, 175, 175},
                            {105, 105, 25, 25, 75, 75, 100, 100},
                            {105, 105, 25, 25, 75, 75, 100, 100},
                            {50, 50, 75, 75, 0, 0, 0, 0},
                            {50, 50, 75, 75, 0, 0, 0, 0}};

    vector<vector<int>> bleu_aggr{
                            {255, 255, 255, 255, 10, 10, 0, 0},
                            {255, 255, 255, 255, 10, 10, 0, 0},
                            {25, 25, 10, 10, 20, 20, 100, 100},
                            {25, 25, 10, 10, 20, 20, 100, 100},
                            {85, 85, 240, 240, 40, 40, 25, 25},
                            {85, 85, 240, 240, 40, 40, 25, 25},
                            {255, 255, 100, 100, 50, 50, 175, 175},
                            {255, 255, 100, 100, 50, 50, 175, 175}};

    Image exepted_aggr(rouge_aggr, vert_aggr, bleu_aggr);
    Image result_aggr = testImage.agrandissement(2);

    if (exepted_aggr == result_aggr) cout<<"Test Agrandissement :::\tREUSSI !"<<endl;
    else cout <<"Test Agrandissement :::\tECHEC !"<<endl;

    cout<<":::::::::::::::::::::::::::::::::::::::::::::\n\n"<<endl;

    return 0;
}*/

