#include "ofApp.h"
#include "Sorting.h"

// ------------------------------ RESOURCS ---------------------------------------------
//
// Regarding threading
//https://openframeworks.cc/ofBook/chapters/threads.html#whatsathreadandwhentouseit
//
//--------------------------------------------------------------------------------------

using std::vector;
using std::string;

ofApp::ofApp() :is_vertical(true), left_index(-1), right_index(-1), user_selection(0) {
  SortingApp = new SortThread();
}

ofApp::~ofApp() {
  delete SortingApp;
}

void ofApp::setup() {

  // Set the collor pattern
  colors.resize(5);
  colors[0] = ofColor::navy;
  colors[1] = ofColor::blueSteel;
  colors[2] = ofColor::seaGreen;
  colors[3] = ofColor::cadetBlue;
  colors[4] = ofColor::greenYellow;

  // Set pixel density
  ofTrueTypeFont::setGlobalDpi(96);

  // load the desired font / title
  font.load("sans-serif", 12);
  sorting_info = "SORT: THE APP";

  // OSC revover will be listening on port 12345
  receiver.setup(PORT);

  ofSetLogLevel(OF_LOG_VERBOSE);

  // ----------------------------- CONTROL PANEL ----------------------------------------
  settings_panel = gui.addPanel("Settings", ofJson({ {"width", 300} }));
  settings_panel->setPosition(ofGetWidth() - settings_panel->getWidth(), 0);
  settings_panel->getHeader()->setBackgroundColor(ofColor::mediumSlateBlue);
  settings_panel->setShowHeader(true);

  // First add status info to display info to the user
  status_info = settings_panel->addGroup("Status", ofJson({ {"width", 300} }));
  status_info->add(add_load_file);
  status_info->add(sorting_info);
  status_info->setShowHeader(false);

  // Sorting strategy group
  sorting_parameters.setName("Select Sorting Strategy");
  sorting_parameters.add(random_shufle.set("Random shuffle", false));
  sorting_parameters.add(bubblesort_abc.set("Bubble sort alphabetically", false));
  sorting_parameters.add(bubblesort_length.set("Bubble sort by word length", false));
  sorting_parameters.add(quicksort_abc.set("Quicksort alphabetically", false));
  sorting_parameters.add(quicksort_length.set("Quicksort by word length", false));

  // display options group
  display_parameters.setName("Select display option");
  display_parameters.add(horizontal_display.set("Horizontal Display", false));
  display_parameters.add(vertical_display.set("Vertical Display", false));

  // add sorting strategy group
  sorting_toggles = settings_panel->addGroup(sorting_parameters, ofJson({ {"width", 300} }));
  sorting_toggles->setExclusiveToggles(true);
  sorting_toggles->setConfig(ofJson({ {"type", "radio"} }));
  sorting_toggles->getHeader()->setBackgroundColor(ofColor::mediumSlateBlue);

  // add listener to the sorting strategy group
  sorting_toggles->getActiveToggleIndex().addListener(this, &ofApp::HandleUserEntry);

  // add the display group
  display_toggles = settings_panel->addGroup(display_parameters, ofJson({ {"width", 300} }));
  display_toggles->setExclusiveToggles(true);
  display_toggles->setConfig(ofJson({ {"type", "radio"} }));
  display_toggles->getHeader()->setBackgroundColor(ofColor::mediumSlateBlue);
  display_toggles->setActiveToggle(1); // default to vertical

  // add listener to the display group
  display_toggles->getActiveToggleIndex().addListener(this, &ofApp::DisplayOption);

  // THE MENU
  fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
  fbo.setAnchorPoint(0, 0);
  data.add(add_load_file.set("Load data file..."));
  ofxGuiContainer* menu = gui.addMenu(data);
  // menu->loadTheme("theme_light.json", true);
  add_load_file.addListener(this, &ofApp::SeletDataFile);
  // ------------------------------------------------------------------------------------
}

void ofApp::exit() {
  sorting_toggles->getActiveToggleIndex().removeListener(this, &ofApp::HandleUserEntry);
  display_toggles->getActiveToggleIndex().removeListener(this, &ofApp::DisplayOption);
}

void ofApp::update() {
  // check for waiting messages
  while (receiver.hasWaitingMessages()) {

    // get the next message
    ofxOscMessage m;
    receiver.getNextMessage(m);

    if (m.getNumArgs() == 1) {
      string type = m.getTypeString();
      user_selection = m.getArgAsInt(0);
      HandleUserEntry(user_selection);
    }
  }
}

