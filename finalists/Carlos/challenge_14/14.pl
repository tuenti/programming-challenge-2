#!/usr/bin/perl

use strict;

my $line;

# save input data, just for review
open F, ">input_data.txt";

while ( ($line = <>) )
{
  print F $line;
  chomp $line;

  my $i;
  my $w = 7;
  my $msg = '';
  my $error = 0;
  for ($i = 0; $i < length($line); $i += $w)
  {
    $msg .= removeHamming(correctHamming(substr($line, $i, $w), \$error));
  }

  my @letters;
  if (!$error and toText($msg, \@letters))
  {
    print join('', @letters), "\n";
  }
  else
  {
    #print "Error: \"", join('', @letters), "\"\n";
    print "Error!\n";
  }
}

close F;

sub toText ($$)
{
  my $msg = $_[0];
  my $ret = $_[1];
  my @msg = split(//, $msg);
  my $n = 7;
  my $c;
  my $acc = 0;
  my $error = 0;

  @$ret = ();

  foreach $c (@msg)
  {
    $acc |= $c << $n;
    $n--;
    if ($n < 0)
    {
      push(@$ret, chr($acc));
      if (($acc < 32) || ($acc > 127))
      {
        $error = 1;
      }
      $n = 7;
      $acc = 0;
    }
  }

  if (($n == 7) && !$error)
  {
    return 1;
  }
  else
  {
    push(@$ret, chr($acc));
    return 0;
  }
}

sub is_power_of_2 ($)
{
  my $n = $_[0];

  return ($n & ($n - 1)) == 0;
}

sub addHamming ($)
{
  my $msg = $_[0];
  my @msg = split(//, $msg);
  my $n = scalar @msg;
  my @ret = ();
  my $i;
  my $r;
  my $p;
  my $k;
  my $parity_pos;

  push(@ret, ''); # use indexes from 1 to $n;

  $r = 0;
  $i = 0;
  while ($i < $n)
  {
    $r++;
    # parity bits are located at power-of-2 addresses
    if (is_power_of_2($r))
    {
      push(@ret, 0);
    }
    else
    {
      push(@ret, $msg[$i++]);
    }
  }

  # calculate correct parity bits
  for ($k = 0; 2 ** $k <= $r; $k++)
  {
    $parity_pos = 2 ** $k;
    $p = 0;
    for ($i = $parity_pos + 1; $i <= $r; $i++)
    {
      if (($i & $parity_pos) != 0)
      {
        $p ^= $ret[$i];
      }
    }
    $ret[$parity_pos] = $p;
  }

  shift(@ret);

  return join('', @ret);
}

sub removeHamming ($)
{
  my $msg = $_[0];
  my @msg = split(//, $msg);
  my $n = scalar @msg;
  my @ret = ();
  my $i;
  for ($i = 0; $i < $n; $i++)
  {
    # remove parity bits
    if (!is_power_of_2($i + 1))
    {
      push(@ret, $msg[$i]);
    }
  }
  return join ('', @ret);
}

sub correctHamming ($$)
{
  my $msg = $_[0];
  my $error = $_[1];
  my @msg = split(//, $msg);
  my $n = scalar @msg;
  my $k;
  my $syndrome = 0;
  my $parity_pos;
  my $p;
  my $i;

  unshift(@msg, ''); # use indexes from 1 to $n

  # for all parity bits
  for ($k = 0; 2 ** $k <= $n; $k++)
  {
    $parity_pos = 2 ** $k;
    $p = int($msg[$parity_pos]);
    for ($i = $parity_pos + 1; $i <= $n; $i++)
    {
      if (($i & $parity_pos) != 0)
      {
        $p ^= $msg[$i];
      }
    }
    $syndrome |= $p << $k;
  }

  if ($syndrome != 0)
  {
    # if error, correct it
    if ($syndrome <= $n)
    {
      $msg[$syndrome] ^= 1;
    }
    else
    {
      $$error = 1;
      #print STDERR "####### More than one bit-error. Can't correct! #######\n";
    }
  }

  shift(@msg);

  return join ('', @msg);
}
