#!/usr/bin/perl

use strict;

my $line;

# save input data, just for review
open F, ">input_data.txt";

my $test_cases;

#first line is number of test cases
$test_cases = <>;
print F $test_cases;
chomp $test_cases;

# letter to possition (x, y) and number of taps
my %letter_info = (
  ' ' => [0, 3, 1],
  '1' => [0, 3, 2],
  'a' => [1, 3, 1],
  'b' => [1, 3, 2],
  'c' => [1, 3, 3],
  '2' => [1, 3, 4],
  'd' => [2, 3, 1],
  'e' => [2, 3, 2],
  'f' => [2, 3, 3],
  '3' => [2, 3, 4],
  'g' => [0, 2, 1],
  'h' => [0, 2, 2],
  'i' => [0, 2, 3],
  '4' => [0, 2, 4],
  'j' => [1, 2, 1],
  'k' => [1, 2, 2],
  'l' => [1, 2, 3],
  '5' => [1, 2, 4],
  'm' => [2, 2, 1],
  'n' => [2, 2, 2],
  'o' => [2, 2, 3],
  '6' => [2, 2, 4],
  'p' => [0, 1, 1],
  'q' => [0, 1, 2],
  'r' => [0, 1, 3],
  's' => [0, 1, 4],
  '7' => [0, 1, 5],
  't' => [1, 1, 1],
  'u' => [1, 1, 2],
  'v' => [1, 1, 3],
  '8' => [1, 1, 4],
  'w' => [2, 1, 1],
  'x' => [2, 1, 2],
  'y' => [2, 1, 3],
  'z' => [2, 1, 4],
  '9' => [2, 1, 5],
  '0' => [1, 0, 1]
);

while ($test_cases > 0)
{
  # initial possition of the finger
  my $pos_x = $letter_info{'0'}[0];
  my $pos_y = $letter_info{'0'}[1];

  # next possition
  my $new_x;
  my $new_y;

  # offset to the next
  my $off_x;
  my $off_y;

  # status of upper case
  my $up_case = 0;

  # sms to write, letter by letter
  my @sms;

  my $first_letter = 1;

  my $time;

  $test_cases--;

  $line = <>;

  print F $line;

  chomp $line;

  @sms = split(//, $line);

  $time = 0;
  # write each letter
  foreach my $l (@sms)
  {
    # if we have to change the case (it is a letter and we have the wrong case)
    if ((($l =~ /[a-z]/) and $up_case) or (($l =~ /[A-Z]/) and !$up_case))
    {
      $up_case = !$up_case;

      $new_x = 2;
      $new_y = 0;

      $off_x = abs($new_x - $pos_x);
      $off_y = abs($new_y - $pos_y);

      # move diagonal the maximun possible (ie: the minimum offset)
      if ($off_x < $off_y)
      {
        $off_y -= $off_x;
        $time += 350 * $off_x;

        #then move vertical
        $time += 300 * $off_y;
      }
      else
      {
        $off_x -= $off_y;
        $time += 350 * $off_y;

        #them move horizontal
        $time += 200 * $off_x;
      }

      # then push caps button
      $time += 100;

      # update pos
      $pos_x = $new_x;
      $pos_y = $new_y;
    }

    #move now to the letter

    $new_x = $letter_info{lc($l)}[0];
    $new_y = $letter_info{lc($l)}[1];

    $off_x = abs($new_x - $pos_x);
    $off_y = abs($new_y - $pos_y);

    # if not the first letter and we are repeating button
    if (!$first_letter and ($new_x == $pos_x) and ($new_y == $pos_y))
    {
      $time += 500;
    }
    
    # move diagonal the maximun possible (ie: the minimum offset)
    if ($off_x < $off_y)
    {
      $off_y -= $off_x;
      $time += 350 * $off_x;

      #then move vertical
      $time += 300 * $off_y;
    }
    else
    {
      $off_x -= $off_y;
      $time += 350 * $off_y;

      #them move horizontal
      $time += 200 * $off_x;
    }

    #push button
    $time += 100 * $letter_info{lc($l)}[2];    
    
    # update pos
    $pos_x = $new_x;
    $pos_y = $new_y;
    $first_letter = 0;
  }

  print "$time\n";
}

close F;

