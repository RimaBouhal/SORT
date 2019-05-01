<h1>Final Project Proposal</h1>

For my final project, I plan on creating a visualisaton for different sotring algorithims. I want this project to function as
a learning tool for a classroom setting. I created the following:  

	1. Bubble Sort Alphabetically
	2. Bubble Sort By Word Length
	3. Quicksort Alphabetically 
	4. Quicksort By Word Length

	NOTE: This project will only really work for lists of words, and not numbers, I have found that sorting with word lists
	is easier to represent length and order visually.

Features that my application will have include the following: 

	1. I will allow the user to select their own text files of strings to sort.
		- I included lists of my own to practice with. 

	2. The user can also controll the project with and OSC controlling application
		- The controller I first used was 
		- This will work so long as the device running the program and the device
		  running the controller are on the same wireless network (Illinois_net_geust works)

	3. The user can also controll the project using keyboard shortcuts and/or a button panel
	   I made via ofxGuiExtended
		- Groups of radio buttons
			- Sorting 
			- Orientation
			- Menu Options (file explorer)

	4. The user can also select which way the list is oriented
		- horizontally
		- vertically

<h2>Libraries to use</h2>
Because I will be using an OSC controller as a remote controll for my application, I needed to use the Ofx OFC libary
linked here: https://openframeworks.cc/documentation/ofxOsc/

For the Menu panel and buttons, I used ofxGuiExtended.
linked here: https://github.com/frauzufall/ofxGuiExtended

Both of these libraries allowed for me to create a visually appealing and convenient User Interface (though I also included
keyboard shortcuts).

<h2>Additonal Notes</h2>
For automatic testing, my test cases essentially run the application and preform one of the four sorting methods. The tests
pass once they sucsessfully sort the list.

I would like to make this project more extensible by completing any of the following:
	1. Implementing some form of a numerical sort
	2. Creating a dark mode/ theme selection for colors 
	3. Adding a swapping sound that would vary in pitch as the sorting went on.