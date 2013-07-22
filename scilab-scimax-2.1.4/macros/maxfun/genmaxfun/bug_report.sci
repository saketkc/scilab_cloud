function a=bug_report()

if argn(2)~=0 then error(42), end
a=maxevalf('bug_report')

endfunction
