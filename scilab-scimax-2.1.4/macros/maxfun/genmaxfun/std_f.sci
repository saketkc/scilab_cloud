function c=std_f(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('std_f',a,b)

endfunction
