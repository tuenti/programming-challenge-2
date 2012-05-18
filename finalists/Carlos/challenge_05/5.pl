#!/usr/bin/perl

use strict;

my $line;

sub days_of_month ($$)
{
  my $year = $_[0];
  my $m = $_[1];
  my @days = (0, 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31);
  my $d = $days[$m];
  if ($d == 0)
  {
    if ($year % 4 != 0)
    {
      $d = 28;
    }
    else
    {
      if ($year % 400 == 0)
      {
        $d = 29;
      }
      else
      {
        if ($year % 100 == 0)
        {
          $d = 28;
        }
        else
        {
          $d = 29;
        }
      }
    }
  }
  return $d;
}

my @leds_on_of_digit = (6, 2, 5, 5, 4, 5, 6, 3, 7, 6);
my $leds_on_00_to_60 = 564;
my $leds_on_00_to_24 = 216;
my $leds_on_segs_mins_in_1h = 67680;
my $leds_on_day = 2401920;

my @delta_to_next = (0, 4, 1, 1, 2, 1, 1, 4, 0, 1); # $delta_to_next[x] is the leds on when changing from x to x+1
my $delta_2_to_0 = 2;
my $delta_3_to_0 = 2;
my $delta_5_to_0 = 2;
my $delta_00_to_60 = 100;
my $delta_00_to_24 = 43;
my $delta_of_segs_mins_in_1h = 6100;
my $delta_day = 146443;

# save input data, just for review
open F, ">input_data.txt";

