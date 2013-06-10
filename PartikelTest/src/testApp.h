#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxOpenCv.h"
#include "Partikel.h"
#define MAXPARTICLES 10

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        
        int w; // Breite des Kinect Bildes
        int h; // Hšhe des Kinect Bildes
        
        void exit();
    
private:
    ofxKinect kinect;
    ofxCvGrayscaleImage grayscaleImgInput;
    ofxCvGrayscaleImage grayscaleImgFar;
    ofxCvGrayscaleImage grayscaleImgNear;
    ofxCvGrayscaleImage grayscaleImgOutput;
    ofxCvContourFinder contourFinder;

    
    int thresholdFar, thresholdNear; //Schwellwerte
    
    int angle; // Winkel Kinect
    bool isThreshold;
    bool isBlur;
    bool isContour;             //Silhoutte 
    bool isDebug;               //Umschalten in Debug Modus
    
    vector<Partikel*> PartikelSystem;
    
    int numParticles;
    std::vector<Partikel*>::iterator itP;

    
		
};
