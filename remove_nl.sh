#!/bin/bash

data=$(cat $1 | tr -d "\n");
if [[ -f $1 ]]; then
    rm $1
fi

echo $data > $1;
echo "OK."
