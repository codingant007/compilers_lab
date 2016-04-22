#! /usr/bin/sh

NOTROOT=1
UNKNOWNFILE=2
OVERWRITE=3
UNZIPPROBLEM=4
MVERROR=5
DELERROR=6
YUMERROR=7

USER=$USERNAME
STARTUSER=`whoami`

QURL="http://sourceforge.net/projects/spimsimulator/files/qtspim_9.1.9_linux64.deb/download"
QFILETYPE="application/x-debian-package"
QZIPNAME="qtspimzip"
TARGETFILE="data.tar.gz"
FINALFILE="usr"
TEMPDIRNAME=".qttemp"

WGETOPTS="--output-document $QZIPNAME"
FILEOPTS="-b --mime-type"
AROPTS="-vx $QZIPNAME $TARGETFILE"
TAROPTS="--overwrite -xzvf"
MVOPTS="-vf"
RMOPTS="-rf"
READOPTS="-n 1"
MIMETYPE="application/x-debian-package"

USAGE="Usage:\n$0 [install, remove, download]\n\t-all other arguments will be ignored\
\n\t-can be used to fix a broken installation; just install\n\t-install:\n\t\t\
-must be run as root\n\t\t-a complete installation and cleanup\n\t-remove:\n\t\t\
-if invoked as root will completely un-do everything\n\t\t-otherwise, will just remove\
 downloaded packages if they exist\n\t-download:\n\t\t-use this option if you \
don't have root privelages\n\t\t-will only download and extract the package\n"

# ensure that this script is started as root user
if [ "$STARTUSER" == "root" ]
then
    echo "$0 script started as root user."
fi

# to install or download QtSpim
if [[ "$1" == "install" || "$1" == "download" ]]
then

    # won't do anything if user tried installing without root
    if [[ "$STARTUSER" != "root" && "$1" == "install" ]]
    then
        echo "$0 script must be started as root user to install QtSpim."
        printf "$USAGE"
        exit $NOTROOT
    fi

    echo "Hit ctrl-C at anytime to cancel."
    echo "Downloading and extracting necessary files..."    

    # download the QtSpim zip file if it already exists will overwrite
    sudo -u $USER wget $WGETOPTS $QURL
    if [[ $? != 0 ]]
    then
        echo 'There was a problem downloading the required package.'
        exit $EXIT
    fi
    
    # ensure that file just downloaded is a debian package
    FILETYPE=`file $FILEOPTS $QZIPNAME`
    if [[ $FILETYPE != $MIMETYPE ]]
    then
        cd ..
        rm $RMOPTS $TEMPDIRNAME
        echo "Downloaded an unknown file - it has already been deleted."
        exit $UNKNOWNFILE
    fi
    
    # now extract the required files from the downloaded package to a file
    # named usr
    sudo -u $USER ar $AROPTS
    if [ $? -ne 0 ]
    then
        echo 'There was a problem de-archiving the downloaded package.'
        exit $UNZIPPROBLEM
    fi
    
    sudo -u $USER tar $TAROPTS $TARGETFILE
    if [ $? -ne 0 ]
    then
        echo 'There was a problem unzipping the downloaded package.'
        exit $UNZIPPROBLEM
    fi
    
    file $FILEOPTS $FINALFILE
    if [[ $? != 0 ]]
    then
        echo 'There was a problem unzipping the downloaded package.'
        exit $UNZIPPROBLEM
    fi

    echo "Download and extraction complete."

    # finally, move all of the correct files to the correct places on the system
    # only if this script was called as root user
    # ok to overwrite since all of the files that we are moving have the str
    # 'qtspim' somewhere in them it's safe to assume that we aren't overwriting
    # important system files    

    if [[ "$STARTUSER" == "root" && "$1" == "install" ]]
    then

        echo
        echo "Installing QtSpim onto your system, this won't take long..."

        # ensure that proper shared libraries are installed - if they already exist no reason to reinstall
        rpm -qa | grep qt-x11 > /dev/null
        if [ $? -ne 0 ]
        then
            yum install -y qt-x11
            if [ $? -ne 0 ]
            then
                echo "Was unable to install the dependency package: qt-x11 from the repositories."
                exit $YUMERROR
            fi
        fi

        # start with the binary
        mv $MVOPTS ./usr/bin/qtspim /usr/bin/
        chown root /usr/bin/qtspim
        chgrp root /usr/bin/qtspim
        if [ $? -ne 0 ]
        then
            WD=`pwd`
            echo "Error moving file $WD/usr/bin/qtspim to /usr/bin/"
            exit $MVERROR
        fi
        
        # next, the .desktop file
        mv $MVOPTS ./usr/share/applications/qtspim.desktop /usr/share/applications/
        chown root /usr/share/applications/qtspim.desktop
        chgrp root /usr/share/applications/qtspim.desktop
        if [ $? -ne 0 ]
        then
            WD=`pwd`
            echo "Error moving file $WD/usr/share/applications/qtspim.desktop to /usr/share/applications/"
            exit $MVERROR
        fi
        
        # next, the docs
        rm $RMOPTS /usr/share/doc/qtspim
        mv $MVOPTS ./usr/share/doc/qtspim /usr/share/doc/
        chown root /usr/share/doc/qtspim
        chgrp root /usr/share/doc/qtspim
        if [ $? -ne 0 ]
        then
            WD=`pwd`
            echo "Error moving file $WD/usr/share/doc/qtspim to /usr/share/doc/"
            exit $MVERROR
        fi
        
        mv $MVOPTS './usr/share/man/man1/qtspim.1.gz' '/usr/share/man/man1/'
        chown root /usr/share/man/man1/qtspim.1.gz
        chgrp root /usr/share/man/man1/qtspim.1.gz
        if [ $? -ne 0 ]
        then
            WD=`pwd`
            echo "Error moving file $WD/usr/share/man/man1/qtspim.1.gz to /usr/share/man/man1/"
            exit $MVERROR
        fi

        rm $RMOPTS /usr/share/qtspim
        mv $MVOPTS ./usr/share/qtspim /usr/share/
        chown root /usr/share/qtspim
        chgrp root /usr/share/qtspim
        if [ $? -ne 0 ]
        then
            WD=`pwd`
            echo "Error moving file $WD/usr/share/qtspim to /usr/share/"
            exit $MVERROR
        fi
        
        # clean up after ourselves
        rm $RMOPTS $FINALFILE
        rm $RMOPTS $QZIPNAME
        rm $RMOPTS $TARGETFILE

        # use restorecon to ensure file context labels are proper so that SELinux
        # doesn't complain later
        echo "Checking the file context for the installed files for SELinux's benefit."
        restorecon -R -v /usr/bin/qtspim
        restorecon -R -v /usr/share/applications/qtspim.desktop
        restorecon -R -v /usr/share/doc/qtspim
        restorecon -R -v /usr/share/man/man1/qtspim.1.gz
        restorecon -R -v /usr/share/qtspim

        echo 'QtSpim was successfully installed onto your system!'
        printf "  Tip: For it to show up in your applications launcher try:\n\t\
-hit <ALT-F2>\n\t-type r and hit <ENTER>\n\t\tOR\n\t-logout and log back in\n    \
or type \"qtspim\" and hit <ENTER>\n"

    fi

    # success!!
    exit 0



