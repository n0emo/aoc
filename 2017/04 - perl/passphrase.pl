#!/usr/bin/perl

use strict;
use warnings;

sub part1 {
    my $file = $_[0];
    open(FH, "<", $file) or die $!;

    my $count = 0;

    while(<FH>) {
        my @words = split(" ", $_);
        my @wordlist = ();
        my $valid = 1;

        foreach my $word (@words) {
            if ($word ~~ @wordlist) {
                $valid = 0;
            }
            push(@wordlist, $word);
        }

        if($valid) {
            $count += 1;
        }

    }
    return $count;
}

sub sortstr {
    my $str = $_[0];
    return join('', sort({$a cmp $b} split('', $str)))
}

sub part2 {
    my $file = $_[0];
    open(FH, "<", $file) or die $!;

    my $count = 0;

    while(<FH>) {
        my @words = split(" ", $_);
        my @wordlist = ();
        my $valid = 1;

        foreach my $word (@words) {
            $word = sortstr($word);
            if ($word ~~ @wordlist) {
                $valid = 0;
            }
            push(@wordlist, $word);
        }

        if($valid) {
            $count += 1;
        }

    }
    return $count;
}

foreach my $arg (@ARGV) {
    print "Solving $arg\n";
    my $res1 = part1($arg);
    print "Part 1: $res1\n";
    my $res2 = part2($arg);
    print "Part 2: $res2\n";
}
