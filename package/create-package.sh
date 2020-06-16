#!/bin/bash

VERSION=0.1
VERSION_PACKAGE=0.1-1
ARCHITECTURE=amd64
PACKAGE_NAME=pong_${VERSION_PACKAGE}_${ARCHITECTURE}

ninja -C build &&
cd build &&

mkdir -p ${PACKAGE_NAME}/usr/local/bin &&
mkdir -p ${PACKAGE_NAME}/usr/local/share/pong-${VERSION} &&
mkdir -p ${PACKAGE_NAME}/usr/share/applications &&

cp -r ../package/DEBIAN ${PACKAGE_NAME}/ &&
cp pong ${PACKAGE_NAME}/usr/local/bin/ &&
cp -r ../package/icon.png ${PACKAGE_NAME}/usr/local/share/pong-${VERSION}/ &&
cp -r ../themes ${PACKAGE_NAME}/usr/local/share/pong-${VERSION}/ &&
cp ../package/pong.desktop ${PACKAGE_NAME}/usr/share/applications/ &&

chmod +x ${PACKAGE_NAME}/DEBIAN/postinst &&

fakeroot dpkg-deb --build ${PACKAGE_NAME}