function d=poly_depends_p(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('poly_depends_p',a,b,c)

endfunction
