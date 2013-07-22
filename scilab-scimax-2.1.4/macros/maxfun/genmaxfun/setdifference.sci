function c=setdifference(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('setdifference',a,b)

endfunction
