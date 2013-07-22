// ====================================================================
// Copyright INRIA 2008
// This file is released into the public domain
// ====================================================================



function buildhelp(language)
    path = get_absolute_file_path('build_help.sce');
    scimax = path + '/SciMax/'; 
    maxima = path + '/Maxima/';
    global maxima_version;
    create_Master_Help ([scimax maxima], ['SciMax' maxima_version], 'SciMax"+...
    " Toolbox', path+'master_help.xml', language);
    name = 'scilab_'+language+'_help'
    mkdir(name);
    chdir(name);
    buildDocv2("javaHelp",path+"/master_help.xml",language,path);
    mkdir(path+'/../../jar');
    copyfile(name+'.jar',path+'/../../jar/'+name+'.jar');
    mdelete(name+'.jar');
endfunction

function create_Master_Help(my_dirs, my_titles, my_tbx_title, output_filename, language)

    if or(language == ["fr_FR";"pt_BR"]) then
        encoding = "ISO-8859-1";
    else
        encoding = "UTF-8";
    end

    master_document = ["<?xml version=""1.0"" encoding="""+encoding+"""?>"; ..
    "<!DOCTYPE book [";
    "<!--Begin Entities-->"];

    for my_dir=my_dirs

        xml_files = basename(listfiles(my_dir+"/*.xml"));
        xml_files = gsort(listfiles(my_dir+"/*.xml"),"lr","i");

        xml_files(grep(xml_files,"master_help.xml")) = [];

        if MSDOS then
            for j=1:size(xml_files,'*')
                xml_files_tmp(j) = "file:///"+ getshortpathname(xml_files(j));
            end
        else
            xml_files_tmp = xml_files;
        end

        master_document    = [master_document; ..
        "<!ENTITY "+basename(xml_files)+" SYSTEM """+xml_files_tmp+""">"];
    end

    master_document    = [ master_document; ..
    "<!--End Entities-->"; ..
    "]>"; ..
    "<book version=""5.0-subset Scilab"" xml:lang="""+language+""""; ..
    "      xmlns=""http://docbook.org/ns/docbook"""; ..
    "      xmlns:xlink=""http://www.w3.org/1999/xlink"""; ..
    "      xmlns:xi=""http://www.w3.org/2001/XInclude"""; ..
    "      xmlns:svg=""http://www.w3.org/2000/svg"""; ..
    "      xmlns:mml=""http://www.w3.org/1998/Math/MathML"""; ..
    "      xmlns:html=""http://www.w3.org/1999/xhtml"""; ..
    "      xmlns:db=""http://docbook.org/ns/docbook"">"; ..
    "  <info>"; ..
    "    <title>"+my_tbx_title+"</title>"; ..
    "  </info>"; ..
    "<!--Begin Reference-->"];
    for i=1:size(my_dirs,'*')

        xml_files = gsort(listfiles(my_dirs(i)+"/*.xml"),"lr","i");

        xml_files(grep(xml_files,"master_help.xml")) = [];
        master_document    = [ master_document; ..
        //"<chapter xml:id=''"+title2category(my_tbx_title)+"''>"; ..
        "<title>"+text2html(my_titles(i))+"</title>"; ..
        "&"+basename(xml_files)+";"; ..
        //"</chapter>"
	]
    end

    master_document    = [ master_document; ..
    "  <!--End Reference-->"; ..
    "</book>" ];

    mputl(master_document,output_filename);

endfunction

function category = title2category(mytitle)

    category = mytitle;
    category = strsubst(category , "&"  , "_" );

    category = strsubst(category , "À"  , "A" );
    category = strsubst(category , "Á"  , "A" );
    category = strsubst(category , "Â"  , "A" );
    category = strsubst(category , "Ã"  , "A" );
    category = strsubst(category , "Ä"  , "A" );
    category = strsubst(category , "Å"  , "A" );
    category = strsubst(category , "Æ"  , "AE");
    category = strsubst(category , "Ç"  , "C" );
    category = strsubst(category , "È"  , "E" );
    category = strsubst(category , "É"  , "E" );
    category = strsubst(category , "Ê"  , "E" );
    category = strsubst(category , "Ë"  , "E" );
    category = strsubst(category , "Ì"  , "I" );
    category = strsubst(category , "Í"  , "I" );
    category = strsubst(category , "Î"  , "I" );
    category = strsubst(category , "Ï"  , "I" );
    category = strsubst(category , "Ð"  , "D" );
    category = strsubst(category , "Ñ"  , "N" );
    category = strsubst(category , "Ò"  , "O" );
    category = strsubst(category , "Ó"  , "O" );
    category = strsubst(category , "Ô"  , "O" );
    category = strsubst(category , "Õ"  , "O" );
    category = strsubst(category , "Ö"  , "O" );
    category = strsubst(category , "Ù"  , "U" );
    category = strsubst(category , "Ú"  , "U" );
    category = strsubst(category , "Û"  , "U" );
    category = strsubst(category , "Ü"  , "U" );
    category = strsubst(category , "Ý"  , "Y" );
    category = strsubst(category , "à"  , "a" );
    category = strsubst(category , "á"  , "a" );
    category = strsubst(category , "â"  , "a" );
    category = strsubst(category , "ã"  , "a" );
    category = strsubst(category , "ä"  , "a" );
    category = strsubst(category , "å"  , "a" );
    category = strsubst(category , "æ"  , "ae");
    category = strsubst(category , "ç"  , "c" );
    category = strsubst(category , "è"  , "e" );
    category = strsubst(category , "é"  , "e" );
    category = strsubst(category , "ê"  , "e" );
    category = strsubst(category , "ë"  , "e" );
    category = strsubst(category , "ì"  , "i" );
    category = strsubst(category , "í"  , "i" );
    category = strsubst(category , "î"  , "i" );
    category = strsubst(category , "ï"  , "i" );
    category = strsubst(category , "ñ"  , "n" );
    category = strsubst(category , "ò"  , "o" );
    category = strsubst(category , "ó"  , "o" );
    category = strsubst(category , "ô"  , "o" );
    category = strsubst(category , "õ"  , "o" );
    category = strsubst(category , "ö"  , "o" );
    category = strsubst(category , "ù"  , "u" );
    category = strsubst(category , "ú"  , "u" );
    category = strsubst(category , "û"  , "u" );
    category = strsubst(category , "ü"  , "u" );
    category = strsubst(category , "ý"  , "y" );
    category = strsubst(category , "ÿ"  , "y" );

    category = strsubst(category , ":"  , ""  );
    category = strsubst(category , "\"  , "_" );
    category = strsubst(category , "/"  , "_" );
    category = strsubst(category , "''" , "_" );
    category = strsubst(category , "  " , " " );
    category = strsubst(category , " "  , "_" );
    category = strsubst(category , "["  , ""  );
    category = strsubst(category , "]"  , ""  );

    category = convstr(category,"l");
    category = "category_"+category;

endfunction


function out = text2html(in)

    out = in;
    out = strsubst(out , "&"  , "&amp;"    );

    // 		
    // 		out = strsubst(out , """" , "&quot;"   );
    // 		out = strsubst(out , "&"  , "&amp;"    );
    // 		out = strsubst(out , "¤"  , "&euro;"   );
    // 		out = strsubst(out , "À"  , "&Agrave;" );
    // 		out = strsubst(out , "Á"  , "&Aacute;" );
    // 		out = strsubst(out , "Â"  , "&Acirc;"  );
    // 		out = strsubst(out , "Ã"  , "&Atilde;" );
    // 		out = strsubst(out , "Ä"  , "&Auml;"   );
    // 		out = strsubst(out , "Å"  , "&Aring;"  );
    // 		out = strsubst(out , "Æ"  , "&Aelig"   );
    // 		out = strsubst(out , "Ç"  , "&Ccedil;" );
    // 		out = strsubst(out , "È"  , "&Egrave;" );
    // 		out = strsubst(out , "É"  , "&Eacute;" );
    // 		out = strsubst(out , "Ê"  , "&Ecirc;"  );
    // 		out = strsubst(out , "Ë"  , "&Euml;"   );
    // 		out = strsubst(out , "Ì"  , "&Igrave"  );;
    // 		out = strsubst(out , "Í"  , "&Iacute;" );
    // 		out = strsubst(out , "Î"  , "&Icirc;"  );
    // 		out = strsubst(out , "Ï"  , "&Iuml;"   );
    // 		out = strsubst(out , "Ð"  , "&eth;"    );
    // 		out = strsubst(out , "Ñ"  , "&Ntilde;" );
    // 		out = strsubst(out , "Ò"  , "&Ograve;" );
    // 		out = strsubst(out , "Ó"  , "&Oacute;" );
    // 		out = strsubst(out , "Ô"  , "&Ocirc;"  );
    // 		out = strsubst(out , "Õ"  , "&Otilde;" );
    // 		out = strsubst(out , "Ö"  , "&Ouml;"   );
    // 		out = strsubst(out , "Ù"  , "&Ugrave;" );
    // 		out = strsubst(out , "Ú"  , "&Uacute;" );
    // 		out = strsubst(out , "Û"  , "&Ucirc;"  );
    // 		out = strsubst(out , "Ü"  , "&Uuml;"   );
    // 		out = strsubst(out , "Ý"  , "&Yacute;" );
    // 		out = strsubst(out , "Þ"  , "&thorn;"  );
    // 		out = strsubst(out , "ß"  , "&szlig;"  );
    // 		out = strsubst(out , "à"  , "&agrave;" );
    // 		out = strsubst(out , "á"  , "&aacute;" );
    // 		out = strsubst(out , "â"  , "&acirc;"  );
    // 		out = strsubst(out , "ã"  , "&atilde;" );
    // 		out = strsubst(out , "ä"  , "&auml;"   );
    // 		out = strsubst(out , "å"  , "&aring;"  );
    // 		out = strsubst(out , "æ"  , "&aelig;"  );
    // 		out = strsubst(out , "ç"  , "&ccedil;" );
    // 		out = strsubst(out , "è"  , "&egrave"  );;
    // 		out = strsubst(out , "é"  , "&eacute;" );
    // 		out = strsubst(out , "ê"  , "&ecirc;"  );
    // 		out = strsubst(out , "ë"  , "&euml;"   );
    // 		out = strsubst(out , "ì"  , "&igrave"  );;
    // 		out = strsubst(out , "í"  , "&iacute;" );
    // 		out = strsubst(out , "î"  , "&icirc;"  );
    // 		out = strsubst(out , "ï"  , "&iuml;"   );
    // 		out = strsubst(out , "ð"  , "&eth;"    );
    // 		out = strsubst(out , "ñ"  , "&ntilde;" );
    // 		out = strsubst(out , "ò"  , "&ograve;" );
    // 		out = strsubst(out , "ó"  , "&oacute;" );
    // 		out = strsubst(out , "ô"  , "&ocirc;"  );
    // 		out = strsubst(out , "õ"  , "&otilde;" );
    // 		out = strsubst(out , "ö"  , "&ouml;"   );
    // 		out = strsubst(out , "ù"  , "&ugrave;" );
    // 		out = strsubst(out , "ú"  , "&uacute;" );
    // 		out = strsubst(out , "û"  , "&ucirc;"  );
    // 		out = strsubst(out , "ü"  , "&uuml;"   );
    // 		out = strsubst(out , "ý"  , "&yacute;" );
    // 		out = strsubst(out , "þ"  , "&thorn;"  );
    // 		out = strsubst(out , "ÿ"  , "&yuml;"   );
    // 		out = strsubst(out , "µ"  , "&micro;"  );

endfunction