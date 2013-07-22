function e=%sym_polar(a,b,c,d)

if argn(2)~=4 then error(42), end
e=maxevalf('polar',a,b,c,d)

endfunction
