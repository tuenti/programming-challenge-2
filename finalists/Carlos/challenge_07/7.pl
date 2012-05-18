#!/usr/bin/perl

use strict;


my $line;

# save input data, just for review
open F, ">input_data.txt";

my %edges = (); # $edges{node1}{node2} exists and is 1 iif there is an edge from node1 to node2
my %nodes = (); # $nodes{node} exists and is 1 iff the node exists

while ( ($line = <>) )
{
  print F $line;
  chomp $line;

  my @letters = split(//, $line);
  my $i;
  my $n = scalar @letters;

  for ($i = 0; $i < $n - 1; $i++)
  {
    $edges{$letters[$i]}{$letters[$i + 1]} = 1;
    $nodes{$letters[$i]} = 1;
  }
  $nodes{$letters[$i]} = 1;
}

close F;

my @nodes = sort keys %nodes; # array of nodes
my $num_nodes = scalar @nodes;

my %incoming_edges = (); # number of incoming edges of a node

my $i;
my $j;

for ($i = 0; $i < $num_nodes; $i++)
{
  $incoming_edges{$nodes[$j]} = 0;
}

for ($i = 0; $i < $num_nodes; $i++)
{
  for ($j = 0; $j < $num_nodes; $j++)
  {
    if (exists $edges{$nodes[$i]}{$nodes[$j]})
    {
      $incoming_edges{$nodes[$j]}++;
    }
  }
}

# now, do a topological sorting

my @nodes_without_incoming_edges = ();

foreach my $node (sort keys %incoming_edges)
{
  if ($incoming_edges{$node} == 0)
  {
    push(@nodes_without_incoming_edges, $node);
  }
}

my $result = topological_order(\@nodes_without_incoming_edges, \%incoming_edges, \%edges);

foreach my $res (sort @$result)
{
  print "$res\n";
}

sub topological_order ($$$)
{
  my @nodes_without_incoming_edges = @{$_[0]};
  my %incoming_edges = %{$_[1]}; # current number of incoming edges of a node
  my $edges = $_[2]; # reference to edges hash
  my $num_nodes = scalar @nodes_without_incoming_edges;
  my @ret = ();

  if ($num_nodes == 0)
  {
    push(@ret, "");
  }
  else
  {
    my $i;
    for ($i = 0; $i < $num_nodes; $i++)
    {
      my $n = $nodes_without_incoming_edges[$i];
      my $j;
      my @new_s = ();
      for ($j = 0; $j < $num_nodes; $j++)
      {
        if ($j != $i)
        {
          push(@new_s, $nodes_without_incoming_edges[$j]);
        }
      }

      my %new_inc_edges = %incoming_edges;

      foreach my $m (keys %{$edges->{$n}})
      {
        $new_inc_edges{$m}--;
        if ($new_inc_edges{$m} == 0)
        {
          push(@new_s, $m);
        }
      }

      my $sub_results = topological_order(\@new_s, \%new_inc_edges, $edges);
      
      foreach my $res (@$sub_results)
      {
        push(@ret, $n . $res);
      }
    }
  }

  return \@ret;
}

