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
(declaim (optimize (Speed 3) (Safety 0) (Space 0)))
#+gcl (si::use-fast-links t)

(defun $__poly2coef (P x)
  (let ((P ($rat P)) (hp ($hipow P x)) (l nil))
    (loop for i from hp downto 0 do (setq l (cons ($ratcoef P x i) l)))
    (cons '(mlist) l)))

(defmspec $__span2list (x)
  (cons '(mlist) (cdr (cadr x))))

(defmspec $__symb (expr)
  (meval `(($bfloat),(__convAllFloat2Bfloat (cadr expr)))))

(defmspec $__symr (expr)
  (meval `(($rat),(__convAllFloat2Rat (cadr expr)))))

(defun __convAllFloat2Bfloat (l) 
  (if (listp l) 
      (if (not (and (listp (car l)) (eq (caar l) '$&)))
	  (mapcar '__convAllFloat2Bfloat l)
	(meval `(($bfloat),l))) 
    (if (floatp l)
	(meval `(($bfloat),l))
      l)))

(defun __convAllFloat2Rat (l) 
  (if (listp l)
      (if (not (and (listp (car l)) (eq (caar l) '$&)))
	  (mapcar '__convAllFloat2Rat l)
	(meval `(($rat),l)))
    (if (floatp l)
	($rat l) 
      l)))

(defmacro mfn (nam)
  (let ((v (intern (format nil "~:@($__~A~)" nam)))
	(w (intern (format nil "~:@(%~A~)" nam))))
    `(defun ,v (x)
       (cond (($matrixp x)
	      (meval (list '($matrixmap) ',w x)))
	     (t
	      (meval (list '(,w) x)))))))

(defmacro mfnm (nam)
  (let ((v (intern (format nil "~:@($__~Am~)" nam)))
	(w (intern (format nil "~:@(%~A~)" nam)))
	(z))
    (setq z (list '(lambda) (list '(mlist) '$y) (list `(,w) '$y)))
    `(defun ,v (x)
       (cond (($matrixp x)
	      (meval (list '($matrixfun) ',z x)))
	     (t
	      (meval (list '(,w) x)))))))

(defun $__exp (x)
  (cond (($matrixp x) (meval `(($matrixmap),'$exp,x)))
	(t (meval `(($exp),x)))))

(defun $__expm (x)
  (cond (($matrixp x) (meval `(($matrixexp),x)))
	(t (meval `(($exp),x)))))

(eval-when (load)
	   (mfn "sin") (mfnm "sin")
	   (mfn "cos") (mfnm "cos")
	   (mfn "tan") (mfnm "tan")
	   (mfn "sinh") (mfnm "sinh")
	   (mfn "cosh") (mfnm "cosh")
	   (mfn "tanh") (mfnm "tanh")
	   (mfn "log") (mfnm "log"))

(defun $__det (x)
  (meval `(($determinant),x)))

(defmspec $trsp (mat)
  (meval `(($transpose),`(($conjugate),(cadr mat)))))