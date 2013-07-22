function c=std_gamma(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('std_gamma',a,b)

endfunction