# to remove QtSpim
elif [ "$1" == "remove" ]
then
    
    # first make sure that the user really, really wants to erase shit
    echo "Are you sure that you would like to permanently erase any trace of \
QtSpim from your system?"
    read $READOPTS USERIN
    echo
    if [[ "$USERIN" != "y" && "$USERIN" != "Y" ]]
    then
        echo 'No changes have been made to your system.'
        exit 0
    fi

    echo "Removing the downloaded files."

    # second, get rid of the stuff that was downloaded since it may still be there
    sudo -u $USER rm $RMOPTS ./$QZIPNAME
    if [ $? -ne 0 ]
    then
        echo -n 'Error removing the downloaded file '
        echo $QZIPNAME
        exit $DELERROR
    fi
    sudo -u $USER rm $RMOPTS ./$TARGETFILE
    if [ $? -ne 0 ]
    then
        echo -n 'Error removing the de-archived downloaded file '
        echo $TARGETFILE
        exit $DELERROR
    fi
    sudo -u $USER rm $RMOPTS ./$FINALFILE
    if [ $? -ne 0 ]
    then
        echo -n 'Error removing the de-archived, de-compressed downloaded file '
        echo $FINALFILE
        exit $DELERROR
    fi

    echo "The downloaded files have been removed."

    if [[ "$STARTUSER" == "root" ]]
    then

        echo "Removing QtSpim from your system."

        # next, remove the binary
        rm $RMOPTS /usr/bin/qtspim
        if [ $? -ne 0 ]
        then
            echo 'Error removing the binary from /usr/bin/qtspim'
            exit $DELERROR
        fi
        
        # next, the .desktop file
        rm $RMOPTS /usr/share/applications/qtspim.desktop
        if [ $? -ne 0 ]
        then
            echo 'Error removing file /usr/share/applications/qtspim.desktop'
            exit $DELERROR
        fi
            
        # next, the docs
        rm $RMOPTS /usr/share/doc/qtspim
        if [ $? -ne 0 ]
        then
            echo 'Error removing file /usr/share/doc/qtspim'
            exit $DELERROR
        fi
        
        # next, the man pages
        rm $RMOPTS "/usr/share/man/man1/qtspim.1.gz"
        if [ $? -ne 0 ]
        then
            echo 'Error removing file /usr/share/man/man1/qtspim.1.gz'
            exit $DELERROR
        fi
        
        rm $RMOPTS /usr/share/qtspim
        if [ $? -ne 0 ]
        then
            echo 'Error removing file /usr/share/qtspim'
            exit $DELERROR
        fi

        echo 'All QtSpim files have been successfully removed from your system!'

    fi

    # success!!
    exit 0

# print a usage message if this script was invoked without 'install', 'remove' or 'download'
else
    echo "Unrecognized command."
    printf "$USAGE"
    exit 0
fi


