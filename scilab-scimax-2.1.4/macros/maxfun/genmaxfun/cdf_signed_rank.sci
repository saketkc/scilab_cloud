function c=cdf_signed_rank(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('cdf_signed_rank',a,b)

endfunction
