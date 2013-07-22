function b=harmonic_mean(a)

if argn(2)~=1 then error(42), end
b=maxevalf('harmonic_mean',a)

endfunction
