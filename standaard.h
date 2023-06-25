// Defintie van standaard functies.

#ifndef StandaardHVar  // om te voorkomen dat dit .h bestand meerdere keren
#define StandaardHVar  // wordt ge-include 

#include<vector>
using namespace std;

// Controleer of variabele met naam `variabele' een waarde `waarde' heeft
// die tussen (inclusief) minWaarde en maxWaarde in ligt.
// Zo nee, geef een passende foutmelding.
//
// Voorbeeld van aanroep:
//   if (integerInBereik ("teller", teller, 0, 1000))
//     ...
bool integerInBereik (const char *variabele, int waarde,
                      int minWaarde, int maxWaarde);

// Controleer of waarde `waarde' tussen (inclusief) minWaarde en maxWaarde
// in ligt.
// Geef GEEN foutmelding als het niet zo is.
bool integerInBereik (int waarde, int minWaarde, int maxWaarde);

// Controleer of variabele met naam `variabele' een waarde `waarde' heeft
// die positief is.
// Zo nee, geef een passende foutmelding.
//
// Voorbeeld van aanroep:
//   if (integerPositief ("teller", teller))
//     ...
bool integerPositief (const char *variabele, int waarde);

// Genereer een random geheel getal r waarvoor  min <= r <= max.
// Pre: min <= max;
int randomGetal (int min, int max);

// Controleer of waarde `waarde' voorkomt in vector `waardes'.
bool komtVoor (int waarde, vector<int> waardes);

// Kijk naar het i-de bit (vanaf achter) van getal. Het achterste bit is
// bit 0, het een-na-achterste is bit 1, enzovoort
// Controleer eerst of i niet-negatief is.
// Retourneer
// * true, als i niet-negatief is en het i-de bit (vanaf achter) van getal
//   1 is
// * false, als i negatief is of het i-de bit (vanaf achter) van getal 0 is
bool geefBit (int getal, int i);

#endif

