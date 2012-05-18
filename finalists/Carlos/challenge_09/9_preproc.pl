#!/usr/bin/perl

use strict;

my $file;

for ($file = 1; $file <= 800; $file++)
{
  print "file $file...\n";
  my $file_name = sprintf("documents/%04d", $file);
  my $file_name_out = sprintf("documents_proc/%04d", $file);
  open F, "<$file_name";

  my %word_count = ();

  my $line;
  while ( ($line = <F>) )
  {
    chomp $line;

    $line = lc($line);
    my @words = split(/\s+/, $line);

    foreach my $word (@words)
    {
      if (exists $word_count{$word})
      {
        $word_count{$word}++;
      }
      else
      {
        $word_count{$word} = 1;
      }
    }
  }

  close F;

  open F, ">$file_name_out";

  foreach my $word (sort keys %word_count)
  {
    if ($word ne "")
    {
      print F $word . " " . $word_count{$word} . "\n";
    }
  }

  close F;
}


