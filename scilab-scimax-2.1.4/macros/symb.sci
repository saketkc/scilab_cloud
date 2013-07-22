function z=symb(x,y)

maxaff('fpprec',y);
z=maxevalf('__symb',x);

endfunction
