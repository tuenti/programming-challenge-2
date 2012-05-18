#!/usr/bin/perl
$path=$0;
$path =~ s/challenge20_test.pl$//;

use Crypt::DES;
use Crypt::OpenSSL::AES;

#known plaintext
$known_plaintext="Key=";
foreach(split '',$known_plaintext) {$plaintext4_hex .= sprintf "%02x",ord($_);}

#padding
$suffix = "0000";
foreach(split '',$suffix) {$padding4_hex .= sprintf "%02x",ord($_);}


while ($entry=<>) {
    chop $entry;
    ($encrypted_message,$game_messages) = split ':',$entry;

#    print "ENCRYPTED MESSAGE $kk: $encrypted_message\n";

    @game_messages=();
    %sizes=();
    foreach (split '~',$game_messages) {
	push @game_messages,$_;
	$sizes{length($_)}++;
    }
    
#    print "NUM GAME MESSAGES: ",scalar(@game_messages),"\n";
    foreach $size (sort {$a<=>$b} keys %sizes) {
#	print "$size $sizes{$size}\n";
    }

  GAME_MESSAGE:
#    foreach $gamemsg_hex (@game_messages) {
    foreach $gamemsg_hex (@game_messages[501,244,656,253,394]) {
#	print "$gamemsg_hex\n";

	#first 8 bytes
	$ciphertext8_hex = substr($gamemsg_hex,0,2*8);

	#break key using a spceial purpose fast C program...
	$cmd="$path/breakkey/breakkey $ciphertext8_hex $plaintext4_hex $padding4_hex";
	$keyshex=`$cmd`;
#	print "$keyshex\n";

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
#	    print "KEY=$aes_key  Puzzle=$puzzle\n";

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
	    print "$plaintext\n";
	    last GAME_MESSAGE;
	}
    }
}
