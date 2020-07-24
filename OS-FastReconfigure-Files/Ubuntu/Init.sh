#!/bin/bash

sudo apt-get update;
sudo apt-get upgrade -y;

sudo apt-get install aptitude net-tools htop gcc g++ gdb lightdm i3-wm terminator i3status rustc cargo \
                     cmake automake htop nodejs npm yarn yasm nasm ghex zsh csh fish nano curl golang \
                     qemu ffmpeg python python3 php7 apache2 php-xdebug gnome-tweaks dconf-editor lua5.3 \
                     nmap docker.io mysql-server openjdk-11-jdk fcitx fcitx-sunpinyin fcitx-mozc fcitx-googlepinyin \
                     git 

sudo apt-get clean

cd ~
git clone https://github.com/pwndbg/pwndbg
cd pwndbg
bash -c "./setup.sh"

cd ~
curl -L https://get.oh-my.fish | fish
fish -c "omf install bobthefish"
fish -c "omf theme bobthefish"
sudo chsh -s /usr/bin/fish
