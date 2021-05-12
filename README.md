![](https://imgur.com/OxkEniC.png)
##  Introduction
Spotlists is an application that utilizes Spotify's API to build local playlists and play its available samples. It is written in C++ using the Qt Framework.
## Installation
Requirements: Visual C++ Redistributable.

To make this application easier to use for the first time, it is provided an installer which you can download from the SpotlistsSetup folder. Currently, only Windows platforms support this installer.
## **Compilation Instructions**
##### Windows OS
Requirements: 
[Microsoft Visual Studio (VS)](https://visualstudio.microsoft.com/pt-br/downloads/ "Visual Studio") installed in your machine.
Qt5 version compatible with the MSVC compiler. MinGW versions will not work.

Procedures:
1.	Install the *vcpkg* Package Manager.
2.	Install [OpenSSL](https://slproweb.com/products/Win32OpenSSL.html "OpenSSL").
3.	Install, through vcpkg, the networking library [CPR](https://github.com/whoshuu/cpr "CPR").
4.	With Visual Studio open, Install the Qt VS Tools Extension (**Extensions > Manage Extensions**).
5.	Restart Visual Studio.
6.	Open VS without any project and select the Qt version compatible with the MSVC compiler. **(Extensions> Qt VS Tools > Qt Versions)**
![Select the Qt5 version](https://imgur.com/Jedg1Xu.png)
7.	Create a new Qt Widgets project with the following Qt5 modules:
![Qt5 modules](https://imgur.com/PJHa0hC.png "Qt5 modules")
8.	Add the header and source files from this repository into the project folder.
9.	Add the header and source files into the solution.
![](https://imgur.com/WWZ4lAr.png)
10. Build the solution.

PS: Though sharing the .sln folder would somewhat cut down on these steps, I cannot guarantee at this moment that this approach will indeed work.
##### Linux OS (as tested in Ubuntu)
1. Open your terminal and install all of the following dependencies:
```shell
sudo apt install qt5-default
sudo apt install g++
sudo apt install git
sudo apt install cmake
sudo apt install openssl
sudo apt install libssl-dev
sudo apt install qtmultimedia5-dev
sudo apt install libqt5multimedia5-plugins
```
Some of these dependencies may seem redundant, but they are in place in case of an attempt to compile this project after a clean distro install.

2. Clone this repository or download the source files from this repository's website page.
3. Run CMake over the CMakeLists.txt file in the source folder.
```shell
cmake CMakeLists.txt
```
4. After CMake completes generating the Makefile, compile the project with make:
```shell
make
```
5. Don't forget to install the font Tw Cen MT Condensed, which is located in the *fonts* folder.
6. After a successful compilation, run Spotlists with (assuming you are in the same directory as the executable):
```shell
./Spotlists
```
## Class Diagrams
Back-End classes:
![](https://imgur.com/AiNyZJW.png)
GUI classes:
![](https://imgur.com/hHdLBxQ.png)

## Class Dictionary
- ContentPage: Widget that displays the albums or tracks of a certain artist.
- CURLDispatcher: Concrete implementation of the IHTTPDispatcher class using the CPR networking library.
- CURLRequest: Concrete implementation of the IHTTPRequest class using the CPR networking library.
- HTTPDispatcherFactory: Class belonging to the Factory Design Pattern, that its purpose is to choose which concrete instance of IHTTPDispatcher to return. Currently, it is set to always return an instance of CURLRequest. It exists to allow for extension with Qt's networking classes.
- HTTPRequestFactory: Class belonging to the Factory Design Pattern, that its purpose is to choose which concrete instance of IHTTPRequest to return. Currently, it is set to always return an instance of CURLRequest. It exists to allow for extension with Qt's networking classes.
- IHTTPDispatcher: Abstract class that represents the entity that sends an HTTP request over the network.
- IHTTPRequest: Abstract class that represents an HTTP request.
- ImageLoader: class that contains the very important raw binary-QPixmap conversion algorithms.
- MainWindow: Spotlists' Main Application Window.
- MediaControls: Widget that controls (e.g. plays, pauses, adjusts volume) the music being played.
- MusicPlayer: Widget responsible for collecting a track and playing it for the user.
- NetworkReply: Struct that couples together the most important aspects of a http response.
- Playlist: Array of PlaylistElementGUI objects.
- PlaylistData: Array of PlaylistElement objects.
- PlaylistElement: Main Data Transfer Object (DTO) of this application. It contains every information belonging to an artist, album or track.
- PlaylistElementGUI: GUI representation of a PlaylistElement.
- PlaylistWidget:  Widget that allows the user to manage the playlist.
- TopBar: Navigation Bar.
- SearchPage: Widget that displays the search results from the API.
- SpotifyAPI: class that works as a wrapper to Spotify's Official API, takes a request and returns a JSON document through its static classes.
- SpotifyFilter: class that transforms SpotifyAPI's json responses into PlaylistElement objects.
- SpotifyFlow: works as a high-level manager of the work among SpotifyAPI and SpotifyFilter classes. It simplifies use within the UI.
