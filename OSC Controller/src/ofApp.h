#pragma once

#include "ofMain.h"
#include <string>
#include "ofxOsc.h"
#include "ofxGuiExtended.h"


// listening port
#define DEFAULT_PORT 12345
#define LOCAL_HOST "localhost"

class ofApp : public ofBaseApp {
public:
  ofApp();
  ~ofApp();
  void setup();
  void update();
  void draw();

  void exit();

  void keyPressed(int key) {};
  void keyReleased(int key) {};
  void mouseMoved(int x, int y) {};
  void mouseDragged(int x, int y, int button) {};
  void mousePressed(int x, int y, int button) {};
  void mouseReleased(int x, int y, int button) {};
  void mouseEntered(int x, int y) {};
  void mouseExited(int x, int y) {};
  void windowResized(int w, int h) {};
  void dragEvent(ofDragInfo dragInfo) {};
  void gotMessage(ofMessage msg) {};

  // -------------------------------------------- MY DATA ----------------------------------------------------
  void buttonPressed(const void * sender);

  // osc reciver
  ofxOscSender sender;

private:

  ofxGui gui;
  ofxGuiPanel* settings_panel;

  // --------------------------------- NOTE ------------------------------------------
  //   This OSC controller is based off of the OSC project example from within the 
  //   openframworks package of examples that comes with it's instalation. 
  //
  //   For the purposes of my final project, I made this project to
  //   act in coordinance with my other controlls in my project, I did this by 
  //   corresponing the meaning of each of the shortcut keys. As one can tell
  //   the code listed here for my control panel matches almost exactly the code for
  //   the control panel I used in the main part of my project (it's the same commands for
  //   the same program, the only deference is that this one operates remotley).
  //
  //  Resources: 
  //    https://www.geeksforgeeks.org/program-to-validate-an-ip-address/
  //    This is where I got the code in lines 91 -92 of this file
  // ----------------------------------------------------------------------------------

  // IP and port
  ofParameterGroup  ip_parameters;
  ofParameter<string> ip_address;
  ofParameter<int> port_number;
  ofParameter<void> connect_button{ "Click to connect" };
  ofParameterGroup connect_group{ "Connect",connect_button };

  ofxGuiGroup *connectButtons;

  // sorting group (to function as radio buttons)
  ofxGuiGroup *sorting_toggles;
  ofParameterGroup  sorting_parameters;
  ofParameter<bool> bubblesort_abc;
  ofParameter<bool> bubblesort_length;
  ofParameter<bool> quicksort_abc;
  ofParameter<bool> quicksort_length;
  ofParameter<bool> random_shufle;

  // display group (to function as radio buttons)
  ofxGuiGroup *display_toggles;
  ofParameterGroup  display_parameters;
  ofParameter<bool> horizontal_display;
  ofParameter<bool> vertical_display;

  // display status
  ofParameterGroup status_group;
  ofxGuiGroup *status_info;
  ofParameter<string> sorting_info;

  void HandleUserEntry(int& key);
  void DisplayOption(int& key);

  int valid_digit(char *ip_str);
  int is_valid_ip(char *ip_str);
};