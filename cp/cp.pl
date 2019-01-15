#!/usr/bin/perl
use strict;
use warnings;

open(my $IN,  "<", "$ARGV[0]") or die "can't open $ARGV[0]: $!";
open(my $OUT, ">", "$ARGV[1]") or die "can't open $ARGV[1]: $!";

my $blksize = (stat $IN)[11] || 16384;
while (my $len = sysread $IN, my $buf, $blksize) {
    die "System read error: $!\n" if !defined $len;
    my $offset = 0;
    while ($len) {
        defined(my $written = syswrite $OUT, $buf, $len, $offset) 
            or die "System write error: $!\n";
        $len    -= $written;
        $offset += $written;
    };
}

close($IN);
close($OUT);