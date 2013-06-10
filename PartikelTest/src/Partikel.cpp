#include "Partikel.h"

Partikel::Partikel(int x, int y)
{
    vel.x = ofRandom(-1, 1);
    pos.x = x;
    pos.y = y;
}