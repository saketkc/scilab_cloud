function b=var_student_t(a)

if argn(2)~=1 then error(42), end
b=maxevalf('var_student_t',a)

endfunction
