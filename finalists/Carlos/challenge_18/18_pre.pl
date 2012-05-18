#!/usr/bin/perl

use strict;

# SOP is Ook!, which in turn it is Brainfuck

my $line;
my $program = "";
while ( ($line = <>) )
{
  chomp $line;
  $program .= $line;
}
my $i;
# the file has already been processed and all the Bee and whitespace is removed
for ($i = 0; $i < length $program; $i += 2)
{
  my $instr = substr $program, $i, 2;

  if ($instr eq ".?") # brainfuc >
  {
    print '$stack_ptr++;', "\n";
  }
  elsif ($instr eq "?.") # brainfuck <
  {
    print '$stack_ptr--;', "\n";
  }
  elsif ($instr eq "..") # brainfuck +
  {
    print '$stack[$stack_ptr]++;', "\n";
  }
  elsif ($instr eq "!!") # brainfuck -
  {
    print '$stack[$stack_ptr]--;', "\n";
  }
  elsif ($instr eq "!.") # brainfuck .
  {
    print 'print chr $stack[$stack_ptr];', "\n";
  }
  elsif ($instr eq ".!") # brainfuck ,
  {
    print '$stack[$stack_ptr] = next_char();', "\n";
  }
  elsif ($instr eq "!?") # brainfuck [
  {
    print 'while ($stack[$stack_ptr]) {', "\n";
  }
  elsif ($instr eq "?!") # brainfuck ]
  {
    print '}', "\n";
  }
  else
  {
    print '# error: unknown code: ', $instr, "\n";
  }
}
