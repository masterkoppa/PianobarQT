PianobarQT
=========

This is the repository for the QT frontend for pianobar

What is working:

* Logging into pandora from GUI
* Retrieving the list of stations
* Retrieving the playlist
* The second station is selected and started
* Music will play indefinately(Until pandora quits on me)
* The GUI Shows the following information:
  * Song Name
  * Artist
  * Album
  * All Stations
  * All the songs in the playlist(4 by for from pandora)  


Buidl Instructions:
==================

Clone the git repository using your favorite client.  

Change into the repository directory and run the following command:  
~~~
cmake CMakeLists.txt
make all
~~~

This will produce the binary file: Pianobar-QT  
If you have all the required dependencies you should be able to execute it by running the following:
~~~
./Pianobar-QT
~~~

  
Screenshot:
==========
![Current State of the App](https://dl.dropbox.com/u/784245/PianobarQT_Screenshot6.png)


Known Problems:
===============

None so far :D