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
void ofApp::setup(){

  // set the color array
  colors.resize(5);
  colors[0] = ofColor::blue;
  colors[1] = ofColor::gold;
  colors[2] = ofColor::orange;
  colors[3] = ofColor::navy;
  colors[4] = ofColor::orangeRed;

  // set the pixel density
  ofTrueTypeFont::setGlobalDpi(96);

  // load the desired font
  font.load("sans-serif", 14);
  sorting_info = "1 - unsorted list";

  // load the txt document into a ofBuffer
  ofBuffer buffer = ofBufferFromFile("data.txt");
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

//--------------------------------------------------------------
void ofApp::update(){
// To use for ofx reciver
}

//--------------------------------------------------------------
void ofApp::draw(){
  if (word_list.empty()) {
    ofSetColor(ofColor::red);
    ofDrawBitmapString("Error: Missing data file (data.txt) in bin\\Data\\", 50, 50, 10);
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

  // menu-instructions
  ofSetColor(ofColor::purple);
  string menuList("\nPress 1 for no sort");
  menuList.append("\nPress 2 for bubble sort alphabetically");
  menuList.append("\nPress 3 for bubble sort word length");
  menuList.append("\nPress 4 for quicksort alphabetically");
  menuList.append("\nPress 5 for quicksort word length");
  ofDrawBitmapString(menuList, 20, 20, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  user_selection = key - '0';
  HandleUserEntry(user_selection);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

std::string ofApp::ToVerticalText(const std::string& originString) {
  std::string str = "";
  std::string returnChar = "\n";
  for (unsigned i = 0; i < originString.size(); i++) {
    str = str + originString[i] + returnChar;
  }
  return str;
}

void ofApp::HandleUserEntry(int selecltion) {

  switch (selecltion) {
  case 1: // setup (reload)
    sorting_info = "1 - unsorted list";
    setup();
    break;
  case 2: // bubble sort alphabetically
    sorting_info = "2 - bubble sorting alphabetically";
    SortingApp->setup(this);
    SortingApp->startThread();
    break;
  case 3: // bubble sort by word length
    sorting_info = "3 - bubble sorting on word length";
    SortingApp->setup(this);
    SortingApp->startThread();
    break;
  case 4: // quick sort alphabetically
    sorting_info = "4 - quick-sorting alphabetically";
    SortingApp->setup(this);
    SortingApp->startThread();
    break;
  case 5: // quick sort by word length
    sorting_info = "5 - quick-sorting on word length";
    SortingApp->setup(this);
    SortingApp->startThread();
    break;
  default:
    sorting_info = "Invalid Selection";
  }

}
