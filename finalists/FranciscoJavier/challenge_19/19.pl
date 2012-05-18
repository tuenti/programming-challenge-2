#!/usr/bin/perl

#read input and convert from base64
$input = <>;
chop $input;
$input = `echo -n $input | base64 -d`;

#process input
foreach (1..length($input)/8) {
    #read 8 byte hex number
    $numhex = substr($input,$pos,8);
    $pos += 8;

    #calculate delta
    $num = oct("0x$numhex");
    $delta = $num - $prev;

    if ($delta > 15 || $delta <-16) {
	#delta does not fits in 5 signed bits: must do full number encoding 
	$outputbits .= sprintf "1%032b",$num;
    }
    else {
	#delta encoding
	$deltabits = sprintf "%032b",$delta;
	$deltabits = substr($deltabits,32-5,5);
	$outputbits .= sprintf "0$deltabits";
    }
    $prev = $num;
}

#padding
if (length($outputbits) % 8) {
    $outputbits.="0" x (8- length($outputbits) % 8)
}

#encode to hex
$len = length($outputbits);
for ($i=0 ; $i<$len ; $i+=8) {
    $bits = substr($outputbits,$i,8);
    $outputhex .= sprintf("%02x",oct("0b$bits"));
}

#convert to base64 (without whitespace or terminators)
$output = `echo -n $outputhex | base64`;
$output =~ s/\n//g;
$output =~ s/=//g;

#FINALLY PRINT OUTPUT !!!!!!!
print "$output\n";
