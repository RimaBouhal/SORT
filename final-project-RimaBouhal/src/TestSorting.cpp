#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "Sorting.h"
#include "ofApp.h"


TEST_CASE("Test Bubble Sort Alphabitically", "[BBS Alphabitically]") {

  ofApp*AppToTest = new ofApp();
  AppToTest->SortingApp->setup(AppToTest);
  AppToTest->setup();

  
  // copy the word list
  std::vector<string> words = AppToTest->word_list;

  // sort alphabitically using sdd::sort
  std::sort(words.begin(), words.end(), SortThread::CompareAlphabetically);

  // sort word list using bubble sort
  AppToTest->SortingApp->BubbleSort(SortThread::CompareAlphabetically, true);

  REQUIRE(words == AppToTest->wordList);

  AppToTest->SortingApp->stopThread();

  delete AppToTest;

}

TEST_CASE("Test Bubble Sort Word Length", "[BBS WordLength]") {

  ofApp*AppToTest = new ofApp();
  AppToTest->SortingApp->setup(AppToTest);
  AppToTest->setup();

  // copy the word list
  std::vector<string> words = AppToTest->word_list;

  // sort alphabitically using sdd::sort
  std::sort(words.begin(), words.end(), SortThread::CompareLength);

  // sort word list using our bubble sort
  AppToTest->SortingApp->BubbleSort(SortThread::CompareLength, true);

  REQUIRE(words == AppToTest->wordList);

  delete AppToTest;

}

// ------------------------------------------------------------------------------- QUICKSORT -------------------------------------------------------------------------------------

TEST_CASE("Test QuickSort Alphabitically", "[Quicksort]") {

  ofApp*AppToTest = new ofApp();
  AppToTest->SortingApp->setup(AppToTest);
  AppToTest->setup();


  // copy the word list
  std::vector<string> words = AppToTest->word_list;

  // sort alphabitically using sdd::sort
  std::sort(words.begin(), words.end(), SortThread::CompareAlphabetically);

  // sort word list using bubble sort
  AppToTest->SortingApp->QuickSort(0,0, SortThread::CompareLength);

  REQUIRE(words == AppToTest->wordList);

  AppToTest->SortingApp->stopThread();

  delete AppToTest;

}

TEST_CASE("Test Bubble Sort Word Length", "[Quicksort]") {

  ofApp*AppToTest = new ofApp();
  AppToTest->SortingApp->setup(AppToTest);
  AppToTest->setup();

  // copy the word list
  std::vector<string> words = AppToTest->word_list;

  // sort alphabitically using sdd::sort
  std::sort(words.begin(), words.end(), SortThread::CompareLength);

  // sort word list using our bubble sort
  AppToTest->SortingApp->QuickSort(0,0, SortThread::CompareLength);

  REQUIRE(words == AppToTest->wordList);

  delete AppToTest;

}

// other things to test 
