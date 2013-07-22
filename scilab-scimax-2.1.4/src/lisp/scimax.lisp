;;    <SciMax, a Scilab toolbox to connect Maxima.>
;;    Copyright (C) <2009>  <Calixte DENIZET>
;;
;;    This program is free software: you can redistribute it and/or modify
;;    it under the terms of the GNU General Public License as published by
;;    the Free Software Foundation, either version 3 of the License, or
;;    (at your option) any later version.
;;
;;   This program is distributed in the hope that it will be useful,
;;   but WITHOUT ANY WARRANTY; without even the implied warranty of
;;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;;   GNU General Public License for more details.
;;
;;   You should have received a copy of the GNU General Public License
;;   along with this program.  If not, see <http://www.gnu.org/licenses/>.
;;
;;
;;   Contact : Calixte DENIZET <calixte.denizet@ac-rennes.fr>

(in-package :maxima)

(macsyma-module scimax)

(declaim (optimize (Speed 3) (Safety 0) (Space 0)))
#+gcl (si::use-fast-links t)

;; La fonction $_ permet d'afficher le resultat de expr sous forme d'une
;; chaine de caracteres. J'ai choisi un nom court pour gagner qques millisecs
;; sur le parsage

;;(defun $_ (expr)
;;  (setq expr (print-invert-case (implode (mstring expr) nil)))
;; (format t "~%<BO>~A~%~A" (length expr) expr))

(defun $_ (expr)
  (let ((dec (list 1)) (ch (list)))
    (declare (list ch dec))
;;  (setq expr (meval expr))
    (cond (($matrixp expr)
	   (format t "~%<BO>M~%")
	   (let ((l 0) (c 0) (sl 1) (ml nil))
	     (declare (fixnum l c sl) (list ml))
	     (setq expr ($transpose expr))
	     (loop for v in (cdr expr) do
		   (incf l)
		   (loop for w in (cdr v) do
			 (incf c)
			 (setq ml (mstring w))
			 (setq sl (+ sl (length ml)))
			 (setq ch (append ch ml))
			 (setq dec (append dec (list sl)))))
	     (setq dec (append (list (+ 1 c sl) (/ c l) l) dec)))) 
	     ((or ($listp expr) ($setp expr))
	      (let ((c 0) (sl 1) (ml nil))
		(declare (fixnum c sl) (list ml))
		(if ($listp expr) (format t "~%<BO>[~%") (format t "~%<BO>{~%"))
		(loop for v in (cdr expr) do
		      (incf c)
		      (setq ml (mstring v))
		      (setq sl (+ sl (length ml)))
		      (setq ch (append ch ml))
		      (setq dec (append dec (list sl))))
		(setq dec (append (list (+ 1 c sl) 1 c) dec)))) 
	     (t 
	      (format t "~%<BO>E~%")
	      (setq ch (mstring expr))
	      (setq dec (cons (+ 3 (length ch)) nil)))) 
    (loop for n in dec do
	  (format t "~A~%" n))
    (if (eq (car dec) 3) 
	(format t "~%")
      (princ (print-invert-case (implode ch))))))

;; La fonction $__ permet de laisser l'output tel quel 
(defun $__ (expr)
  (let ((ch (print-invert-case (implode (mstring expr)))) (len))
    (setq len (+ 3 (length ch)))
    (format t "~%<BO>E~%~A~%" len)
    (if (eq len 3)
	(format t "~%")
      (princ ch))))

;; La fonction $___ permet de faire un joli output de l'expression
(defun $___ (expr)
  (format t "~%<BO>~%")
  (if (not (and (listp expr) (equal (car expr) nil))) ($disp expr)))

;; La fonction $_t permet de LateXiser l'expression 
(defun $_t (expr)
  (setq expr (meval `(($tex),expr,nil)))
  (format t "~%<BO>~A~%~A" (length expr) expr))

;; La fonction $_m permet de MathMLiser l'expression 
(defun $_m (expr)
  (setq expr (meval `(($mathml),expr,nil)))
  (format t "~%<BO>~A~%~A" (length expr) expr))

