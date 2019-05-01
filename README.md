# SORT: a learning tool for sorting algorithims 
### by Rima Boual

This application can take in lists of words or phrases, and can demonstrate how each can be sorted alphabetically or 
by string length. 
--------------------------------------------------------------------------------------------------------------------
## Features: 

One thing I placed heavy emphasis on when it came to the making of this app was it's user interface. Af of right now, 
one can control my app three different ways. 

	1) Keyboard shortcuts

	This was the simplest of controls to implement, for it did not need to include any external libaries, API's or
	anything. This was the first User interface I created for the app, and while I meant to remove it in the end, I 
	decided to keep it for the sake of it's convenience.

	Below is a brief overview of their functionalities, please not that they are all independant of casing.

		0. Will un-sort the list.
		1. Will use Bubble sort to sort alphabetically.
		2. Will use Bubble sort to sort by word length.
		3. Will use Quicksort to sort by word length.
		4. Will use Quicksort to sort by word length. 

		L.  Will open file explorer. From here the user can select the .txt file they would like to sort.
		H.  Will display the text list horizontally.
		V.  Will display the text list vertically.

	2) Radio Buttons

	Each set of radio buttons is grouped as followes: 
		- a group for sorting (coresponding to keys 0-4)
		- a group for orientation (keys H,V)
		- a group for the menu/file explorer (key L)

	3) an OSC controller
	
	The buttons on the OSC controller are coordinated directly with the key shortcuts, and the buttons thereof are
	all labeled

		- Will work with a simple Android app like the OSC Control app made by Adam Katz on the Google Play Store
--------------------------------------------------------------------------------------------------------------------

## Resources

For Sorting : 
	Bubble sort: https://www.hackerearth.com/practice/algorithms/sorting/bubble-sort/tutorial/ 

For OSC control: 
	Library: https://openframeworks.cc/documentation/ofxOsc/

For ofxGuiExtended: 
	Libary: https://github.com/frauzufall/ofxGuiExtended

For threading: 
	Links: https://openframeworks.cc/ofBook/chapters/threads.html#whatsathreadandwhentouseit
	Documentation: https://en.cppreference.com/w/cpp/thread/condition_variable
----------------------------------------------------------------------------------------------------------------------