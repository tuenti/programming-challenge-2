#!/usr/bin/perl

# *** Challenge 9: Il nomme della magnolia ***
#
# My dear Adso, we must not allow ourselves to 
# be influenced by irrational rumors of the 
# Antichrist, hmm? Let us instead exercise our
# brains and try to solve this tantalizing conundrum.
#
#                           - William of Baskerville

use strict;

my $doc_dir = "documents";

my @file_list = sort(glob("$doc_dir/*"));

# Skip the first line
<>;

while(<>) {
    next if (m#^\s*$#);
    chomp();

    my ($word, $ocurrence) = split;

    # We will search the lowercase word
    my $lc_word = lc($word);
    my $count = 0;
    my $found = "";

    # Search the documents in order
    for my $filename (@file_list) {
        open FILE, "< $filename";

        my $line_number = 0;

        while(<FILE>) {
            $line_number++;
            my $lc_line = lc;

            # Check if the word is in the line as a complete word.
            # If we are searching for "king" we won't match "kingdom"
            if ($lc_line =~ m/\b$lc_word\b/) {
                
                my @words = split /\s+/, $lc_line;

                for my $i (0..@words) {
                    $count++ if ($words[$i] eq $lc_word);
                    
                    if ($count == $ocurrence) {
                        # We have found the correct word
                        # Convert the filename to integer    
                        (my $file_number = $filename) =~ s#^.*/##;
                        $file_number = int($file_number);

                        $found = $file_number . "-" . $line_number . "-" . ($i + 1);
                        last;
                    }
                } 

                last if ($found);
            }
        }

        close FILE;
        last if ($found);
    }

    print $found . "\n";
}



