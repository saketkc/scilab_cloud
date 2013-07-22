function d=get_pixel(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('get_pixel',a,b,c)

endfunction
