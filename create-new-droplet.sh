#!/usr/bin/env bash

function printHelp {
    echo 'This bash script will create a new droplet. Please input the name for the droplet in PascalCase as a command line argument.'
}

# Check for arguments
if [ $# -eq 0 ]
  then
    printHelp
fi

# Setup Droplet names
dropletName=$1
dropletNameWords=$(echo $dropletName | sed 's/\([A-Z][^A-Z]\)/ \1/g')
upper=$(echo ${dropletNameWords} | tr '[:lower:]' '[:upper:]')
upper="${upper// /_}"
lower=$(echo ${upper} | tr '[:upper:]' '[:lower:]')

# Create copy from template
folder=$(dirname "$0")
headerFile="${folder}/src/droplets/${lower}_droplet.h"
cppFile="${folder}/src/droplets/${lower}_droplet.cpp"
cp ${folder}/src/droplets/template_droplet.cpp ${cppFile}
cp ${folder}/src/droplets/template_droplet.h ${headerFile}

# Replace 
sed -i "s/Template/${dropletName}/g" ${headerFile}
sed -i "s/Template/${dropletName}/g" ${cppFile}
sed -i "s/template/${lower}/g" ${headerFile}
sed -i "s/template/${lower}/g" ${cppFile}
sed -i "s/TEMPLATE/${upper}/g" ${headerFile}
sed -i "s/TEMPLATE/${upper}/g" ${cppFile}
