#!/usr/bin/perl

use strict;

my $print_debug = 0;

my $line;

# save input data, just for review
open F, ">input_data.txt";

my $known_sw_reports = <>;
print F $known_sw_reports;
chomp $known_sw_reports;

my $unknown_sw_reports = <>;
print F $unknown_sw_reports;
chomp $unknown_sw_reports;

my $system_calls = <>;
print F $system_calls;
chomp $system_calls;

my $i;

my @reports = ();

for ($i = 0; $i < $known_sw_reports; $i++)
{
  $line = <>;
  print F $line;
  chomp $line;

  $line =~ /^\s*(.)\s+(.*)/;

  my $sm = $1;
  my $v = $2;
  my $safe = ($sm eq "S") ? 1 : 0;
  my @data = split(/\s+/, $v);

  push(@reports, {'safe' => $safe, 'data' => \@data});
}

my @unk_reports = ();

for ($i = 0; $i < $unknown_sw_reports; $i++)
{
  $line = <>;
  print F $line;
  chomp $line;
  my @data = split(/\s+/, $line);

  # by now, we assume not safe, but that doesn't matter...
  push(@unk_reports, {'safe' => 0, 'data' => \@data});
}

close F;

my $report;

# for each system call, we calculate the maximun calls of safe programs and
# the minimum and avegare of malware programs. If a the min or avg of malware
# is > than the max of safe, that system call is suspicious. If a program
# does more than X of those system calls, it gets suspicious points. X is a 
# value in between the min or avg of malware and the max of safe program.
# If a program gets more than a threshold of suspicious points, it is malware.

my @max_safe = (0) x $system_calls;
my @min_malware = (-1) x $system_calls;
my @avg_malware = (0) x $system_calls;
my @suspicious_calls_thres = (0) x $system_calls;
my @suspicious_points = (0) x $system_calls;
my $max_susp_points = 0;
my $malware_reported = 0;

for ($i = 0; $i < $system_calls; $i++)
{
  $malware_reported = 0;
  foreach $report (@reports)
  {
    if ($report->{'safe'})
    {
      if ($report->{'data'}[$i] > $max_safe[$i])
      {
        $max_safe[$i] = $report->{'data'}[$i];
      }
    }
    else
    {
      $malware_reported++;
      $avg_malware[$i] += $report->{'data'}[$i];
      if (($report->{'data'}[$i] < $min_malware[$i]) || ($min_malware[$i] == -1))
      {
        $min_malware[$i] = $report->{'data'}[$i];
      }
    }
  }
  if ($malware_reported > 0)
  {
    $avg_malware[$i] /= $malware_reported;

    if ($min_malware[$i] >= $max_safe[$i])
    {
      $suspicious_calls_thres[$i] = ($min_malware[$i] + $max_safe[$i]) / 2;
      $suspicious_points[$i] = 2;
      $max_susp_points += 2;
    }
    elsif ($avg_malware[$i] >= $max_safe[$i])
    {
      $suspicious_calls_thres[$i] = ($avg_malware[$i] + $max_safe[$i]) / 2;
      $suspicious_points[$i] = 1;
      $max_susp_points += 1;
    }
  }
}

if ($print_debug)
{
  print STDERR "max_susp_points $max_susp_points\n";
  print STDERR "suspicious_points ";
  print_data(\@suspicious_points);
  print STDERR "\n";
  print STDERR "susp_calls_thres ";
  print_data(\@suspicious_calls_thres);
  print STDERR "\n";
}

foreach $report (@reports)
{
  my $points = 0;
  for ($i = 0; $i < $system_calls; $i++)
  {
    if ($report->{'data'}[$i] >= $suspicious_calls_thres[$i])
    {
      $points += $suspicious_points[$i];
    }
  }

  if ($print_debug)
  {
    print STDERR ($report->{'safe'} ? "S" : "M"), " $points ";
    print_data($report->{'data'});
    print STDERR "\n";
  }
}

my $total = 0;
# scan unknown reports
foreach $report (@unk_reports)
{
  # scan this report. is it safe or not?
  my $points = 0;
  my $possible_sum = 0;
  for ($i = 0; $i < $system_calls; $i++)
  {
    $possible_sum += $report->{'data'}[$i];
    if ($report->{'data'}[$i] >= $suspicious_calls_thres[$i])
    {
      $points += $suspicious_points[$i];
    }
  }

  if ($points > 1) # this is how sensitive is the algorithm... i think this threshold should be ok
  {
    $total += $possible_sum;
  }

  if ($print_debug)
  {
    print STDERR "X $points ";
    print_data($report->{'data'});
    print STDERR "\n";
  }
}



print "$total\n";

# only for debug
sub print_data ($)
{
  my $d = $_[0];
  my $n = scalar @$d;
  my $i;

  print STDERR "[";
  for ($i = 0; $i < $n; $i++)
  {
    if ($i != 0)
    {
      print STDERR ", ";
    }
    print STDERR $d->[$i];
  }
  print STDERR "]";
}
