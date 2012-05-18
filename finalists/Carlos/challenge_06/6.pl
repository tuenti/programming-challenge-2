#!/usr/bin/perl

use strict;

my $line;

# save input data, just for review
open F, ">input_data.txt";


my $test_cases = <>;
print F $test_cases;
chomp $test_cases;

my $case;
for ($case = 1; $case <= $test_cases; $case++)
{
  $line = <>;
  print F $line;
  chomp $line;
  
  $line =~ /(\d+)\s+(\d+)\s+(\d+)/;

  my $width = $1;
  my $height = $2;
  my $ct = $3;

  # real W and H in pixels:
  $width *= $ct;
  $height *= $ct;

  $line = <>;
  print F $line;
  chomp $line;

  # remove spaces at the end (we know there are not any at the begining)
  $line =~ s/\s*$//;

  # the message:
  my @words = split(/\s/, $line);
  my $num_words = scalar @words;
  my $num_spaces = $num_words - 1;

  # what we really care about is the length of each word:
  my $i;
  my $max_word_len = 0;
  my $total_chars = 0;
  for ($i = 0; $i < $num_words; $i++)
  {
    $words[$i] = length($words[$i]);
    $total_chars += $words[$i];
    if ($words[$i] > $max_word_len)
    {
      $max_word_len = $words[$i];
    }
  }

  # estimate max font size
  my $max_font_size;

  $max_font_size = int($width / $max_word_len);
  if ($max_font_size > $height)
  {
    $max_font_size = $height;
  }

  if ($max_font_size == 0)
  {
    # impossible to write message
    print "Case #$case: 0\n";
    next; # next test case
  }

  # assure that the maximun teorethical characters we can write is more than the number we have to write
  while (int($height / $max_font_size) * (int($width / $max_font_size) + 1) - 1 < $total_chars + $num_spaces)
  {
    $max_font_size--;
    if ($max_font_size == 0)
    {
      last;
    }
  }

  if ($max_font_size == 0)
  {
    # impossible to write message
    print "Case #$case: 0\n";
    next; # next test case
  }


  # estimate min font size
  my $min_font_size = 1;


  # do a pseudo binary search to find the biggest valid font size
  #
  # $min_font_size and $max_font_size, from now on, will contain values that are NOT valid for the font size we're looking for.

  my $font;
  $min_font_size--;
  $max_font_size++;
  while ($max_font_size - $min_font_size > 3)
  {
    $font = int(($max_font_size + $min_font_size) / 2);

    # try this font size

    my $max_lines = int($height / $font);
    my $max_chars = int($width / $font);
    my $word;
    my $line_num = 0;
    my $chars_used_in_line = 0;
    my $ok;

    # try to place each word
    $ok = 1;
    for ($word = 0; $word < $num_words; $word++)
    {
      if ($chars_used_in_line)
      {
        # if there are already words in this line

        # does it fit in this line?
        if ($chars_used_in_line + 1 + $words[$word] <= $max_chars)
        {
          # yes; place it
          $chars_used_in_line += 1 + $words[$word];
        }
        else
        {
          # no; change line
          $line_num++;
          if ($line_num >= $max_lines)
          {
            # we ran out of space. This font is too big
            $ok = 0;
            last;
          }
          else
          {
            $chars_used_in_line = $words[$word];
          }
        }
      }
      else
      {
        # place this word in the first possition of this line
        $chars_used_in_line = $words[$word];
      }
    }

    if ($ok)
    {
      $min_font_size = $font - 1;
    }
    else
    {
      $max_font_size = $font;
    }
  }

  # here, $max_font_size - $min_font_size is either 3 or 2

  my $found = 0;

  # linear seach
  for ($font = $max_font_size - 1; $font > $min_font_size; $font--)
  {
    # try this font size

    my $max_lines = int($height / $font);
    my $max_chars = int($width / $font);
    my $word;
    my $line_num = 0;
    my $chars_used_in_line = 0;
    my $ok;

    # try to place each word
    $ok = 1;
    for ($word = 0; $word < $num_words; $word++)
    {
      if ($chars_used_in_line)
      {
        # if there are already words in this line

        # does it fit in this line?
        if ($chars_used_in_line + 1 + $words[$word] <= $max_chars)
        {
          # yes; place it
          $chars_used_in_line += 1 + $words[$word];
        }
        else
        {
          # no; change line
          $line_num++;
          if ($line_num >= $max_lines)
          {
            # we ran out of space. This font is too big
            $ok = 0;
            last;
          }
          else
          {
            $chars_used_in_line = $words[$word];
          }
        }
      }
      else
      {
        # place this word in the first possition of this line
        $chars_used_in_line = $words[$word];
      }
    }

    if ($ok)
    {
      $found = 1;
      last;
    }
  }

  if ($found)
  {
    my $stitches = $total_chars * $font * $font / 2;
    my $inches = $stitches / $ct;

    if ($inches != int($inches))
    {
      $inches += 1;
    }

    $inches = int($inches);
    print "Case #$case: $inches\n";
  }
  else
  {
    # impossible to write message
    print "Case #$case: 0\n";
  }
}


close F;

