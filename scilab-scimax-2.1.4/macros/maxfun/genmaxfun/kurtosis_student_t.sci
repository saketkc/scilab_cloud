function b=kurtosis_student_t(a)

if argn(2)~=1 then error(42), end
b=maxevalf('kurtosis_student_t',a)

endfunction
