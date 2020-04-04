

############################
# Setup the Geant4 environment
###########################


export G4HOME=$HOME/geant4/share/Geant4-10.6.0/geant4make

source ${G4HOME}/geant4make.sh

export G4WORKDIR=`pwd`


#
# set the VRML viewer
export G4VRMLFILE_VIEWER=freewrl

