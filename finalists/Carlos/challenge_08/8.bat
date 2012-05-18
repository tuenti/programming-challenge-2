@echo off
perl 8.pl | md5sum - | perl 8_2nd_step.pl

