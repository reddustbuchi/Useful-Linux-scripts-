#!/bin/bash
# Script crée par Simbd

## INFO : 
ce script n'est plus d'actualité (pour l'ancienne version 16.04), utilisez plutôt le script de post-installation pour la 18.04 ici :
# => https://gitlab.com/simbd/Scripts_Ubuntu/blob/master/Ubuntu18.04_Bionic_Postinstall.sh


# Vérification que le script est lancé avec sudo (droit root nécessaire)
if [ "$UID" -ne "0" ]
then
  echo "Il faut etre root pour executer ce script ==> sudo ./linuxPI.sh"
  exit 
fi 

# Choix du profil pour l'utilisateur
echo "Profil à utiliser : "
echo -e "================================"
echo "(ancien profil 1,2,3 retiré, utilisation du nouveau script...)"
echo "[4] profil Cor pour LinuxMint 18/Cinnamon x64 (HP)"
echo "[5] profil Raphael.B : Ubuntu 16.04/Unity x64"
echo -e "================================"
read -p "Choix : " choixProfil

# ----------------------------------------------------------------------------------------------------------------

##################################
# Commun à tous pour base Ubuntu
##################################
if [ "$choixProfil" = "4" ] || [ "$choixProfil" = "5" ]
then
  export DEBIAN_FRONTEND="noninteractive" #permet d'automatiser l'installation de certains logiciels
  # activation dépot partenaire si ce n'est pas encore fait
  sed -i "/^# deb .*partner/ s/^# //" /etc/apt/sources.list
  
  # nettoyage puis maj du système
  apt autoremove --purge -y && apt clean ; apt update && apt full-upgrade -y

  # outils utiles
  apt install htop gparted curl net-tools git gdebi openjdk-8-jre numlockx screenfetch -y
  
  # éditeur/bureautique
  apt install vim libreoffice libreoffice-l10n-fr libreoffice-help-fr evince -y
  
  # internet
  apt install firefox firefox-locale-fr chromium-browser chromium-browser-l10n pidgin transmission-gtk thunderbird thunderbird-locale-fr -y
  
  # multimedia, codecs & graphisme
  apt install vlc x264 x265 gimp gimp-help-fr shutter -y
  
  # désactivation message d'erreurs
  sed -i 's/^enabled=1$/enabled=0/' /etc/default/apport
  
  # inutile dans tous les cas
  apt purge ubuntu-web-launchers -y #suppression icone amazon
  
  # optimisation swap
  echo "vm.swappiness=5" > /etc/sysctl.d/99-swappiness.conf 
fi

##################################
# Supplément spécifique suivant profil
##################################

## spécifique profil 4 : Corinne/Mint
if [ "$choixProfil" = "4" ] 
then
  sed -ri 's/GRUB_TIMEOUT=10/GRUB_TIMEOUT=2/g' /etc/default/grub && mkdir /boot/old && mv /boot/memtest86* /boot/old/ ; update-grub #pour grub

  # Navigateur supplémentaire
  wget -q -O - https://dl-ssl.google.com/linux/linux_signing_key.pub | apt-key add - && sh -c 'echo "deb [arch=amd64] http://dl.google.com/linux/chrome/deb/ stable main" >> /etc/apt/sources.list.d/google-chrome.list' && apt update && apt install google-chrome-stable -y #Chrome
  
  # Système
  apt install snapd flatpak -y
  
  # Outil web
  apt install pidgin deluge grsync subdownloader -y
  snap install discord 
  flatpak install --from https://flathub.org/repo/appstream/com.github.JannikHv.Gydl.flatpakref -y #Gydl
  wget https://repo.skype.com/latest/skypeforlinux-64.deb && dpkg -i skypeforlinux-64.deb ; apt install -fy ; rm skypeforlinux-64.deb #Skype
  
  # Multimedia
  apt install gnome-mpv quodlibet handbrake winff openshot -y
  flatpak install --from https://flathub.org/repo/appstream/de.haeckerfelix.gradio.flatpakref -y #Gradio

  # Graphisme/audio
  apt install sound-juicer pinta inkscape darktable audacity lame -y
  
  # Supplément bureautique
  apt install geary pdfmod -y
  
  # Utilitaires sup
  apt install keepassx ncdu screen openssh-server unrar -y
  #plus tard une fois en 19 : wormhole
  
  ## Driver
  # Pour imprimante HP
  apt install hplip hplip-gui sane
 
  # nettoyage
  apt install -fy ; apt autoremove --purge -y ; apt clean ; clear
  exit
fi

# ----------------------------------------------------------------------------------------------------------------

## spécifique profil 5 : Raphael.B (Ubuntu 16.04/Unity) 
if [ "$choixProfil" = "5" ] 
then
  #Alias Maj
  echo "alias maj='sudo apt update && sudo apt full-upgrade -y && sudo apt autoremove --purge -y && sudo snap refresh && sudo apt clean ; clear'" >> /home/$SUDO_USER/.bashrc
 
  # Prise en compte de l'alias "maj"
  su $SUDO_USER -c "source ~/.bashrc"
  
  # Suppression icon Amazon
  rm -f /usr/share/applications/ubuntu-amazon-default.desktop ; apt purge unity-webapps-amazoncloudreader -y 
  
  # Xcfa (X Convert File Audio) - mettre la ligne juste ci-dessous en commentaire si tu n'en n'a pas besoin
  apt install cdparanoia cd-discid xcfa -y #(cdparanoia et cd-discid sont des dépendances nécessaires pour xcfa)
  
  # Outils utiles 
  apt install unity-tweak-tool synaptic dmsetup diodon brasero xsane sane virtualbox handbrake -y
  
  #Ajout pack d'extension virtualbox
  echo virtualbox-ext-pack virtualbox-ext-pack/license select true | debconf-set-selections | apt install virtualbox-ext-pack -y
  
  #Shrew Soft VPN Access Manager (IKE)
  apt install ike ike-qtgui -y
  
  #Truecrypt
  add-apt-repository ppa:stefansundin/truecrypt -y ; apt update ; apt install truecrypt -y
  
  # Outil web
  apt install hexchat pidgin filezilla grsync -y
  
  # Teamviewer 8 pour assistance académique
  wget http://download.teamviewer.com/download/version_8x/teamviewer_linux.deb && dpkg -i teamviewer_linux.deb ; apt install -fy ; rm teamviewer_linux.deb 
 
  # Graphisme/Video
  apt install kazam pinta shutter -y
  # si besoin d'openshot dernière version stable => add-apt-repository ppa:openshot.developers/ppa -y && apt update && apt install openshot-qt -y
  
  # Police d'écriture Microsoft (dépendance de Scenari), placé avant pour automatiser sans intervenion :
  echo ttf-mscorefonts-installer msttcorefonts/accepted-mscorefonts-eula select true | /usr/bin/debconf-set-selections | apt install ttf-mscorefonts-installer -y
  
  # Scenari 4.1
  add-apt-repository ppa:openjdk-r/ppa -y ; apt update ; apt install openjdk-7-jre -y #openjdk 7 nécessaire en dépendance pour scenari 4.1
  echo "deb https://download.scenari.org/deb xenial main" > /etc/apt/sources.list.d/scenari.list ; wget -O- https://download.scenari.org/deb/scenari.asc | apt-key add -
  apt update ; apt install scenarichain4.1.fr-fr opale3.6.fr-fr -y
  # Si besoin de la 4.2 (plus besoin d'openjdk 7 dans ce cas) : apt install scenarichain4.2.fr-fr -y
  
  # Supplément bureautique
  apt install zim keepass2 xournal -y

  ## Pilote
  # Imprimante du travail (Kyocera Taskalfa 3511i)
  wget https://raw.githubusercontent.com/dane-lyon/fichier-de-config/master/Kyocera_taskalfa_3511i.PPD ; mv Kyocera_taskalfa_3511i.PPD /etc/cups/ppd/
  # Imprimante perso1 : MCF5890cn 
  wget http://download.brother.com/welcome/dlf006168/mfc5890cnlpr-1.1.2-2.i386.deb ; dpkg -i mfc5890cnlpr-1.1.2-2.i386.deb ; apt install -fy ; rm mfc5890cnlpr-1.1.2-2.i386.deb #pilote imprimante
  wget http://download.brother.com/welcome/dlf006642/brscan3-0.2.13-1.amd64.deb ; dpkg -i brscan3-0.2.13-1.amd64.deb ; apt install -fy ; rm brscan3-0.2.13-1.amd64.deb #pilote scanner
  # Imprimante perso2 : Lexmark mx511
  wget http://www.openprinting.org/download/printdriver/debian/dists/lsb3.2/main/binary-amd64/openprinting-ppds-postscript-lexmark_20160218-1lsb3.2_all.deb ; dpkg -i openprinting* ; apt install -fy ; rm openprinting*
  
  # Thèmes
  add-apt-repository ppa:numix/ppa -y ; apt update ; apt install numix-gtk-theme numix-icon-theme numix-icon-theme-bevel numix-icon-theme-circle -y
  apt install breeze-icon-theme breeze-cursor-theme -y
  wget http://nux87.free.fr/script-postinstall-ubuntu/theme/papirus-icon-theme-20171124.tar.xz ; tar Jxvf papirus-icon-theme-20171124.tar.xz ; mv *Papirus* /usr/share/icons/ ; rm -f papirus* #papirus icon

  # mBlock (serveur assez lent pour récupérer le deb)
  wget http://nux87.free.fr/script-postinstall-ubuntu/deb/mb404x64.deb ; dpkg -i mb404x64.deb ; apt install -fy ; rm mb404x64.deb
  
  # Scratch 2
  wget https://scratch.mit.edu/scratchr2/static/sa/Scratch-455.air ; chmod +x Scratch* ; mv Scratch* /root/ #nb: il y a la 456 mais elle semble poser problème
  wget https://raw.githubusercontent.com/dane-lyon/fichier-de-config/master/adobe-air.sh ; chmod +x adobe-air.sh
  ./adobe-air.sh 
  Adobe\ AIR\ Application\ Installer #choisir manuellement le fichier Scratch-455.air présent dans /root
  
  # nettoyage
  apt autoremove --purge -y ; apt clean ; rm adobe-air.sh ; rm /root/Scratch* ; clear

  echo "Le script a terminé son travail, il est maintenant conseillé de redémarrer la machine !"
fi
