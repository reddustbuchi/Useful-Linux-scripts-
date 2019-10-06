#!
# include file by the my.... command series (post installation scripts)
#

DOWNLOAD_DIR="/tmp/"
#MY_PROG=$(basename $0 .sh)
MY_PROG=DC_LangueFR_Pi
GUI=""
ALL_PPA_INSTALL=""
ALL_PPA_NS=""

# Set language with given parameter
if [ "X$1" != "X" ]
then
	LANG=$1
fi

# Langue ## Uniquement en FR pour l'instant.
f_get_msg(){
	no_msg_file="Erreur : fichier non trouvé ou problème de permission d'accès !"
	lang=${LANG:=english}
	case ${lang} in
		[Ee][Nn][Gg]*	)	all_msg=${MY_DIR}/${MY_PROG}.fr 
							DOWNLOAD_DIR=~/Downloads/;;
		[Ff][Rr]*	)	all_msg=${MY_DIR}/${MY_PROG}.fr 
						DOWNLOAD_DIR=~/Téléchargements/;;
		*			)	all_msg=${MY_DIR}/${MY_PROG}.fr
						DOWNLOAD_DIR=~/Downloads/;;
	esac
	if [ -f ${all_msg} -a -r ${all_msg} ]
	then
		. ${all_msg}
	else
		echo ${no_msg_file}
		exit 3
	fi
}

# Run Action $1 with command $2 and display notification $3, if given
f_action_exec() {
	if [[ "$GUI" = *"$1"* ]]
	then
		if [ "X$3" = "X" ]
		then
			ns_exec="$NS_INSTALL $1"
		else
			ns_exec="$3"
		fi
		echo $ns_exec " ..."
		echo ""
		notify-send -i system-software-update "$MY_PROG" "$ns_exec" -t 5000
		dash -c "$2"
	fi
}

# Run Action $1 by installing $2 and display notification
f_action_install() {
	if [[ "$GUI" == *"$1"* ]]
	then
		echo "$NS_INSTALL $1 ..."
		echo ""
		notify-send -i system-software-update "$MY_PROG" "$NS_INSTALL $1" -t 5000
		sudo apt install -y $2
	fi
}

# Run Action $1 by adding ppa $2 and installing $3 and display notification

#f_action_ppa_install() {
#	if [[ "$GUI" == *"$1"* ]]
#	then
#		echo  "$NS_DEFERED $1 ..."
#		echo ""
#		ALL_PPA_NS="${ALL_PPA_NS} $1"
#		sudo add-apt-repository -y $2
#		ALL_PPA_INSTALL="${ALL_PPA_INSTALL} $3"
#	fi
#}

# Installation via un PPA
f_action_ppa_install() {
	if [[ "$GUI" == *"$1"* ]]
	then
		echo "$NS_INSTALL $1 ..."
		echo ""
		notify-send -i system-software-update "$MY_PROG" "$NS_INSTALL $1" -t 5000
		sudo add-apt-repository -y $2
		sudo apt update ; sudo apt install -y $3
	fi
}







# Run Action $1 by downloading $2 and installing the downloaded file (end of $2), and display notification
f_action_get() {
	if [[ "$GUI" == *"$1"* ]]
	then
		echo "$NS_INSTALL $1 ..."
		echo ""
		notify-send -i system-software-update "$MY_PROG" "$NS_INSTALL $1" -t 5000
		cd $DOWNLOAD_DIR
		wget "$2" --no-check-certificate
		sudo apt install -y ./"${2##*/}"
		rm *.deb
	fi
}

# Récupération paquet AppImage + droit d'execution
f_action_get_appimage() {
	if [[ "$GUI" == *"$1"* ]]
	then
		echo "$NS_INSTALL $1 ..."
		echo ""
		notify-send -i system-software-update "$MY_PROG" "$NS_INSTALL $1" -t 5000
		cd $DOWNLOAD_DIR
		wget "$2" --no-check-certificate
		chmod u+x "${2##*/}"
	fi
}

# Installation paquet Snap
f_action_snap_install() {
	if [[ "$GUI" == *"$1"* ]]
	then
		echo  "$NS_DEFERED $1 ..."
		echo ""
		ALL_SNAP_NS="${ALL_SNAP_NS} $1"
		sudo snap install $2
		ALL_SNAP_INSTALL="${ALL_SNAP_INSTALL} $3"
	fi
}

# Installation paquet Flatpak
f_action_flatpak_install() {
	if [[ "$GUI" == *"$1"* ]]
	then
		echo  "$NS_DEFERED $1 ..."
		echo ""
		ALL_FLATPAK_NS="${ALL_FLATPAK_NS} $1"
		flatpak install flathub $2 -y
		ALL_FLATPAK_INSTALL="${ALL_FLATPAK_INSTALL} $3"
	fi
}
## Fin test


#send back TRUE/FALSE according the choice defined in $CHK_REP, and the default value given in $1
chkDef() {
	case "$CHK_REP" in
		"$BGN_DEF") echo -n "$1" ;;
		"$BGN_CHECKED") echo -n "TRUE";;
		"$BGN_UNCHECKED") echo -n "FALSE";;
	esac
}

# Clear the Terminal
#clear

#Install tools for the script
which zenity > /dev/null
if [ $? = 1 ]
then
	sudo apt install -y zenity
fi

which notify-send > /dev/null
if [ $? = 1 ]
then
	sudo apt install -y libnotify-bin
fi

which add-apt-repository > /dev/null
if [ $? = 1 ]
then
	sudo apt install -y python-software-properties software-properties-common
fi

which curl > /dev/null
if [ $? = 1 ]
then
	sudo apt install -y curl
fi

#Get Language message
f_get_msg

notify-send  --icon=dialog-error "$NS_WATCH_OUT" "$NS_PWD_ASKED" -t 10000

