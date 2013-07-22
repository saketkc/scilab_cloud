function c=std_gumbel(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('std_gumbel',a,b)

endfunction
