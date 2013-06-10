#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    //Kinect initialisieren
    kinect.init();
    kinect.open();
    
    // Abfrage vom Kinect Winkel
    angle = kinect.getCurrentCameraTiltAngle(); 
    
    // Initialisierung des Graustufenbilds
    w = kinect.width;
    h = kinect.height;
    grayscaleImgInput.allocate(w, h);
    grayscaleImgFar.allocate(w, h);
    grayscaleImgNear.allocate(w, h);
    grayscaleImgOutput.allocate(w, h);
    
    //Schwellwert setzen
    thresholdFar = 230;
    thresholdNear = 70;
    
    isThreshold = false;
    isBlur = false;
    isContour = false;
    isDebug = true;
    
    //Hintergrund schwarz setzen
    ofBackground(0, 0, 0);
    
    numParticles = 0;
}

//--------------------------------------------------------------
void testApp::update(){
    // Bild Aufnahme
    kinect.update();

    if (kinect.isFrameNew()){
        
        // Tiefenbild laden und speichern
        grayscaleImgInput.setFromPixels(kinect.getDepthPixels(), w, h);
        
        grayscaleImgFar = grayscaleImgInput;
        grayscaleImgNear = grayscaleImgInput;
        grayscaleImgOutput = grayscaleImgInput;
        
        //Abfrage ob isThreshold true
        if (isThreshold) {                                      
            grayscaleImgNear.threshold(thresholdNear);
            grayscaleImgFar.threshold(thresholdFar, true);
            cvAnd(grayscaleImgFar.getCvImage(), grayscaleImgNear.getCvImage(), grayscaleImgOutput.getCvImage(), NULL);
            grayscaleImgOutput.flagImageChanged();

        }
        
        //Weichzeichner
        if (isBlur) {
            grayscaleImgOutput.dilate_3x3();
            grayscaleImgOutput.dilate_3x3();
            grayscaleImgOutput.blur(5);
            grayscaleImgOutput.flagImageChanged();
        }
        
        if (isContour) {
            contourFinder.findContours(grayscaleImgOutput, 5, (w * h)/2, 3, false, true);
        }
    }
    
    if (!isDebug) {
        if (PartikelSystem.size() < 10) {
            //ofPixels pixels = kinect.getPixelsRef();
            
            PartikelSystem.push_back(new Partikel(ofRandom(0, w), ofRandom(0, h)));
           
            //PartikelSystem.push_back(new Partikel(pixels.getWidth(), pixels.getHeight()));           //Erzeugung eines neuen Partikels
            
            //PartikelSystem.push_back(new Partikel(w/2, h/2));           //Erzeugung eines neuen Partikels
            
//            PartikelSystem.push_back(new Partikel(w/2+200, h/2+2));           //Erzeugung eines neuen Partikels
//            PartikelSystem.push_back(new Partikel(w/2+40, h/2+4));           //Erzeugung eines neuen Partikels
        }
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    
    if(isDebug) {
        ofSetColor(255, 255, 255);
        grayscaleImgInput.draw(0, 0, 320, 240);
        grayscaleImgFar.draw(321, 0, 320, 240);
        grayscaleImgNear.draw(0, 241, 320, 240);
        grayscaleImgOutput.draw(321, 241, 320, 240);
        contourFinder.draw(321, 241, 320, 240);
        
        
        ofSetColor(255, 0, 255);
        ofDrawBitmapString("Standard Bild", 10, 10);
        ofDrawBitmapString("ThresholdFar", 331, 10);
        ofDrawBitmapString("ThresholdNear", 10, 251);
        ofDrawBitmapString("Output", 331, 251);
        
        ofDrawBitmapString("Winkel der Kinect: " + ofToString(angle), 10, 20);
    }
    else
    {
        ofSetColor(255, 255, 255);
    
        int i = 0;
        for (itP = PartikelSystem.begin(); itP != PartikelSystem.end(); itP++) {
            ofSphere((*itP)->pos.x, (*itP)->pos.y, 0, 3);
            //gl_Vertex((*itP)->pos.x, (*itP)->pos.y);  //zur not mit array wenn keine Lšsung
            ofDrawBitmapString("Position Vertex: x= " + ofToString((*itP)->pos.x) + " y= " + ofToString((*itP)->pos.y), 10, 10 + (i*10));
            i++;
        }
        
        //ofSetPolyMode(OF_POLY_WINDING_ODD);
        //ofBeginShape();
//        ofSetColor(0,0,255);
//        for (int i = 0; i < PartikelSystem.size(); i++) {
//            ofVertex(PartikelSystem[i]->pos.x, PartikelSystem[i]->pos.y);
//        }
        //ofEndShape();
    }
}

//--------------------------------------------------------------

void testApp::exit() {
	kinect.close();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    // Winkel der Kinect Šndern
    switch (key) {
        case OF_KEY_UP:
			angle++;
			if(angle>30) angle=30;
			kinect.setCameraTiltAngle(angle);
			break;
			
		case OF_KEY_DOWN:
			angle--;
			if(angle<-30) angle=-30;
			kinect.setCameraTiltAngle(angle);
			break;
            
        case 't':                           //Schwellwert abschalten mit "t"
            isThreshold = !isThreshold;
            break;
            
        case 'b':                           //Weichzeichner
            isBlur = !isBlur;
            break;
    
        case 'c':                           //Blobs
            isContour = !isContour;
            break;
            
        case ' ':
            isDebug = !isDebug;
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}