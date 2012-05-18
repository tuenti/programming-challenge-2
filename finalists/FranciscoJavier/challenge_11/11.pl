#!/usr/bin/perl
$path=$0;
$path =~ s/challenge11.pl$//;

%tmp=("1","A E I L N O R S T U",
      "2","D G",
      "3","B C M P",
      "4","F H V W Y",
      "5","K",
      "8","J X",
      "10","Q Z");
foreach $score (keys %tmp) {
    foreach $letter (split " ",$tmp{$score}) {
	$letter_score{$letter} = $score;
    }
}


#LOAD DICT
open DICT,"$path/descrambler_wordlist.txt";
while ($word=<DICT>) {
    chop $word;

    $word_score{$word} = get_wordscore($word);

    #word combination (sorted letters)
    $sorted_letters = join '',sort split '',$word;
    if ($comb{$sorted_letters} eq "" || $comb{$sorted_letters} gt $word) {
	$comb{$sorted_letters} = $word;
    }
}

sub get_wordscore() {
    my $_;
    my $s;
    foreach (split '',$_[0]) {
	$s += $letter_score{$_};
    }
    $s;
}

#TEST CASES
$C=<>;
foreach (1..$C) {
    $high_score = 0;
    $_=<>;
    chop;
    ($R,$B) = split / /;

    foreach $l (split '',$B) {
	#extend and sort
	$extended_R = join '',sort split '',($R.$l);

	#pick letters in a binary fashion and see if word exists
	foreach $mask (1..(1<<length($extended_R))-1) {
	    $sub_R = pick($extended_R,$mask);
	    if ($comb{$sub_R}) {
		$word= $comb{$sub_R};
		$score =  $word_score{$word};
		if ($score > $high_score) {
		    $best_word = $word;
		    $high_score = $score;
		}
		elsif ($score == $high_score && $word lt $best_word) {
		    $best_word = $word;
		}
	    }
	}
    }
    print "$best_word $high_score\n";
}

sub pick() {
    my $word = shift;
    my $mask = shift;
    my $output = "";
    my $i;
    while ($mask) {	
	if ($mask & 1) {
	    $output.=substr($word,$i,1);
	}
	$mask = $mask >> 1;
	$i++;
    }
    $output;
}
