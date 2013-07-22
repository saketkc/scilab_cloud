function c=zeromatrix(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('zeromatrix',a,b)

endfunction
