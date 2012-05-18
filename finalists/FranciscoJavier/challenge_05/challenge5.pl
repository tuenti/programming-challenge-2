#!/usr/bin/perl
use Time::Local;

$path=$0;
$path =~ s/challenge5.pl$//;

while(<>) {
    ($time1,$time2) = split / - /;
    $seconds = getseconds($time2)-getseconds($time1);

    $leds1 = `echo $seconds | $path/tc1-challenge6.pl`;
    $leds2 = `echo $seconds | $path/tc1-challenge13.pl`;
    $efficiency = $leds1-$leds2;

    print "$efficiency\n";
}


sub getseconds() {
    my $time=shift;
    ($year,$mon,$day,$hour,$min,$sec) = 
        $time =~ /(\d+)-(\d+)-(\d+) (\d+):(\d+):(\d+)/;
    timegm($sec, $min, $hour, $day, $mon - 1, $year - 1900);
}
