function a=absolute_real_time()

if argn(2)~=0 then error(42), end
a=maxevalf('absolute_real_time')

endfunction
