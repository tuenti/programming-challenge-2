#!/usr/bin/perl

use strict;

my $line;

my %points_of_letter = (
  'A' => 1,
  'E' => 1,
  'I' => 1,
  'L' => 1,
  'N' => 1,
  'O' => 1,
  'R' => 1,
  'S' => 1,
  'T' => 1,
  'U' => 1,
  'D' => 2,
  'G' => 2,
  'B' => 3,
  'C' => 3,
  'M' => 3,
  'P' => 3,
  'F' => 4,
  'H' => 4,
  'V' => 4,
  'W' => 4,
  'Y' => 4,
  'K' => 5,
  'J' => 8,
  'X' => 8,
  'Q' => 10,
  'Z' => 10
);

my %word_points = ();
my @words = ();
my %letters_needed = ();

# load word data
open F, "<descrambler_wordlist.txt"; # the lines are already sorted
while ( ($line = <F>) )
{
  chomp $line;
  my @letters = split(//, $line);
  my $points = 0;
  push(@words, $line);

  $letters_needed{$line} = {};

  # calculate points
  foreach my $letter (@letters)
  {
    $points += $points_of_letter{$letter};
    if (!exists $letters_needed{$line}{$letter})
    {
      $letters_needed{$line}{$letter} = 1;
    }
    else
    {
      $letters_needed{$line}{$letter}++;
    }
  }

  $word_points{$line} = $points;
}
close F;


# sort words from most to less points, and then from A to Z
@words = sort {
  if ($word_points{$a} > $word_points{$b})
  {
    return -1;
  }
  elsif ($word_points{$a} < $word_points{$b})
  {
    return 1;
  }
  else
  {
    return $a cmp $b;
  }
} @words;

#foreach my $w (@words)
#{
#  print $w . " " . $word_points{$w} . "\n";
#}


# save input data, just for review
open F, ">input_data.txt";

my $test_cases = <>;
print F $test_cases;
chomp $test_cases;

while ($test_cases-- > 0)
{
  $line = <>;
  print F $line;
  chomp $line;
  $line =~ /(\S+)\s+(\S+)/;

  my $rack = $1;
  my $board = $2;

  my @rack = split(//, $rack);
  my @board = split(//, $board);

  my $n_rack_letters = scalar @rack;

  my %letters_in_rack = ();
  foreach my $lr (@rack)
  {
    if (!exists $letters_in_rack{$lr})
    {
      $letters_in_rack{$lr} = 1;
    }
    else
    {
      $letters_in_rack{$lr}++;
    }
  }

  my $i;
  my $candidate_word;
  my $ok = 0;
  # look for the best word that fits with the letters we have
  for ($i = 0; $i < scalar @words; $i++)
  {
    $candidate_word = $words[$i];
    if (length($candidate_word) > 1 + $n_rack_letters)
    {
      next;
    }
    if (can_build_word($candidate_word, \@board, \%letters_in_rack, \%letters_needed))
    {
      $ok = 1;
      last;
    }
  }

  if ($ok)
  {
    print "$candidate_word " . $word_points{$candidate_word} . "\n";
  }
  else
  {
    print " 0\n";
  }
}


close F;


sub can_build_word ($$$$)
{
  my $word = $_[0];
  my $board = $_[1];
  my $letters_in_rack = $_[2];
  my $all_words_letters_needed = $_[3];
  my $letters_needed = $all_words_letters_needed->{$word};
  my $ok = 0;

  foreach my $board_letter (@$board)
  {
    $ok = 0;

    if (!exists $letters_needed->{$board_letter})
    {
      # we must use one board letter
      next;
    }
    else
    {
      $letters_needed->{$board_letter}--;

      $ok = 1;
      foreach my $letter (keys %$letters_needed)
      {
        if ((!exists $letters_in_rack->{$letter}) and ($letters_needed->{$letter} > 0))
        {
          $ok = 0;
          last;
        }
        elsif ($letters_needed->{$letter} > $letters_in_rack->{$letter})
        {
          $ok = 0;
          last;
        }
      }

      $letters_needed->{$board_letter}++;

      if ($ok)
      {
        last;
      }
    }
  }

  return $ok;
}

