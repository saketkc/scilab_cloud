function b=mandelbrot(a)

if argn(2)~=1 then error(42), end
b=maxevalf('mandelbrot',a)

endfunction
