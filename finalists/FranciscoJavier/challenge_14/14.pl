#!/usr/bin/perl


#hamming 7,4
$WORD_LEN=7;
@is_parity= (1,1,0,1,0,0,0);

#parity check matrix
@H=([1,0,1,0,1,0,1],
    [0,1,1,0,0,1,1],
    [0,0,0,1,1,1,1]);


while($cad=<>) {
    $error = 0;

    #check for invalid length
    chop $cad;
    if (length($cad) % $WORD_LEN) {
	$error = 1;
    }
    else {
	@byte=();
	$decoded_msg="";
	PROCESS_MSG:
	for ($i=0 ; $i<length($cad) ; $i+=$WORD_LEN) {
	    #convert to bit array and calculate syndrome
	    $wordstr = substr($cad,$i,$WORD_LEN);
	    @word = ();
	    for ($j=0;$j<$WORD_LEN;$j++) {
		$bit = substr($wordstr,$j,1) eq "1" ? 1 : 0;
		push @word,$bit;
	    }
	    @z = syndrome(\@word);

	    #CORRECT AND CALCULATE SYNDROME AGAIN (SHOULD BE ZERO)
	    $bit_error = get_error_bit(\@z);
	    @corr_word = @word;
	    if($bit_error) {
		$pos = $bit_error-1;
		$corr_word[$pos] = 1-$corr_word[$pos];
	    }
	    @z_corr = syndrome(\@corr_word);
	    $bit_error2 = get_error_bit(\@z_corr);
	    if ($bit_error2) {
		#message can't be fully decoded
		$error = 1;
		last PROCESS_MSG;
	    }
	    
	    #get data bits
	    @msg = ();
	    for ($j=0 ; $j<$WORD_LEN ; $j++) {
		$bit = $corr_word[$j];
		push @msg,$bit if !$is_parity[$j];
	    }
	    
	    #for debug only
	    #printf("word=@word  z=@z bit_error=$bit_error   corr=@corr_word z_corr=@z_corr  msg=@msg\n");

	    #compose byte
	    push @byte,@msg;
	    if (@byte == 8) {
		$byte=bits2num(@byte);
		if ($byte<32 || $byte>127) {
		    #message not readable
		    $error = 1;
		    last PROCESS_MSG;
		}
		@byte = ();
		$decoded_msg .=chr($byte);
	    }
	}
    }
    
    if ($error) {
	print "Error!\n";
    }
    else {
	print "$decoded_msg\n";
    }
}


sub syndrome {
    my @s;
    my $i;
    foreach$j (0..@H-1) {
	my $row = $H[$j];
	my $prod =0;
	foreach $i (0..@{$row}-1) {
	    $prod += $row->[$i] * ${_[0]}->[$i];
	}
	push @s,$prod % 2;
    }
    @s;
}

sub bits2num {
    my $_;
    my $res;
    foreach (@_) {
	$res = ($res<<1) + $_;
    }
    $res;
}

sub get_error_bit {
    my $i;
    my $res;
    for ($i=@{$_[0]}-1;$i>=0;$i--) {
	$res = ($res<<1) + ${_[0]}->[$i];
    }
    $res;
}


