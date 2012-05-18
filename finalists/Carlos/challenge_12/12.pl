#!/usr/bin/perl

use strict;

my $line = <>;

my $k1 = "ed8ce15da9b7b5e2ee70634cc235e363"; # From QR code
my $k2 = "a541714a17804ac281e6ddda5b707952"; # tEXt chunk of PNG
my $k3 = "62cd275989e78ee56a81f0265a87562e"; # LSB of first pixels of image

# save input data, just for review
open F, ">input_data.txt";
print F $line;
close F;

chomp $line;

my @a = split(//, $k1);
my @b = split(//, $k2);
my @c = split(//, $k3);
my @d = split(//, $line);
my @e = ();
my $n = scalar @a;
my $i;

for ($i = 0; $i < $n; $i++)
{
  my $sum = (hex($a[$i]) + hex($b[$i]) + hex($c[$i]) + hex($d[$i])) % 16;
  push(@e, sprintf("%x", $sum));
}
print join("", @e) . "\n";

