#!/bin/sh

# Try to pull the git revision
COMMIT=`git rev-parse --verify --short HEAD`
REV_STR="\"UNKNOWN\""

if [ "$COMMIT" != "" ]; then
  echo "rev-parse success: $COMMIT"
  REV_STR="\"$COMMIT\""
fi

# Build version.h
cat version.h.in > version.h
echo "#define QHAMLOG_APP_REV  $REV_STR" >> version.h
