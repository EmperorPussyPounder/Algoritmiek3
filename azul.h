// Definitie van klasse Azul

#ifndef AzulHVar  // voorkom dat dit bestand meerdere keren
#define AzulHVar  // ge-include wordt

#include "constantes.h"
#include <vector>
using namespace std;

class Azul
{ public:

    // Default constructor
    Azul ();

    // Constructor met parameters.
    // Controleer eerst of parameters nwHoogte en nwBreedte geldige waardes
    // hebben. In dat geval wordt er een geldig bord gecreeerd.
    Azul (int nwHoogte, int nwBreedte);

    // Destructor
    ~Azul ();

    // Getters voor hoogte en breedte
    int getHoogte()
    { return hoogte;
    }

    int getBreedte()
    { return breedte;
    }

    // Getter voor de inhoud van vakje (rij,kolom) op het bord
    // (rijen genummerd van 0..hoogte-1, van boven naar beneden,
    //  kolommen van 0..breedte-1, van links naar rechts): 0 of 1
    // Controleer eerst of er een geldig bord is, en of (rij,kolom)
    // een geldig vakje is op dit bord.
    // Retourneer:
    // * -1 als er geen geldig bord is, of (rij,kolom) geen geldig vakje is
    // * 0 als (rij,kolom) wel een geldig vakje en niet bedekt is
    // * 1 als (rij,kolom) wel een geldig vakje en bedekt is
    int getVakje(int rij, int kolom);

    // Lees vanuit invoerNaam een bord in, met eventueel al tegels daarop.
    // Controleer of:
    // * het bestand invoerNaam te openen is
    // * de dimensies hoogte en breedte van het bord binnen de grenzen
    //   van de opdracht vallen
    // * alle getallen die de vakjes van het bord beschrijven 0 of 1 zijn
    //   (0 = niet bedekt, 1 = bedekt)
    // Retourneer:
    // * true, als alle controles goed uitpakken.
    // * false, anders
    // Post:
    // * Als returnwaarde true is, is alle ingelezen informatie in het object
    //   opgeslagen.
    // * De returnwaarde is ook in een membervariabele opgeslagen, zodat
    //   bij andere memberfuncties gecontroleerd kan worden of er een geldig
    //   bord is waarvoor die functies kunnen worden uitgevoerd.
    bool leesInBord (const char* invoerNaam);

    // Druk het huidige bord overzichtelijk af op het scherm.
    // Vermeld ook de totaalscore tot nu toe (vanaf het begin van het spel
    // of het inlezen van een bord).
    // Controleer eerst of er een geldig bord is.
    void drukAfBord ();

    // Doe de zet waarbij een tegel wordt gelegd op vakje (rij,kolom).
    // Controleer eerst of
    // * er een geldig bord is
    // * vakje (rij,kolom) een geldig vakje is voor dit bord,
    //   dat bovendien nog niet bedekt is.
    // Retourneer:
    // * true, als alle controles goed uitpakken
    // * false, anders
    // Post:
    // * Als de returnwaarde true is, is vakje (rij,kolom) ook bedekt.
    // * Anders is de bedekking van het bord niet veranderd.
    bool doeZet (int rij, int kolom);

    // Maak de laatst gedane zet ongedaan.
    // Controleer eerst of
    // * er een geldig bord is
    // * er een zet is om ongedaan te maken.
    // Retourneer:
    // * true, als de controles goed uitpakken
    // * false, anders
    // Post:
    // * Als de returnwaarde true is, is het laatst bedekte vakje
    //   weer onbedekt.
    // * Anders is de bedekking van het bord niet veranderd.
    bool unDoeZet ();

    // Bepaal rechtstreeks recursief de minimale en de maximale totaalscore
    // die gehaald kunnen worden als je het bord compleet wil bedekken met
    // tegels, uitgaande van de huidige bedekking van het bord.
    // Bepaal ook met hoeveel volgordes je deze scores kunt bereiken.
    // Controleer eerst of er een geldig bord is.
    // Retourneer:
    // * true, als er een geldig bord is
    // * false, anders
    // Post:
    // * Als er een geldig bord is, bevatten parameters mini, volgordesMini,
    //   maxi en volgordesMaxi de gezochte waardes.
    // * De bedekking van het bord is niet veranderd.
    bool bepaalMiniMaxiScoreRec (int &mini, long long &volgordesMini,
                                 int &maxi, long long &volgordesMaxi);
    
