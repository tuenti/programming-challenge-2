#!/usr/bin/perl 

@keys=(
    #in PNG comment, as obtained by pngmeta
    #  pngmeta: PNG metadata for CANTTF.png:
    #  Comment: a541714a17804ac281e6ddda5b707952
    #  Modification Time: 9 Apr 2012 15:31:33 +0000
    "a541714a17804ac281e6ddda5b707952",

    #from QR code (rotated and inverted with GIMP, saved as qr.png and decoded via http://zxing.org/w/decode.jspx)
    "ed8ce15da9b7b5e2ee70634cc235e363",   

    #lsb from first row of PNG (see pngdecoder.pl)
    "62cd275989e78ee56a81f0265a87562e"
);

#for SAMPLE
#@keys=("a182","1357","23f1");


while(<>) {
    chop;
    $keys[3]=$_;

    $output="";
    foreach $pos (0..(length($_)-1)) {
	$out_char=0;
	foreach $num_key (0..3) {
	    $c = hex(substr($keys[$num_key],$pos,1));
	    $out_char+=$c;
	}
	$output .= sprintf "%1x",($out_char % 16);
    }
    print "$output\n";
}
