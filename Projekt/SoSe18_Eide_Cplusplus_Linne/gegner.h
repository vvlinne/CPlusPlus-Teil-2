#include "QWidget"
using namespace std;

// Gegner-Objekt, welches Koordinaten und Typ (1 = Quadrat / 2 = Kreis) des Objekt enthält
class gegner
{
public:
    int y = 0;
    int x = rand() % 600 + 1;
    int typ = rand() % 2 + 1;
    bool calculatePosition(int stepRange);
};
