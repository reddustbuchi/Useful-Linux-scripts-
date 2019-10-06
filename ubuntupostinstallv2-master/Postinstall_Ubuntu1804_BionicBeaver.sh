#!/bin/bash
# v3.0.2
# Script de post-installation pour Ubuntu 18.04 et les dérivés

# Code couleur
rouge='\e[1;31m'
jaune='\e[1;33m' 
bleu='\e[1;34m' 
violet='\e[1;35m' 
vert='\e[1;32m'
neutre='\e[0;m'

# Vérification que le script n'est pas lancé directement avec sudo (le script contient déjà les sudos pour les actions lorsque c'est nécessaire)
if [ "$UID" -eq "0" ]
then
    echo -e "${rouge}Merci de ne pas lancer directement ce script avec les droits root : lancez le sans sudo (./Postinstall_Ubuntu1804_BionicBeaver.sh), le mot de passe sera demandé dans le terminal lors de la 1ère action nécessitant le droit administrateur.${neutre}"
    exit
fi

MY_DIR=$(dirname $0)
. $MY_DIR/config_pi.sh

CHK_REP=$(zenity --entry --title="$BGN_TITLE" --text "$BGN_TEXT" --entry-text="$BGN_DEF" $BGN_CHECKED $BGN_UNCHECKED)
if [ $? -ne 0 ] ; then
	exit
fi

