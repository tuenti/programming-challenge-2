#!/usr/bin/perl



use strict;



my $debug = 0;



sub fromBinary ($)

{

  my @bits = split(//, $_[0]);

  my $len = scalar @bits;

  my $i;

  my $n = $bits[0];

  for ($i = 1; $i < $len; $i++)

  {

    $n <<= 1;

    $n |= $bits[$i];

  }

  return int($n);

}



my %hexToBin = (

  '0' => '0000',

  '1' => '0001',

  '2' => '0010',

  '3' => '0011',

  '4' => '0100',

  '5' => '0101',

  '6' => '0110',

  '7' => '0111',

  '8' => '1000',

  '9' => '1001',

  'a' => '1010',

  'b' => '1011',

  'c' => '1100',

  'd' => '1101',

  'e' => '1110',

  'f' => '1111'

);



sub toBinary ($)

{

  my @hex = split(//, sprintf("%08x", $_[0]));

  my $i;

  my $ret = '';

  for ($i = 0; $i < scalar @hex; $i++)

  {

    $ret .= $hexToBin{$hex[$i]};

  }

  return $ret;

}



my %fromBase64 = (

  'A' => '000000',

  'B' => '000001',

  'C' => '000010',

  'D' => '000011',

  'E' => '000100',

  'F' => '000101',

  'G' => '000110',

  'H' => '000111',

  'I' => '001000',

  'J' => '001001',

  'K' => '001010',

  'L' => '001011',

  'M' => '001100',

  'N' => '001101',

  'O' => '001110',

  'P' => '001111',

  'Q' => '010000',

  'R' => '010001',

  'S' => '010010',

  'T' => '010011',

  'U' => '010100',

  'V' => '010101',

  'W' => '010110',

  'X' => '010111',

  'Y' => '011000',

  'Z' => '011001',

  'a' => '011010',

  'b' => '011011',

  'c' => '011100',

  'd' => '011101',

  'e' => '011110',

  'f' => '011111',

  'g' => '100000',

  'h' => '100001',

  'i' => '100010',

  'j' => '100011',

  'k' => '100100',

  'l' => '100101',

  'm' => '100110',

  'n' => '100111',

  'o' => '101000',

  'p' => '101001',

  'q' => '101010',

  'r' => '101011',

  's' => '101100',

  't' => '101101',

  'u' => '101110',

  'v' => '101111',

  'w' => '110000',

  'x' => '110001',

  'y' => '110010',

  'z' => '110011',

  '0' => '110100',

  '1' => '110101',

  '2' => '110110',

  '3' => '110111',

  '4' => '111000',

  '5' => '111001',

  '6' => '111010',

  '7' => '111011',

  '8' => '111100',

  '9' => '111101',

  '+' => '111110',

  '/' => '111111'

);



my %toBase64 = ();

foreach my $b64 (keys %fromBase64)

{

  $toBase64{$fromBase64{$b64}} = $b64;

}



my %asHex = (

  '00110000' => '0000',

  '00110001' => '0001',

  '00110010' => '0010',

  '00110011' => '0011',

  '00110100' => '0100',

  '00110101' => '0101',

  '00110110' => '0110',

  '00110111' => '0111',

  '00111000' => '1000',

  '00111001' => '1001',

  '01100001' => '1010',

  '01100010' => '1011',

  '01100011' => '1100',

  '01100100' => '1101',

  '01100101' => '1110',

  '01100110' => '1111'

);



my %fromHex = ();



foreach my $ah (keys %asHex)

{

  $fromHex{$asHex{$ah}} = $ah;

}



sub base64Decode ($)

{

  my @letters = split(//, $_[0]);

  my @ret = ();

  my $equals = 0;

  while ($letters[$#letters] eq '=')

  {

    pop(@letters);

    $equals++;

  }

  foreach my $l (@letters)

  {

    push(@ret, $fromBase64{$l});

  }

  if ($equals > 0)

  {

    my $t = pop(@ret);

    $t = substr($t, 0, 6 - 2 * $equals);

    push(@ret, $t);

  }

  return join('', @ret);

}



sub base64Encode ($)

{

  my $data = $_[0];

  my $len = length($data);

  my $i;

  my @ret = ();

  for ($i = 0; $i + 5 < $len; $i += 6)

  {

    push(@ret, $toBase64{substr($data, $i, 6)});

  }

  if ($i < $len)

  {

    if ($debug)

    {

      print STDERR "base64encode: $i < $len; [", substr($data, $i), "] ", substr(substr($data, $i) . '00000', 0, 6), "\n";

    }

    push(@ret, $toBase64{substr(substr($data, $i) . '00000', 0, 6)});

  }

  return join('', @ret);

}



sub asHex ($)

{

  my $data = $_[0];

  my $len = length($data);

  my $i;

  my @ret = ();

  for ($i = 0; $i < $len; $i += 8)

  {

    push(@ret, $asHex{substr($data, $i, 8)});

  }

  return join('', @ret);

}



sub fromHex ($)

{

  my $data = $_[0];

  my $len = length($data);

  my $i;

  my @ret = ();

  for ($i = 0; $i < $len; $i += 4)

  {

    push(@ret, $fromHex{substr($data, $i, 4)});

  }

  return join('', @ret);

}







my $line;



# save input data, just for review

open F, ">input_data.txt";



while ( ($line = <>) )

{

  print F $line;

  chomp $line;



  my $decoded = base64Decode($line);

  my $ashex = asHex($decoded);

  my @numbers_bin = ();

  my @numbers = ();

  my $i;



  if ($debug)

  {

    print STDERR "Line: ", substr($line, 0, 100), "...\n";

    print STDERR "Decoded: ", substr($decoded, 0, 100), "...\n";

    print STDERR "Ashex: ", substr($ashex, 0, 100), "...\n";

    print STDERR "Len axhex: ", length($ashex), "\n";

  }



  for ($i = 0; $i < length($ashex); $i += 32)

  {

    if ($debug)

    {

      if ($i < 16 * 32)

      {

        print STDERR "Number $i: ", sprintf("%08x", fromBinary(substr($ashex, $i, 32))), "\n";

      }

    }

    push(@numbers_bin, substr($ashex, $i, 32));

    push(@numbers, fromBinary(substr($ashex, $i, 32)));

  }



  my @out = ();

  $i = 0;

  push(@out, '1');

  push(@out, $numbers_bin[0]);



  for ($i = 1; $i < scalar @numbers; $i++)

  {

    my $diff = $numbers[$i] - $numbers[$i - 1];

    if ($debug)

    {

      if ($i < 16)

      {

        print STDERR "Diff $i: $diff => ";

      }

    }

    if (($diff < -16) or ($diff > 15))

    {

      if ($debug)

      {

        if ($i < 16)

        {

          print STDERR "1...\n";

        }

      }

      push(@out, '1');

      push(@out, @numbers_bin[$i]);

    }

    else

    {

      if ($debug)

      {

        if ($i < 16)

        {

          print STDERR "[", toBinary($diff), "] 0... ", substr(toBinary($diff), -5), "\n";

        }

      }

      push(@out, '0');

      push(@out, substr(toBinary($diff), -5));

    }

  }



  my $out = join('', @out);

  if ($debug)

  {

    print STDERR "Out:\n$out\n";

  }

  if (length($out) % 4 != 0)

  {

    $out .= '0' x (4 - (length($out) % 4));

    if ($debug)

    {

      print STDERR "Out fixed:\n$out\n";

    }

  }

  my $hexed = fromHex($out);

  if ($debug)

  {

    print STDERR "Hexed:\n$hexed\n";

  }

  my $encoded = base64Encode($hexed);



  if ($debug)

  {

    print STDERR "Encoded:\n$encoded\n";

  }





  print "$encoded\n";



}



close F;





