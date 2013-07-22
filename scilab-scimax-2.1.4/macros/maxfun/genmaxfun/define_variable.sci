function d=define_variable(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('define_variable',a,b,c)

endfunction
