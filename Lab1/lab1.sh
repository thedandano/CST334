# Name: Ricardo Barbosa 
# Date: 03/05/2020
# Title: Lab 1 - Sampling a Shell Program
# Description: This program requests parameters and calculates 
#              the areas of a rectangle and a circle.

#!/bin/bash
echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$"=$$
user=`whoami`
numusers=`who | wc -l`
pi=3.14
echo "Hi $user! There are $numusers users logged on."
if [ $user = "Bandito" ]
then
 echo "Now you can proceed!"
else
 echo "Check who logged in!"
 exit 1
fi

response="Yes"
while [ $response != "No" ]
do
 echo "Enter height of rectangle: "
 read height
 echo "Enter width of rectangle: "
 read width
 area=`expr $height \* $width`
 echo "The area of the rectangle is $area"
 echo "Would you like to repeat for areas of rectangle [Yes/No]?"
 read response
done

response="Yes"
while [ $response != "No" ]
do
echo "Enter the radius of a circle"
read radius
area_circle=`expr "$pi * ($radius * $radius)" | bc`
area=`expr $height \* $width`
echo "Would you like to repeat another area of a circle?"
read response
done