while ( ($line = <>) )
{
  print F $line;
  chomp $line;

  $line =~ /(\d+)-(\d+)-(\d+)\s+(\d+):(\d+):(\d+)\s+-\s+(\d+)-(\d+)-(\d+)\s+(\d+):(\d+):(\d+)/;
  my $year_ini = $1;
  my $month_ini = $2;
  my $day_ini = $3;
  my $hour_ini = $4;
  my $min_ini = $5;
  my $seg_ini = $6;
  my $year_end = $7;
  my $month_end = $8;
  my $day_end = $9;
  my $hour_end = $10;
  my $min_end = $11;
  my $seg_end = $12;

  my $used_leds = 0;
  my $used_deltas = 0;

#  print STDERR "$year_ini-$month_ini-$day_ini $hour_ini:$min_ini:$seg_ini = $year_end-$month_end-$day_end $hour_end:$min_end:$seg_end\n";

  my $is_000000 = ($hour_ini == 0) and ($min_ini == 0) and ($seg_ini == 0);

  if (!$is_000000 and (($year_ini != $year_end) or ($month_ini != $month_end) or ($day_ini != $day_end)))
  {
    # count until next midnight
#    print STDERR "Count midnight\n";
    do
    {
      #while ($seg_ini != 0)
      {
        $used_deltas += $delta_to_next[$seg_ini % 10];
        if ($seg_ini % 10 == 9)
        {
          if ($seg_ini == 59)
          {
            $used_deltas += $delta_5_to_0;
          }
          else
          {
            $used_deltas += $delta_to_next[int($seg_ini / 10)];
          }
        }

        $seg_ini++;
        if ($seg_ini == 60)
        {
          $seg_ini = 0;
          
          $used_deltas += $delta_to_next[$min_ini % 10];
          if ($min_ini % 10 == 9)
          {
            if ($min_ini == 59)
            {
              $used_deltas += $delta_5_to_0;
            }
            else
            {
              $used_deltas += $delta_to_next[int($min_ini / 10)];
            }
          }

          $min_ini++;
          if ($min_ini == 60)
          {
            $min_ini = 0;

            if ($hour_ini == 23)
            {
              $used_deltas += $delta_2_to_0 + $delta_3_to_0;
              $hour_ini = 0;

              $day_ini++;
              if ($day_ini > days_of_month($year_ini, $month_ini))
              {
                $day_ini = 1;
                $month_ini++;
                if ($month_ini > 12)
                {
                  $month_ini = 1;
                  $year_ini++;
                }
              }
            }
            else
            {
              $used_deltas += $delta_to_next[$hour_ini % 10];
              if ($hour_ini % 10 == 9)
              {
                $used_deltas += $delta_to_next[int($hour_ini / 10)];
              }
              $hour_ini++;
            }
          }
        }

        $used_leds += $leds_on_of_digit[$seg_ini % 10];
        $used_leds += $leds_on_of_digit[int($seg_ini / 10)];
        $used_leds += $leds_on_of_digit[$min_ini % 10];
        $used_leds += $leds_on_of_digit[int($min_ini / 10)];
        $used_leds += $leds_on_of_digit[$hour_ini % 10];
        $used_leds += $leds_on_of_digit[int($hour_ini / 10)];
      }
      
      $is_000000 = ($hour_ini == 0) and ($min_ini == 0) and ($seg_ini == 0);
#      print STDERR "$year_ini-$month_ini-$day_ini $hour_ini:$min_ini:$seg_ini = $year_end-$month_end-$day_end $hour_end:$min_end:$seg_end\n";
    } while (!$is_000000);
  }

  $used_leds -= $used_deltas;
  $used_deltas = 0;
#  print STDERR "Advance date\n";
  while (($year_ini != $year_end) or ($month_ini != $month_end) or ($day_ini != $day_end))
  {
#    print STDERR "$year_ini-$month_ini-$day_ini $hour_ini:$min_ini:$seg_ini = $year_end-$month_end-$day_end $hour_end:$min_end:$seg_end\n";
    $used_leds += $leds_on_day - $delta_day;

    $day_ini++;
    if ($day_ini > days_of_month($year_ini, $month_ini))
    {
      $day_ini = 1;
      $month_ini++;
      if ($month_ini > 12)
      {
        $month_ini = 1;
        $year_ini++;
      }
    }
  }

#  print STDERR "$year_ini-$month_ini-$day_ini $hour_ini:$min_ini:$seg_ini = $year_end-$month_end-$day_end $hour_end:$min_end:$seg_end\n";
#  print STDERR "Advance hour\n";
  while ($hour_ini < $hour_end)
  {
#    print STDERR "$year_ini-$month_ini-$day_ini $hour_ini:$min_ini:$seg_ini = $year_end-$month_end-$day_end $hour_end:$min_end:$seg_end\n";
    $used_leds += $leds_on_segs_mins_in_1h;
    $used_leds += 3599 * $leds_on_of_digit[$hour_ini % 10];
    $used_leds += 3599 * $leds_on_of_digit[int($hour_ini / 10)];
    $used_leds += $leds_on_of_digit[($hour_ini + 1) % 10];
    $used_leds += $leds_on_of_digit[int(($hour_ini + 1) / 10)];

    $used_deltas += $delta_of_segs_mins_in_1h;
    $used_deltas += $delta_to_next[$hour_ini % 10];
    if ($hour_ini % 10 == 9)
    {
      $used_deltas += $delta_to_next[int($hour_ini / 10)];
    }
    $hour_ini++;
  }

  $used_leds -= $used_deltas;
  $used_deltas = 0;

#  print STDERR "$year_ini-$month_ini-$day_ini $hour_ini:$min_ini:$seg_ini = $year_end-$month_end-$day_end $hour_end:$min_end:$seg_end\n";
#  print STDERR "Advance min\n";
  while ($min_ini < $min_end)
  {
#    print STDERR "$year_ini-$month_ini-$day_ini $hour_ini:$min_ini:$seg_ini = $year_end-$month_end-$day_end $hour_end:$min_end:$seg_end\n";
    $used_leds += $leds_on_00_to_60;
    $used_leds += 59 * $leds_on_of_digit[$min_ini % 10];
    $used_leds += 59 * $leds_on_of_digit[int($min_ini / 10)];
    $used_leds += $leds_on_of_digit[($min_ini + 1) % 10];
    $used_leds += $leds_on_of_digit[int(($min_ini + 1) / 10)];
    $used_leds += 60 * $leds_on_of_digit[$hour_ini % 10];
    $used_leds += 60 * $leds_on_of_digit[int($hour_ini / 10)];

    $used_deltas += $delta_00_to_60;
    $used_deltas += $delta_to_next[$min_ini % 10];
    if ($min_ini % 10 == 9)
    {
      $used_deltas += $delta_to_next[int($min_ini / 10)];
    }
    $min_ini++;
  }
 
  $used_leds -= $used_deltas;
  $used_deltas = 0;

#  print STDERR "$year_ini-$month_ini-$day_ini $hour_ini:$min_ini:$seg_ini = $year_end-$month_end-$day_end $hour_end:$min_end:$seg_end\n";
#  print STDERR "Advance seg\n";
  while ($seg_ini < $seg_end)
  {
#    print STDERR "$year_ini-$month_ini-$day_ini $hour_ini:$min_ini:$seg_ini = $year_end-$month_end-$day_end $hour_end:$min_end:$seg_end\n";
    $used_leds += $leds_on_of_digit[($seg_ini + 1) % 10];
    $used_leds += $leds_on_of_digit[int(($seg_ini + 1) / 10)];
    $used_leds += $leds_on_of_digit[$min_ini % 10];
    $used_leds += $leds_on_of_digit[int($min_ini / 10)];
    $used_leds += $leds_on_of_digit[$hour_ini % 10];
    $used_leds += $leds_on_of_digit[int($hour_ini / 10)];

    $used_deltas += $delta_to_next[$seg_ini % 10];
    if ($seg_ini % 10 == 9)
    {
      $used_deltas += $delta_to_next[int($seg_ini / 10)];
    }
    $seg_ini++;
  }

#  print STDERR "End\n$year_ini-$month_ini-$day_ini $hour_ini:$min_ini:$seg_ini = $year_end-$month_end-$day_end $hour_end:$min_end:$seg_end\n";
  $used_leds -= $used_deltas;
  $used_deltas = 0;

  print "$used_leds\n";
}


close F;

