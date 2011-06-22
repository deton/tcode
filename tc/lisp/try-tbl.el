;;; try-tbl.el --- Try-Code dependent data

;; Copyright (C) 1989--2001 Kaoru Maeda, Yasushi Saito and KITAJIMA Akira.

;; Author: Kaoru Maeda <maeda@src.ricoh.co.jp>
;;	Yasushi Saito <yasushi@is.s.u-tokyo.ac.jp>
;;      KITAJIMA Akira <kitajima@isc.osakac.ac.jp>

;; $Id: tc-tbl.el,v 1.10 2002/12/18 02:03:31 kitajima Exp $

;; This program is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 2 of the License, or
;; (at your option) any later version.
;;
;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with this program; if not, write to the Free Software
;; Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.

;;; Commentary:
;;
;; set following variables:
;;	tcode-input-method
;;	tcode-transparent-mode-indicator
;;	tcode-tcode-mode-indicator
;;	tcode-alnum-2byte-tcode-mode-indicator
;;	tcode-hiragana-mode-indicator
;;	tcode-katakana-mode-indicator
;;	tcode-tbl
;;	tcode-non-2-stroke-char-list
;;	tcode-another-table
;;	tcode-special-commands-alist
;;	tcode-mode-help-string
;;	tcode-stroke-file-name
;;      eelll-text

;;; Code:

