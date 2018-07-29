#include "gegner.h"

bool gegner::calculatePosition(int stepRange)
{
    if(this->y + stepRange >= 650) {
        return true;
    } else {
        this->y = this->y + stepRange;
        return false;
    }
}
