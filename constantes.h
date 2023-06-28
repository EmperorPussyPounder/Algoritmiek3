// Enkele constantes die op verschillende plekken gebruikt kunnen worden.


#ifndef ConstantesHVar  // voorkom dat dit bestand meerdere keren
#define ConstantesHVar  // ge-include wordt
#include <map>
using namespace std;

const int MaxDimensie = 5;
const int Leeg = 0;
const int Gevuld = 1;
const int MinScore = 0;
const int MaxScore = (MaxDimensie*2)*MaxDimensie*MaxDimensie;
const map<int,int> DummyMap;
#endif
