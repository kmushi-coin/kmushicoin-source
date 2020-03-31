#!/bin/bash

############--COLORES--############
blanco="\033[1;37m"
magenta="\033[0;35m"
rojo="\033[1;31m"
verde="\033[1;32m"
amarillo="\033[1;33m"
azul="\033[1;34m"
nombre="\033[3;32m"
############--COLORES--############

installLibs14() {
    sudo add-apt-repository -y ppa:bitcoin/bitcoin && sudo apt-get -y update && \
    sudo apt-get -y install autoconf automake autotools-dev build-essential \
    g++ gcc git libboost-all-dev libcrypto++-dev libcurl4-openssl-dev libevent-dev \
    libgmp-dev libgmp3-dev libjansson-dev libminiupnpc-dev libprotobuf-dev libqrencode-dev libqt5core5a \
    libqt5dbus5 libqt5gui5 libssl-dev libssl1.0.0-dbg libtool make miniupnpc pkg-config qrencode qt5-default \
    qt5-qmake qtbase5-dev-tools qttools5-dev qttools5-dev-tools software-properties-common libdb++-dev
}

installLibs16() {
    sudo add-apt-repository -y ppa:bitcoin/bitcoin && sudo apt-get -y update && \
    sudo apt-get -y install autoconf automake autotools-dev build-essential \
    g++ gcc git libboost-all-dev libcrypto++-dev libcurl4-openssl-dev libevent-dev \
    libgmp-dev libgmp3-dev libjansson-dev libminiupnpc-dev libprotobuf-dev libqrencode-dev libqt5core5a \
    libqt5dbus5 libqt5gui5 libssl-dev libssl1.0.0-dbg libtool make miniupnpc pkg-config qrencode qt5-default \
    qt5-qmake qtbase5-dev-tools qttools5-dev qttools5-dev-tools software-properties-common libdb4.8-dev
}

installLibs18() {
     
    sudo add-apt-repository -y ppa:bitcoin/bitcoin && sudo apt-get -y update && \
    sudo apt-get -y install build-essential git libboost-all-dev libboost-filesystem-dev \
    libboost-program-options-dev libboost-thread-dev libcrypto++-dev \
    libdb4.8++-dev libdb4.8-dev libevent-dev libgmp3-dev libminiupnpc-dev libprotobuf-dev \
    libqrencode-dev libqt5core5a libqt5dbus5 libqt5gui5 libssl1.0-dev protobuf-compiler \
    qt5-default qttools5-dev qttools5-dev-tools 
}

installLibs19() {
    sudo apt-get -y update && \
    sudo apt-get -y install build-essential git libboost-all-dev libboost-filesystem-dev \
    libboost-program-options-dev libboost-thread-dev libcrypto++-dev \
    libdb4.8++-dev libdb4.8-dev libevent-dev libgmp3-dev libminiupnpc-dev libprotobuf-dev \
    libqrencode-dev libqt5core5a libqt5dbus5 libqt5gui5 libssl1.0-dev protobuf-compiler \
    qt5-default qttools5-dev qttools5-dev-tools 
}

instalar_programas() {
    echo $blanco" "
    . /etc/os-release
    case "$ID-$VERSION_ID" in
        ubuntu-14.04 ) installLibs14 ;;
        ubuntu-16.04 ) installLibs16 ;;
        ubuntu-18.04 ) installLibs18 ;;
        ubuntu-19.10 ) installLibs19 ;;
        * ) echo "No se reconoce el sistema operativo"; exit 1;;
    esac
}

clonar_github() {
echo $amarillo"Clonando repositorio"
echo $blanco""
sleep 1
rm -R kmushicoin-source
git clone https://github.com/kmushi-coin/kmushicoin-source
sleep 1
echo $blanco""
echo $amarillo"Repositorio Clonado"
sleep 1
echo $blanco""
}

compilar_qt(){
clonar_github
echo $amarillo"Entrando en el repositorio"
cd kmushicoin-source
sleep 1
echo $amarillo"Ejecutando comando "$verde"qmake"
echo $blanco""
qmake USE_UPNP=1 RELEASE=1
sleep 1
echo $amarillo"Ejecutando comando "$verde"make"
echo $blanco""
make -j$(nproc)
sleep 1
echo $amarillo"Se ha compilado la wallet QT"
sleep 1
}

compilar_make(){
clonar_github
echo $amarillo"Entrando en el repositorio"
cd kmushicoin-source/src
sleep 1
echo $amarillo"Ejecutando comando "$verde"make"
echo $blanco""
make -j$(nproc) -f makefile.unix RELEASE=1 STATIC=1
sleep 1
echo $amarillo"Se ha compilado la wallet DAEMON"
sleep 1
}

compilar_qt_daemon(){
clonar_github
echo $amarillo"Entrando en el repositorio"
cd kmushicoin-source
sleep 1
echo $amarillo"Ejecutando comando "$verde"qmake"
echo $blanco""
qmake USE_UPNP=1 RELEASE=1
sleep 1
echo $amarillo"Ejecutando comando "$verde"make"
echo $blanco""
make -j$(nproc)
sleep 1
echo $amarillo"Se ha compilado la wallet QT"
sleep 1
echo $amarillo"Entrando en el repositorio /src"
cd src
sleep 1
echo $amarillo"Ejecutando comando "$verde"make"
echo $blanco""
make -j$(nproc) -f makefile.unix RELEASE=1 STATIC=1
sleep 1
echo $amarillo"Se ha compilado la wallet DAEMON"
sleep 1
}


echo -e $blanco"Programa creado para compilar "$verde"billetera qt"$blanco" y "$verde"demonio (daemon) "$blanco"de "$amarillo"Kmushicoin"
sleep 2
echo -e $rojo"Version: "$verde"1.9"
echo -e $rojo"Creado por "$amarillo"CarmeloCampos"
echo ""
echo ""

START(){

echo -e $azul "Opciones:"
echo -e $magenta "Compilar QT: "$verde"1"
echo -e $magenta "Compilar DAEMON: "$verde"2"
echo -e $magenta "Compilar QT & DAEMON: "$verde"3"
echo -e $blanco "Instalar dependencias: "$verde"4"
echo ""
echo -e $rojo "Salir: "$verde"5"

read -p "Elejir opcion: " opcion
if [ "$opcion" = "1" ]; then
echo ""
echo -e $amarillo"Compilando QT"
compilar_qt
START
elif [ "$opcion" = "2" ]; then
echo ""
echo -e $amarillo"Compilando DAEMON"
compilar_make
START
elif [ "$opcion" = "3" ]; then
echo ""
echo -e $blanco"Compilando QT && DAEMON"
compilar_qt_daemon
START
elif [ "$opcion" = "4" ]; then
echo ""
echo -e $verde"Actualizando e instalando dependencias"
instalar_programas
elif [ "$opcion" = "5" ]; then
echo "Adios"
exit
else
echo "Elija opcion correcta"
fi
START
}
ANTE_START(){
if [ "$(whoami)" == "root" ] ; then
START
else
echo -e $rojo"No has iniciado como root"
fi
}
ANTE_START
