// Implementatie van klasse Azul

#include <iostream>
#include <fstream>
#include <map>
#include <array>
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

    auto scoreVakje = scoreBerekening(rij, kolom);
    score.push_back(scoreVakje);

    totaleScore += scoreVakje;

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
  if(!geldigBord) return false;
  int mogelijkeBedekkingen = 1;
  for (auto i = 0; i < beschikbareVakjes; ++i) mogelijkeBedekkingen *= 2;

  map<int, pair<int,long long>> maxScores;
  for (auto i = 0; i < mogelijkeBedekkingen; ++i)
    maxScores[i] = make_pair(MinScore,1);
  map<int, pair<int, long long>>  minScores;
  for (auto i = 0; i < mogelijkeBedekkingen; ++i)
    minScores[i] = make_pair(MaxScore,1);
  minScores[0].first = 0;
  map<int, pair<int,int>> vakMap;
  vakVolgorde(vakMap);

  int bedekking = mogelijkeBedekkingen - 1;
  mini = maxi = volgordesMini = volgordesMaxi = 0;
  bepaalMiniMaxiScoreTD(mini, volgordesMini, maxi, volgordesMaxi,
                        bedekking, mogelijkeBedekkingen, maxScores,
                        minScores, vakMap);
  return true;

}  // bepaalMiniMaxiScoreTD

void Azul::vakVolgorde(map<int,pair<int,int>> & coordinaten)
{
    auto index = 1;
    for (auto rij = 0; rij < hoogte; ++rij) {
        for (auto kolom = 0; kolom < breedte; ++kolom) {
            if(bord[rij][kolom] == Leeg) {
                coordinaten[index] = make_pair(rij, kolom);
                index *= 2;
            }
        }
    }
}

void Azul::bepaalMiniMaxiScoreTD (int &mini, long long &volgordesMini,
                                  int &maxi, long long &volgordesMaxi,
                                  int bedekking, int mogelijkeBedekkingen,
                                  map<int,pair<int,long long>> & maxScores, map<int,pair<int,long long>> & minScores,
                                  map<int, pair<int,int>> & coordinaten)
{
  if (!bedekking) return;

  int deelBedekking;
  long long laagsteDeelScore = 0;
  long long hoogsteDeelScore = 0;
  for (auto vakje = 1; vakje < mogelijkeBedekkingen; vakje*=2) {
     if (vakje & bedekking) {
       deelBedekking = bedekking ^ vakje;

       auto vakRij = coordinaten[vakje].first;
       auto vakKolom = coordinaten[vakje].second;
       if (!maxScores[deelBedekking].first) {
         doeZet(vakRij, vakKolom);
         bepaalMiniMaxiScoreTD(mini, volgordesMini,
                               maxi, volgordesMaxi,
                               deelBedekking, mogelijkeBedekkingen,
                               maxScores, minScores,
                               coordinaten);
         unDoeZet();
       }

       hoogsteDeelScore = maxScores[deelBedekking].first;
       laagsteDeelScore = minScores[deelBedekking].first;


       auto score2 = laagsteDeelScore  +  scoreBerekening(vakRij, vakKolom);
       auto score1 = hoogsteDeelScore  +  scoreBerekening(vakRij, vakKolom);
       if(score1 > maxScores[bedekking].first) {
         maxScores[bedekking].first = score1;
         maxScores[bedekking].second = maxScores[deelBedekking].second;
       }
       else if(score1 == maxScores[bedekking].first) maxScores[bedekking].second += maxScores[deelBedekking].second;

       if (score2 < minScores[bedekking].first) {
         minScores[bedekking].first = score2;
         minScores[bedekking].second = minScores[deelBedekking].second;
       }
       else if(score2 == minScores[bedekking].first) minScores[bedekking].second += minScores[deelBedekking].second;
     }
  }

  maxi = maxScores[bedekking].first;
  mini = minScores[bedekking].first;
  volgordesMaxi = maxScores[bedekking].second;
  volgordesMini = minScores[bedekking].second;

}

//*************************************************************************

