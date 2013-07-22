function c=std_weibull(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('std_weibull',a,b)

endfunction
