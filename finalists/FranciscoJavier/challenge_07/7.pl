#!/usr/bin/perl

while(<>) {
    chop;
    ($l,$c,$r) = split '';

    $may{$l}.=$c if $may{$l} !~ /$c/;
    $may{$c}.=$r if $may{$c} !~ /$r/;
    $may{$r}.="";

    $men{$l}.="";
    $men{$c}.=$l if $men{$c} !~ /$l/;
    $men{$r}.=$c if $men{$r} !~ /$c/;
}

@chars= keys %men;
$NUM_CHARS=@chars;
foreach $i (0..@chars-1) {
    $indice{$chars[$i]}=$i;
}
procesa();
print sort @SOLUCIONES;

sub procesa() {
    if(@_==$NUM_CHARS) {
       my $solucion="";
       foreach(@_) {
	   $solucion.= $chars[$_];
       }
       $solucion.="\n";
       push(@SOLUCIONES,$solucion);
       return;
    }
    my @array=@_;
    my $i;
    foreach $i (0..$NUM_CHARS-1) {
	next if (existe(\@array,$i));

	#verificar que el nuevo elem cumple las reglas de orden
	push(@array,$i);
	@complem=complementario(\@array);
	pop(@array);
	
	my $midchar=$chars[$i];
	my $valido=1;
	my $c;

	foreach $c (split '',$may{$midchar}) {
	    $valido=0,last if existe (\@array,$indice{$c});
	}
	next if !$valido;
	foreach $c (split '',$men{$midchar}) {
	    $valido=0,last if existe (\@complem,$indice{$c});
	}
	next if !$valido;

	procesa(@array,$i);
    }
}

sub complementario() {
    my $i;
    my $array = shift;
    my @complem;
    foreach $i (0..$NUM_CHARS-1) {
	push(@complem,$i) if !existe($array,$i);
    }
    @complem;
}

sub existe() {
    my $_;
    my $array = shift;
    my $elem = shift;
    foreach (@{$array}) {
	return 1 if ($_ == $elem);
    }
    return 0;
}


