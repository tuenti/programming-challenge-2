#!/usr/bin/perl

while(<>) {
    chop;
    push @vals,$_;
}

for ($i=@vals-1;$i>=0;$i--) {
    $max=$vals[$i], $imax=$i if $vals[$i]>$max;
    $imax[$i]=$imax;
}

for ($i=0;$i<@vals;$i++) {
    $gain[$i]=$vals[$imax[$i]]-$vals[$i];
}

for ($i=0;$i<@gain;$i++) {
    $maxgain=$gain[$i],$imaxgain=$i if $gain[$i]>$maxgain;
}
print $imaxgain*100," ",$imax[$imaxgain]*100," ",$maxgain,"\n";
