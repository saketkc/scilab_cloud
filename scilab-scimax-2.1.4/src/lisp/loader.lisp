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

(defun sm_getenv (name &optional default)
  #+CMU
  (let ((x (assoc name ext:*environment-list*
		  :test #'string=)))
    (if x (cdr x) default))
  #-CMU
  (or
   #+GCL (sys:getenv name) 
   #+Allegro (sys:getenv name)
   #+CLISP (ext:getenv name)
   #+ECL (si:getenv name)
   #+SBCL (sb-unix::posix-getenv name)
   #+LISPWORKS (lispworks:environment-variable name)
   default))

;; The environment variable SCIMAX_TOOLBOX_PATH is set by Scilab in the file etc/SciMax.start

(handler-case
 (let ((path (concatenate 'string (sm_getenv "SCIMAX_TOOLBOX_PATH") "/src/lisp/")))
       (load (concatenate 'string path "scimath"))
       (load (concatenate 'string path "scimax")))
 (error () (format t "Files scimath and scimax cannot be loaded~%<BD>~%")))
(format t "Files scimath and scimax loaded~%")