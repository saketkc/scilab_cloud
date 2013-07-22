function b=std_student_t(a)

if argn(2)~=1 then error(42), end
b=maxevalf('std_student_t',a)

endfunction
