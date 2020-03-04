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
 echo "Enter radius of a circle"
 read radius
 area_circle=`expr "$pi * ($radius * $radius)" | bc`
 area=`expr $height \* $width`
 echo "The area of the rectangle is $area"
 echo "The area of the circle is $area_circle"
 echo "Would you like to repeat for areas of shapes [Yes/No]?"
 read response
done