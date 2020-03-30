#!/bin/bash

installLibs14_16() {
    sudo env LC_ALL=C.UTF-8 add-apt-repository -y ppa:bitcoin/bitcoin
    sudo apt-get -y update
    sudo apt-get -y install  \
      qt5-default qt5-qmake qtbase5-dev-tools qttools5-dev-tools software-properties-common build-essential \
      libssl-dev libdb++-dev libboost-all-dev libqrencode-dev qrencode libminiupnpc-dev automake autoconf \
      git pkg-config libcurl4-openssl-dev libjansson-dev libgmp-dev make g++ gcc
    sudo apt-get -y install libdb4.8-dev libdb4.8++-dev

}

installLibs18() {
    sudo env LC_ALL=C.UTF-8 add-apt-repository -y ppa:bitcoin/bitcoin
    sudo apt-get -y update
    sudo apt-get -y install  \
      qt5-default qt5-qmake qtbase5-dev-tools qttools5-dev-tools software-properties-common build-essential \
      libssl1.0-dev libdb++-dev libboost-all-dev libqrencode-dev qrencode libminiupnpc-dev automake autoconf \
      git pkg-config libcurl-openssl1.0-dev libjansson-dev libgmp-dev make g++ gcc 
    sudo apt-get -y install libdb4.8-dev libdb4.8++-dev

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
echo -e $rojo"Version: "$verde"1.0"
echo -e $rojo"Creado por CarmeloCampos"
echo ""
echo ""

START(){

echo -e $azul "Opciones:"
echo -e $magenta "Compilar Wallet qt: "$verde"1"
echo -e $magenta "Compilar Wallet daemon: "$verde"2"
echo -e $blanco "Instalar dependencias: "$verde"3"
echo ""
echo -e $rojo "Salir: "$verde"4"

read -p "Elejir opcion: " opcion
if [ "$opcion" = "1" ]; then
echo ""
echo -e $blanco"Compilando wallet qt"
git clone https://github.com/kmushi-coin/kmushicoin-source
echo ""
echo -e $blanco"Se Clona el repositorio (HECHO)"
cd kmushicoin-source
echo -e $blanco"Se entra al repositorio (HECHO)"
qmake USE_UPNP=1 USE_QRCODE=1
echo -e $blanco"Se Crea archivo Makefile (HECHO)"
make -j$(nproc)
echo -e $blanco"Se compila (HECHO)"
START
elif [ "$opcion" = "2" ]; then
echo ""
echo -e $blanco"Compilando wallet daemon"
git clone https://github.com/kmushi-coin/kmushicoin-source
cd kmushicoin-source/src
make -j$(nproc) -f makefile.unix RELEASE=1 STATIC=1
START
elif [ "$opcion" = "3" ]; then
echo ""
echo -e $verde"Actualizando e instalando dependencias"
instalar_programas
elif [ "$opcion" = "4" ]; then
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
