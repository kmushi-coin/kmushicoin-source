#!/bin/bash

installLibs14_16() {
    sudo add-apt-repository -y ppa:bitcoin/bitcoin && sudo apt-get -y update && sudo apt-get -y upgrade && \
    sudo apt-get -y dist-upgrade && sudo apt-get -y install autoconf automake autotools-dev build-essential \
    g++ gcc git libboost-all-dev libcrypto++-dev libcurl4-openssl-dev libdb++-dev libdb-dev libevent-dev \
    libgmp-dev libgmp3-dev libjansson-dev libminiupnpc-dev libprotobuf-dev libqrencode-dev libqt5core5a \
    libqt5dbus5 libqt5gui5 libssl-dev libssl1.0.0-dbg libtool make miniupnpc pkg-config qrencode qt5-default \
    qt5-qmake qtbase5-dev-tools qttools5-dev qttools5-dev-tools software-properties-common libdb4.8-dev libdb4.8++-dev
}

installLibs18() {
    sudo add-apt-repository -y ppa:bitcoin/bitcoin && sudo apt-get -y update && sudo apt-get -y upgrade && \
    sudo apt-get -y dist-upgrade && sudo apt-get -y install  \
    build-essential libdb-dev libdb++-dev libboost-all-dev git libssl1.0-dev \
    libdb-dev libdb++-dev libboost-all-dev libminiupnpc-dev libevent-dev libcrypto++-dev libgmp3-dev
    sudo apt-get -y install libdb4.8-dev libdb4.8++-dev \
    build-essential libboost-filesystem-dev libboost-program-options-dev libboost-thread-dev libdb-dev libdb++-dev \
    libminiupnpc-dev libssl1.0-dev libboost-all-dev qt5-default libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev \
    qttools5-dev-tools libprotobuf-dev protobuf-compiler libqrencode-dev
}

instalar_programas() {
    . /etc/os-release
    case "$ID-$VERSION_ID" in
        ubuntu-14.04 ) installLibs14_16 ;;
        ubuntu-16.04 ) installLibs14_16 ;;
        ubuntu-18.04 ) installLibs18 ;;
        * ) echo "No se reconoce el sistema operativo"; exit 1;;
    esac
}

############--COLORES--############
blanco="\033[1;37m"
magenta="\033[0;35m"
rojo="\033[1;31m"
verde="\033[1;32m"
amarillo="\033[1;33m"
azul="\033[1;34m"
nombre="\033[3;32m"
############--COLORES--############
echo -e $blanco"Programa creado para compilar "$verde"billetera qt"$blanco" y "$verde"demonio (daemon) "$blanco"de "$amarillo"Kmushicoin"
sleep 2
echo -e $rojo"Version: "$verde"1.7"
echo -e $rojo"Creado por CarmeloCampos"
echo ""
echo ""

START(){

echo -e $azul "Opciones:"
echo -e $magenta "Compilar QT: "$verde"1"
echo -e $magenta "Compilar DAEMON: "$verde"2"
echo -e $blanco "Compilar QT & DAEMON: "$verde"3"
echo -e $blanco "Instalar dependencias: "$verde"4"
echo ""
echo -e $rojo "Salir: "$verde"5"

read -p "Elejir opcion: " opcion
if [ "$opcion" = "1" ]; then
echo ""
echo -e $blanco"Compilando QT"
git clone https://github.com/kmushi-coin/kmushicoin-source
echo ""
echo -e $blanco"Se Clona el repositorio (HECHO)"
cd kmushicoin-source
echo -e $blanco"Se entra al repositorio (HECHO)"
qmake USE_UPNP=1 USE_QRCODE=1 RELEASE=1
echo -e $blanco"Se Crea archivo Makefile (HECHO)"
make -j$(nproc) STATIC=1
echo -e $blanco"Se compila (HECHO)"
START
elif [ "$opcion" = "2" ]; then
echo ""
echo -e $blanco"Compilando DAEMON"
git clone https://github.com/kmushi-coin/kmushicoin-source
cd kmushicoin-source/src
make -j$(nproc) -f makefile.unix RELEASE=1 STATIC=1
START
elif [ "$opcion" = "3" ]; then
echo ""
echo -e $blanco"Compilando QT && DAEMON"
git clone https://github.com/kmushi-coin/kmushicoin-source
cd kmushicoin-source
qmake USE_UPNP=1 USE_QRCODE=1 RELEASE=1
make -j$(nproc) STATIC=1
cd src
make -j$(nproc) -f makefile.unix RELEASE=1 STATIC=1
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
