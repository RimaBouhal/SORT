#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#include <string>
#include <vector>
#include <string>
#include<Poco/Condition.h>

class SortThread;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		

    // ==========================================================================   MY CODE  ==========================================================================================
    
    ofApp();
    ~ofApp();

    SortThread* SortingApp;
    string ToVerticalText(const std::string& originString);
    void HandleUserEntry(int key);

    ofTrueTypeFont    font;
    string            sorting_info;

    std::vector <ofPoint> word_postions;
    std::vector <string> word_list;
    std::vector<ofColor> colors;

    int left_index;
    int right_index;
    int user_selection;

    // Wait for draw to run before animating
    Poco::Condition condition_variable;

    // Syncronyse acess between main/sorting threads
    ofMutex mutex;
};
