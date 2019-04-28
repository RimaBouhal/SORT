#include "ofApp.h"
#include "Sorting.h"

using std::vector;
using std::string;

ofApp::ofApp() {
  SortingApp = new SortThread();
}

ofApp::~ofApp() {
  delete SortingApp;
}

//--------------------------------------------------------------
void ofApp::setup() {

  // set the color array
  colors.resize(5);
  colors[0] = ofColor::turquoise;
  colors[1] = ofColor::lightBlue;
  colors[2] = ofColor::lightGreen;
  colors[3] = ofColor::darkBlue;
  colors[4] = ofColor::cadetBlue;

  // set the pixel density
  ofTrueTypeFont::setGlobalDpi(96);

  // load the desired font
  font.load("sans-serif", 14);

  sorting_info = "SORTING ALGORITHIM VISUALISER";

  // OSC revover listening on port 12345
  receiver.setup(PORT);
}

//--------------------------------------------------------------
void ofApp::update() {
  // check for waiting messages
  while (receiver.hasWaitingMessages()) {

    // get the next message
    ofxOscMessage m;
    receiver.getNextMessage(m);

    if (m.getNumArgs() == 1)
    {
      string type = m.getTypeString();
      user_selection = m.getArgAsInt(0);
      HandleUserEntry(user_selection);
    }
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofBackground(ofColor::floralWhite);

  // menu-instructions
  ofSetColor(ofColor::black);
  string menuList("\nPress 0 to select a file to sort");
  menuList.append("\nPress 1 for no sort");
  menuList.append("\nPress 2 for bubble sort alphabetically");
  menuList.append("\nPress 3 for bubble sort by word length");

  menuList.append("\nPress 4 for quicksort alphabetically");
  menuList.append("\nPress 5 for quicksort by word length");

  ofDrawBitmapString(menuList, 20, 20, 10);

  if (word_list.empty()) {
    ofSetColor(ofColor::darkRed);
    ofDrawBitmapString("Error: Missing data file (data.txt) in bin\\Data\\", 500, 60);
    return;
  }

  int wWidth = ofGetWindowWidth();
  int wHeihgt = ofGetWindowHeight();

  int ws = wWidth / word_list.size();

  int vLocation = wHeihgt / 4;
  int hLocation = 1;

  ofDrawBitmapString(sorting_info, 500, 50);

  mutex.lock();
  for (unsigned i = 0; i < word_list.size(); i++)
  {

    int cIndex = i % 5;
    ofSetColor(colors[cIndex].r, colors[cIndex].g, colors[cIndex].b);

    //  // determin the x,y
    float x = word_postions[i].x * ws;
    float y = vLocation;

    std::string text = ToVerticalText(word_list[i]);
    if (i == left_index || i == right_index) {
      ofNoFill();
      ofDrawRectangle(font.getStringBoundingBox(text, x, y));
    }

    font.drawString(text, x, y);
  }

  condition_variable.signal();
  mutex.unlock();



  // -------------------------------------------------------------------------------  CREATE BUTTONS  ---------------------------------------------------------------------------------------------

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void ofApp::keyPressed(int key) {
  user_selection = key - '0';
  HandleUserEntry(user_selection);
}

void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

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

std::string ofApp::ToVerticalText(const std::string& originString) {
  std::string str = "";
  std::string returnChar = "\n";
  for (unsigned i = 0; i < originString.size(); i++) {
    str = str + originString[i] + returnChar;
  }
  return str;
}

void ofApp::LoadDataFile(string file_name) {
  // load the txt document into a ofBuffer
  ofBuffer buffer = ofBufferFromFile(file_name);
  string   content = buffer.getText();

  // split string and ignore empty strings and trim white space
  word_list = ofSplitString(content, "\r\n", true, true);

  word_postions.resize(word_list.size());
  for (unsigned i = 0; i < word_list.size(); i++) {
    word_postions[i] = ofPoint(i + 0.5, 0, 0);
  }

  user_selection = 0; // user selection

  left_index = -1;
  right_index = -1;
}

void ofApp::HandleUserEntry(int selecltion) {
  switch (selecltion) {
  case 1: // setup (reload)
    sorting_info = "UNSORTED LIST";
    setup();
    break;
  case 2: // bubble sort alphabetically
    sorting_info = "BUBBLE-SORTING ALPHABETICALLY...";
    SortingApp->setup(this);
    SortingApp->startThread();
    break;
  case 3: // bubble sort by word length
    sorting_info = "BUBBLE SORTING BY WORD LENGTH...";
    SortingApp->setup(this);
    SortingApp->startThread();
    break;
  case 4: // quick sort alphabetically
    sorting_info = "QUICKSORTING ALPHABETICALLY...";
    SortingApp->setup(this);
    SortingApp->startThread();
    break;
  case 5: // quick sort by word length
    sorting_info = "QUICKSORTING BY WORD LENGTH...";
    SortingApp->setup(this);
    SortingApp->startThread();
    break;
  case 0:
  {
    ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a .txt file to sort", false, file_path);

    if (openFileResult.bSuccess) {
      ofLogVerbose("User selected a file");

      ofFile file(openFileResult.getPath());

      if (file.exists()) {
        LoadDataFile(file.getFileName());
      }
      else {
        ofLogVerbose("File does not exist");
      }
    }
  }
  default:
    sorting_info = "INVALID SELECTION";
  }
}