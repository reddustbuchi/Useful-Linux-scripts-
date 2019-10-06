#!/bin/bash

# Ubuntu (GNOME) 18.04 setup script.

dpkg -l | grep -qw gdebi || sudo apt-get install -yyq gdebi

# Initial Software

sudo apt update

sudo apt install virtualbox virtualbox-guest-additions-iso virtualbox-ext-pack \
net-tools htop grsync lame asunder soundconverter brasero git mc flatpak \
openssh-server sshfs gedit-plugin-text-size simplescreenrecorder nano \
ubuntu-restricted-extras mpv vlc gthumb gnome-tweaks tracker chrome-gnome-shell \
gnome-tweak-tool qt5-style-plugins spell synaptic -yy

# Add me to any groups I might need to be a part of:

sudo adduser $USER vboxusers

# Remove undesirable packages:

sudo apt purge gstreamer1.0-fluendo-mp3 deja-dup shotwell -yy

# Remove snaps and get packages from apt:

sudo snap remove gnome-characters gnome-calculator gnome-system-monitor
sudo apt install gnome-characters gnome-calculator gnome-system-monitor \
gnome-software-plugin-flatpak -yy

# Purge Firefox, install Google Chrome:

sudo apt purge firefox -yy
sudo apt purge firefox-locale-en -yy
if [ -d "/home/$USER/.mozilla" ]; then
    rm -rf /home/$USER/.mozilla
fi
if [ -d "/home/$USER/.cache/mozilla" ]; then
    rm -rf /home/$USER/.cache/mozilla
fi
mkdir /tmp/gc-install-tmp
pushd /tmp/gc-install-tmp
wget https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb
sudo gdebi -n google-chrome-stable_current_amd64.deb
popd
rm -rf /tmp/gc-install-tmp

#set icons to minimize on click
gsettings set org.gnome.shell.extensions.dash-to-dock click-action 'minimize'

## Remove junk
sudo apt-get remove ubuntu-web-launchers thunderbird rhythmbox -y

## Multimedia
sudo apt-get install -y gimp mypaint scribus openshot audacious nautilus-dropbox

## Games
sudo apt-get install -y steam

## Disable Apport
sudo sed -i 's/enabled=1/enabled=0/g' /etc/default/apport

# set Qt variable in /etc/environment:

sudo bash -c "echo 'QT_QPA_PLATFORMTHEME=gtk2' >> /etc/environment"

# Gotta reboot now:
sudo apt update && sudo apt upgrade -y

echo $'\n'$"*** All done! Please reboot now. ***"