# Zenity
GUI=$(zenity --list --checklist --height 700 --width 950 \
	--title="$MSG_ZEN_TITLE" --text="$MSG_ZEN_TEXT" \
	--column="$MSG_ZEN_CHECK" --column="$MSG_ZEN_ACTION" --column="$MSG_ZEN_DESCRIPTION" \
	$(chkDef "TRUE") "$CA_PARTNER" "$CD_PARTNER" \
	$(chkDef "TRUE") "$CA_UPGRADE" "$CD_UPGRADE" \
	$(chkDef "TRUE") "$CA_FLATPAK" "$CD_FLATPAK" \
	$(chkDef "FALSE") "$CA_SNAP" "$CD_SNAP" \
	FALSE "$SCT_SESSION" "===========================================================" \
    $(chkDef "FALSE") "$CA_GNOMEVANILLA" "$CD_GNOMEVANILLA" \
    $(chkDef "FALSE") "$CA_GNOMECLASSIC" "$CD_GNOMECLASSIC" \
    $(chkDef "FALSE") "$CA_GNOMEFLASHBACKM" "$CD_GNOMEFLASHBACKM" \
    $(chkDef "FALSE") "$CA_GNOMEFLASHBACKC" "$CD_GNOMEFLASHBACKC" \
    $(chkDef "FALSE") "$CA_COMMUNITHEME" "$CD_COMMUNITHEME" \
    $(chkDef "FALSE") "$CA_UNITY" "$CD_UNITY" \
    $(chkDef "FALSE") "$CA_MATE" "$CD_MATE" \
	FALSE "$SCT_BROWSER" "===========================================================" \
    $(chkDef "FALSE") "$CA_BEAKER" "$CD_BEAKER" \
    $(chkDef "FALSE") "$CA_BRAVE" "$CD_BRAVE" \
    $(chkDef "TRUE") "$CA_CHROMIUM" "$CD_CHROMIUM" \
    $(chkDef "FALSE") "$CA_DILLO" "$CD_DILLO" \
    $(chkDef "FALSE") "$CA_EOLIE" "$CD_EOLIE" \
    $(chkDef "FALSE") "$CA_FALKON" "$CD_FALKON" \
    $(chkDef "FALSE") "$CA_FIREFOXBETA" "$CD_FIREFOXBETA" \
    $(chkDef "FALSE") "$CA_FIREFOXDEV" "$CD_FIREFOXDEV" \
    $(chkDef "FALSE") "$CA_FIREFOXESR" "$CD_FIREFOXESR" \
    $(chkDef "FALSE") "$CA_FIREFOXNIGHTLY" "$CD_FIREFOXNIGHTLY" \
    $(chkDef "FALSE") "$CA_EPIPHANY" "$CD_EPIPHANY" \
    $(chkDef "FALSE") "$CA_CHROME" "$CD_CHROME" \
    $(chkDef "FALSE") "$CA_LYNX" "$CD_LYNX" \
    $(chkDef "FALSE") "$CA_MIDORI" "$CD_MIDORI" \
    $(chkDef "FALSE") "$CA_MIN" "$CD_MIN" \
    $(chkDef "FALSE") "$CA_OPERA" "$CD_OPERA" \
    $(chkDef "FALSE") "$CA_PALEMOON" "$CD_PALEMOON" \
    $(chkDef "FALSE") "$CA_SRWAREIRON" "$CD_SRWAREIRON" \
    $(chkDef "FALSE") "$CA_TORBROWSER" "$CD_TORBROWSER" \
    $(chkDef "FALSE") "$CA_VIVALDI" "$CD_VIVALDI" \
	FALSE "$SCT_INTERNET" "===========================================================" \
	$(chkDef "FALSE") "$CA_AMULE" "$CD_AMULE" \
	$(chkDef "TRUE") "$CA_DELUGE" "$CD_DELUGE" \
	$(chkDef "FALSE") "$CA_DISCORD" "$CD_DISCORD" \
	$(chkDef "FALSE") "$CA_DROPBOX" "$CD_DROPBOX" \
	$(chkDef "FALSE") "$CA_DUKTO" "$CD_DUKTO" \
	$(chkDef "FALSE") "$CA_EISKALTDC" "$CD_EISKALTDC" \
	$(chkDef "FALSE") "$CA_EMPATHY" "$CD_EMPATHY" \
	$(chkDef "TRUE") "$CA_FILEZILLA" "$CD_FILEZILLA" \
	$(chkDef "FALSE") "$CA_FROSTWIRE" "$CD_FROSTWIRE" \
	$(chkDef "FALSE") "$CA_GYDL" "$CD_GYDL" \
	$(chkDef "FALSE") "$CA_HEXCHAT" "$CD_HEXCHAT" \
	$(chkDef "FALSE") "$CA_HUBIC" "$CD_HUBIC" \
	$(chkDef "FALSE") "$CA_JITSI" "$CD_JITSI" \
	$(chkDef "FALSE") "$CA_LINPHONE" "$CD_LINPHONE" \
	$(chkDef "FALSE") "$CA_MUMBLE" "$CD_MUMBLE" \
	$(chkDef "FALSE") "$CA_NICOTINE" "$CD_NICOTINE" \
	$(chkDef "TRUE") "$CA_PIDGIN" "$CD_PIDGIN" \
	$(chkDef "FALSE") "$CA_POLARI" "$CD_POLARI" \
	$(chkDef "FALSE") "$CA_PSI" "$CD_PSI" \
	$(chkDef "FALSE") "$CA_QARTE" "$CD_QARTE" \
	$(chkDef "FALSE") "$CA_QBITTORRENT" "$CD_QBITTORRENT" \
	$(chkDef "FALSE") "$CA_RING" "$CD_RING" \
	$(chkDef "FALSE") "$CA_RIOT" "$CD_RIOT" \
	$(chkDef "FALSE") "$CA_SIGNAL" "$CD_SIGNAL" \
	$(chkDef "FALSE") "$CA_SKYPE" "$CD_SKYPE" \
	$(chkDef "FALSE") "$CA_SLACK" "$CD_SLACK" \
	$(chkDef "FALSE") "$CA_SUBDOWNLOADER" "$CD_SUBDOWNLOADER" \
	$(chkDef "FALSE") "$CA_TEAMSPEAK" "$CD_TEAMSPEAK" \
	$(chkDef "FALSE") "$CA_TELEGRAM" "$CD_TELEGRAM" \
	$(chkDef "FALSE") "$CA_UGET" "$CD_UGET" \
	$(chkDef "FALSE") "$CA_VUZE" "$CD_VUZE" \
	$(chkDef "FALSE") "$CA_WEECHAT" "$CD_WEECHAT" \
	$(chkDef "FALSE") "$CA_WHALEBIRD" "$CD_WHALEBIRD" \
	$(chkDef "FALSE") "$CA_WHATSAPP" "$CD_WHATSAPP" \
	$(chkDef "FALSE") "$CA_WIRE" "$CD_WIRE" \
	$(chkDef "FALSE") "$CA_YTDLND" "$CD_YTDLND" \
	FALSE "$SCT_LECTUREMULTIMEDIA" "===========================================================" \
	$(chkDef "FALSE") "$CA_AUDACIOUS" "$CD_AUDACIOUS" \
	$(chkDef "FALSE") "$CA_BANSHEE" "$CD_BANSHEE" \
	$(chkDef "FALSE") "$CA_CLEMENTINE" "$CD_CLEMENTINE" \
	$(chkDef "FALSE") "$CA_GMUSICBROWSER" "$CD_GMUSICBROWSER" \
	$(chkDef "TRUE") "$CA_GNOMEMPV" "$CD_GNOMEMPV" \
	$(chkDef "FALSE") "$CA_GNOMEMUSIC" "$CD_GNOMEMUSIC" \
	$(chkDef "FALSE") "$CA_GNOMETWITCH" "$CD_GNOMETWITCH" \
	$(chkDef "FALSE") "$CA_GRADIO" "$CD_GRADIO" \
	$(chkDef "FALSE") "$CA_LOLLYPOP" "$CD_LOLLYPOP" \
	$(chkDef "FALSE") "$CA_MOLOTOVTV" "$CD_MOLOTOVTV" \
	$(chkDef "TRUE") "$CA_PAVUCONTROL" "$CD_PAVUCONTROL" \
	$(chkDef "FALSE") "$CA_QMMP" "$CD_QMMP" \
	$(chkDef "FALSE") "$CA_QUODLIBET" "$CD_QUODLIBET" \
	$(chkDef "FALSE") "$CA_RHYTHMBOX" "$CD_RHYTHMBOX" \
	$(chkDef "TRUE") "$CA_SHOTWELL" "$CD_SHOTWELL" \
	$(chkDef "FALSE") "$CA_SMPLAYER" "$CD_SMPLAYER" \
	$(chkDef "FALSE") "$CA_SPOTIFY" "$CD_SPOTIFY" \
	$(chkDef "FALSE") "$CA_UFRAW" "$CD_UFRAW" \
	$(chkDef "TRUE") "$CA_VLCSTABLE" "$CD_VLCSTABLE" \
	$(chkDef "FALSE") "$CA_VLCDEV" "$CD_VLCDEV" \
	$(chkDef "FALSE") "$CA_RESTRICT_EXTRA" "$CD_RESTRICT_EXTRA" \
	FALSE "$SCT_MONTAGEMULTIMEDIA" "===========================================================" \
	$(chkDef "FALSE") "$CA_ARDOUR" "$CD_ARDOUR" \
	$(chkDef "FALSE") "$CA_AUDACITY" "$CD_AUDACITY" \
	$(chkDef "FALSE") "$CA_AVIDEMUX" "$CD_AVIDEMUX" \
	$(chkDef "FALSE") "$CA_BLENDER" "$CD_BLENDER" \
	$(chkDef "FALSE") "$CA_CINELERRA" "$CD_CINELERRA" \
	$(chkDef "FALSE") "$CA_DARKTABLE" "$CD_DARKTABLE" \
	$(chkDef "FALSE") "$CA_EASYTAG" "$CD_EASYTAG" \
	$(chkDef "FALSE") "$CA_FLACON" "$CD_FLACON" \
	$(chkDef "FALSE") "$CA_FLAMESHOT" "$CD_FLAMESHOT" \
	$(chkDef "FALSE") "$CA_FLOWBLADE" "$CD_FLOWBLADE" \
	$(chkDef "FALSE") "$CA_FREECAD" "$CD_FREECAD" \
	$(chkDef "TRUE") "$CA_GIMPDEPOT" "$CD_GIMPDEPOT" \
	$(chkDef "FALSE") "$CA_GIMP" "$CD_GIMP" \
	$(chkDef "FALSE") "$CA_GNOMESOUNDRECORDER" "$CD_GNOMESOUNDRECORDER" \
	$(chkDef "TRUE") "$CA_HANDBRAKE" "$CD_HANDBRAKE" \
	$(chkDef "FALSE") "$CA_HYDROGEN" "$CD_HYDROGEN" \
	$(chkDef "FALSE") "$CA_INKSCAPE" "$CD_INKSCAPE" \
	$(chkDef "FALSE") "$CA_K3D" "$CD_K3D" \
	$(chkDef "FALSE") "$CA_KAZAM" "$CD_KAZAM" \
	$(chkDef "FALSE") "$CA_KDENLIVE" "$CD_KDENLIVE" \
	$(chkDef "FALSE") "$CA_KOLOURPAINT" "$CD_KOLOURPAINT" \
	$(chkDef "FALSE") "$CA_KRITA" "$CD_KRITA" \
	$(chkDef "FALSE") "$CA_LIGHTWORKS" "$CD_LIGHTWORKS" \
	$(chkDef "FALSE") "$CA_LIBRECAD" "$CD_LIBRECAD" \
	$(chkDef "FALSE") "$CA_LIVES" "$CD_LIVES" \
	$(chkDef "FALSE") "$CA_LUMINANCE" "$CD_LUMINANCE" \
	$(chkDef "FALSE") "$CA_LMMS" "$CD_LMMS" \
	$(chkDef "FALSE") "$CA_MHWAVEEDIT" "$CD_MHWAVEEDIT" \
	$(chkDef "FALSE") "$CA_MIXXX" "$CD_MIXXX" \
	$(chkDef "FALSE") "$CA_MUSESCORE" "$CD_MUSESCORE" \
	$(chkDef "FALSE") "$CA_MYPAINT" "$CD_MYPAINT" \
	$(chkDef "FALSE") "$CA_NATRON" "$CD_NATRON" \
	$(chkDef "FALSE") "$CA_OBS" "$CD_OBS" \
	$(chkDef "FALSE") "$CA_OPENSHOT" "$CD_OPENSHOT" \
	$(chkDef "FALSE") "$CA_PEEK" "$CD_PEEK" \
	$(chkDef "TRUE") "$CA_PINTA" "$CD_PINTA" \
	$(chkDef "FALSE") "$CA_PITIVI" "$CD_PITIVI" \
	$(chkDef "FALSE") "$CA_PIXELUVO" "$CD_PIXELUVO" \
	$(chkDef "FALSE") "$CA_ROSEGARDEN" "$CD_ROSEGARDEN" \
    $(chkDef "FALSE") "$CA_SHOTCUT" "$CD_SHOTCUT" \
	$(chkDef "TRUE") "$CA_SHUTTER" "$CD_SHUTTER" \
	$(chkDef "FALSE") "$CA_SIMPLESCREENRECORDER" "$CD_SIMPLESCREENRECORDER" \
	$(chkDef "FALSE") "$CA_SOUNDJUICER" "$CD_SOUNDJUICER" \
	$(chkDef "FALSE") "$CA_SWEETHOME" "$CD_SWEETHOME" \
	$(chkDef "FALSE") "$CA_WINFF" "$CD_WINFF" \
	FALSE "$SCT_OFFICE" "===========================================================" \
	$(chkDef "FALSE") "$CA_CALLIGRA" "$CD_CALLIGRA" \
	$(chkDef "FALSE") "$CA_FRDIC" "$CD_FRDIC" \
	$(chkDef "FALSE") "$CA_FBREADER" "$CD_FBREADER" \
	$(chkDef "FALSE") "$CA_FEEDREADER" "$CD_FEEDREADER" \
	$(chkDef "FALSE") "$CA_FREEOFFICE" "$CD_FREEOFFICE" \
	$(chkDef "FALSE") "$CA_FREEPLANE" "$CD_FREEPLANE" \
	$(chkDef "FALSE") "$CA_GEARY" "$CD_GEARY" \
	$(chkDef "FALSE") "$CA_EVOLUTION" "$CD_EVOLUTION" \
	$(chkDef "FALSE") "$CA_GNOMEOFFICE" "$CD_GNOMEOFFICE" \
	$(chkDef "FALSE") "$CA_GRAMPS" "$CD_GRAMPS" \
	$(chkDef "FALSE") "$CA_JOPLIN" "$CD_JOPLIN" \
	$(chkDef "TRUE") "$CA_LIBREOFFICEDEPOT" "$CD_LIBREOFFICEDEPOT" \
	$(chkDef "FALSE") "$CA_LIBREOFFICEFRESH" "$CD_LIBREOFFICEFRESH" \
	$(chkDef "TRUE") "$CA_LIBREOFFICESUP" "$CD_LIBREOFFICESUP" \
	$(chkDef "FALSE") "$CA_MAILSPRING" "$CD_MAILSPRING" \
	$(chkDef "FALSE") "$CA_MASTERPDFEDITOR" "$CD_MASTERPDFEDITOR" \
	$(chkDef "FALSE") "$CA_NOTESUP" "$CD_NOTESUP" \
	$(chkDef "FALSE") "$CA_ONLYOFFICE" "$CD_ONLYOFFICE" \
	$(chkDef "FALSE") "$CA_OPENOFFICE" "$CD_OPENOFFICE" \
	$(chkDef "FALSE") "$CA_PDFMOD" "$CD_PDFMOD" \
	$(chkDef "TRUE") "$CA_POLICEMST" "$CD_POLICEMST" \
	$(chkDef "FALSE") "$CA_SCENARI" "$CD_SCENARI" \
	$(chkDef "FALSE") "$CA_SCRIBUS" "$CD_SCRIBUS" \
	$(chkDef "TRUE") "$CA_THUNDERBIRD" "$CD_THUNDERBIRD" \
	$(chkDef "FALSE") "$CA_UNITY3DEDITOR" "$CD_UNITY3DEDITOR" \
	$(chkDef "FALSE") "$CA_WPSOFFICE" "$CD_WPSOFFICE" \
	$(chkDef "FALSE") "$CA_XPAD" "$CD_XPAD" \
	$(chkDef "FALSE") "$CA_ZIM" "$CD_ZIM" \
	FALSE "$SCT_EDUSCIENCE" "===========================================================" \
	$(chkDef "FALSE") "$CA_ALGOBOX" "$CD_ALGOBOX" \
	$(chkDef "FALSE") "$CA_ASTROEDU" "$CD_ASTROEDU" \
	$(chkDef "FALSE") "$CA_AVOGADRO" "$CD_AVOGADRO" \
	$(chkDef "FALSE") "$CA_CELESTIA" "$CD_CELESTIA" \
	$(chkDef "FALSE") "$CA_CONVERTALL" "$CD_CONVERTALL" \
	$(chkDef "FALSE") "$CA_GANTTPROJECT" "$CD_GANTTPROJECT" \
	$(chkDef "FALSE") "$CA_GCOMPRIS" "$CD_GCOMPRIS" \
	$(chkDef "FALSE") "$CA_GELEMENTAL" "$CD_GELEMENTAL" \
	$(chkDef "FALSE") "$CA_GEOGEBRA" "$CD_GEOGEBRA" \
	$(chkDef "TRUE") "$CA_GNOMEMAPS" "$CD_GNOMEMAPS" \
	$(chkDef "FALSE") "$CA_GOOGLEEARTH" "$CD_GOOGLEEARTH" \
	$(chkDef "FALSE") "$CA_MARBLE" "$CD_MARBLE" \
	$(chkDef "FALSE") "$CA_MBLOCK" "$CD_MBLOCK" \
	$(chkDef "FALSE") "$CA_OPENBOARD" "$CD_OPENBOARD" \
	$(chkDef "FALSE") "$CA_OPTGEO" "$CD_OPTGEO" \
	$(chkDef "FALSE") "$CA_PLANNER" "$CD_PLANNER" \
	$(chkDef "FALSE") "$CA_SCRATCH" "$CD_SCRATCH" \
	$(chkDef "FALSE") "$CA_STELLARIUM" "$CD_STELLARIUM" \
	$(chkDef "FALSE") "$CA_TOUTENCLIC" "$CD_TOUTENCLIC" \
	$(chkDef "FALSE") "$CA_XCAS" "$CD_XCAS" \
	FALSE "$SCT_UTILITAIRES_GRAPHIQUE" "===========================================================" \
	$(chkDef "FALSE") "$CA_ANYDESK" "$CD_ANYDESK" \
    $(chkDef "FALSE") "$CA_BRASERO" "$CD_BRASERO" \
    $(chkDef "FALSE") "$CA_CHEESE" "$CD_CHEESE" \
    $(chkDef "FALSE") "$CA_DEJADUP" "$CD_DEJADUP" \
    $(chkDef "FALSE") "$CA_DIODON" "$CD_DIODON" \
    $(chkDef "FALSE") "$CA_DOSBOX" "$CD_DOSBOX" \
    $(chkDef "FALSE") "$CA_ETCHER" "$CD_ETCHER" \
    $(chkDef "FALSE") "$CA_FLASH" "$CD_FLASH" \
    $(chkDef "TRUE") "$CA_GNOME_DISK" "$CD_GNOME_DISK" \
    $(chkDef "FALSE") "$CA_GNOMERECIPES" "$CD_GNOMERECIPES" \
    $(chkDef "FALSE") "$CA_GSYSLOG" "$CD_GSYSLOG" \
    $(chkDef "FALSE") "$CA_GSYSMON" "$CD_GSYSMON" \
    $(chkDef "TRUE") "$CA_GPARTED" "$CD_GPARTED" \
    $(chkDef "FALSE") "$CA_JRE8" "$CD_JRE8" \
    $(chkDef "FALSE") "$CA_JRE11" "$CD_JRE11" \
    $(chkDef "FALSE") "$CA_MELD" "$CD_MELD" \
    $(chkDef "FALSE") "$CA_MULTISYSTEM" "$CD_MULTISYSTEM" \
    $(chkDef "TRUE") "$CA_ARCHIVAGE" "$CD_ARCHIVAGE" \
    $(chkDef "FALSE") "$CA_POL" "$CD_POL" \
    $(chkDef "FALSE") "$CA_REDSHIFT" "$CD_REDSHIFT" \
    $(chkDef "TRUE") "$CA_REMMINA" "$CD_REMMINA" \
    $(chkDef "FALSE") "$CA_SUBLIM_NAUT" "$CD_SUBLIM_NAUT" \
    $(chkDef "FALSE") "$CA_SUB_EDIT" "$CD_SUB_EDIT" \
    $(chkDef "TRUE") "$CA_SYNAPTIC" "$CD_SYNAPTIC" \
    $(chkDef "FALSE") "$CA_TEAMVIEWER" "$CD_TEAMVIEWER" \
    $(chkDef "TRUE") "$CA_TERMINATOR" "$CD_TERMINATOR" \
    $(chkDef "FALSE") "$CA_TIMESHIFT" "$CD_TIMESHIFT" \
    $(chkDef "FALSE") "$CA_VARIETY" "$CD_VARIETY" \
    $(chkDef "FALSE") "$CA_VBOXDEPOT" "$CD_VBOXDEPOT" \
    $(chkDef "FALSE") "$CA_VBOXLAST" "$CD_VBOXLAST" \
    $(chkDef "FALSE") "$CA_VMWARE" "$CD_VMWARE" \
    $(chkDef "FALSE") "$CA_WINE" "$CD_WINE" \
    $(chkDef "FALSE") "$CA_X2GO" "$CD_X2GO" \
    $(chkDef "FALSE") "$CA_X11VNC" "$CD_X11VNC" \
	FALSE "$SCT_UTILITAIRES_CLI" "===========================================================" \
    $(chkDef "FALSE") "$CA_DDRESCUE" "$CD_DDRESCUE" \
	$(chkDef "FALSE") "$CA_FD" "$CD_FD" \
	$(chkDef "TRUE") "$CA_GIT" "$CD_GIT" \
	$(chkDef "TRUE") "$CA_HTOP" "$CD_HTOP" \
	$(chkDef "FALSE") "$CA_GLANCES" "$CD_GLANCES" \
	$(chkDef "FALSE") "$CA_LAME" "$CD_LAME" \
	$(chkDef "FALSE") "$CA_HG" "$CD_HG" \
	$(chkDef "TRUE") "$CA_PACKOUTILS" "$CD_PACKOUTILS" \
	$(chkDef "FALSE") "$CA_POWERSHELL" "$CD_POWERSHELL" \
	$(chkDef "FALSE") "$CA_RIPGREP" "$CD_RIPGREP" \
	$(chkDef "FALSE") "$CA_RTORRENT" "$CD_RTORRENT" \
	$(chkDef "TRUE") "$CA_SMARTMONTOOLS" "$CD_SMARTMONTOOLS" \
	$(chkDef "FALSE") "$CA_TESTDISK" "$CD_TESTDISK" \
	$(chkDef "FALSE") "$CA_TLDR" "$CD_TLDR" \
	$(chkDef "FALSE") "$CA_WORDGRINDER" "$CD_WORDGRINDER" \
	$(chkDef "FALSE") "$CA_WORMHOLE" "$CD_WORMHOLE" \
	FALSE "$SCT_RESEAUSECURITE" "===========================================================" \
	$(chkDef "FALSE") "$CA_ANSIBLE" "$CD_ANSIBLE" \
	$(chkDef "FALSE") "$CA_CRYPTER" "$CD_CRYPTER" \
	$(chkDef "FALSE") "$CA_ENPASS" "$CD_ENPASS" \
	$(chkDef "FALSE") "$CA_GEM" "$CD_GEM" \
	$(chkDef "FALSE") "$CA_GNS" "$CD_GNS" \
	$(chkDef "FALSE") "$CA_GUFW" "$CD_GUFW" \
	$(chkDef "FALSE") "$CA_KEEPASS" "$CD_KEEPASS" \
	$(chkDef "TRUE") "$CA_KEEPASSXC" "$CD_KEEPASSXC" \
	$(chkDef "FALSE") "$CA_MYSQLWB" "$CD_MYSQLWB" \
	$(chkDef "FALSE") "$CA_SIRIKALI" "$CD_SIRIKALI" \
	$(chkDef "FALSE") "$CA_UPM" "$CD_UPM" \
	$(chkDef "FALSE") "$CA_VERACRYPT" "$CD_VERACRYPT" \
	$(chkDef "FALSE") "$CA_WIRESHARK" "$CD_WIRESHARK" \
	$(chkDef "FALSE") "$CA_ZENMAP" "$CD_ZENMAP" \
	FALSE "$SCT_GAMING" "===========================================================" \
	$(chkDef "FALSE") "$CA_0AD" "$CD_0AD" \
	$(chkDef "FALSE") "$CA_ALBION" "$CD_ALBION" \
	$(chkDef "FALSE") "$CA_ALIENARENA" "$CD_ALIENARENA" \
	$(chkDef "FALSE") "$CA_ASSAULTCUBE" "$CD_ASSAULTCUBE" \
	$(chkDef "FALSE") "$CA_WESNOTH" "$CD_WESNOTH" \
	$(chkDef "FALSE") "$CA_DOFUS" "$CD_DOFUS" \
	$(chkDef "FALSE") "$CA_FLIGHTGEAR" "$CD_FLIGHTGEAR" \
	$(chkDef "FALSE") "$CA_FROZENBUBBLE" "$CD_FROZENBUBBLE" \
	$(chkDef "FALSE") "$CA_GNOMEGAMES" "$CD_GNOMEGAMES" \
	$(chkDef "FALSE") "$CA_LOL" "$CD_LOL" \
	$(chkDef "FALSE") "$CA_LUTRIS" "$CD_LUTRIS" \
	$(chkDef "FALSE") "$CA_MEGAGLEST" "$CD_MEGAGLEST" \
	$(chkDef "FALSE") "$CA_MINECRAFT" "$CD_MINECRAFT" \
	$(chkDef "FALSE") "$CA_MINETEST" "$CD_MINETEST" \
	$(chkDef "FALSE") "$CA_OPENARENA" "$CD_OPENARENA" \
	$(chkDef "FALSE") "$CA_PINGUS" "$CD_PINGUS" \
	$(chkDef "FALSE") "$CA_POKERTH" "$CD_POKERTH" \
	$(chkDef "FALSE") "$CA_QUAKE" "$CD_QUAKE" \
	$(chkDef "FALSE") "$CA_REDECLIPSE" "$CD_REDECLIPSE" \
	$(chkDef "FALSE") "$CA_RUNESCAPE" "$CD_RUNESCAPE" \
	$(chkDef "FALSE") "$CA_STEAM" "$CD_STEAM" \
	$(chkDef "FALSE") "$CA_SUPERTUX" "$CD_SUPERTUX" \
	$(chkDef "FALSE") "$CA_SUPERTUXKART" "$CD_SUPERTUXKART" \
	$(chkDef "FALSE") "$CA_TEEWORLDS" "$CD_TEEWORLDS" \
	$(chkDef "FALSE") "$CA_TMNF" "$CD_TMNF" \
	$(chkDef "FALSE") "$CA_UT4" "$CD_UT4" \
	$(chkDef "FALSE") "$CA_XQF" "$CD_XQF" \
	FALSE "$SCT_DEV" "===========================================================" \
	$(chkDef "FALSE") "$CA_ANDROIDSTUDIO" "$CD_ANDROIDSTUDIO" \
	$(chkDef "FALSE") "$CA_ANJUTA" "$CD_ANJUTA" \
	$(chkDef "FALSE") "$CA_ATOM" "$CD_ATOM" \
	$(chkDef "FALSE") "$CA_BLUEFISH" "$CD_BLUEFISH" \
	$(chkDef "FALSE") "$CA_BLUEGRIFFON" "$CD_BLUEGRIFFON" \
	$(chkDef "FALSE") "$CA_BRACKETS" "$CD_BRACKETS" \
	$(chkDef "FALSE") "$CA_CODEBLOCKS" "$CD_CODEBLOCKS" \
	$(chkDef "FALSE") "$CA_ECLIPSE" "$CD_ECLIPSE" \
	$(chkDef "FALSE") "$CA_EMACS" "$CD_EMACS" \
	$(chkDef "FALSE") "$CA_GDEVELOP" "$CD_GDEVELOP" \
	$(chkDef "FALSE") "$CA_GEANY" "$CD_GEANY" \
	$(chkDef "FALSE") "$CA_INTELLIJIDEA" "$CD_INTELLIJIDEA" \
	$(chkDef "FALSE") "$CA_PYCHARM" "$CD_PYCHARM" \
	$(chkDef "FALSE") "$CA_SCITE" "$CD_SCITE" \
	$(chkDef "FALSE") "$CA_SUBLIMETEXT" "$CD_SUBLIMETEXT" \
	$(chkDef "FALSE") "$CA_TEXSTUDIO" "$CD_TEXSTUDIO" \
	$(chkDef "FALSE") "$CA_TEXWORKS" "$CD_TEXWORKS" \
	$(chkDef "TRUE") "$CA_VIM" "$CD_VIM" \
	$(chkDef "FALSE") "$CA_VSCODE" "$CD_VSCODE" \
	FALSE "$SCT_OPTIMISATION" "===========================================================" \
	$(chkDef "FALSE") "$CA_IMPRIMANTE" "$CD_IMPRIMANTE" \
	$(chkDef "FALSE") "$CA_SECURITECPTE" "$CD_SECURITECPTE" \
	$(chkDef "TRUE") "$CA_COLORFOLDER" "$CD_COLORFOLDER" \
	$(chkDef "FALSE") "$CA_CONKY" "$CD_CONKY" \
	$(chkDef "FALSE") "$CA_SWAPOFF" "$CD_SWAPOFF" \
	$(chkDef "TRUE") "$CA_APPORTOFF" "$CA_APPORTOFF" \
	$(chkDef "FALSE") "$CA_GAMEMODE" "$CD_GAMEMODE" \
	$(chkDef "FALSE") "$CA_GCONF" "$CD_GCONF" \
	$(chkDef "FALSE") "$CA_GS_AUGMENTATIONCAPTURE" "$CD_GS_AUGMENTATIONCAPTURE" \
	$(chkDef "FALSE") "$CA_GS_MINIMISATIONFENETRE" "$CD_GS_MINIMISATIONFENETRE" \
	$(chkDef "FALSE") "$CA_GRUBDEFAULT" "$CD_GRUBDEFAULT" \
	$(chkDef "FALSE") "$CA_GRUBATTENTE" "$CD_GRUBATTENTE" \
	$(chkDef "TRUE") "$CA_GTWEAKTOOL" "$CD_GTWEAKTOOL" \
	$(chkDef "FALSE") "$CA_DVDREAD" "$CD_DVDREAD" \
	$(chkDef "FALSE") "$CA_PACKEXTENSION" "$CD_PACKEXTENSION" \
	$(chkDef "TRUE") "$CA_PACKICON" "$CD_PACKICON" \
	$(chkDef "TRUE") "$CA_PACKTHEME" "$CD_PACKTHEME" \
	$(chkDef "FALSE") "$CA_INTEL" "$CD_INTEL" \
	$(chkDef "FALSE") "$CA_NVNOUVEAU" "$CD_NVNOUVEAU" \
	$(chkDef "FALSE") "$CA_NVIDIA" "$CD_NVIDIA" \
	$(chkDef "FALSE") "$CA_NVIDIA_BP" "$CD_NVIDIA_BP" \
	$(chkDef "TRUE") "$CA_OPTIMIS_SWAP" "$CD_OPTIMIS_SWAP" \
	$(chkDef "FALSE") "$CA_SNAPREMPLACEMENT" "$CD_SNAPREMPLACEMENT" \
	$(chkDef "FALSE") "$CA_NAUTILUS_EXTRA" "$CD_NAUTILUS_EXTRA" \
	$(chkDef "FALSE") "$CA_SYSFIC" "$CD_SYSFIC" \
	$(chkDef "FALSE") "$CA_TLP" "$CD_TLP" \
	$(chkDef "FALSE") "$CA_TLP_THINKPAD" "$CD_TLP_THINKPAD" \
	$(chkDef "FALSE") "$CA_ZRAM" "$CD_ZRAM" \
	FALSE "$SCT_END" "===========================================================" \
	$(chkDef "TRUE") "$CA_AUTOREMOVE" "$CD_AUTOREMOVE" \
	$(chkDef "TRUE") "$CA_RES_DEP" "$CD_RES_DEP" \
	--separator='| ');

