#include "ofApp.hpp"

//--------------------------------------------------------------
void ofApp::setup() {
    string songs[] = {"beat.wav","geesebeat.wav","pigeon-coo.wav","rock-song.wav"};
    sound.load(songs[songNum]);           // Loads a sound file (in bin/data/)
    sound.setLoop(true);              // Makes the song loop indefinitely
    sound.setVolume(1);               // Sets the song volume
    ofSetBackgroundColor(20, 50, 35); // Sets the Background Color
}

//--------------------------------------------------------------
void ofApp::update() {
    /* The update method is called muliple times per second
    It's in charge of updating variables and the logic of our app */
    ofSoundUpdate();               // Updates all sound players
    if (ampUpdate==true){
        visualizer.updateAmplitudes(); // Updates Amplitudes for visualizer
    }
    progress = sound.getPosition();
    if (loop && sound.getPosition()>=0.99){
        if (songNum<3){
            songNum++;
            setup();
            sound.play();
        }
        else{
            songNum=0;
            setup();
            sound.play();
        }
    }
    if (replay && sound.getPosition()>=0.99){
        sound.setPosition(0.00);
    }
    if (shuffle && sound.getPosition()>=0.99){
        songNum = ofRandom(0,4);
        setup();
        sound.play();
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    /* The update method is called muliple times per second
    It's in charge of drawing all figures and text on screen */

    // Progress Bar
    ofSetColor(219,112,147); //progress bar color
    ofFill();
    ofDrawRectangle(0, ofGetHeight() - 60, progress*ofGetWidth(), 25); //Draws the progress Bar

    ofSetColor(256);

    float pos = playing ? progress : lastPos;
    int percent = pos * 100;
    ofDrawBitmapString("Song Progress: " + ofToString(percent) + "%", 0, 30);
    string smode = "None";
    if (loop){
        smode = "Loop";
    }
    if (replay){
        smode = "Replay";
    }
    if (shuffle){
        smode = "Shuffle";
    }
    ofDrawBitmapString("Current mode: " + smode, 0, 40);



    // Mode Selection
    if (!playing) {
        ofDrawBitmapString("Press 'p' to play some music!", ofGetWidth() / 2 - 50, ofGetHeight() / 2);
    }
    vector<float> amplitudes = visualizer.getAmplitudes();
    if (mode == '1') {
        drawMode1(amplitudes);
    } else if (mode == '2') {
        drawMode2(amplitudes);
    } else if (mode == '3') {
        drawMode3(amplitudes);
    }

    // ofDrawBitmapString("Current Mouse Position: " + ofToString(cur_x) + ", " + ofToString(cur_y), 0, 30);
}
void ofApp::drawMode1(vector<float> amplitudes) {
    ofFill();        // Drawn Shapes will be filled in with color
    ofSetColor(256); // This resets the color of the "brush" to white
    ofDrawBitmapString("Rectangle Height Visualizer", 0, 15);
    ofSetColor(0, 0, ofRandom(255));
   for (int i=0; i<64; i++){
    ofDrawRectRounded((ofGetWidth()/64)*i, ofGetHeight() - 100, ofGetWidth()/64, amplitudes[i],10); //Draws all the bars
   }
}
void ofApp::drawMode2(vector<float> amplitudes) {
    ofSetLineWidth(5); // Sets the line width
    ofNoFill();        // Only the outline of shapes will be drawn
    ofSetColor(256);   // This resets the color of the "brush" to white
    ofDrawBitmapString("Circle Radius Visualizer", 0, 15);
    int bands = amplitudes.size();
    for (int i = 0; i < bands; i++) {
        ofSetColor((bands - i) * 32 % 256, 18, 144); // Color varies between frequencies
        ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, amplitudes[0] / (i + 1));
    }
}

void ofApp::drawMode3(vector<float> amplitudes) {
    ofSetColor(256); // This resets the color of the "brush" to white
    ofDrawBitmapString("Disco Visualizer", 0, 15);
    // YOUR CODE HERE
    ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255));
    ofSetBackgroundColor(ofRandom(255), ofRandom(255), ofRandom(255));
    for (int i=0; i<64; i++){
        ofDrawCircle(ofRandom(0,ofGetWidth()), ofRandom(0,ofGetHeight()), ofRandom(10,30)); //Draws all the circles
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    // This method is called automatically when any key is pressed
    switch (key) {
    case 'p':
        if (playing) {
            sound.stop();
        } else {
            sound.play();
        }
        playing = !playing;
        break;
    case 'd':
        if (songNum<3){
            songNum++;
            setup();
            sound.play();
        }
        else{
            songNum=0;
            setup();
            sound.play();
        }
        break;
    case 'a':
        ampUpdate = !ampUpdate;
        break;
    case '=':
        if (sound.getVolume()<1) {
            sound.setVolume(sound.getVolume()+0.2);
        }
        break;
    case '-':
        if (sound.getVolume()>0) {
            sound.setVolume(sound.getVolume()-0.2);
        }
        break;
    case 'l':
        loop = !loop;
        replay = false;
        shuffle = false;
        break;
    case 'r':
        replay = !replay;
        loop = false;
        shuffle = false;
        break;
    case 'b':
        shuffle = !shuffle;
        replay = false;
        loop = false;
        break;
    case '1':
        mode = '1';
        break;
    case '2':
        mode = '2';
        break;
    case '3':
        mode = '3';
        break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    cur_x = x;
    cur_y = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    int newX=0;
    int newY=ofGetHeight() - 60;
    float pos = playing ? progress : lastPos;
    int percent = pos * 100;
    if(x>=newX && x<=newX+float(ofGetWidth()) && y>=newY && y<=newY+ofGetHeight() ){
        percent = (x-newX)/float(ofGetWidth());
        sound.setPosition(x/float(ofGetWidth()));
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
}
//--------------------------------------------------------------