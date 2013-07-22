function c=%s_c_sym(a,b)
c=sym(a)
c=mlist(['sym','t','rep'],'M',[c.rep,b.rep])
endfunction