(defmspec $__list (expr)
  (meval (cons '(mlist) (cdr expr))))

(defmspec $__set (expr)
  (meval (cons '(${) (cdr expr))))

;; La fonction suivante a ete copiee-collee depuis les sources
;; J'ai simplement rajoute deux lignes afin que le prompt soit exactement <EO>\n
;; Les variables suivantes sont definies pour eviter d'avoir des warning a la compilation 
(defvar *maxima-started*)
(defvar *maxima-quiet*)
(defvar *maxima-epilog*)
(defvar $nolabels)

(defun macsyma-top-level (&optional (input-stream *standard-input*)
			  batch-flag)
  (let ((*package* (find-package :maxima)))
    (if *maxima-started*
	(format t "Maxima restarted.~%")
	(progn
      (if (not *maxima-quiet*) (maxima-banner))
	  (setq *maxima-started* t)))
    (if ($file_search "maxima-init.lisp") ($load ($file_search "maxima-init.lisp")))
    (if ($file_search "maxima-init.mac") ($batchload ($file_search "maxima-init.mac")))

;; Voici les lignes
;; *********************************
    (defun main-prompt ()
      (format () "<EO>~%"))
    (setq $nolabels t)
;; *********************************
    (catch 'quit-to-lisp
      (in-package :maxima)
      (loop 
       do
       (catch #+kcl si::*quit-tag* #+(or cmu scl sbcl) 'continue #-(or kcl cmu scl sbcl) nil
	      (catch 'macsyma-quit
		(continue input-stream batch-flag)
		(format t *maxima-epilog*)
		(bye)))))))

(defvar *niv* nil)

(defun merror (sstring &rest l)
  (declare (special errcatch *mdebug*))
  (setq $error `((mlist) ,sstring ,@ l))
  (if (not *niv*) (format t "<BE>~%") (setq *niv* t))
  (and $errormsg ($errormsg))
  (cond (*mdebug*
	 (let ((dispflag t) ret)
	   (declare (special $help dispflag))
	   (format t " -- an error.  Entering the Maxima Debugger dbm~%~Enter `:h' for help~%<EE>")
	   (setq *niv* nil)
	   (progn
	     (setq ret (break-dbm-loop nil)) 
	     (cond ((eql ret :resume)
		    (break-quit))))))
	(errcatch  (error 'maxima-$error))
	(t
	 (fresh-line *standard-output*)
	 ($backtrace 3)
	 (format t "~%<EE>")
	 (setq *niv* nil)
	 (throw 'macsyma-quit 'maxima-error))))

;; Les deux fonctions qui suivent sont copiees-collees depuis les sources et legerement modifiees pour gerer les erreurs
(defun mread-synerr (format-string &rest l)
  (let (tem
	errset
	(file "stdin"))
    (errset
     (setq tem (file-position *parse-stream*))
     (setq file  (namestring *parse-stream*)))
    (when tem
      (format t "~%~a:~a:" file tem))
    (format t "<BE>~%Incorrect syntax: ")
    (apply 'format t format-string (mapcar #'(lambda (x)
					       (if (symbolp x)
						   (print-invert-case x)
						 x))
					   l))
    (cond ((output-stream-p *standard-input*)
	   (let ((n (get '*parse-window* 'length))
		 some ch)
	     (loop for i from (1- n) downto (- n 20)
		   while (setq ch (nth i *parse-window*))
		   do
		   (cond ((eql ch #\newline)
			  (push #\n some)
			  (push #\\ some))
			 ((eql ch #\tab)
			  (push #\t some)
			  (push #\\ some))
			 (t (push ch some))))
	     (format t "~%~{~c~}~%~vt^~%<EE>" some (- (length some) 2))
	     (read-line *parse-stream* nil nil))))
    (terpri)
    (throw-macsyma-top)))

(defun maxima-lisp-debugger (condition me-or-my-encapsulation)
  (declare (ignore me-or-my-encapsulation))
  (format t "<BS>~%~&Maxima encountered a Lisp error:~%~% ~A" condition)
  (format t "~&~%Automatically continuing.~%To reenable the Lisp debugger set *debugger-hook* to nil.~%")
  (throw 'return-from-debugger t))

;; la conversion des float en rationnels doit etre exacte 
(setq $ratepsilon 0)

;; redefinition des delimiteurs pour les matrices
;;(setq $rmxchar '|&!|)
;;(setq $lmxchar '|&!|)
(defun d-matrix (linear? direction h d)
  (d-vbar linear? h d (car (coerce "!" 'list))))

;; on modifie quelques noms de fonctions pour assurer la compat avec scilab
;; la prop reversealias sert a faire en sorte que cot(x) affiche cotg(x)
(defprop $cotg %cot alias)
(defprop %cot cotg reversealias)

(defvar $real)
(defvar $imag)
(setq $real '$realpart)
(defprop $realpart real reversealias)

(setq $imag '$imagpart)
(defprop $imagpart imag reversealias)

(defprop $det $determinant alias)
(defprop %determinant det reversealias)

(defprop |$Matrix| $matrix alias)
(defprop $matrix |Matrix| reversealias)

;; on cree %inf dans maxima
(defprop $%inf $inf alias)
(defprop $minf -%inf reversealias)
;; on definit une regle permettant de convertir -inf en minf
(meval `(($tellsimp),`((mminus),'$inf),'$minf))
(setq $simp nil)
(meval `(($tellsimp),`((mminus),'$inf),'$minf))
(setq $simp t)
(setq $rules '((mlist)))
;; on cree %nan
(defprop $%nan $und alias)

;; on modifie le display de l'operateur = pr le rendre utilisable avec eval dans scilab
;; puis on cree un operateur == identique a = (avec la meme precedence que =) 
;; qd il y a erreur cela signifie que la version de maxima est anterieure a
;; 5.17

(defmfun $== (x y) (meval `((mequal),x,y)))
(displa-def mequal dimension-infix  " == ")

(displa-def mnotequal dimension-infix  " <> ")
(defmfun $<> (x y) (meval `((mnotequal),x,y)))

(handler-case
 (progn
   ($infix "==" 80 80)
   ($infix "<>" 80 80)
   (defprop $inf $%inf reversealias)
   (defprop $und $%nan reversealias))
 (error () (progn
	     ($infix '&== 80 80)
	     ($infix '&<> 80 80)
	     (defprop $inf %inf reversealias)
	     (defprop $und %nan reversealias))))

;; inv est equivalent a ^(-1)
(defmspec $inv (x) (meval `((mncexpt),(cadr x),`((mminus),1))))

;; on fait une version postfixee de inv pour compabilite avec l'op \ dans Scilab puis
;; on definit _b_ version Maxima de \
(defvar $vni)
(setq $vni '$inv)
($postfix '$vni)
(defmfun $_b_ (x y) (meval `((mquotient),y,x)))
($infix '$_b_ 120 120 '$expr '$expr '$expr)

;; definition de l'operateur de feedback (/. dans Scilab)
(defmfun $_f_ (g k)
  (if (and ($matrixp g) ($matrixp k))
      (let ((__kxt (meval `((mnctimes),k,g))))
	(meval `((mnctimes),g,`(($invert),`((mplus),($identfor __kxt),__kxt)))))
    (meval `((mquotient),g,`((mplus),1,`((mtimes),g,k))))))

($infix '$_f_ 120 120 '$expr '$expr '$expr)

;; definition du produit de Kronecker de deux matrices
(defmfun $_k_ (A B)
  (meval `(($kronecker_product),A,B)))
($infix '$_k_ 130 130 '$expr '$expr '$expr)

;; definition de la puissance termes a termes de deux matrices (op .^ dans Scilab)
(defmfun $_p_ (A B)
  (meval `(($addmatrices),'mexpt,A,B)))
($infix '$_p_ 130 130 '$expr '$expr '$expr)

;; definition d'un op d'affectation qui soit evalue quand la fonction $string lui est applique
(defmspec $|_:| (expr)
  (meval `((msetq),(cadr expr),(caddr expr))))
($infix '$|_:| 20 180 '$any '$any '$any)

;; definition d'une fonction de creation de fonction
;; On peut surement ameliorer cette fonction...
;; Je prefere ne pas compiler la fonction car en cas d'erreur celle-ci est mieux geree
;; par exemple, f(x,y):=x+y, puis un appel a f(x) genere une erreur sur le nb d'args, 
;; par contre en version compilee cela genere une erreur Lisp (=> passage en mode debug) 
(defmspec $__scifun (expr)
  (let ((__kxt1 (cadr expr)) (__kxt2) (__kxt3))
    (setq __kxt2 (cdadr __kxt1))
    (setq __kxt3
	  (if (or (listp (car __kxt2)) (listp (car (last __kxt2))))
	      -1
	    (length __kxt2)))
    (setq __kxt2 (coerce (print-invert-case (meval `(($string),(caaadr __kxt1)))) 'list))
    (if (not (eq (car __kxt2) (car (coerce "&" 'list))))
	(setq __kxt2 (coerce (cons (car (coerce "&" 'list)) __kxt2) 'string))
      (setq __kxt2 (coerce __kxt2 'string)))
    (setq __kxt1 (meval __kxt1))
    (format t "<BC>~%")
;;    (meval `(($compile),(caaadr __kxt1)))
    (format t "<BO>~%~A~A~%" __kxt3 __kxt2)))

;; definition d'un op %o% tel que A %o% B=matrix(A,B) ou A,B sont des matrices (utile pour la fonction Matrix
;; dans Scilab)  
(defmfun $%o% (A B)
  (meval `(($addrow),A,B)))
($infix '$%o% 150 150)

;; definition d'un op %a% tel que A %a% B=[A,B] ou A,B sont des objets quelconques (utile pour la fonction List)
;;(defmfun $%a% (A B)
;;  (meval `(($append),A,B)))
;;($infix '&%a% 150 150)
;;(displa-def $|List| dimension-match "[" "]")

;; je m'assure que la variable *debugger-hook* est correctement positionner sur la nouvelle version de 
;; maxima-lisp-debugger
(setf *debugger-hook* #'maxima-lisp-debugger)

;; on ne memorise pas les labels => reduction de la conso de memoire
(setq $nolabels t)

;; on protege le caractere @ pour pouvoir l'utiliser ds des expressions
;;(meval `(($declare),'&@,'$alphabetic)) 

;; cette modif permet de reduire la conso de memoire (qui est un peu excessive)
#+gcl (setq si::*optimize-maximum-pages* nil)

;; il arrive a Maxima de poser des questions et d'attendre une reponse, il faut donc gerer la situation pour eviter 
;; un bloquage de Scilab et de laisser l'utilisateur repondre avec la fonction "answer"
;; j'ai dc fait un copier-coller depuis les sources et fait qques modifs
(defun retrieve (msg flag &aux (print? nil))
  (declare (special msg flag print?))
  (or (eq flag 'noprint) (setq print? t))
  (cond ((not print?) 
	 (setq print? t)
	 (princ "<BQ>")(mterpri)
	 (princ "<EQ>"))
	((null msg)
	 (princ "<BQ>")(mterpri)
	 (princ "<EQ>"))
	((atom msg) 
	 (format t "~a~%~a~a" "<BQ>" msg "<EQ>") 
	 (mterpri))
	((eq flag t)
	 (princ "<BQ>")(mterpri) 
	 (mapc #'princ (cdr msg)) 
	 (princ "<EQ>")
	 (mterpri))
	(t 
	 (princ "<BQ>")(mterpri)
	 (displa msg) 
	 (princ "<EQ>")
	 (mterpri)))
  (let ((res (mread-noprompt *standard-input* nil)))
       (princ *general-display-prefix*) res))

;; Voici qques fonctions pour LaTeXiser l'ouput de tex 
;; Recuperees depuis http://melusine.eu.org/syracuse/maxima/scripts/pmaxima/
(defprop ASINH "\\argsh" texword)
(defprop ACOSH "\\argch" texword)
(defprop ATANH "\\argth" texword)
(defprop INFINITY "\\infty" texword)

(defun tex-mquotient (x l r)
  (if (or (null (cddr x)) (cdddr x)) (wna-err (caar x)))
  (setq l (tex (cadr x) (append l '("\\frac{")) nil 'mparen 'mparen)
	;the divide bar groups things
	r (tex (caddr x) (list "}{") (append '("}")r) 'mparen 'mparen))
  (append l r))

(defprop $matrix tex-matrix tex)

(defun tex-matrix(x l r) ;;matrix looks like ((mmatrix)((mlist) a b) ...)
  (append l `("\\begin{pmatrix}")
	 (mapcan #'(lambda(y)
			  (tex-list (cdr y) nil (list "\\\\[1mm] ") "&"))
		 (cdr x))
	 '("\\end{pmatrix}") r))

(defun tex-int (x l r)
  (let ((s1 (tex (cadr x) nil nil 'mparen 'mparen));;integrand delims / & d
	(var (tex (caddr x) nil nil 'mparen rop))) ;; variable
       (cond((= (length x) 3)
	     (append l `("\\int {" ,@s1 "}{\\;\\mathrm{d}" ,@var "}") r))
	    (t ;; presumably length 5
	       (let ((low (tex (nth 3 x) nil nil 'mparen 'mparen))
		     ;; 1st item is 0
		     (hi (tex (nth 4 x) nil nil 'mparen 'mparen)))
		    (append l `("\\int_{" ,@low "}^{" ,@hi "}{" ,@s1 "\\;\\mathrm{d}" ,@var "}") r))))))


;;:lisp (defmspec $toto (m) (format t "~S~%" (cadr m)))