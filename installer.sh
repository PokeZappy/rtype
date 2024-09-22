#!/bin/bash

# Télécharger vcpkg
wget -qO vcpkg.tar.gz https://github.com/microsoft/vcpkg/archive/master.tar.gz

sudo mkdir /opt/vcpkg

sudo tar xf vcpkg.tar.gz --strip-components=1 -C /opt/vcpkg

sudo /opt/vcpkg/bootstrap-vcpkg.sh

sudo ln -s /opt/vcpkg/vcpkg /usr/local/bin/vcpkg

vcpkg version

rm -rf vcpkg.tar.gz

echo "Votre chemin vers vcpkg est : '/opt/vcpkg' si ce n'est pas le cas contactez Cyprien."

