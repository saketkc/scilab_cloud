function b=skewness_student_t(a)

if argn(2)~=1 then error(42), end
b=maxevalf('skewness_student_t',a)

endfunction
