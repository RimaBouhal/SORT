#include "ofApp.h"

using std::vector;
using std::string;

ofApp::ofApp() {
}

ofApp::~ofApp() {
}

void ofApp::setup() {

  ofSetBackgroundColor(ofColor::lavender);

  // setting pixel density
  ofTrueTypeFont::setGlobalDpi(96);

  // load the desired font
  sorting_info = "";


  // BUILD THE GUI PANEL
  settings_panel = gui.addPanel("Settings", ofJson({ {"width", 300} }));
  settings_panel->setPosition(20, 20);
  settings_panel->getHeader()->setBackgroundColor(ofColor(51,0,51));
  settings_panel->setShowHeader(true);

  // IP PARAMETERS
  settings_panel->add<ofxGuiTextField>(ip_address.set("IP", "xxx.xxx.xxx.xxx"));
  settings_panel->add<ofxGuiIntInputField>(port_number.set("Port number", 12345));

  settings_panel->add(connect_group);
  connect_button.addListener(this, &ofApp::buttonPressed);

  status_group.add(sorting_info);
  status_info = settings_panel->addGroup(status_group, ofJson({ {"width", 300} }));
  status_info->getHeader()->setHidden(true);

  //------------------------  THE CONTROL PANEL -------------------------------------
  // Notice that this is a repeat of what I had in my main project

  // Sorting strategy group
  sorting_parameters.setName("Select Sorting Strategy");
  sorting_parameters.add(random_shufle.set("Random shuffle", false));
  sorting_parameters.add(bubblesort_abc.set("Bubble sort alphabetical order", false));
  sorting_parameters.add(bubblesort_length.set("Bubble sort word length order", false));
  sorting_parameters.add(quicksort_abc.set("Quick sort alphabetical order", false));
  sorting_parameters.add(quicksort_length.set("Quick sort word length order", false));

  // display options group
  display_parameters.setName("Select display option");
  display_parameters.add(horizontal_display.set("Horizontal display", false));
  display_parameters.add(vertical_display.set("Vertical display", false));

  // add sorting strategy group
  sorting_toggles = settings_panel->addGroup(sorting_parameters, ofJson({ {"width", 300} }));
  sorting_toggles->setExclusiveToggles(true);
  sorting_toggles->setConfig(ofJson({ {"type", "radio"} }));
  sorting_toggles->getHeader()->setBackgroundColor(ofColor(51, 0, 51));

  // add listener to the sorting strategy group
  sorting_toggles->getActiveToggleIndex().addListener(this, &ofApp::HandleUserEntry);

  // add the display group
  display_toggles = settings_panel->addGroup(display_parameters, ofJson({ {"width", 300} }));
  display_toggles->setExclusiveToggles(true);
  display_toggles->setConfig(ofJson({ {"type", "radio"} }));
  display_toggles->getHeader()->setBackgroundColor(ofColor(51, 0, 51));
  display_toggles->setActiveToggle(1); // default to vertical

  // add listener to the sorting group
  display_toggles->getActiveToggleIndex().addListener(this, &ofApp::DisplayOption);
}


void ofApp::exit() {
  sorting_toggles->getActiveToggleIndex().removeListener(this, &ofApp::HandleUserEntry);
  display_toggles->getActiveToggleIndex().removeListener(this, &ofApp::DisplayOption);
}


void ofApp::update() {
}


void ofApp::draw() {
  ofDrawBitmapString(sorting_info, 50, 50, 10);
}


void ofApp::HandleUserEntry(int& selecltion) {
  ofxOscMessage m;
  m.setAddress("/SStrategy");
  m.addIntArg(selecltion);
  sender.sendMessage(m);
}


void ofApp::DisplayOption(int& selection) {
  int ch = (selection == 0) ? 'H' : 'V';
  ofxOscMessage m;
  m.setAddress("/SStrategy");
  m.addIntArg(ch);
  sender.sendMessage(m);
}


void ofApp::buttonPressed(const void * arg) {

  bool success = false;

  // check if the ip is in the format xx.xx.xx.xx
  string ipstring = ip_address.toString();
  if (is_valid_ip((char*)ipstring.c_str()) == 1) {
    success = sender.setup(ip_address.toString(), port_number);
  } else {
    ip_address = LOCAL_HOST;
    success = sender.setup(LOCAL_HOST, DEFAULT_PORT);
  } if (success) {
    status_info->setBackgroundColor(ofColor::green);
    sorting_info = "Succefully connetted to " + ip_address.toString();
  } else {
    status_info->setBackgroundColor(ofColor::red);
    sorting_info = "Failed to connect to " + ip_address.toString();
  }
}


// very simple way to validate an ip address.
int ofApp::valid_digit(char *ip_str) {
  while (*ip_str) {
    if (*ip_str >= '0' && *ip_str <= '9')
      ++ip_str;
    else
      return 0;
  }
  return 1;
}


/* return 1 if IP string is valid, else return 0 */
int ofApp::is_valid_ip(char *ip_str) {
  int num, dots = 0;
  char *ptr;

  if (ip_str == NULL) {
    return 0;
  }

  ptr = strtok(ip_str, ".");

  if (ptr == NULL) {
    return 0;
  }

  while (ptr) {

    /* after parsing string, it must contain only digits */
    if (!valid_digit(ptr)) {
      return 0;
    }

    num = atoi(ptr);

    /* check for valid IP address */
    
    if (num >= 0 && num <= 255) {
      /* parse remaining string */

      ptr = strtok(NULL, ".");
      if (ptr != NULL)
        ++dots;

    } else {

      return 0;
    }
  }

  /* valid IP string must contain 3 dots */
  if (dots != 3) {
    return 0;
  }
  return 1;
}