if [ $? = 0 ]
then
    # Debut
	f_action_exec "$CA_PARTNER" "sudo sed -i.bak '/^# deb .*partner/ s/^# //' /etc/apt/sources.list"
	f_action_exec "$CA_UPGRADE" "sudo apt update || read -p 'Attention, la commande de mise à jour (apt update) renvoi une erreur, il est recommandé de stopper le script et de corriger le problème avant de le lancer mais si vous voulez quand même poursuivre, tapez entrée' ; sudo apt full-upgrade -y" "$NS_UPGRADE"
	f_action_exec "$CA_FLATPAK" "sudo apt install flatpak gnome-software-plugin-flatpak -y ; sudo flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo"
	f_action_install "$CA_SNAP" "snapd gnome-software-plugin-snap"
	
    # Sessions
    f_action_install "$CA_GNOMEVANILLA" gnome-session
    f_action_install "$CA_GNOMECLASSIC" gnome-shell-extensions
    f_action_install "$CA_GNOMEFLASHBACKM" gnome-session-flashback
    f_action_install "$CA_GNOMEFLASHBACKC" "gnome-session-flashback compiz compizconfig-settings-manager compiz-plugins compiz-plugins-extra"
    f_action_snap_install "$CA_COMMUNITHEME" "communitheme gtk-common-themes"
    f_action_install "$CA_UNITY" "unity-session unity-tweak-tool"
    f_action_install "$CA_MATE" "mate-desktop-environment-extra"   
    
    # Navigateurs
    f_action_get_appimage "$CA_BEAKER" "https://github.com/beakerbrowser/beaker/releases/download/0.8.2/beaker-browser-0.8.2-x86_64.AppImage"
    f_action_exec "$CA_BRAVE" "curl https://s3-us-west-2.amazonaws.com/brave-apt/keys.asc | sudo apt-key add - ; echo 'deb [arch=amd64] https://s3-us-west-2.amazonaws.com/brave-apt `lsb_release -sc` main' | sudo tee -a /etc/apt/sources.list.d/brave-`lsb_release -sc`.list ; sudo apt update ; sudo apt install brave -y"
    f_action_install "$CA_CHROMIUM" "chromium-browser chromium-browser-l10n"
    f_action_install "$CA_DILLO" dillo
    f_action_flatpak_install "$CA_EOLIE" org.gnome.Eolie
    f_action_install "$CA_FALKON" qupzilla #falkon=qupzilla
   	f_action_ppa_install "$CA_FIREFOXBETA" ppa:mozillateam/firefox-next "firefox firefox-locale-fr"
   	f_action_flatpak_install "$CA_FIREFOXDEV" org.freedesktop.Platform.ffmpeg #dépendance nécessaire pour Firefox Dev Edition
   	f_action_exec "$CA_FIREFOXDEV" "sudo flatpak install --from https://firefox-flatpak.mojefedora.cz/org.mozilla.FirefoxDevEdition.flatpakref -y"
   	f_action_ppa_install "$CA_FIREFOXESR" ppa:mozillateam/ppa "firefox-esr firefox-esr-locale-fr"
   	f_action_ppa_install "$CA_FIREFOXNIGHTLY" ppa:ubuntu-mozilla-daily/ppa firefox-trunk 	
    f_action_install "$CA_EPIPHANY" epiphany-browser	
	f_action_exec "$CA_CHROME" "wget -qO - https://dl-ssl.google.com/linux/linux_signing_key.pub | sudo apt-key add - && sudo sh -c 'echo \"deb https://dl.google.com/linux/chrome/deb/ stable main\" > /etc/apt/sources.list.d/google-chrome.list' && sudo apt update && sudo apt install -y google-chrome-stable"
    f_action_install "$CA_LYNX" lynx
   	f_action_snap_install "$CA_MIDORI" midori
    f_action_get "$CA_MIN" "https://github.com/minbrowser/min/releases/download/v1.8.0/min_1.8.0_amd64.deb"
    f_action_get "$CA_OPERA" "http://nux87.free.fr/script-postinstall-ubuntu/deb/opera.deb"
    f_action_get "$CA_PALEMOON" "http://nux87.free.fr/script-postinstall-ubuntu/deb/palemoon.deb"
    f_action_get "$CA_SRWAREIRON" "http://www.srware.net/downloads/iron64.deb"
    f_action_install "$CA_TORBROWSER" torbrowser-launcher  
    f_action_get "$CA_VIVALDI" "http://nux87.free.fr/script-postinstall-ubuntu/deb/vivaldi.deb"

    # Internet / Transfert / Tchat
    f_action_install "$CA_AMULE" amule
    f_action_install "$CA_DELUGE" deluge
	f_action_get "$CA_DISCORD" "https://dl.discordapp.net/apps/linux/0.0.8/discord-0.0.8.deb"
    f_action_install "$CA_DROPBOX" nautilus-dropbox
	f_action_get "$CA_DUKTO" "https://download.opensuse.org/repositories/home:/colomboem/xUbuntu_16.04/amd64/dukto_6.0-1_amd64.deb"
    f_action_install "$CA_EISKALTDC" "eiskaltdcpp eiskaltdcpp-gtk3"
    f_action_install "$CA_EMPATHY" empathy    
	f_action_install "$CA_FILEZILLA" filezilla    
	f_action_get "$CA_FROSTWIRE" "https://dl.frostwire.com/frostwire/6.7.5/frostwire-6.7.5.all.deb"
   	f_action_snap_install "$CA_GYDL" gydl
	f_action_install "$CA_HEXCHAT" hexchat  
	f_action_get "$CA_HUBIC" "http://mir7.ovh.net/ovh-applications/hubic/hubiC-Linux/2.1.0/hubiC-Linux-2.1.0.53-linux.deb" hubic
	f_action_exec "$CA_JITSI" "wget -qO - https://download.jitsi.org/jitsi-key.gpg.key | sudo apt-key add - && sudo sh -c 'echo \"deb https://download.jitsi.org stable/\" > /etc/apt/sources.list.d/jitsi-stable.list' ; sudo apt update"
	f_action_install "$CA_JITSI" jitsi
	f_action_install "$CA_LINPHONE" linphone 
	f_action_install "$CA_MUMBLE" mumble 
	f_action_install "$CA_NICOTINE" nicotine
	f_action_install "$CA_PIDGIN" "pidgin pidgin-plugin-pack"
	f_action_install "$CA_POLARI" polari
	f_action_install "$CA_PSI" psi
	f_action_ppa_install "$CA_QARTE" ppa:vincent-vandevyvre/vvv qarte
	f_action_install "$CA_QBITTORRENT" qbittorrent	
	f_action_install "$CA_RING" ring
	f_action_flatpak_install "$CA_RIOT" im.riot.Riot
	f_action_exec "$CA_SIGNAL" "curl -s https://updates.signal.org/desktop/apt/keys.asc | sudo apt-key add - ; echo 'deb [arch=amd64] https://updates.signal.org/desktop/apt xenial main' | sudo tee -a /etc/apt/sources.list.d/signal-desktop.list ; sudo apt update ; sudo apt install signal-desktop -y"
    f_action_ppa_install "$CA_SKYPE" ppa:andykimpe/skype skype
	f_action_snap_install "$CA_SLACK" "slack --classic"
    f_action_install "$CA_SUBDOWNLOADER" subdownloader
	f_action_flatpak_install "$CA_TEAMSPEAK" com.teamspeak.TeamSpeak
	f_action_install "$CA_TELEGRAM" telegram-desktop
	f_action_install "$CA_UGET" uget	
	f_action_snap_install "$CA_VUZE" "vuze-vs"
	f_action_install "$CA_WEECHAT" weechat
	f_action_get "$CA_WHALEBIRD" "https://github.com/h3poteto/whalebird-desktop/releases/download/2.6.2/Whalebird-2.6.2-linux-x64.deb"
    f_action_ppa_install "$CA_WHATSAPP" ppa:atareao/whatsapp-desktop whatsapp-desktop
    f_action_exec "$CA_WIRE" "sudo apt-key adv --fetch-keys http://wire-app.wire.com/linux/releases.key && echo 'deb https://wire-app.wire.com/linux/debian stable main' | sudo tee /etc/apt/sources.list.d/wire-desktop.list && sudo apt update ; sudo apt install apt-transport-https wire-desktop -y"
	f_action_ppa_install "$CA_YTDLND" ppa:rvm/smplayer youtube-dl
	
	# Lecture Multimedia
	f_action_install "$CA_AUDACIOUS" audacious
	f_action_install "$CA_BANSHEE" banshee
	f_action_install "$CA_CLEMENTINE" clementine
	f_action_install "$CA_FLASH" "adobe-flashplugin pepperflashplugin-nonfree"
	f_action_install "$CA_GMUSICBROWSER" gmusicbrowser
    f_action_install "$CA_GNOMEMPV" gnome-mpv
    f_action_install "$CA_GNOMEMUSIC" gnome-music
    f_action_install "$CA_GNOMETWITCH" gnome-twitch
	f_action_flatpak_install "$CA_GRADIO" de.haeckerfelix.gradio
	f_action_ppa_install "$CA_LOLLYPOP" ppa:gnumdk/lollypop lollypop
	f_action_install "$CA_MOLOTOVTV" "libgconf2-4 desktop-file-utils" #pré-requis pour Molotov.tv
	f_action_get_appimage "$CA_MOLOTOVTV" "http://desktop-auto-upgrade.molotov.tv/linux/4.0.0/molotov.AppImage"
    f_action_install "$CA_PAVUCONTROL" pavucontrol	
    f_action_install "$CA_QMMP" qmmp	
    f_action_install "$CA_QUODLIBET" quodlibet	
    f_action_install "$CA_RHYTHMBOX" rhythmbox		
    f_action_install "$CA_SHOTWELL" shotwell	
    f_action_install "$CA_SMPLAYER" "smplayer smplayer-l10n smplayer-themes"	    
    f_action_exec "$CA_SPOTIFY" "echo 'deb http://repository.spotify.com stable non-free' | sudo tee -a /etc/apt/sources.list.d/spotify.list ; sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys A87FF9DF48BF1C90 ; sudo apt update && sudo apt install spotify-client spotify-client-gnome-support -y"
    f_action_install "$CA_UFRAW" "ufraw ufraw-batch"
	f_action_install "$CA_VLCSTABLE" "vlc vlc-l10n"
	f_action_snap_install "$CA_VLCDEV" "vlc --edge --classic"
    f_action_exec "$CA_RESTRICT_EXTRA" "echo ttf-mscorefonts-installer msttcorefonts/accepted-mscorefonts-eula select true | sudo /usr/bin/debconf-set-selections ; sudo apt install ttf-mscorefonts-installer -y" #(police d'écriture en dépendance dans Ubuntu Restricted Extra)
    f_action_install "$CA_RESTRICT_EXTRA" "ubuntu-restricted-extras libavcodec-extra-53 gstreamer0.10-plugins-bad-multiverse"
		
	# Montage Multimédia
	f_action_install "$CA_ARDOUR" ardour
	#f_action_exec "$CA_ARDOUR" "debconf-set-selections <<< 'jackd/tweak_rt_limits false' ; sudo apt install ardour -y" ## non-interraction ne fonctionne pas
	f_action_install "$CA_AUDACITY" audacity
	f_action_flatpak_install "$CA_AVIDEMUX" org.avidemux.Avidemux
	f_action_install "$CA_BLENDER" blender	
	f_action_ppa_install "$CA_CINELERRA" ppa:cinelerra-ppa/ppa cinelerra-cv
	f_action_install "$CA_DARKTABLE" darktable
	f_action_install "$CA_EASYTAG" easytag
	f_action_ppa_install "$CA_FLACON" ppa:flacon/ppa flacon
	f_action_install "$CA_FLAMESHOT" flameshot
	f_action_install "$CA_FLOWBLADE" flowblade
	f_action_ppa_install "$CA_FREECAD" ppa:freecad-maintainers/freecad-stable freecad
	f_action_install "$CA_GIMPDEPOT" "gimp gimp-help-fr gimp-data-extras"
	f_action_ppa_install "$CA_GIMP" ppa:otto-kesselgulasch/gimp "gimp gimp-help-fr gimp-data-extras"	
	f_action_install "$CA_GNOMESOUNDRECORDER" gnome-sound-recorder
	f_action_install "$CA_HANDBRAKE" handbrake
	f_action_install "$CA_HYDROGEN" hydrogen
	f_action_install "$CA_INKSCAPE" inkscape
	f_action_install "$CA_K3D" k3d
	f_action_install "$CA_KAZAM" kazam	
	f_action_install "$CA_KDENLIVE" kdenlive		
	f_action_install "$CA_KOLOURPAINT" kolourpaint	
	f_action_install "$CA_KRITA" krita
	f_action_get "$CA_LIGHTWORKS" "https://downloads.lwks.com/v14-5-new/lightworks-14.5.0-amd64.deb"
	f_action_install "$CA_LIBRECAD" librecad
	f_action_install "$CA_LIVES" lives	
	f_action_install "$CA_LUMINANCE" luminance-hdr
	f_action_install "$CA_LMMS" lmms	
	f_action_install "$CA_MHWAVEEDIT" mhwaveedit	
	f_action_install "$CA_MIXXX" mixxx
	f_action_install "$CA_MUSESCORE" musescore	
	f_action_install "$CA_MYPAINT" "mypaint mypaint-data-extras"	 
	f_action_get "$CA_NATRON" "https://downloads.natron.fr/Linux/releases/64bit/files/natron_2.3.14_amd64.deb"
	f_action_ppa_install "$CA_OBS" ppa:obsproject/obs-studio "ffmpeg obs-studio"
	f_action_install "$CA_OPENSHOT" openshot-qt
	f_action_ppa_install "$CA_PEEK" ppa:peek-developers/stable peek
	f_action_install "$CA_PINTA" pinta	
	f_action_install "$CA_PITIVI" pitivi	
	f_action_get "$CA_PIXELUVO" "http://www.pixeluvo.com/downloads/pixeluvo_1.6.0-2_amd64.deb"
	f_action_install "$CA_ROSEGARDEN" rosegarden
	f_action_ppa_install "$CA_SHOTCUT" ppa:haraldhv/shotcut shotcut
	f_action_install "$CA_SHUTTER" shutter
	f_action_install "$CA_SIMPLESCREENRECORDER" simplescreenrecorder
	f_action_install "$CA_SOUNDJUICER" sound-juicer
	f_action_install "$CA_SWEETHOME" sweethome3d
	f_action_get "$CA_UNITY3DEDITOR" "http://fr.archive.ubuntu.com/ubuntu/pool/main/libp/libpng/libpng12-0_1.2.54-1ubuntu1_amd64.deb"
	f_action_get "$CA_UNITY3DEDITOR" "http://download.unity3d.com/download_unity/unity-editor-5.1.0f3+2015090301_amd64.deb"
	f_action_install "$CA_WINFF" "winff winff-qt"
	
	# Bureautique/Mail
	f_action_install "$CA_CALLIGRA" calligra
	f_action_install "$CA_FRDIC" "myspell-fr-gut wfrench aspell-fr hyphen-fr mythes-fr"
	f_action_install "$CA_FBREADER" fbreader
	f_action_flatpak_install "$CA_FEEDREADER" org.gnome.FeedReader
	f_action_get "$CA_FREEOFFICE" "https://www.softmaker.net/down/softmaker-freeoffice-2018_938-01_amd64.deb"
	f_action_install "$CA_FREEPLANE" freeplane
	f_action_install "$CA_GEARY" geary	
	f_action_install "$CA_EVOLUTION" evolution
	f_action_install "$CA_GNOMEOFFICE" "abiword gnumeric dia planner glabels glom tomboy gnucash"	
	f_action_install "$CA_GRAMPS" gramps
	f_action_get_appimage "$CA_JOPLIN" "https://github.com/laurent22/joplin/releases/download/v1.0.104/Joplin-1.0.104-x86_64.AppImage"
    f_action_install "$CA_LIBREOFFICEDEPOT" "libreoffice libreoffice-l10n-fr libreoffice-style-breeze"
	f_action_ppa_install "$CA_LIBREOFFICEFRESH" ppa:libreoffice/ppa "libreoffice libreoffice-l10n-fr libreoffice-style-breeze"
	f_action_install "$CA_LIBREOFFICESUP" "libreoffice-style-elementary libreoffice-style-oxygen libreoffice-style-human libreoffice-style-sifr libreoffice-style-tango libreoffice-templates openclipart-libreoffice"
	f_action_snap_install "$CA_MAILSPRING" mailspring
	f_action_get "$CA_MASTERPDFEDITOR" "https://code-industry.net/public/master-pdf-editor-5.3.00_qt5.amd64.deb"
	f_action_flatpak_install "$CA_NOTESUP" com.github.philip_scott.notes-up  
	f_action_exec "$CA_ONLYOFFICE" "sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys CB2DE8E5 && echo 'deb http://download.onlyoffice.com/repo/debian squeeze main' | sudo tee -a /etc/apt/sources.list.d/onlyoffice.list ; sudo apt update && sudo apt install onlyoffice-desktopeditors -y"
    f_action_exec "$CA_OPENOFFICE" "wget https://netix.dl.sourceforge.net/project/openofficeorg.mirror/4.1.6/binaries/fr/Apache_OpenOffice_4.1.6_Linux_x86-64_install-deb_fr.tar.gz ; sudo tar xvfz Apache_OpenOffice* ; sudo dpkg -i ./fr/DEBS/*.deb ; wget https://gitlab.com/simbd/Fichier_de_config/raw/master/ooo.desktop ; sudo mv ooo.desktop /usr/share/applications/ ; wget http://nux87.free.fr/script-postinstall-ubuntu/theme/openoffice.png && sudo mv openoffice.png /usr/share/icons/ ; sudo rm -rf ./fr Apache_OpenOffice*"
    f_action_install "$CA_PDFMOD" pdfmod
    f_action_exec "$CA_POLICEMST" "echo ttf-mscorefonts-installer msttcorefonts/accepted-mscorefonts-eula select true | sudo /usr/bin/debconf-set-selections ; sudo apt install ttf-mscorefonts-installer -y"
    f_action_exec "$CA_SCENARI" "wget http://nux87.free.fr/script-postinstall-ubuntu/deb/libav-tools_3.3.4-2_all.deb ; sudo dpkg -i libav-tools* ; wget -O- https://download.scenari.org/deb/scenari.asc | sudo apt-key add - ; echo 'deb https://download.scenari.org/deb bionic main' | sudo tee -a /etc/apt/sources.list.d/scenari.list ; sudo apt update ; sudo apt install -fy ; sudo apt install scenarichain4.2.fr-fr opale3.7.fr-fr -y"
    f_action_install "$CA_SCRIBUS" "scribus scribus-template"	
 	f_action_install "$CA_THUNDERBIRD" "thunderbird thunderbird-locale-fr thunderbird-gnome-support ttf-lyx fonts-symbola"
	f_action_get "$CA_WPSOFFICE" "http://fr.archive.ubuntu.com/ubuntu/pool/main/libp/libpng/libpng12-0_1.2.54-1ubuntu1_amd64.deb"
	f_action_get "$CA_WPSOFFICE" "http://kdl.cc.ksosoft.com/wps-community/download/6757/wps-office_10.1.0.6757_amd64.deb"
	f_action_install "$CA_XPAD" xpad
	f_action_install "$CA_ZIM" zim
	
	# Science/Education
	f_action_install "$CA_ALGOBOX" algobox
	f_action_install "$CA_ASTROEDU" astro-education
	f_action_install "$CA_AVOGADRO" avogadro
	f_action_exec "$CA_CELESTIA" "wget --no-check-certificate https://gitlab.com/simbd/Scripts_Ubuntu/raw/master/Celestia_pour_Bionic.sh ; sudo chmod +x Celestia* ; sudo ./Celestia*.sh ; rm Celestia*"
	f_action_install "$CA_CONVERTALL" convertall
	f_action_get "$CA_GANTTPROJECT" "https://datapacket.dl.sourceforge.net/project/ganttproject/ganttproject-2.8.9/ganttproject_2.8.9-r2335-1_all.deb"
	f_action_install "$CA_GCOMPRIS" "gcompris gcompris-qt gcompris-qt-data gnucap"
	f_action_install "$CA_GELEMENTAL" gelemental
	f_action_install "$CA_GEOGEBRA" geogebra
	f_action_install "$CA_GNOMEMAPS" gnome-maps
	f_action_get "$CA_GOOGLEEARTH" "https://dl.google.com/dl/earth/client/current/google-earth-pro-stable_current_amd64.deb"
	f_action_install "$CA_MARBLE" "--no-install-recommends marble"
	f_action_install "$CA_MBLOCK" libgconf-2-4 #dépendance pour Mblock
	f_action_get "$CA_MBLOCK" "http://mblock.makeblock.com/mBlock4.0/mBlock_4.0.4_amd64.deb"
	f_action_flatpak_install "$CA_OPENBOARD" ch.openboard.OpenBoard
	f_action_install "$CA_OPTGEO" optgeo
	f_action_install "$CA_PLANNER" planner
	f_action_exec "$CA_SCRATCH" "wget http://nux87.free.fr/script-postinstall-ubuntu/theme/scratch.png ; wget https://gitlab.com/simbd/Fichier_de_config/raw/master/scratch.desktop ; wget http://www.ac-grenoble.fr/maths/scratch/scratch.zip ; sudo unzip scratch.zip -d /opt/scratch3 ; rm scratch.zip ; sudo mv scratch.png /usr/share/icons/ ; sudo mv scratch.desktop /usr/share/applications/"
	f_action_install "$CA_STELLARIUM" stellarium
	f_action_install "$CA_TOUTENCLIC" python3-pyqt5
	f_action_exec "$CA_TOUTENCLIC" "wget http://www.bipede.fr/downloads/logiciels/ToutEnClic.zip ; unzip ToutEnClic.zip ; rm ToutEnClic.zip ; sudo mv ToutEnClic /opt/ ; wget https://gitlab.com/simbd/Fichier_de_config/raw/master/toutenclic.desktop --no-check-certificate ; sudo mv toutenclic.desktop /usr/share/applications/ ; wget http://nux87.free.fr/script-postinstall-ubuntu/theme/toutenclic.png --no-check-certificate ; sudo mv toutenclic.png /usr/share/icons/"
	f_action_install "$CA_XCAS" xcas
	
	# Utilitaires graphiques
	f_action_get "$CA_ANYDESK" "https://download.anydesk.com/linux/anydesk_4.0.1-1_amd64.deb"
	f_action_install "$CA_BRASERO" "brasero brasero-cdrkit"
	f_action_install "$CA_CHEESE" cheese
	f_action_install "$CA_DEJADUP" deja-dup
	f_action_install "$CA_DIODON" diodon
    f_action_install "$CA_DOSBOX" dosbox
	f_action_exec "$CA_ETCHER" "echo 'deb https://dl.bintray.com/resin-io/debian stable etcher' | sudo tee /etc/apt/sources.list.d/etcher.list ; sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 379CE192D401AB61 ; sudo apt update ; sudo apt install etcher-electron -y"
	f_action_install "$CA_GNOME_DISK" gnome-disk-utility
	f_action_install "$CA_GNOMERECIPES" gnome-recipes
	f_action_install "$CA_GSYSLOG" gnome-system-log
	f_action_install "$CA_GSYSMON" gnome-system-monitor
	f_action_install "$CA_GPARTED" gparted
	f_action_exec "$CA_JRE8" "sudo add-apt-repository -y ppa:webupd8team/java ; sudo apt update ; echo oracle-java8-installer shared/accepted-oracle-license-v1-1 select true | sudo /usr/bin/debconf-set-selections ; sudo apt install oracle-java8-installer -y"
	f_action_exec "$CA_JRE11" "sudo add-apt-repository -y ppa:linuxuprising/java ; sudo apt update ; echo oracle-java11-installer shared/accepted-oracle-license-v1-2 select true | sudo /usr/bin/debconf-set-selections ; sudo apt install oracle-java11-installer -y"	
    f_action_install "$CA_MELD" meld
	f_action_exec "$CA_MULTISYSTEM" "wget -q http://liveusb.info/multisystem/depot/multisystem.asc -O- | sudo apt-key add - ; sudo add-apt-repository -y 'deb http://liveusb.info/multisystem/depot all main' ; sudo apt update ; sudo apt install multisystem -y"
	f_action_install "$CA_ARCHIVAGE" "unace rar unrar p7zip-rar p7zip-full sharutils uudeview mpack arj cabextract lzip lunzip"
	f_action_install "$CA_POL" playonlinux
	f_action_install "$CA_REDSHIFT" redshift-gtk
	f_action_install "$CA_REMMINA" remmina
	f_action_exec "$CA_SUBLIM_NAUT" "wget https://raw.githubusercontent.com/Diaoul/nautilus-subliminal/master/install.sh -O - | sudo bash"
	f_action_install "$CA_SUB_EDIT" subtitleeditor
	f_action_install "$CA_SYNAPTIC" synaptic
	f_action_get "$CA_TEAMVIEWER" "https://download.teamviewer.com/download/linux/teamviewer_amd64.deb"
	f_action_install "$CA_TERMINATOR" terminator
	f_action_ppa_install "$CA_TIMESHIFT" ppa:teejee2008/ppa timeshift
	f_action_install "$CA_VARIETY" variety
	f_action_install "$CA_VBOXDEPOT" "virtualbox virtualbox-qt"
    f_action_exec "$CA_VBOXLAST" "echo 'deb [arch=amd64] http://download.virtualbox.org/virtualbox/debian bionic contrib' | sudo tee /etc/apt/sources.list.d/virtualbox.list && wget -q -O- http://download.virtualbox.org/virtualbox/debian/oracle_vbox_2016.asc | sudo apt-key add - && sudo apt update && sudo apt install virtualbox-6.0 -y && sudo usermod -G vboxusers -a $USER" 
	f_action_exec "$CA_VMWARE" "wget http://download3.vmware.com/software/player/file/VMware-Player-15.0.2-10952284.x86_64.bundle ; sudo chmod +x VMware-Player* ; sudo ./VMware-Player-15.0.2-10952284.x86_64.bundle ; sudo rm VMware-Player*"
	f_action_install "$CA_WINE" "wine-development winetricks"
	f_action_install "$CA_X2GO" x2goclient
	f_action_install "$CA_X11VNC" x11vnc
	
	# Utilitaires en CLI
	f_action_install "$CA_DDRESCUE" gddrescue
	f_action_get "$CA_FD" "https://github.com/sharkdp/fd/releases/download/v7.0.0/fd_7.0.0_amd64.deb"	
	f_action_install "$CA_GIT" git
	f_action_install "$CA_HTOP" htop
	f_action_install "$CA_GLANCES" glances
	f_action_install "$CA_LAME" lame
	f_action_install "$CA_HG" mercurial
	f_action_install "$CA_PACKOUTILS" "neofetch asciinema ncdu screen"
	f_action_get "$CA_POWERSHELL" "https://packages.microsoft.com/config/ubuntu/18.04/packages-microsoft-prod.deb "	
	f_action_install "$CA_POWERSHELL" powershell
	f_action_snap_install "$CA_RIPGREP" "ripgrep --classic"
	f_action_install "$CA_RTORRENT" rtorrent
	f_action_install "$CA_SMARTMONTOOLS" "--no-install-recommends smartmontools"
	f_action_install "$CA_TESTDISK" testdisk
	f_action_snap_install "$CA_TLDR" tldr
	f_action_install "$CA_WORDGRINDER" "wordgrinder wordgrinder-x11"
	f_action_install "$CA_WORMHOLE" magic-wormhole

	# Réseaux et sécurité
	f_action_install "$CA_ANSIBLE" ansible
	f_action_get_appimage "$CA_CRYPTER" "https://github.com/HR/Crypter/releases/download/v3.1.0/Crypter-3.1.0-x86_64.AppImage"
	f_action_exec "$CA_ENPASS" "echo 'deb http://repo.sinew.in/ stable main' | sudo tee /etc/apt/sources.list.d/enpass.list ; wget -O - https://dl.sinew.in/keys/enpass-linux.key | sudo apt-key add - ; sudo apt update ; sudo apt install enpass -y"
	f_action_ppa_install "$CA_GEM" ppa:gencfsm/ppa gnome-encfs-manager
	f_action_install "$CA_GNS" gns3
	f_action_install "$CA_GUFW" gufw
	f_action_install "$CA_KEEPASS" keepass2
    f_action_install "$CA_KEEPASSXC" keepassxc
	f_action_install "$CA_MYSQLWB" mysql-workbench
	f_action_install "$CA_SIRIKALI" sirikali
	f_action_ppa_install "$CA_UPM" "ppa:adriansmith/upm" upm
	f_action_ppa_install "$CA_VERACRYPT" ppa:unit193/encryption veracrypt
	f_action_install "$CA_WIRESHARK" wireshark
	f_action_install "$CA_ZENMAP" zenmap
	
	# Gaming
	f_action_install "$CA_0AD" 0ad
	f_action_flatpak_install "$CA_ALBION" com.albiononline.AlbionOnline
	f_action_install "$CA_ALIENARENA" alien-arena
	f_action_install "$CA_ASSAULTCUBE" assaultcube
	f_action_install "$CA_WESNOTH" wesnoth
	f_action_exec "$CA_DOFUS" "wget https://gitlab.com/simbd/Scripts_divers/raw/master/Dofus_install1804.sh ; sudo chmod +x Dofus*.sh ; sudo ./Dofus_install1804.sh ; rm Dofus*.sh"
	f_action_install "$CA_FLIGHTGEAR" flightgear
	f_action_install "$CA_FROZENBUBBLE" frozen-bubble
	f_action_install "$CA_GNOMEGAMES" "gnome-games gnome-games-app"
	f_action_snap_install "$CA_LOL" "leagueoflegends --edge --devmode"
	f_action_exec "$CA_LUTRIS" "echo 'deb http://download.opensuse.org/repositories/home:/strycore/xUbuntu_18.04/ ./' | sudo tee /etc/apt/sources.list.d/lutris.list ; wget -q https://download.opensuse.org/repositories/home:/strycore/xUbuntu_18.04/Release.key -O- | sudo apt-key add - ; sudo apt update ; sudo apt install lutris -y"
	f_action_install "$CA_MEGAGLEST" megaglest
	f_action_get "$CA_MINECRAFT" "https://launcher.mojang.com/download/Minecraft.deb"
	f_action_install "$CA_MINETEST" "minetest minetest-mod-nether"
	f_action_install "$CA_OPENARENA" openarena
	f_action_install "$CA_PINGUS" pingus
	f_action_install "$CA_POKERTH" pokerth
	f_action_snap_install "$CA_QUAKE" quake-shareware
	f_action_install "$CA_REDECLIPSE" redeclipse
	f_action_install "$CA_RUNESCAPE" runescape
	f_action_install "$CA_STEAM" steam
	f_action_install "$CA_SUPERTUX" supertux
	f_action_install "$CA_SUPERTUXKART" supertuxkart	
	f_action_install "$CA_TEEWORLDS" teeworlds		
	f_action_snap_install "$CA_TMNF" tmnationsforever
	f_action_exec "$CA_UT4" "wget https://gitlab.com/simbd/Scripts_divers/raw/master/UnrealTournament4_Install.sh ; sudo chmod +x UnrealTournament*"
	f_action_install "$CA_XQF" xqf
	
	# Programmation / Dev  
	f_action_ppa_install "$CA_ANDROIDSTUDIO" ppa:maarten-fonville/android-studio android-studio
	f_action_install "$CA_ANJUTA" "anjuta anjuta-extras"
	f_action_ppa_install "$CA_ATOM" ppa:webupd8team/atom atom
	f_action_install "$CA_BLUEFISH" "bluefish bluefish-plugins"
	f_action_get "$CA_BLUEGRIFFON" "http://bluegriffon.org/freshmeat/3.0.1/bluegriffon-3.0.1.Ubuntu16.04-x86_64.deb"
	f_action_ppa_install "$CA_BRACKETS" ppa:webupd8team/brackets brackets
	f_action_install "$CA_CODEBLOCKS" "codeblocks codeblocks-contrib"
	f_action_snap_install "$CA_ECLIPSE" "eclipse --classic"
	f_action_install "$CA_EMACS" emacs
	f_action_exec "$CA_GDEVELOP" "sudo apt install libgconf-2-4 -y ; wget https://github.com/4ian/GDevelop/releases/download/v5.0.0-beta55/gdevelop-5.0.0-beta55.tar.gz ; sudo tar xzvf gdevelop*.tar.gz ; rm gdevelop*tar.gz ; sudo mv gdevelop* /opt/gdevelop ; wget https://gitlab.com/simbd/Fichier_de_config/raw/master/gdevelop.desktop ; sudo mv gdevelop.desktop /usr/share/applications/ ; wget http://nux87.free.fr/script-postinstall-ubuntu/theme/gdevelop.png && sudo mv gdevelop.png /usr/share/icons/"
	f_action_install "$CA_GEANY" "geany geany-plugins"	
	f_action_snap_install "$CA_INTELLIJIDEA" "intellij-idea-community --classic"
	f_action_snap_install "$CA_PYCHARM" "pycharm-community --classic"
	f_action_install "$CA_SCITE" scite
	f_action_flatpak_install "$CA_SUBLIMETEXT" com.sublimetext.three
	f_action_install "$CA_TEXSTUDIO" texstudio
	f_action_install "$CA_TEXWORKS" "texlive texlive-lang-french texworks"
	f_action_install "$CA_VIM" vim
	f_action_exec "$CA_VSCODE" "sudo curl https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > microsoft.gpg ; sudo install -o root -g root -m 644 microsoft.gpg /etc/apt/trusted.gpg.d/"
	f_action_exec "$CA_VSCODE" "echo 'deb [arch=amd64] https://packages.microsoft.com/repos/vscode stable main' | sudo tee -a /etc/apt/sources.list.d/vscode.list ; sudo apt update"
	f_action_install "$CA_VSCODE" "apt-transport-https code"
	
	# Hardware, Customisation et Optimisation
	f_action_install "$CA_IMPRIMANTE" "hplip hplip-doc hplip-gui sane sane-utils"
	f_action_exec "$CA_SECURITECPTE" "sudo chmod -R o=- /home/$USER"
	f_action_install "$CA_COLORFOLDER" folder-color
	f_action_exec "$CA_CONKY" "wget https://gitlab.com/simbd/Fichier_de_config/raw/master/.conkyrc && mv .conkyrc ~/ ; sudo apt install conky -y"
    f_action_exec "$CA_SWAPOFF" "sudo swapoff /swapfile ; sudo rm /swapfile ; sudo sed -i -e '/.swapfile*/d' /etc/fstab" 
    f_action_exec "$CA_APPORTOFF" "sudo sed -i 's/^enabled=1$/enabled=0/' /etc/default/apport"
    f_action_exec "$CA_GAMEMODE" "sudo apt install meson libsystemd-dev pkg-config ninja-build mesa-utils -y && git clone https://github.com/FeralInteractive/gamemode.git ; cd gamemode ; sudo ./bootstrap.sh ; cd .."
	f_action_install "$CA_GCONF" gconf-editor
	f_action_exec "$CA_GS_AUGMENTATIONCAPTURE" "gsettings set org.gnome.settings-daemon.plugins.media-keys max-screencast-length 600"
	f_action_exec "$CA_GS_MINIMISATIONFENETRE" "gsettings set org.gnome.shell.extensions.dash-to-dock click-action 'minimize'"
	f_action_exec "$CA_GRUBDEFAULT" "sudo sed -ri 's/GRUB_DEFAULT=0/GRUB_DEFAULT="saved"/g' /etc/default/grub ; echo 'GRUB_SAVEDEFAULT="true"' | sudo tee -a /etc/default/grub ; sudo update-grub"
	f_action_exec "$CA_GRUBATTENTE" "sudo sed -ri 's/GRUB_TIMEOUT=10/GRUB_TIMEOUT=2/g' /etc/default/grub ; sudo mkdir /boot/old ; sudo mv /boot/memtest86* /boot/old/ ; sudo update-grub"
	f_action_exec "$CA_GTWEAKTOOL" "if [ '$(which gnome-shell)' != '/dev/null' ] ; then sudo apt install gnome-tweak-tool -y ; fi"
	f_action_exec "$CA_DVDREAD" "sudo apt install libdvdcss2 libdvd-pkg -y ; sudo dpkg-reconfigure libdvd-pkg"
	f_action_install "$CA_PACKEXTENSION" "gnome-shell-extension-caffeine gnome-shell-extension-dashtodock gnome-shell-extension-dash-to-panel gnome-shell-extension-impatience gnome-shell-extension-weather gnome-shell-extension-system-monitor"
	f_action_install "$CA_PACKICON" "papirus-icon-theme numix-icon-theme breeze-icon-theme gnome-brave-icon-theme elementary-icon-theme oxygen-icon-theme"
	f_action_install "$CA_PACKTHEME" "arc-theme numix-blue-gtk-theme numix-gtk-theme materia-gtk-theme yuyo-gtk-theme human-theme"
	f_action_install "$CA_INTEL" intel-microcode
	f_action_install "$CA_NVNOUVEAU" switcheroo-control
	f_action_install "$CA_NVIDIA" "nvidia-driver-390 nvidia-prime nvidia-settings"
	f_action_ppa_install "$CA_NVIDIA_BP" ppa:graphics-drivers/ppa "nvidia-graphics-drivers-415 nvidia-settings nvidia-prime vulkan"
	f_action_exec "$CA_OPTIMIS_SWAP" "echo vm.swappiness=5 | sudo tee /etc/sysctl.d/99-swappiness.conf ; echo vm.vfs_cache_pressure=50 | sudo tee -a /etc/sysctl.d/99-sysctl.conf ; sudo sysctl -p /etc/sysctl.d/99-sysctl.conf"
	f_action_exec "$CA_SNAPREMPLACEMENT" "sudo snap remove gnome-calculator gnome-characters gnome-logs gnome-system-monitor ; sudo apt install gnome-calculator gnome-characters gnome-logs gnome-system-monitor -y"
	f_action_install "$CA_NAUTILUS_EXTRA" "nautilus-compare nautilus-admin nautilus-extension-gnome-terminal nautilus-filename-repairer nautilus-gtkhash nautilus-script-audio-convert nautilus-sendto nautilus-share nautilus-wipe"
	f_action_install "$CA_SYSFIC" "btrfs-tools exfat-utils exfat-fuse hfsprogs hfsutils hfsplus xfsprogs xfsdump zfsutils-linux"
	f_action_ppa_install "$CA_TLP" "ppa:linrunner/tlp" "tlp tlp-rdw"
	f_action_ppa_install "$CA_TLP_THINKPAD" "ppa:linrunner/tlp" "tlp tlp-rdw tp-smapi-dkms acpi-call-tools"	
	f_action_install "$CA_ZRAM" zram-config
	
	# Installations de tous les PPA
	#if [ "X$ALL_PPA_INSTALL" != "X" ]
	#then
	#	notify-send -i system-software-update "$NS_ALL_PPA" "$NS_INSTALL $ALL_PPA_NS" -t 5000
	#	sudo apt update
	#	sudo apt install -y $ALL_PPA_INSTALL
	#fi
    
    # Fin
	f_action_exec "$CA_AUTOREMOVE" "sudo apt update ; sudo apt full-upgrade -y ; sudo apt autoremove --purge -y && sudo apt clean -y"
	f_action_exec "$CA_RES_DEP" "sudo apt install -fy"

	# Notification End 
	notify-send -i dialog-ok "$NS_END_TITLE" "$NS_END_TEXT" -t 5000

	zenity --warning --no-wrap --height 500 --width 900 --title "$MSG_END_TITLE" --text "$MSG_END_TEXT"
else
	zenity --question --title "$MSG_END_CANCEL_TITLE" --text "$MSG_END_CANCEL_TEXT"
	if [ $? == 0 ] 
	then
		gxmessage -center -geometry 400x900 -name "$MSG_END_TITLE" "$MSG_END_TEXT"
	fi
fi