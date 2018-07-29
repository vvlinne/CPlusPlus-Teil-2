#include "QWidget"

// Stats-Objekt enthält verfügbare Leben und Punktanzahl
class stats
{
public:
    void updatePoints(void);
    int punkte = 0;
    int leben = 3;
};
