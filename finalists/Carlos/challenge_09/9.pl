#!/usr/bin/perl

use strict;

sub load_data ($)
{
  my $data = $_[0];
  my $file;

  for ($file = 1; $file <= 800; $file++)
  {
    my $file_name = sprintf("documents_proc/%04d", $file);

    #print STDERR "File $file...\n";

    open F, "<$file_name";

    my $line;
    
    while ( ($line = <F>) )
    {
      $line =~ /([a-z0-9]*)\s(\d+)/;
      $data->{$1}{$file} = $2;
    }

    close F;
  }
}

sub find_word ($$$)
{
  my $word = lc($_[0]);
  my $num = $_[1];
  my $data = $_[2];

  my $ret;

  my $file;
  for ($file = 1; $file <= 800; $file++)
  {
    my $file_name;

    my $num_in_file;

    if (exists $data->{$word}{$file})
    {
      $num_in_file = $data->{$word}{$file};
    }
    else
    {
      $num_in_file = 0;
    }


    if ($num > $num_in_file)
    {
      #print STDERR "not in this file $num - $num_in_file\n";
      $num -= $num_in_file;
    }
    else
    {
      # it is in this file
      #print STDERR "in this file\n";

      $file_name = sprintf("documents/%04d", $file);

      open F, "<$file_name";

      my $line;
      my $line_num = 0;
      my $found = 0;
      my $line_pos;

      while ( ($line = <F>) )
      {
        $line_num++;
        chomp $line;
        $line = lc($line);
        my @words_in_line = split(/\s+/, $line);

        for ($line_pos = 0; $line_pos < scalar @words_in_line; $line_pos++)
        {
          if ($words_in_line[$line_pos] eq $word)
          {
            $num--;
            if ($num == 0)
            {
              $found = 1;
              last;
            }
          }
        }
        if ($found)
        {
          last;
        }
      }
      close F;

      $line_pos++;

      $ret = "$file-$line_num-$line_pos\n";

      last;
    }
  }


  return $ret;
}

my $line;

my %data = ();
load_data(\%data);

open I, ">input_data.txt";

$line = <>;
print I $line;

chomp $line;

my $test_cases = $line;

while ($test_cases-- > 0)
{
  $line = <>;
  print I $line;
  chomp $line;
  $line =~ /(.*)\s+(\d+)/;
  print find_word($1, $2, \%data);
}

close I;

