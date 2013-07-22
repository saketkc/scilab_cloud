function f=ematrix(a,b,c,d,e)

if argn(2)~=5 then error(42), end
f=maxevalf('ematrix',a,b,c,d,e)

endfunction
