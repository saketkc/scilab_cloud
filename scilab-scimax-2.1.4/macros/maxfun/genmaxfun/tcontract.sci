function c=tcontract(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('tcontract',a,b)

endfunction
