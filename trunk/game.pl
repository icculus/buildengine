#!/usr/bin/perl -w

# This is an example of a perl module that is run from inside BUILD.
#
#  Written by Ryan C. Gordon. (icculus@clutteredmind.org)
#
# Please do NOT harrass Ken Silverman about any code modifications
#  (including this file) to BUILD.
#
#
#// "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
#// Ken Silverman's official web site: "http://www.advsys.net/ken"
#// See the included license file "BUILDLIC.TXT" for license info.
#// This file IS NOT A PART OF Ken Silverman's original release

use strict;


# Global/package data works.
my $build_counter = 0;



# The sub BUILD_frame() is called once before each video frame is rendered.
#  This means it may run from < 10 to > 500 times per second, and should
#  run AS FAST AS POSSIBLE.

sub BUILD_frame {
    $build_counter++;

    if ($build_counter == 1024) {
	$build_counter = 0;
	print("INSIDE PERL ROUTINE: build counter hit 1024.\n");
    }
}


# Stuff outside a function is mainline code. This is run once when game
#  loads.

print("INSIDE PERL ROUTINE: this is the mainline.\n");

# end of game.pl ...

