function e=%sym_sum(a,b,c,d)

if argn(2)~=4 then error(42), end
e=maxevalf('sum',a,b,c,d)

endfunction
