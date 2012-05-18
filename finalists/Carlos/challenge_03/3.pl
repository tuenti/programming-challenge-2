#!/usr/bin/perl

use strict;

my $line;

# save input data, just for review
open F, ">input_data.txt";

my @data = ();
my $t = 0;
while ( ($line = <>) )
{
  print F $line;
  chomp $line;
  push(@data, {'val' => $line, 'time' => $t});
  $t += 100;
}

close F;

my $i;
my $j;
my $n;

my $best_deleted_diff = 0;
my $best_deleted_time1;
my $best_deleted_time2;

my @new_data;

# first of all, we do a simplification of the data, deleting repeated values, values in between of a given tendence (all going up or all going down)
# and things like that

my $changes = 1;

while ($changes)
{
  $changes = 0;

  @new_data = ();
  $n = scalar @data;

  $i = 0;
  
  while ($i < $n - 1)
  {
    push(@new_data, $data[$i]);

    if ($data[$i]{'val'} == $data[$i + 1]{'val'})
    {
      $j = $i + 1;
      $changes = 1;
      while (($j < $n - 1) and ($data[$j]{'val'} == $data[$j + 1]{'val'}))
      {
        $j++;
      }
      $i = $j + 1;
    }
    elsif ($data[$i]{'val'} < $data[$i + 1]{'val'})
    {
      $j = $i + 1;
      while (($j < $n - 1) and ($data[$j]{'val'} <= $data[$j + 1]{'val'}))
      {
        $j++;
        $changes = 1;
      }
      $i = $j;
    }
    else
    {
      $j = $i + 1;
      while (($j < $n - 1) and ($data[$j]{'val'} >= $data[$j + 1]{'val'}))
      {
        $j++;
        $changes = 1;
      }
      $i = $j;
    }
  }

  if ($i < $n)
  {
    push(@new_data, $data[$i]);
  }

  @data = @new_data;

  ###################################################################
  #foreach my $q (@data)
  #{
  #  print $q->{'val'} . "\n";
  #}
  #print "\n";
  ###################################################################

  @new_data = ();
  $n = scalar @data;
  $i = 0;
  while ($i < $n - 3)
  {
    push (@new_data, $data[$i]);

    if (($data[$i]{'val'} < $data[$i + 1]{'val'}) and ($data[$i]{'val'} <= $data[$i + 2]{'val'}) and ($data[$i + 1]{'val'} <= $data[$i + 3]{'val'}))
    {
      $changes = 1;
      $i = $i + 3;
    }
    elsif (($data[$i]{'val'} > $data[$i + 1]{'val'}) and ($data[$i]{'val'} >= $data[$i + 2]{'val'}) and ($data[$i + 1]{'val'} >= $data[$i + 3]{'val'}))
    {
      if ($data[$i + 2]{'val'} - $data[$i + 1]{'val'} > $best_deleted_diff)
      {
        $best_deleted_diff = $data[$i + 2]{'val'} - $data[$i + 1]{'val'};
        $best_deleted_time1 = $data[$i + 1]{'time'};
        $best_deleted_time2 = $data[$i + 2]{'time'};
      }
      $changes = 1;
      $i = $i + 3;
    }
    else
    {
      $i++;
    }
  }

  while ($i < $n)
  {
    push (@new_data, $data[$i]);
    $i++;
  }

  @data = @new_data;

  ###################################################################
  #foreach my $q (@data)
  #{
  #  print $q->{'val'} . "\n";
  #}
  #print "\n";
  ###################################################################
}

#print (scalar @data);
#print "\n";
#
#foreach my $q (@data)
#{
#  print $q->{'val'} . "\n";
#}
#print "\n";



my $time1;
my $time2;
my $max_diff;

# calculate all the possible differences and look for the best
$max_diff = $best_deleted_diff;
$time1 = $best_deleted_time1;
$time2 = $best_deleted_time2;
for ($i = 0; $i < $n; $i++)
{
  for ($j = 0; $j <= $i; $j++)
  {
    my $diff = $data[$i]{'val'} - $data[$j]{'val'};
    if ($diff > $max_diff)
    {
      $max_diff = $diff;
      $time1 = $data[$j]{'time'};
      $time2 = $data[$i]{'time'};
    }
  }
}

print "$time1 $time2 $max_diff\n";

