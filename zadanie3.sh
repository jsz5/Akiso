#!/bin/bash

cat=$(curl -s https://api.thecatapi.com/v1/images/search?size=full)
cat_url=$(echo ${cat} |jq -r '.[].url')
wget $cat_url -O  image
img2txt image
chuck=$(curl -s http://api.icndb.com/jokes/random/)
echo
echo ${chuck} |jq '.value.joke'
