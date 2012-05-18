#!/usr/bin/perl -w

my $first_value = <>;

my $min_value = $first_value;
my $max_value = $first_value;

my $min_time = 0;
my $gain = 0;
my $buy_time = 0;
my $sell_time = 0;

my $i = 1;

while(<>) {
    next if (m/^\s*$/);

    if ($_ < $min_value) {
        $min_value = $_;
        $min_time = $i * 100;
        $max_value = $min_value;
    }
    elsif ($_ > $max_value) {
        $max_value = $_;
        $difference = $max_value - $min_value;
        if ($difference > $gain) {
            $gain = $difference;
            $buy_time = $min_time;
            $sell_time = $i * 100;
        }
    }

    $i++;
}

print "$buy_time $sell_time $gain\n";

