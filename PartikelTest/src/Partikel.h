#include "ofMain.h"
#ifndef __PartikelTest__Partikel__
#define __PartikelTest__Partikel__

class Partikel {

        public:
        Partikel(int x, int y);
        float lifeTime, age;
        ofVec2f pos;            //Position
        ofVec2f vel;            //Geschwindigkeit
};

#endif /* defined(__PartikelTest__Partikel__) */
