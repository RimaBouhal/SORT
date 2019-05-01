#pragma once
#include <vector>
#include "ofApp.h"

using std::string;

class SortThread : public ofThread {

public:

  SortThread() {
    openGLApp = nullptr;
  }

  void setup(ofApp* app) {
    openGLApp = app;
  }

  void threadedFunction() {

    if (openGLApp->user_selection == 1) {
      // buble sort alphabitically
      BubbleSort(SortThread::CompareAlphabetically);
    }
    else if (openGLApp->user_selection == 2) {
      // buble sort by word length
      BubbleSort(SortThread::CompareLength);
    }
    else if (openGLApp->user_selection == 3) {
      // quick sort alphabitically
      QuickSort(0, openGLApp->word_list.size() - 1, SortThread::CompareAlphabetically);
    }
    else if (openGLApp->user_selection == 4) {
      // quick sort by word length
      QuickSort(0, openGLApp->word_list.size() - 1, SortThread::CompareLength);
    }
  }


  // -------------------------------------------------------------------------  BUBBLE SORT  --------------------------------------------------------------------------------------------
  //(For Testing call with uncloked =true)
  void BubbleSort(bool(*compare)(const string&, const std::string&), bool uncloked = false) {
    bool swapped;
    vector<string>& vec = openGLApp->word_list;

    for (int i = 0; i < vec.size() - 1; i++) {
      swapped = false;

      for (int j = 0; j < vec.size() - i - 1; j++) {
        if (compare(vec[j + 1], vec[j])) {
          swap(vec[j + 1], vec[j], j + 1, j, uncloked);
          swapped = true;
        }
      }

      if (swapped == false) {
        break;
      }
    }
  }

  // ---------------------------------------------------------------------------  QUICKSORT  -------------------------------------------------------------------------------------------

  int Partition(int low, int high, bool(*compare)(const string&, const std::string&)) {
    vector<string>& vec = openGLApp->word_list;
    string pivot = vec[high];    // pivot 
    int i = (low - 1);  // Index of smaller element 

    for (int j = low; j <= high - 1; j++) {
      // If current element is smaller than or 
      // equal to pivot 
      if (compare(vec[j], pivot)) {
        i++;    // increment index of smaller element
        swap(vec[i], vec[j], i, j);
      }
    }
    swap(vec[i + 1], vec[high], i + 1, high);
    return (i + 1);
  }

  void QuickSort(int low, int high, bool(*compare)(const string&, const std::string&)) {
    if (low < high)
    {
      // pi is partitioning index, arr[p] is now at right place
      int pi = Partition(low, high, compare);

      // Separately sort elements before 
      // partition and after partition 
      QuickSort(low, pi - 1, compare);
      QuickSort(pi + 1, high, compare);
    }
  }

  // ---------------------------------------------------------------------------  MERGESORT  ------------------------------------------------------------------------------------------

  int FindMiddle(bool(*compare)(const string&, const std::string&), int low, int high) {
    return (1 + high) / 2;
  }

  void MergeSort(bool(*compare)(const string&, const std::string&), int low, int high) {
    vector<string>& vec = openGLApp->word_list;
    int middle = FindMiddle(compare, low, high);

    int left_size = middle - low + 1;
    int right_size = high - middle;

    // make temporary halves and copy their data
    string left_temp = vec[left_size];
    string right_temp = vec[right_size];

    // Call MergeSort on both halves

  }

  // -----------------------------------------------------------------------  SWAP AND COMPARE  -------------------------------------------------------------------------------------
  // for testing: unlocked is set true

  void swap(string& left, string& right, int leftIndex, int rightIndex, bool unlocked = false) {
    //  wait for the draw function (main update/draw() thread) to signal the condition
    // this guarantees a draw before each swap

    if (unlocked == false) {
      openGLApp->mutex.lock();
      openGLApp->condition_variable.wait(openGLApp->mutex);

      openGLApp->left_index = leftIndex;
      openGLApp->right_index = rightIndex;
    }

    string temp = left;
    left = right;
    right = temp;

    if (unlocked == false) {
      openGLApp->mutex.unlock();
    }
  }

  static bool CompareAlphabetically(const string& left, const string& right) {
    return left < right;
  }

  static bool CompareLength(const string& left, const string& right) {
    return left.length() < right.length();
  }

  // pointer to the main OpenGL Application
  ofApp* openGLApp;
};