    // Bepaal met top-down dynamisch programmeren de minimale en de maximale
    // totaalscore die gehaald kunnen worden als je het bord compleet wil
    // bedekken met tegels, uitgaande van de huidige bedekking van het bord.
    // Bepaal ook met hoeveel volgordes je deze scores kunt bereiken.
    // Controleer eerst of er een geldig bord is.
    // Retourneer:
    // * true, als er een geldig bord is
    // * false, anders
    // Post:
    // * Als er een geldig bord is, bevatten parameters mini, volgordesMini,
    //   maxi en volgordesMaxi de gezochte waardes.
    // * De bedekking van het bord is niet veranderd.
    bool bepaalMiniMaxiScoreTD (int &mini, long long &volgordesMini, 
                                int &maxi, long long &volgordesMaxi);

    // Bepaal met bottom-up dynamisch programmeren de minimale en de maximale
    // totaalscore die gehaald kunnen worden als je het bord compleet wil
    // bedekken met tegels, uitgaande van de huidige bedekking van het bord.
    // Bepaal ook met hoeveel volgordes je deze scores kunt bereiken.
    // Bepaal ten slotte ook een concrete zettenreeks voor elk van de twee
    // scores.
    // Controleer eerst of er een geldig bord is.
    // Retourneer:
    // * true, als er een geldig bord is
    // * false, anders
    // Post:
    // * Als er een geldig bord is, bevatten parameters mini, volgordesMini,
    //   maxi, volgordesMaxi, zettenReeksMini en zettenReeksMaxi de gezochte
    //   waardes.
    // * Elke zettenreeks begint (op plek 0) met het vakje (rij,kolom)
    //   dat als eerste bedekt zou moeten worden, dan (op plek 1) het vakje
    //   dat als tweede bedekt zou moeten worden, enzovoort.
    // * De bedekking van het bord is niet veranderd.
    bool bepaalMiniMaxiScoreBU (int &mini, long long &volgordesMini, 
                                int &maxi, long long &volgordesMaxi,
                                vector< pair<int,int> > &zettenReeksMini,
                                vector< pair<int,int> > &zettenReeksMaxi);

    // Druk zettenreeksen zettenReeksMini en zettenReeksMaxi af op het scherm,
    // samen met de scores die de reeksen opleveren, uitgaande van
    // de huidige bedekking van het bord.
    // Elke zettenreeks bestaat uit een reeks vakjes (rij,kolom) op het bord
    // die achtereenvolgens worden bedekt: eerst zettenReeks[0],
    // dan zettenReeks[1], enzovoort.
    // Controleer eerst of er een geldig bord is.
    // Pre:
    // * Als er een geldig bord is, zijn de zettenreeksen geldig voor dit
    //   bord, uitgaande van de huidige bedekking van het bord.
    // Post:
    // * De bedekking van het bord is niet veranderd.
    void drukAfZettenReeksen (vector<pair <int,int> > &zettenReeksMini,
                              vector<pair <int,int> > &zettenReeksMaxi);

  private:
    int hoogte, breedte;   // hoogte, breedte van het bord
    bool bord[MaxDimensie][MaxDimensie];
    bool geldigBord;
    vector<int> score;
    vector<pair <int,int>> gedaneZetten;
    int totaleScore;
    int beschikbareVakjes;
    int scoreBerekening(int rij, int kolom);
    bool eindeSpel();
    void vakScores(int maxScores[], int minScores[]);
    bool bepaalMiniMaxiScoreTD (int &mini, long long &volgordesMini,
                                int &maxi, long long &volgordesMaxi,
                                int bedekking, int mogelijkeBedekkingen,
                                int maxScores[], int minScores[]);





  // TODO: uw eigen private memberfuncties en -variabelen

};

#endif

