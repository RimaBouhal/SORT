#pragma once

#include <string>
#include <vector>
#include <string>
#include<Poco/Condition.h>

#include "ofxOsc.h"
#include "ofMain.h"
#include "ofxGuiExtended.h"

// listening port for OSC Controller
#define PORT 12345

class SortThread;

class ofApp : public ofBaseApp {
public:
  ofApp();
  ~ofApp();
  void setup();
  void update();
  void draw();

  void exit();

  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y);
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void mouseEntered(int x, int y);
  void mouseExited(int x, int y);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);

  SortThread* SortingApp;
  string ToVerticalText(const std::string& originString);
  void HandleUserEntry(int& key);
  void LoadDataFile(string fileName);

  ofTrueTypeFont    font;

  std::vector <string> word_list; // Holds the position of the word
  std::vector<ofColor> colors;   // Gives the sorted display a color pattern

  int left_index;
  int right_index;
  int user_selection;
  bool is_vertical;

  ofxOscReceiver receiver;    // osc reciver

  // ------------------------------- NOTE -----------------------------------------
  // condition_variable is used in combination with a
  // std::mutex to facilitate inter - thread communication.
  //
  // https://en.cppreference.com/w/cpp/thread/condition_variable
  // -------------------------------------------------------------------------------

  Poco::Condition condition_variable;  // Wait for Draw to run
  ofMutex mutex; // Syncronize acess between the main thread and the sorting thread


private:

  ofxGui gui;
  ofxGuiPanel* settings_panel;

  // SORTING GROUP (to act as radio buttons)
  ofxGuiGroup *sorting_toggles;
  ofParameterGroup  sorting_parameters;
  ofParameter<bool> bubblesort_abc;
  ofParameter<bool> bubblesort_length;
  ofParameter<bool> quicksort_abc;
  ofParameter<bool> quicksort_length;
  ofParameter<bool> random_shufle;

  // DISPLAY GROUP (to act as radio buttons)
  ofxGuiGroup *display_toggles;
  ofParameterGroup  display_parameters;
  ofParameter<bool> horizontal_display;
  ofParameter<bool> vertical_display;

  // display status
  ofxGuiGroup *status_info;

  // sorting status
  ofParameter<string> sorting_info;

  // THE MENU
  ofFbo fbo;
  ofParameterGroup data;
  ofParameter<void> add_load_file;

  void SeletDataFile();
  void DisplayOption(int& key);
};