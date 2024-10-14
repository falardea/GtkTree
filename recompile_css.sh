#!/bin/bash

THIS_FILENAME=$(basename "$0")
ARG=$1

echo "running $THIS_FILENAME $ARG $2"

sassc -t expanded ./resources/style/scss/gtk_tree_style.scss ./resources/style/gtk_tree_style.css
