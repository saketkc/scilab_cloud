mode(-1);
ici=get_absolute_file_path('builder_c.sce');
include='-I'+ici+'../include/ ' +'-D__USE_DEPRECATED_STACK_FUNCTIONS__';
include=include+'-I'+SCI+'/../../include/scilab/shell/'

cfuns=['sci_answer.c','sci_latex.c','sci_Matrix.c','sci_maxevalfl.c','sci_maxinit.c','sci_maxprint.c','sci_sym.c','sci_Syms.c','sci_defmf.c','sci_mathml.c','sci_maxevalf.c','sci_maxevalop.c','sci_maxkill.c','sci_noanswer.c','sci_symnp.c','donnees.c','latex.c','mathml.c','maxevalf.c','maxevalop.c','maxkill.c','symnp.c','defmf.c','gestionVar.c','Matrix.c','maxevalfl.c','maxinit.c','maxprint.c','sym.c'];

functions=['maxinit' 'sci_maxinit';
	   'maxkill' 'sci_maxkill';
	   'maxevalf' 'sci_maxevalf';
	   'maxevalfl' 'sci_maxevalfl';
	   '%sym_p' 'sci_maxprint';
	   'sym' 'sci_sym';
	   'Matrix' 'sci_Matrix';
	   'symnp' 'sci_symnp';
	   'defmf' 'sci_defmf';
	   'Syms' 'sci_Syms';
	   'latex' 'sci_latex';
	   'mathml' 'sci_mathml';
	   'answer' 'sci_answer';
	   'noanswer' 'sci_noanswer';
	   'maxevalopA' 'sci_maxevalop';
	   'maxevalopB' 'sci_maxevalop';
	   'maxevalopC' 'sci_maxevalop';
	   'maxevalopD' 'sci_maxevalop';
	   'maxevalopE' 'sci_maxevalop';
	   'maxevalopF' 'sci_maxevalop';
	   'maxevalopG' 'sci_maxevalop';
	   'maxevalopH' 'sci_maxevalop';
	   'maxevalopI' 'sci_maxevalop';
	   'maxevalopJ' 'sci_maxevalop';
	   'maxevalopK' 'sci_maxevalop';
	   'maxevalopL' 'sci_maxevalop';
	   'maxevalopM' 'sci_maxevalop';
	   'maxevalopN' 'sci_maxevalop';
	   'maxevalopO' 'sci_maxevalop';
	   'maxevalopP' 'sci_maxevalop';
	   'maxevalopQ' 'sci_maxevalop';
	   'maxevalopR' 'sci_maxevalop';
	   'maxevalopS' 'sci_maxevalop'];

ilib_build('maxima',functions,cfuns,'','Makelib','',include,'',%f,'');

clear mpath ici functions cfuns include;

