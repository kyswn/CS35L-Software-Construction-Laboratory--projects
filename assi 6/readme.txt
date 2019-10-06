testing parallel results:

time ./srt 1-test.ppm >1-test.ppm.tmp

real    0m44.139s
user    0m44.131s
sys     0m0.002s

time ./srt 2-test.ppm >2-test.ppm.tmp

real    0m22.619s
user    0m44.222s
sys     0m0.004s

time ./srt 4-test.ppm >4-test.ppm.tmp

real    0m15.047s
user    0m44.261s
sys     0m0.029s

time ./srt 8-test.ppm >8-test.ppm.tmp

real    0m9.423s
user    0m44.417s
sys     0m0.004s

obviously, the more threads we use, the less the real time is, while the user time amd system 
time stays relatively constant. In fact, because it is embarrassing parallel, with n threads, the 
real time is almost realtimeof1thread/n

issues I ran into: I first had problem understanding what the program does, but I understood
it after talking to a friend. Also, I at first forgot to declare some variables as global.