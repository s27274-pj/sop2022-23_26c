#!/usr/bin/env bash
regex="^[A-Za-z0-9\.+-]+@[A-Za-z0-9\.+]+[A-Za-z0-9\.+-]*[^-]+(\..+)*$"
if [[ $1 =~ $regex ]]; then
  echo "To adres email."
fi