void ofApp::draw() {

  fbo.draw(0, 0);

  ofBackground(ofColor::floralWhite);

  if (word_list.empty()) {
    return;
  }

  int wWidth = ofGetWindowWidth();
  int wHeihgt = ofGetWindowHeight();

  mutex.lock();

  for (unsigned i = 0; i < word_list.size(); i++) {
    int cIndex = i % 5;
    ofSetColor(colors[cIndex].r, colors[cIndex].g, colors[cIndex].b);

    // determine coordinates
    float x = 0;
    float y = 0;

    // Scale differently depending on orientation
    if (is_vertical) {
      float width_scale = wWidth / word_list.size();
      x = (i + 0.5) * width_scale;
      y = wHeihgt / 3.0;
    } else {
      float hight_scale = wHeihgt / word_list.size();
      x = wWidth / 4;
      y = (i + 5)* hight_scale;
    }

    std::string text = is_vertical ? ToVerticalText(word_list[i]) : word_list[i];

    if (i == left_index || i == right_index) {
      ofNoFill();
      ofDrawRectangle(font.getStringBoundingBox(text, x, y));
    }

    font.drawString(text, x, y);
  }

  condition_variable.signal();
  mutex.unlock();
}

// KEYBOARD SHORTCUTS
void ofApp::keyPressed(int key) {
  // convert input to uppercase to avoid differences
  int Ukey = toupper(key);

  if (Ukey == 'L') {                         // Load a new data file
    SeletDataFile();

  } else if (Ukey == 'H') {                  // Horizontal display
    display_toggles->setActiveToggle(0);
    HandleUserEntry(key);

  } else if (Ukey == 'V') {                  // Veritical display
    display_toggles->setActiveToggle(1);
    HandleUserEntry(key);

  } else {                                   // Select sorting algorithm.
    int sel = key - '0';

    if (sel >= 0 && sel <= 4) {
      sorting_toggles->setActiveToggle(sel);
      HandleUserEntry(sel);
    }
  }
}

// All the unused methods from App.cpp folded here
#pragma region
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
#pragma endregion 


// insert /n to to display vertically
std::string ofApp::ToVerticalText(const std::string& originString) {
  std::string str = "";
  std::string returnChar = "\n";
  for (unsigned i = 0; i < originString.size(); i++) {
    str = str + originString[i] + returnChar;
  }
  return str;
}

void ofApp::LoadDataFile(string fileName) {
  // load the txt document into a ofBuffer
  ofBuffer buffer = ofBufferFromFile(fileName);

  // get text file content as a string
  string  content = buffer.getText();

  // split string using "\r\n" as delimeter and ignore empty strings and trim white_space (befor/after whitespace)
  word_list = ofSplitString(content, "\r\n", true, true);

  // reset user_selection
  user_selection = 0;

  // reset the swapping indecies (-1 means NO pair of item is selected)
  left_index = -1;
  right_index = -1;
}

void ofApp::HandleUserEntry(int& selecltion) {

  // first make sure that a file has already been loaded..(i.e. we have something to sort)
  if (word_list.empty())
  {
    sorting_info = "Please load data file first...";
    return;
  }

  switch (selecltion) {

  case 0: {                                                 // CASE 0: shuffle
    sorting_info = "0 - random shuffle";
    user_selection = selecltion;
    std::random_shuffle(word_list.begin(), word_list.end());
    left_index = -1;
    right_index = -1;
  }
  break;
  case 1:                                                  // CASE 1: Bubblesort alphabetically
    sorting_info = "1 - Bubblesort alphabetically";
    user_selection = selecltion;
    SortingApp->setup(this);
    SortingApp->startThread();
    break;
  case 2:                                                  // CASE 2: Bubblesort by word length
    sorting_info = "2 - Bubblesort by word length";
    user_selection = selecltion;
    SortingApp->setup(this);
    SortingApp->startThread();
    break;
  case 3:                                                  // CASE 3: Quicksort alphabetically
    sorting_info = "3 - Quicksort alpabetically";
    user_selection = selecltion;
    SortingApp->setup(this);
    SortingApp->startThread();
    break;
  case 4:                                                 // CASE 4: Quicksort by word length
    sorting_info = "4 - Quicksort by word length";
    user_selection = selecltion;
    SortingApp->setup(this);
    SortingApp->startThread();
    break;

  case 'h':
  case 'H':                                               // CASE 'h'/'H': Display Horizontally
    is_vertical = false;
    break;

  case 'v':
  case 'V':
    is_vertical = true;                                  // CASE 'v'/'V': Display Vertically
    break;

  default:
    sorting_info = "Invalid Selection";
  }
}

void ofApp::DisplayOption(int& selecltion) {
  int select = (selecltion == 0) ? 'H' : 'V';
  HandleUserEntry(select);
}

void ofApp::SeletDataFile(){
  //Open the Open File Dialog
  ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a text file to sort", false, "..//data");
  if (openFileResult.bSuccess) {

    //We have the file, exisit and process then
    ofFile file(openFileResult.getPath());
    if (file.exists()) {
      LoadDataFile(file.getFileName());
    }
    else {
      sorting_info = "File does not exisit";
    }
  }
}