bool Azul::bepaalMiniMaxiScoreBU (int &mini, long long &volgordesMini,
                                  int &maxi, long long &volgordesMaxi,
                                  vector< pair<int,int> > &zettenReeksMini,
                                  vector< pair<int,int> > &zettenReeksMaxi)
{
  if(!geldigBord) return false;
  int mogelijkeBedekkingen = 1;
  for (auto i = 0; i < beschikbareVakjes; ++i) mogelijkeBedekkingen *= 2;
  map<int,pair<int,long long>> maxScores;
  map<int,pair<int,int>> subMaxToLast;
  for (auto i = 0; i < mogelijkeBedekkingen; ++i)
    maxScores[i] = make_pair(MinScore,1);
  map<int, pair<int,long long>>  minScores;
  map<int,pair<int,int>> subMinToLast;
  for (auto i = 0; i < mogelijkeBedekkingen; ++i)
    minScores[i] = make_pair(MaxScore,1);
  minScores[0].first = 0;
  map<int, pair<int,int>> vakMap;
  vakVolgorde(vakMap);

  const int GrensBedekking = mogelijkeBedekkingen - 1;
  mini = maxi = volgordesMini = volgordesMaxi = 0;

  int deelBedekking;
  long long laagsteDeelScore = 0;
  long long hoogsteDeelScore = 0;
  for (auto bedekking = 1; bedekking <= GrensBedekking; ++bedekking) {
    for(auto vakje = 1; vakje <= bedekking; vakje *= 2) {
      if (!(vakje & bedekking)) continue;
      auto deelVakRij = vakMap[vakje].first;
      auto deelVakKolom = vakMap[vakje].second;
      doeZet(deelVakRij, deelVakKolom);
    }

    for (auto vakje = 1; vakje <= bedekking; vakje*=2) {

      if (vakje & bedekking) {
        deelBedekking = bedekking ^ vakje;
        auto vakRij = vakMap[vakje].first;
        auto vakKolom = vakMap[vakje].second;

        hoogsteDeelScore = maxScores[deelBedekking].first;
        laagsteDeelScore = minScores[deelBedekking].first;


        auto score2 = laagsteDeelScore + scoreBerekening(vakRij, vakKolom);
        auto score1 = hoogsteDeelScore + scoreBerekening(vakRij, vakKolom);
        if(score1 > maxScores[bedekking].first) {
          maxScores[bedekking].first = score1;
          maxScores[bedekking].second = maxScores[deelBedekking].second;
          subMaxToLast[deelBedekking] = vakMap[vakje];
        }
        else if(score1 == maxScores[bedekking].first) maxScores[bedekking].second += maxScores[deelBedekking].second;

        if (score2 < minScores[bedekking].first) {
          minScores[bedekking].first = score2;
          minScores[bedekking].second = minScores[deelBedekking].second;
          subMinToLast[deelBedekking] = vakMap[vakje];
        }
        else if(score2 == minScores[bedekking].first) minScores[bedekking].second += minScores[deelBedekking].second;
        }
    }

    for(auto vakje = 1; vakje <= bedekking; vakje *= 2) unDoeZet();
  }

  maxi = maxScores[GrensBedekking].first;
  mini = minScores[GrensBedekking].first;
  volgordesMaxi = maxScores[GrensBedekking].second;
  volgordesMini = minScores[GrensBedekking].second;

  for (auto overdekking = GrensBedekking; overdekking > 0; overdekking /=2 ) {
    zettenReeksMaxi.push_back(subMaxToLast[overdekking]);
    zettenReeksMini.push_back(subMinToLast[overdekking]);
  }

  return true;

}  // bepaalMiniMaxiScoreBU

//*************************************************************************

void Azul::drukAfZettenReeksen (vector<pair <int,int> > &zettenReeksMini,
                                vector<pair <int,int> > &zettenReeksMaxi)
{
  if (zettenReeksMini.empty()) {
      cout << "Geen zetten hoeven voor de minimale en maximale score gezet worden. \n";
  }

  cout << "Voor minimale score vult U ";
  for (auto vak : zettenReeksMini) cout << "( " << vak.first << ", " << vak.second << " )" << ",\n";
  cout << "Op volgorde in. \n";

  cout << "Voor maximale score vult U ";
  for (auto vak : zettenReeksMaxi) cout << "( " << vak.first << ", " << vak.second << " )" << ",\n";
  cout << "Op volgorde in. \n";


}  // drukAfZettenReeksen

//*************************************************************************

// TODO: implementatie van uw eigen private memberfuncties


int Azul::scoreBerekening(int rij, int kolom)
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

    return totaleScoreVakje;

}  // scoreBerekening

//****************************************************************************

bool Azul::eindeSpel()
{
    return !beschikbareVakjes;
}  // eindespel

//****************************************************************************
