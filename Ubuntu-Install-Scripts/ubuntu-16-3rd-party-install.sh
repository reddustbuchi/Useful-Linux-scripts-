#!/bin/bash

# Script to install third party apps on Ubuntu 16.04.

# The following commands will test for required packages install them.

dpkg -l | grep -qw gdebi || sudo apt-get install -yyq gdebi
dpkg -l | grep -qw synaptic || sudo apt-get install -yyq synaptic
dpkg -l | grep -qw htop || sudo apt-get install -yyq htop

# Install Ocenaudio from .deb file.

wget https://www.ocenaudio.com/downloads/index.php/ocenaudio_debian64.deb
sudo gdebi -n ocenaudio_debian64.deb
rm ocenaudio_debian64.deb

# Remove Firefox and replace with Google Chrome.

sudo apt-get purge -yyqq firefox firefox-locale-en
wget https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb
sudo gdebi -n google-chrome-stable_current_amd64.deb
rm google-chrome-stable_current_amd64.deb

# Install SSR and Spotify from their repositories.

sudo apt-add-repository -y ppa:maarten-baert/simplescreenrecorder
sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys D2C19886
sudo apt-get update -qq
sudo apt-get install -yyq simplescreenrecorder

# Remove Fluendo mp3 codec if installed.

sudo apt-get purge -yyqq gstreamer1.0-fluendo-mp3

echo "--------------------
-       Done!      -
--------------------
"








