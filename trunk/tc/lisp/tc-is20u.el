;;; tc-is20u.el -*- Emacs-Lisp; coding:shift_jis -*-

;; Copyright (C) 2005 YAGI Tatsuya <ynyaaa@ybb.ne.jp>

;; Author: YAGI Tatsuya <ynyaaa@ybb.ne.jp>
;; Maintainer: Masayuki Ataka <masayuki.ataka@gmail.com>

;;; Code:
(require 'tc-is20)

(defvar tcode-isearch-enable-unification-search t
  "*2�o�C�g�����ŃT�[�`����Ƃ��ɁA���퓝������������B")

(put 'tcode-isearch-unification-char-table 'char-table-extra-slots 0)

(defvar tcode-isearch-unification-char-table nil
  "���퓝����������Ƃ��̓������[�����߂�\�B")

(defvar tcode-isearch-unification-list
  '(" �@" "!�I" "\"�h" "#��" "$��" "%��" "&��" "'�f"
    "(�i" ")�j" "*��" "+�{" ",�C" "-�|" ".�D" "/�^"
    "0�O" "1�P" "2�Q" "3�R" "4�S" "5�T" "6�U" "7�V" "8�W" "9�X"
    ":�F" ";�G" "<��" "=��" ">��" "?�H"
    "@��" "A�`" "B�a" "C�b" "D�c" "E�d" "F�e" "G�f"
    "H�g" "I�h" "J�i" "K�j" "L�k" "M�l" "N�m" "O�n"
    "P�o" "Q�p" "R�q" "S�r" "T�s" "U�t" "V�u" "W�v"
    "X�w" "Y�x" "Z�y" "[�m" "\\��" "]�n" "^�O" "_�Q"
    "`�e" "a��" "b��" "c��" "d��" "e��" "f��" "g��"
    "h��" "i��" "j��" "k��" "l��" "m��" "n��" "o��"
    "p��" "q��" "r��" "s��" "t��" "u��" "v��" "w��"
    "x��" "y��" "z��" "{�o" "|�b" "}�p" "~�P"
    "�B�" "�u�" "�v�" "�A�" "�E�" "�J�" "�K�" "�[�"
    "�A�" "�C�" "�E�" "�G�" "�I�"
    "�J�" "�L�" "�N�" "�P�" "�R�"
    "�T�" "�V�" "�X�" "�Z�" "�\�"
    "�^�" "�`�" "�c�" "�e�" "�g�"
    "�i�" "�j�" "�k�" "�l�" "�m�"
    "�n�" "�q�" "�t�" "�w�" "�z�"
    "�}�" "�~�" "���" "���" "���"
    "���" "���" "���"
    "���" "���" "���" "���" "���"
    "���" "���" "���"
    "�@�" "�B�" "�D�" "�F�" "�H�"
    "���" "���" "���" "�b�"
    (?�K "��") (?�M "��") (?�O "��") (?�Q "��") (?�S "��")
    (?�U "��") (?�W "��") (?�Y "��") (?�[ "��") (?�] "��")
    (?�_ "��") (?�a "��") (?�d "��") (?�f "��") (?�h "��")
    (?�o "��") (?�r "��") (?�u "��") (?�x "��") (?�{ "��")
    (?�p "��") (?�s "��") (?�v "��") (?�y "��") (?�| "��")
    (?�� "��"))
  "���퓝����������Ƃ��̓������[�����߂郊�X�g�B")

(defvar tcode-isearch-unification-reverse t
  "*non-nil �̎��� tcode-isearch-unification-list �̕�������ɋ�ʂ��Ȃ��B
nil �̎��� alist �̐擪�v�f�̕��������͂��ꂽ��������ʂ��Ȃ��B")

(defun tcode-isearch-unification-setup (&optional no-reverse)
  (interactive "P")
  (let ((tab (make-char-table 'tcode-isearch-unification-char-table))
	reg)
    (if no-reverse
	(dolist (cell tcode-isearch-unification-list)
	  (if (stringp cell) (setq cell (string-to-list cell)))
	  (setq reg (tcode-isearch-unification-make-regexp cell))
	  (aset tab (car cell) reg))
      (dolist (cell tcode-isearch-unification-list)
	(if (stringp cell) (setq cell (string-to-list cell)))
	(dolist (c cell)
	  (when (not (stringp c))
	    (setq reg (tcode-isearch-unification-make-regexp
		       (cons c (delq c (copy-sequence cell)))))
	    (aset tab c reg)))))
    (setq tcode-isearch-unification-char-table tab)))

(defun tcode-isearch-unification-make-regexp (l)
  (let ((c (car l))
	(ch-l nil)
	(st-l nil))
    (while (setq l (cdr l))
      (cond ((stringp (car l))
	     (setq st-l (cons (car l) st-l)))
	    ((memq (car l) '(?^ ?- ?\]))
	     (setq st-l (cons (string (car l)) st-l)))
	    (t (setq ch-l (cons (car l) ch-l)))))
    (if (null ch-l)
	(if (null st-l)
	    nil ;; character itself
	  (setq st-l (cons (string c) st-l))
	  (concat "\\(" (mapconcat 'regexp-quote st-l "\\|") "\\)"))
      (if (eq c ?^) ;; ?- or ?\] is not special as a first char in [...].
	  (if (null (cdr ch-l))
	      (concat "\\("
		      (mapconcat 'regexp-quote
				 (cons (string c)
				       (cons (string (car ch-l)) st-l))
				 "\\|")
		      "\\)")
	    (setq st-l (mapcar 'regexp-quote st-l)
		  st-l (cons (concat "[" (apply 'string ch-l) "]") st-l)
		  st-l (cons (regexp-quote (string c)) st-l))
	    (concat "\\("
		    (mapcar 'identity st-l "\\|")
		    "\\)"))
	(setq ch-l (cons c ch-l))
	(if (null st-l)
	    (concat "[" (apply 'string ch-l) "]")
	  (concat "\\(" (concat "[" (apply 'string ch-l) "]")
		  (mapcar 'regexp-quote st-l "\\|")
		  "\\)"))
	))))

(defun tcode-isearch-unification-char-to-regexp (c)
  (or (aref tcode-isearch-unification-char-table c)
      (char-to-string c)))

(defun tcode-isearch-unification-regexp-to-char (regexp pos)
  (let ((c (aref regexp pos)))
    (cond ((eq ?\[ c)
	   (aref regexp (1+ pos)))
	  ((not (eq ?\\ c))
	   c)
	  ((not (eq ?\( (setq c (aref regexp (1+ pos)))))
	   c)
	  ((eq ?\[ (setq c (aref regexp (+ pos 2))))
	   (aref regexp (+ pos 3)))
	  ((eq ?\\ c)
	   (aref regexp (+ pos 3)))
	  (t c))))

(defun tcode-isearch-unification-regexp-to-string (regexp)
  (let ((il (length tcode-isearch-ignore-regexp))
	(b 0) (l (length regexp)) (ret nil) c)
    (while (< b l)
      (if (eq t (compare-strings tcode-isearch-ignore-regexp 0 il
				 regexp b (+ b il)))
	  (setq b (+ b il))
	(setq c (tcode-isearch-unification-regexp-to-char regexp b)
	      ret (cons c ret)
	      b (+ (if (or (not (eq c (aref regexp b)))
			   (eq c ?\[))
		       (length (tcode-isearch-unification-char-to-regexp c))
		     1)
		   b))))
    (apply 'string (nreverse ret))))

(defun tcode-isearch-make-string-for-wrapping (string)
  (let ((string-list (and string
			  (string-to-list string))))
    (if (and tcode-isearch-enable-wrapped-search
	     (not isearch-regexp)
	     string-list)
	(mapconcat
	 (lambda (a)
	   (let ((s (char-to-string a)))
	     (cond ((and (string-match tcode-isearch-ignore-regexp s)
			 (> (match-end 0) 0))
		    tcode-isearch-ignore-regexp)
		   (tcode-isearch-enable-unification-search
		    (if (= (char-width a) 2)
			(concat tcode-isearch-ignore-regexp 
				(tcode-isearch-unification-char-to-regexp a))
		      (tcode-isearch-unification-char-to-regexp a)))
		   ((= (char-width a) 2)
		    (concat tcode-isearch-ignore-regexp s))
		   (t
		    (regexp-quote s)))))
	 string-list
	 nil)
      string)))

(defun tcode-isearch-remove-ignore-regexp (str)
  "�ϐ� `tcode-isearch-enable-wrapped-search' �� nil �łȂ��Ƃ��A
STR ���� `tcode-isearch-ignore-regexp' ����菜���B"
  (if (or (not tcode-isearch-enable-wrapped-search)
	  isearch-regexp)
      str
    (if tcode-isearch-enable-unification-search
	(tcode-isearch-unification-regexp-to-string str)
      (let (idx
	    (regexp-len (length tcode-isearch-ignore-regexp)))
	(while (setq idx (string-match
			  (regexp-quote tcode-isearch-ignore-regexp)
			  str))
	  (setq str (concat (substring str 0 idx)
			    (substring str (+ idx regexp-len) nil))))
	(tcode-regexp-unquote str)))))

(unless tcode-isearch-unification-char-table
  (tcode-isearch-unification-setup (not tcode-isearch-unification-reverse)))

(provide 'tc-is20u)
;;; tc-is20u.el ends here.
