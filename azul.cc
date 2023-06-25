// Implementatie van klasse Azul

#include <iostream>
#include <fstream>
#include "standaard.h"
#include "azul.h"
using namespace std;

//*************************************************************************

Azul::Azul ()
{
    hoogte = MaxDimensie;
    breedte = MaxDimensie;
    totaleScore = 0;
    geldigBord = true;

    for (int i = 0; i < hoogte; ++i) {
        for (int j = 0; j < breedte; ++j) {
            bord[i][j] = false;
        }
    }

}  // default constructor

//*************************************************************************

Azul::Azul (int nwHoogte, int nwBreedte)
{
  // TODO: implementeer deze constructor

}  // constructor met parameters

//*************************************************************************

Azul::~Azul ()
{
  // TODO: implementeer zo nodig deze destructor

}  // destructor

//*************************************************************************

int Azul::getVakje (int rij, int kolom)
{
    if (!geldigBord || rij > hoogte - 1 || kolom > breedte - 1) {
        return -1;
    }

    if (!bord[rij][kolom]){
        return 0;
    }
    else{
        return 1;
    }

}  // getVakje

//*************************************************************************

bool Azul::leesInBord (const char* invoerNaam)
{
    ifstream fin;
    fin.open (invoerNaam);
    if (!fin.is_open()){
        geldigBord = false;
        return false;
    }

    int tempgetal = -1;
    fin >> hoogte >> breedte;

    if (hoogte > MaxDimensie || breedte > MaxDimensie){
        geldigBord = false;
        return false;
    }

    bool tempBord[MaxDimensie][MaxDimensie];

    for (int i = 0; i < hoogte; ++i) {
        for (int j = 0; j < breedte; ++j) {
            fin >> tempgetal;
            if (tempgetal == 0){
                tempBord[i][j] = false;
            }
            else if (tempgetal == 1){
                tempBord[i][j] = true;
            }
            else{
                geldigBord = false;
                return false;
            }
        }
    }
    fin.close();

    for (int i = 0; i < hoogte; ++i) {
        for (int j = 0; j < breedte; ++j) {
            bord[i][j] = tempBord[i][j];
        }
    }

    geldigBord = true;

    return true;

}  // leesInBord


//*************************************************************************

void Azul::drukAfBord ()
{
    if (!geldigBord){
        return;
    }

    cout << endl << "De totale score is: " << totaleScore << endl << endl;

    cout << "   ";
    for (int j = 0; j < breedte; ++j) {
        cout << j << " ";
    }
    cout << endl << endl;

    for (int i = 0; i < hoogte; ++i) {
        cout << i << "  ";
        for (int j = 0; j < breedte; ++j) {
            cout << (bord[i][j] ? 1 : 0) << " ";
        }
        cout << endl;
    }

}  // drukAfBord

//****************************************************************************

bool Azul::doeZet (int rij, int kolom)
{
    if (!geldigBord || rij >= hoogte || kolom >= breedte || bord[rij][kolom]) {
        return false;
    }

    bord[rij][kolom] = true;
    gedaneZetten.push_back(make_pair(rij, kolom));

    scoreBerekening(rij, kolom);

    return true;

}  // doeZet

//****************************************************************************

bool Azul::unDoeZet ()
{
    if (!geldigBord || gedaneZetten.empty()) {
        return false;
    }

    totaleScore -= score.back();
    score.pop_back();

    pair<int, int> laatsteZet = gedaneZetten.back();
    gedaneZetten.pop_back();
    bord[laatsteZet.first][laatsteZet.second] = false;

    return true;

}  // unDoeZet

//****************************************************************************

bool Azul::bepaalMiniMaxiScoreRec(int &mini, long long &volgordesMini, int &maxi, long long &volgordesMaxi)
{
    if (!geldigBord){
        return false;
    }

    mini = INT_MAX;
    maxi = INT_MIN;
    volgordesMini = 0;
    volgordesMaxi = 0;

    if (eindeSpel()) {
        mini = totaleScore;
        maxi = totaleScore;
        volgordesMini = 1;
        volgordesMaxi = 1;
        return true;
    }

    for (int i = 0; i < hoogte; i++){
        for (int j = 0; j < breedte; j++){
            if (!bord[i][j]){
                doeZet(i, j);

                // Recursieve aanroep
                int huidigeMini, huidigeMaxi;
                long long huidigeVolgordesMini, huidigeVolgordesMaxi;
                bepaalMiniMaxiScoreRec(huidigeMini, huidigeVolgordesMini, huidigeMaxi, huidigeVolgordesMaxi);

                if (huidigeMini < mini){
                    mini = huidigeMini;
                    volgordesMini = huidigeVolgordesMini;
                }
                else if (huidigeMini == mini){
                    volgordesMini += huidigeVolgordesMini;
                }

                if (huidigeMaxi > maxi){
                    maxi = huidigeMaxi;
                    volgordesMaxi = huidigeVolgordesMaxi;
                }
                else if (huidigeMaxi == maxi){
                    volgordesMaxi += huidigeVolgordesMaxi;
                }

                unDoeZet();
            }
        }
    }

    return true;
}


//*************************************************************************

bool Azul::bepaalMiniMaxiScoreTD (int &mini, long long &volgordesMini,
                                  int &maxi, long long &volgordesMaxi)
{
  // TODO: implementeer deze memberfunctie

  return false;

}  // bepaalMiniMaxiScoreTD

//*************************************************************************

bool Azul::bepaalMiniMaxiScoreBU (int &mini, long long &volgordesMini,
                                  int &maxi, long long &volgordesMaxi,
                                  vector< pair<int,int> > &zettenReeksMini,
                                  vector< pair<int,int> > &zettenReeksMaxi)
{
  // TODO: implementeer deze memberfunctie

  return false;

}  // bepaalMiniMaxiScoreBU

//*************************************************************************

void Azul::drukAfZettenReeksen (vector<pair <int,int> > &zettenReeksMini,
                                vector<pair <int,int> > &zettenReeksMaxi)
{
  // TODO: implementeer deze memberfunctie

}  // drukAfZettenReeksen

//*************************************************************************

// TODO: implementatie van uw eigen private memberfuncties


void Azul::scoreBerekening(int rij, int kolom)
{
    // horizontale score
    int scoreH = 1;
    for (int k = kolom - 1; k >= 0 && bord[rij][k]; --k)
        ++scoreH;
    for (int k = kolom + 1; k < breedte && bord[rij][k]; ++k)
        ++scoreH;

    // verticale score
    int scoreV = 1;
    for (int k = rij - 1; k >= 0 && bord[k][kolom]; --k)
        ++scoreV;
    for (int k = rij + 1; k < hoogte && bord[k][kolom]; ++k)
        ++scoreV;

    int totaleScoreVakje;
    if (scoreH == 1) totaleScoreVakje = scoreV;
    else if (scoreV == 1) totaleScoreVakje = scoreH;
    else totaleScoreVakje = scoreH + scoreV;

    score.push_back(totaleScoreVakje);

    totaleScore += totaleScoreVakje;

}  // scoreBerekening

//****************************************************************************

bool Azul::eindeSpel()
{
    for (int i = 0; i < hoogte; ++i) {
        for (int j = 0; j < breedte; ++j) {
            if (!bord[i][j]){
                return false;
            }
        }
    }
    return true;

}  // eindespel

//****************************************************************************