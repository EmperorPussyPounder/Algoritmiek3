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
            bord[i][j] = Leeg;
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
    while(!gedaneZetten.empty()) gedaneZetten.pop_back();
    geldigBord = false;
    ifstream fin;
    fin.open (invoerNaam);
    if (!fin.is_open()) {
        cout << "We konden de file niet openen. \n";
        return geldigBord;
    }
    auto input = -1;
    fin >> hoogte >> breedte;
    beschikbareVakjes = hoogte*breedte;

    if (!integerInBereik("hoogte", hoogte, 1, MaxDimensie)
    || !integerInBereik("breedte", breedte, 1, MaxDimensie)) return geldigBord;

    bool tempBord[MaxDimensie][MaxDimensie];

    for (int i = 0; i < hoogte; ++i) {
        for (int j = 0; j < breedte; ++j) {
            fin >> input;
            if (!integerInBereik("bord vakje", input, Leeg, Gevuld)) {
                fin.close();
                return geldigBord;
            }
            tempBord[i][j] = input;
            beschikbareVakjes -= input;
        }
    }
    fin.close();
    geldigBord = true;
    for (int i = 0; i < hoogte; ++i) {
        for (int j = 0; j < breedte; ++j) {
            bord[i][j] = tempBord[i][j];
        }
    }
    return geldigBord;

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
    --beschikbareVakjes;

    scoreBerekening(rij, kolom);

    return true;

}  // doeZet

//****************************************************************************

bool Azul::unDoeZet ()
{
    if (!geldigBord || gedaneZetten.empty()) {
        return false;
    }

    ++beschikbareVakjes;
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
    mini = MaxScore;
    maxi = MinScore;
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
                int huidigeMini = 0, huidigeMaxi = 0;
                long long huidigeVolgordesMini = 0, huidigeVolgordesMaxi = 0;
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
  int mogelijkeBedekkingen = 1;
  for (auto i = 0; i < beschikbareVakjes; ++i) mogelijkeBedekkingen *= 2;
  int maxScores[mogelijkeBedekkingen];
  int minScores[mogelijkeBedekkingen];
  int bedekking = mogelijkeBedekkingen*2 - 1;
  mini = maxi = volgordesMini = volgordesMaxi = 0;

  maxScores[bedekking] = MinScore;
  minScores[bedekking] = MaxScore;
  bepaalMiniMaxiScoreTD(mini, volgordesMini, maxi, volgordesMaxi,
                        bedekking, mogelijkeBedekkingen, maxScores, minScores);
  return false;

}  // bepaalMiniMaxiScoreTD

bool Azul::bepaalMiniMaxiScoreTD (int &mini, long long &volgordesMini,
                                  int &maxi, long long &volgordesMaxi,
                                  int bedekking, int mogelijkeBedekkingen,
                                  int maxScores[], int minScores[])
{
   int deelBedekking;
   int none;
   long long no;
   for (auto vakje = 1; vakje < mogelijkeBedekkingen; vakje*=2 ) {
      if (vakje &= bedekking) {
          deelBedekking = bedekking ^ vakje;
          auto score = bepaalMiniMaxiScoreTD(none, no, none, no,
                                             deelBedekking, mogelijkeBedekkingen,
                                             maxScores, minScores) + maxScores[vakje];
          if(score > maxScores[bedekking]) maxScores[bedekking] = score;
          //TODO: houd dezelfde scores bij, zoals bij de recursie
          //TODO: op een mooie manier < implementatie
      }
  }

}

//*************************************************************************

bool Azul::bepaalMiniMaxiScoreBU (int &mini, long long &volgordesMini,
                                  int &maxi, long long &volgordesMaxi,
                                  vector< pair<int,int> > &zettenReeksMini,
                                  vector< pair<int,int> > &zettenReeksMaxi)
{
  // TODO: implementeer deze memberfunctie

  return true;

}  // bepaalMiniMaxiScoreBU

//*************************************************************************

void Azul::drukAfZettenReeksen (vector<pair <int,int> > &zettenReeksMini,
                                vector<pair <int,int> > &zettenReeksMaxi)
{
  if (zettenReeksMini.empty()) {
      cout << "Geen zetten hoeven voor de minimale en maximale score gezet worden. \n";
  }

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
    return !beschikbareVakjes;
}  // eindespel

//****************************************************************************
