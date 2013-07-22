mode(-1);
lines(0);
try
 getversion('scilab');
catch
 error(gettext('Scilab 5.0 or more is required.'));
end;
// ====================================================================

toolbox_dir = get_absolute_file_path('builder.sce');

// By default, %otb_path is set to '../Overload_Toolbox/'
if ~exists('%otb_path') then
   %otb_path='../Overload_Toolbox'
end

%otb_loader='/'+%otb_path+'/'+'loader.sce';
if fileinfo(toolbox_dir+%otb_loader)~=[] then
  path=toolbox_dir+%otb_loader;
elseif fileinfo(%otb_loader)~=[] then
    path=%otb_loader;
else
  printf("I need to know where the Overload Toolbox is installed.\nPlease s"+..
	"et the variable %%otb_path=''path of Overload Toolbox''\n(maybe ''../Overload_Toolbox'') and"+...
	 " re-exec builder.sce.\n");
  abort;
end

fd=mopen('etc/Overload_TB_path.sce','w');
mputl('Overload_TB_path='''+path+'''',fd);
mclose(fd);

// ====================================================================

// ====================================================================
if ~with_module('development_tools') then
  error(msprintf(gettext('%s module not installed.'),'development_tools'));
end
// ====================================================================
TOOLBOX_NAME = 'SciMax';
TOOLBOX_TITLE = 'SciMax Toolbox';
// ====================================================================

tbx_builder_src(toolbox_dir);

global %lisp_error;

if (%lisp_error) then
  printf('Process aborted\n');
  abort
end

tbx_builder_macros(toolbox_dir);
tbx_build_loader(TOOLBOX_NAME, toolbox_dir);

clear toolbox_dir TOOLBOX_NAME TOOLBOX_TITLE %otb_path fd %lisp_error;

// ====================================================================
