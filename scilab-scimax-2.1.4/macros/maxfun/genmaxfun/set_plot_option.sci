function b=set_plot_option(a)

if argn(2)~=1 then error(42), end
b=maxevalf('set_plot_option',a)

endfunction