(require 'tc)

(setq tcode-input-method 'trycode)

(setq tcode-transparent-mode-indicator "--"
      tcode-tcode-mode-indicator "TC"
      tcode-alnum-2byte-tcode-mode-indicator "��"
      tcode-hiragana-mode-indicator ""
      tcode-katakana-mode-indicator "")

(setq tcode-tbl [
"���������������������������������õ�ݤ����������Ͳ�����������ʳ�����ڿ���"
"���������������������������Ⱦ�����յ����������αױ�������������ʢ���������"
"�����������������������������ü˴��������Ƶѵ����̷ʽ褼���������վ����Ϲ���"
"���������������������ɸز������۶찵�øǹ������ˮ�񻨴���Ĭ¡�μ��ɷ㴳ɧ����"
"����������������������˿���ιݻ���̩�벡��껽�򼧽����������ĺ������¬�컶����"
"���������������������������ܶ�©�����뾼�������찡����ūƸȪ�ؾ˼����ù�������"
"��������������������ü��͹��������������Ƚ����æ������º�Ḩ�︻���׶���»ɶ��"
"�������������������������������Ѿ�ξ��޽�����˽�߳���������ľ�εʻ����Ũ�ϳ�"
"���������������������̰��һ����ǵǡ��Ģ�����������ϲγ����������ð������Ƽ���"
"������������������������ɼ�ʰ���ζάθ��§¸�ܵ������ﷻ����˳������鹧��ǳ�µ�"
"�򰥲˷��Ļ���ú����̹���������̳�糫������̵�����������������Ū����"
"�������Ȳ���ܰ��ٵ쳵���ͳ�७����ɴ�ڲ���������ʬ����饢���΢�ﺹ�եפХ��"
"���������򹶾�Ʈ��ͼ���ξ��! ��Х����ݰƶʾ����7 ��( �Ȥ콾���������⹩Ȭ�Ƹ�"
"�°ϳӷ������Ӱ�®������ǽ����������ȯΩ������¦�Ф���������Ŭ��汧���̾���"
"�Űô����͵�������ߺٸ����ڤ�ʶ���½����򤰴���夯8 ��ǯ������򿭥���������"
"��ħ������ɡ����������������ɾ��ˡ��Ϻ������Ǥ��˭������μ�������Ψ����û�����"
"���ϸ���ʣɹ�������·�������������ǵ޸��ѿ������ݽ������²��۹�ι���˱󥩾�����"
"���ݻ�ɮΤ�����������Ὠ��չ���ī�Υ����¸�ϫ���򥻱�����ë��Ƴǧ����������ǰƯ"
"��Ǽ��ƨ���л��������������㸺�����񥣵մ������������ǶХ㻦�鲿���̼����Ǹ���"
"������ٺ�������˸ι������̵�в��������������ͥ���ʸ����������ؼ�¨������"
"�Ѱֲ��ɩ����Ļ�ž�����������楹�⤪��ﲬ��ʿ�3 �ȡ��Ƥ�ҹ��̹͸��ÿͻ�����"
"�԰ٳݷ�ɳŵ���������ͺ���վޤ������������Լ�ʡ������줬�ڵ�¢��¤����������"
"�ױ����������ش�ʩ���ػ��³����4 ) �������ڳ�ͻ�������5 1 �����Ⱦ����ޥ�Ļ�"
"�ڱ��Ÿ�ʰ��������ɸ���ʼ����Ф���6 �ط��ͽ�ڰ��ӡ���0 ��2 ��������������������"
"�ݰߴ�������;�ٸ��Ż׽ѹ���ʹ�ܤ���⥷�ѥܲü����ǤϤˤʤ�ž�����ȵ�Ȼ���Ĺ��"
"���ٹ����ƴ��꼢�����½���ϩ�ۤ����ʪ��ɬ�ְ������߿�ƣͭ��ʼ������۶���ʿ��"
"���Ἧ���������ź���ĥ���������������͢������ήϢŴ���ϥ��ӱʿ����ɻ䥴�迮��"
"���˻ﾷ���߿��Ű̦�����Ź����ú���������̣����Ǹ���¾����������̿¼��������"
"����̴������������������ƶ̱���̱������­���۴Ѹ�����ŷ��ʸ�ĵһ������δ������"
"�ٷ�����뷱��Ʒƫ�ײ��ֶ����ʴ����ж������ʱҳ۽¼�ǽ�Ĥ����������ᳰ�ƥ��"
"�����������������������ϼ�����Ź��Į��۷�ͧ´�鴷�ԥɱ߾�������ڴ�% ��ƻ������"
"��ɲ�����뵪�˷���Ȩ����ˬͻ�������������ܰ˵ᵻ���̥�����ƱȽ�����ͥ������ᥦ��"
"������˴��˼�Ӽ�°�����λ��Ǯ����ϻ��ư��Ƭ�۹������꡽����ѵȤ����Թ�������"
"�������İ�����Υ���붲�Ķ���־�˻�������ľ�ҿ���9 �Ҹ��⽵�����ɰѲ����ܻ�"
"����Χ�Ĳ����ϳ˱���²��̤������༷���̳����˾�����Ĳ������پʱ�ʡ�赤�䲼�Գ�"
"�����н�ϯ�������ұ���ģ���ץ������İ��Ų�Ͽ���۾ûٶ���ɽ���޵󸱥��ȥ俴���պ�"
"������ǾϷ����«��̮�ƴ��ã�Ƕ�˺Ƥ�˴Ŀ������Ի���¿���ϸ�Ƿ���ܳ��Ⱥƥ͡�����"
"α���Ʀ�Ƿ��¹��ͦ������񼺻ʷ޲ڵ��亸�ֱֲɥ�Ĵ���ݷ�߽�ʧ��˾��ķ��׿���"
"�ؾ�? �����޽����ӱդ彤���������±������Ÿ�ٷ�ï���������������Ž�ͷ�ͤҤ��Ϳ"
"�Թ���Ȣ�����Ĳʴ����ȴ���ؿ�ôΦ��������Ȼ�Ʋ��ʥ̱ļ�������ñ�ȥԾ�ȿ��"
])

(setq tcode-non-2-stroke-char-list
      (mapcar (function
	       (lambda (str)
		 (tcode-string-to-char str)))
	      '("��" "��" "��")))

(setq tcode-another-table nil)

(setq tcode-special-commands-alist
      '(((0 0) . (lambda () (tcode-show-tables nil nil)))
				       ; 11 : LLɽ��ɽ��
	((0 9) . (lambda () (tcode-show-tables nil t)))
				       ; 10 : LRɽ��ɽ��
	((9 0) . (lambda () (tcode-show-tables t nil)))
				       ; 01 : RLɽ��ɽ��
	((9 9) . (lambda () (tcode-show-tables t t)))
				       ; 00 : RRɽ��ɽ��
	((1 1) . tcode-start-jiscode)
				 ; 22 : JIS ������ɽ����
	((2 2) . tcode-toggle-alnum-mode)
				; 33 : 1-2�Х����ڤ괹��
	((2 1) . tcode-switch-variable)
				   ; 32 : �������Υȥ���
	((3 3) . (lambda ()
		   (tcode-display-stroke-sequence tcode-last-help-char-list)))
					; 44 : �إ��
	((4 4) . (lambda () (tcode-query-stroke (point))))
					; 55 : �إ��
	((6 6) . tcode-bushu-begin-alternate-conversion)
			     ; 77 : postfix ��������Ѵ�
	((7 7) . (lambda () (tcode-transpose-strokes nil)))
				; 88 : transpose-strokes
	((8 8) . tcode-clear)
		     ; 99 : ��������Ѵ��ʤɤΥ���󥻥�
	((26 23) . tcode-bushu-begin-conversion) ; jf : ��������Ѵ��γ���
	((25 23) . tcode-kuten)
	((26 22) . tcode-touten)
	((23 26) . tcode-mazegaki-begin-conversion)
				      ; fj: �򤼽��Ѵ�
	((9 8) . tcode-mazegaki-begin-alternate-conversion)
			  ; ���֡����֤��դθ򤼽��Ѵ�
	;; ��18�פ��ɤ�1ʸ���θ��ַ��򤼽��Ѵ�
	((0 7) . (lambda ()
		   (tcode-mazegaki-convert 1 current-prefix-arg)))
	;; ��28�פ��ɤ�2ʸ���θ��ַ��򤼽��Ѵ�
	((1 7) . (lambda ()
		   (tcode-mazegaki-convert 2 current-prefix-arg)))

	;; ��38�פ��ɤ�3ʸ���θ��ַ��򤼽��Ѵ�
	((2 7) . (lambda ()
		   (tcode-mazegaki-convert 3 current-prefix-arg)))

	;; ��48�פ��ɤ�4ʸ���θ��ַ��򤼽��Ѵ�
	((3 7) . (lambda ()
		   (tcode-mazegaki-convert 4 current-prefix-arg)))

     ;; ��58�פǳ��Ѥ������оݤȤ������ַ��򤼽��Ѵ�
	((4 7) . (lambda () (tcode-mazegaki-convert nil t)))

	;; ��29�פ��ɤ�2ʸ���γ��Ѥ������оݤȤ���
	;; ���ַ��򤼽��Ѵ�
	((1 8) . (lambda () (tcode-mazegaki-convert 2 t)))

	;; ��39�פ��ɤ�3ʸ���γ��Ѥ������оݤȤ���
	;; ���ַ��򤼽��Ѵ�
	((2 8) . (lambda () (tcode-mazegaki-convert 3 t)))

	;; ��49�פ��ɤ�4ʸ���γ��Ѥ������оݤȤ���
	;; ���ַ��򤼽��Ѵ�
	((3 8) . (lambda () (tcode-mazegaki-convert 4 t)))

	;; ��59�פ��ɤ�5ʸ���γ��Ѥ������оݤȤ���
	;; ���ַ��򤼽��Ѵ�
	((4 8) . (lambda () (tcode-mazegaki-convert 5 t)))))

(setq tcode-mode-help-string "\
T�����ɥ⡼����Υ������ϼ��ΤȤ��ꡣ
   jf : ��������Ѵ��⡼�ɤ����롣jf���Ǥ�³����ȺƵ�Ū����������Ѵ���
	�Ԥ����Ȥ��Ǥ���(see variable `tcode-use-postfix-bushu-as-default')��
   fj : �򤼽��Ѵ���Ԥ�(see variable `tcode-use-prefix-mazegaki')��
   00, 01, 10, 11 : T�����ɤ�ɽ��ɽ������(0������1����)��
   22 : JIS �����ɰ���ɽ�ˤ�����ϡ�
   32 : ������, . ���ڤ��ؤ��롣(see variable `tcode-switch-table-list')��
   33 : T������ɽ�ˤ���ѿ����������ʸ�������ɤ�1�Х��ȡ�2�Х����ڤ��ؤ���
   44 : ľ����ɽ�������Ǥ������ɽ�����롣
   55 : �ݥ���Ȱ��֤ˤ���ʸ�����Ǥ�����ɽ�����롣
   58 : ���Ѹ��ͥ�褷�Ƹ򤼽��Ѵ���Ԥ���
   77 : �ݥ�������ˤ���2ʸ������������Ѵ���Ԥ���
   88 : �ݥ���Ȱ��֤ˤ���ʸ����ե��ȥ�����������(��: ̣->��)��
        �����Ǥϥݥ���Ȥ�ľ����ʸ�����Ѵ����롣
   99 : �򤼽��Ѵ��⡼�ɤ���������Ѵ��⡼�ɤˤ������ˡ�
	��������������󥻥뤹�롣�ޤ����إ�פ�ä���
   [1-4]8, [2-5]9: ʸ��������ꤷ�Ƹ򤼽��Ѵ���Ԥ���
   \\[toggle-input-method] : T�����ɥ⡼�ɤ�ȴ���롣

���Ƶ�ư���줿���ˤϡ�`tcode-ready-hook' ��¹Ԥ��롣
�ޤ�����ư������٤�`tcode-toggle-hook'��¹Ԥ��롣")

(setq tcode-stroke-file-name (concat tcode-data-directory "trycode.st"))

(setq eelll-text "EELLLTXT")

(setq tcode-key-num 41
      tcode-ext-keys '(32))

(let ((i 0))
  (while (< i 40)
    (setq tcode-special-commands-alist
	  (cons (cons (list i 40)
		      'try-code-verbose-stroke)
		tcode-special-commands-alist))
    (setq i (1+ i))))

(defun try-code-verbose-stroke ()
  (interactive)
  (let ((l tcode-this-command-keys) x)
    (while (cdr l)
      (insert (car l))
      (setq l (cdr l)))))

(setq tcode-special-prefix-alist
      '(((40) "try-etbl" "��" "��" "��" "��")))

(setq tcode-stroke-to-string-function 'try-code-stroke-to-string)

(defvar try-code-stroke-to-string-use-association 'stroke)

(defun try-code-stroke-to-string (stroke)
  (let ((dat (tcode-stroke-prefix-match stroke)))
    (if (null dat)
	(tcode-stroke-to-string stroke)
      (let ((x (and try-code-stroke-to-string-use-association
		    (tcode-decode (cdr dat)))))
	(if (not (and (eq 'complete (car x))
		      (char-or-string-p (cdr x))))
	    (setq x nil)
	  (setq x (cdr x))
	  (if (not (stringp x))
	      (setq x (char-to-string x))))
	(concat (nth 2 (car dat))
		(if x
		    (if (eq try-code-stroke-to-string-use-association 'stroke)
			(concat x (tcode-stroke-to-string (cdr dat)))
		      x)
		  (if (equal '(40) (cdr dat))
		      (tcode-key-to-help-string 40)
		    (tcode-stroke-to-string (cdr dat))))))
      )))

;;; try-tbl.el ends here