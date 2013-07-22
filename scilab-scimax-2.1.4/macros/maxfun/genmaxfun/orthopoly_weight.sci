function c=orthopoly_weight(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('orthopoly_weight',a,b)

endfunction
