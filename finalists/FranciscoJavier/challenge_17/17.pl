#!/usr/bin/perl
use Math::Trig ':pi';
use Math::Trig ':radial';

#process input data
$C = <>;
foreach $case (1..$C) {
    @vertex_x=();
    @vertex_y=();
    @name=();
    %namelist=();
    $num_ingredients = 0;

    $_ = <>;
    chop;
    ($Cx,$Cy,$R) = split ' ';
    $N = <>;
    chop $N;
    foreach $i (0..$N-1) {
	$_= <>;
	chop;
	($name, $num_edges, $count) = split ' ';
	foreach $j (1..$count) {
	    $_ = <>;
	    chop;
	    ($cx, $cy, $vx, $vy) = split  ' ';
	    #process relative to center of pizza (and don't use Cx,Cy anymore)
	    $cx -= $Cx;
	    $cy -= $Cy;
	    $vx -= $Vx;
	    $vy -= $Vy;

	    #expand all vertexes
	    $x = $vx - $cx;
	    $y = $vy - $cy;
	    ($rho, $theta, $phi) = cartesian_to_spherical($x, $y, 0);
	    @x = ($vx);
	    @y = ($vy);
	    foreach $v (1..$num_edges-1) {
		$theta += (2*pi)/$num_edges;
		($x, $y, $z) = spherical_to_cartesian($rho, $theta, $phi);
		$vx = $x + $cx;
		$vy = $y + $cy;
		push @x, $vx;
		push @y, $vy;
	    }
	    #save data for future ref
	    $vertex_x[$num_ingredients] = [@x];
	    $vertex_y[$num_ingredients] = [@y];
	    $name[$num_ingredients] = $name;
	    $namelist{$name} = 1;
	    $num_ingredients++;
	}
    }

    #try all possible angles (up to a certain precision)
    $salomonic=0;
  ANGLE:
    for ($ANGLE = 0 ; $ANGLE < pi ; $ANGLE += 0.001) {

	%myside = ();
	%yourside = ();

	foreach $i (0..$num_ingredients-1) {
	    $vx = $vertex_x[$i];
	    $vy = $vertex_y[$i];

	    #check each vertex
	    $left=0;
	    $right=0;
	    foreach $j (0..@{$vx}-1) {
		#rotate vertex
		$x = $vx->[$j];
		$y = $vy->[$j];
		($rho, $theta, $phi) = cartesian_to_spherical($x, $y, 0);
		$theta += $ANGLE;
		$theta -= (2*$pi) if $theta > pi;
		
		#check side of vertex
		if ($theta> 0) {
		    $left++;
		}
		else {
		    $right++;
		}
	    }
	    
	    if ($left && $right) {
		#element is cut
		next ANGLE;
	    }
	    elsif ($left) {
		$myside{$name[$i]}++ ;
	    }
	    else {
		$yourside{$name[$i]}++;
	    }
	}

	#check if all elements are evenly distributed
	foreach $name (keys %namelist) {
	    next ANGLE if ($myside{$name} != $yourside{$name});
	}

	#we made it !!
	$salomonic = 1;
	last ANGLE;
    }

    #output result
    print "Case #$case: ",($salomonic? "TRUE" : "FALSE"),"\n";

}

