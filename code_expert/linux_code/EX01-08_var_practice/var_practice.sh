#!/bin/bash

name="linux"
course="expert"

# linux expert
var="$name $course"
echo $var

# $linux \expert
echo "\$$name \\$course"

# $$linux \\expert
echo "\$\$$name \\\\$course"

# experted linux
echo "${course}ed $name"


