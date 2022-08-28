#!/usr/bin/env bash

#
# Requirements:
#
# Install the packaging tools and add your account to the mock group:
#
# dnf install fedora-packager fedora-review clang
# usermod -a -G mock yourusername
#
# (Log out and back in again for the changes to take effect)
# Verify you're a member of the mock group with one of these commands:
#
# groups
# id

name=datadiff
dir=dist/${name}

cd src
mkdir -p obj
make
cd ..

if [ $(uname -o) == 'GNU/Linux' ]; then
  echo "Building on GNU/Linux"

  mkdir -p ${dir}
  cp ${name}.spec ${dir}/.
  cp ${name} ${dir}/.
  cd ${dir} && fedpkg --release f36 local
  echo "Done"
fi
