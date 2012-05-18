#!/usr/bin/perl

$DOCS="documents";
$INDEX="index";

#to reduce I/O time
$BLOCK_SIZE = 50;


if (-d $INDEX) {
    `rm -rf $INDEX`;
}
`mkdir $INDEX`;


foreach $doc (`ls $DOCS -1`) {
    chop $doc;
    $num_doc++;
    open DOC,"<$DOCS/$doc";
    $num_line = 0;
    print "$doc\n";
    while (<DOC>) {
	$num_line++;
	chop;
	@palabras = split / /;
	$num_pal = 0;
	foreach $p (@palabras) {
	    $p = lc($p);
	    $num_pal++;
	    $pos{$p}->[$occurences{$p}++] = "$num_doc-$num_line-$num_pal";
	}
    }

    $num_doc % $BLOCK_SIZE and next;

    #dump to disk and clear memory
    dump_to_disk();
}
dump_to_disk();

sub dump_to_disk() {
    print STDERR "Dumping to disk\n";
    foreach $p (keys %pos) {
	open IDX,">>$INDEX/$p";
	foreach (@{$pos{$p}}) {
	    print IDX "$_\n";
	}
	close IDX;

	@{$pos{$p}}=();
    }
    %occurences=();
    %pos=();

}
