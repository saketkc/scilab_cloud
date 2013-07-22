// ====================================================================
// Copyright INRIA 2008
// This file is released into the public domain
// ====================================================================

help_lang_dir = get_absolute_file_path('build_help.sce');

tbx_build_help(TOOLBOX_TITLE, help_lang_dir);
//global %helps;
//global %helps_modules;
//%helps_modules=[];
//%helps=[help_lang_dir TOOLBOX_TITLE];
//xmltoformat("javaHelp");

clear help_lang_dir;