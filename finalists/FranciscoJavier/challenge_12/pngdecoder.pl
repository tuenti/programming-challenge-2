#!/usr/bin/perl
use Image::PNG;

my $png = Image::PNG->new();
$png->read("CANTTF.png");

printf "Your PNG is %d x %d\n", $png->width, $png->height;

printf "Rowbytes: %d\n", $png->rowbytes;

$rows=$png->rows;

#print "ROW 0: $rows->[0]\n";
for($i=0;$i<$png->rowbytes;$i++) {
    $lsb=ord(substr($rows->[0],$i,1)) & 1;
#    printf "%1x",$lsb;

    $byte=($byte<<1)+$lsb;
    if(++$num_bits ==8) {
	printf "%c",$byte;
	$byte=0;
	$num_bits=0;
    }
}
print "\n";
