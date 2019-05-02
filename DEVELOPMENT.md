# DEVELOPMENT 

## Week 1: finding a project and testing libraries
1. Completed my Proposal.md

2. Explored libraries that I may be using.

3. Learned how to properly make an of project using the project generator.

4. Explored the example of projects where I found inspartation for my own.


## Week 2: continuing on
1. Proposal got approved (yay!)

2. Began to draw out my User Interface
     - Taking in word files (ie a list of movies)
	 - Using key shortcuts for different types of sorting
		- Numerically
		- Alphabetically
	 - Allow the user to sort using differtnt algorithims
		- Quicksort
		- BubbleSort
	- Represent the movie lists as strings (written vertically)
	- Using different colors to differentiate between strings
	- Relative layout (the strings will spread out depending on the width of my screen)

3. Considered different libraries to use (those not mentioned in class)
	- JSON
		- Suggested by Michael from code review, to use for parsing the text files to sort
		- This would allow me to sort by episode (for a JSON of shows), year, title, etc.
	- SOUND
		- Suggested by Patrick (aka the best code mod)
		- Must add more to my idea for this to count as credit
			- Reading out the text
			- Making sounds of various pitches on each swap
				- dependant on the length/ heirarchy in the sort
				- super satisfying VooooOOOOOOooooP sound at the end
	- OFC CONTROLLER 
		- Considering that I want my project to act as a learning tool, It would be cool to be able to present it
		and controll it all remotley.
		- I downloaded this ofc remote app from the Google Play store, and while the ui for it is bad, it does work, and I could
		deffinitly make a small Android application to accompany my own project If I have the time.


## Week 3: a hiccup / recovery period
 My computer broke down on Saturday, got a temporary replacement on Monday (morning). Luckily I saved my progress ahead of time, and did not loose much work...

 1. Recovered my work (yay!)

 2. Continued along with the functionalities and features of my project

 3. Began (and completed) automatic testing
	- What I did for each test was essentiallly the same
		1) created a new application within the test case
		2) ran it to sort with one of the four sorting options
		3) I did this for each sorting algorithim for a total of 4 test cases

	- Manual testing was simply running the code, and me trying to break it

4) I now have my code working with a proper OSC controller
	- OSC (short for open sound control) is typically used for music preformances, DJ's etc
	- Currently I am using an app called OSC Contoller that I got off of the play store (developer: Adam Katz)
	- If I put connect my phone and my computer to the same wifi network and input my computers IP addres and
	the port number that I initialised in my computer (12345), I can contoll my program with my phone as the remote!
	- Library used: ofxOFC 
		- link: 


## Week 4: the final stretch
1. My app now contains functioning buttons using the ofxExtendedGui 
	- link: https://github.com/frauzufall/ofxGuiExtended
	- My control panel is based off of the example project that came with this repository
	- Here I was able to group my buttons like radio buttons
		- GROUP 1: uploading the files to sort in my computer
		- GROUP 2: the sorting algorithims to choose from
		- GROUP 3: selecting oreientaton (ie horizontal/ vertical)

2. I allow the user to select from which file they would like to sort

3. I allow the user to selcet the orientation in which they would like to sort
	- Horizontally
	- Vertically

	THE DOWNSIDE: I found that creating a scolling feature with the multithreading
	I already have in place is HARD, so it is hard to fit so many words to sort all
	in my screen.

	WHAT I HAVE INSTEAD: I set this in place early on in my project, but the list itself
	will spread out relative to my screen size. 


## MAY 1: the final, final stretch
1. Updated my PROPOSAL.md to better represent what my application was doing
	- Provided links to extennal libraries that I used
	- Considered what I could have done to make my application more extensive or
	more interesting.

2. Wrote and completed my Proposal.md
	- Summarize the app and explains the ways in which my app can be controled.

3.  Completed my own OSC controller app and added it to my repository
	- I was not planning on doing this when I first made it, but It works now!