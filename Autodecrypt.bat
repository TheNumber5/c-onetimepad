@echo off

rem Run this to auto decrypt the images from the repository
rem https://github.com/TheNumber5/onetimepad-c

onetimepad -d example1encrypted.bmp example1result.bmp example1key.bin
onetimepad -d example2encrypted.bmp example2result.bmp example2key.bin
onetimepad -d example3encrypted.bmp example3result.bmp example3key.bin
onetimepad -d example4encrypted.bmp example4result.bmp example4key.bin
onetimepad -d example5encrypted.png example5result.png example5key.bin
