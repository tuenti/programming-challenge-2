#!/usr/bin/perl

#usamos nuestro crackeador para romper la clave del challenge19 de TUENTI1 suponiendo que conocemos los ultimos 4 chars de la clave

$ciphertext8_hex = "4939f027ea845864";
$plaintext4_hex="daf6f0be";
$padding4_hex="74690000";   #"ti\0\0"

$key=`./breakkey $ciphertext8_hex $plaintext4_hex $padding4_hex`;

print "KEY FOUND: \"$key\" \n" if $key ne "";
