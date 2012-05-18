#!/usr/bin/perl
use Crypt::DES;
use Crypt::OpenSSL::AES;

$FILENAME="$ARGV[0]";

-f "$FILENAME.0" or die "Must speficy filename prefix\n";


#la 0 no la hacemos, ya la sabemos
foreach $num_file (0..4) {
#    open PREPROC,"<output.$num_file";
    open PREPROC,"<$FILENAME.$num_file";
    $_=<PREPROC>;

    ($encrypted_message)=/: (.*)\n/;
    print "ENCRYPTED MESSAGE: $encrypted_message\n";

    foreach $num_game_message (0..999) {
	$gamemsg_hex=<PREPROC>;
	chop $gamemsg_hex;
	$keyshex=<PREPROC>;
	chop $keyshex;
#	print "MSG $num_game_message:  $gamemsg_hex\n";

	#there could be several candidate keys
	$num_keys = length($keyshex)/16;
	foreach $num_key (0..$num_keys-1) {
	    $keyhex = substr($keyshex,$num_key*16,16);
	    $key = pack("H16", $keyhex);

	    #decode DES
	    $cipher = new Crypt::DES $key;
	    $data = pack("H".length($gamemsg_hex), $gamemsg_hex);
	    $tmp="";
	    for($j=0;$j<length($data);$j+=8) {
		$tmp .= $cipher->decrypt( substr($data,$j,8) );
	    }

	    #remove parity bits
	    $plaintext = "";
	    foreach (split '',$tmp) {
		$plaintext .= sprintf "%s",chr(ord($_) & 0x7F);
	    }

	    #parse
	    $plaintext =~ /Key=([^ ]+) & Puzzle=(\d+)/;
	    $aes_key=$1;
	    $puzzle=$2;
	    next if $aes_key eq "" || $puzzle eq "";

	    print "DECRYPTED GAME MESSAGE $num_game_message with DES key $keyhex:   Key=$aes_key & Puzzle=$puzzle\n";

	    #decode AES
	    $cipher = new Crypt::OpenSSL::AES($aes_key);
	    $data= pack("H".length($encrypted_message), $encrypted_message);
	    $tmp="";
	    for($j=0;$j<length($data);$j+=16) {
		$tmp .= $cipher->decrypt( substr($data,$j,16) );
	    }
	    #remove parity bits
	    $plaintext = "";
	    foreach (split '',$tmp) {
		$plaintext .= sprintf "%s",chr(ord($_) & 0x7F);
	    }
	    
	    #remove padding byte
	    $padbyte=substr($plaintext,length($plaintext)-1,1);
	    next if ord($padbyte)>=0x32; 
	    while (substr($plaintext,length($plaintext)-1,1) eq $padbyte) {
		substr($plaintext,length($plaintext)-1,1) = "";
	    }

	    next if $plaintext =~ /[\00-\031\[\]\{\}\|]/;

	    #final output
	    print "FOUND $num_file! USING KEY FROM GAME MESSAGE $num_game_message  of (0..999)\n";
	    print "$plaintext\n";

#	    open SALIDA,">decod.$num_file";
#	    print SALIDA $plaintext;
#	    close SALIDA;
	}
    }
}


