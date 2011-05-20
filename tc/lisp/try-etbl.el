;;; try-etbl.el --- Try-Code extention table

(setq tcode-tbl [
"�����������������������������բ������墣���������ꢣ����ȩ�ᢣ�������������ˢ���"
"�����������������������Ϣ����������͹��Ģ�ť����������������ˢ����ݢ���������"
"��������������������������������٢��͢�庢���������������٢�Ϫ���мࢣ��������"
"�����������������������Ѣ��ޢ�����������ࢣ���碣��Ƨ��ò�����΢��ۢ��������ճ�"
"���������������������𢣢��Ѣ������Ƣ����������̢�������������ƽ�����¢������΢�"
"��������������������������������������墣�ܢ����䢣����������߽ܢ�Ŀ�Ӣ�����"
"������������������������������������������������������Ʊ������䢣�ܢ��ݢ�������"
"���������������������������������������Ң������袣�����������ڢ�Ľ��������������"
"���������������������������ڢ��Ǣ�������������ʺ�ߵ��ټ�Ĥ�����֢����ڹ�����ʯ��"
"�����������������������â�����������κ�ݢ������ڢ��������̼���������梣��˨����"
"�����ů���ݢ�����ʨ�۹󢣶�ǻ���䢣�����좣���ߢ����좣ݦ�ٲ㢣�����˸�������"
"������ڢ����������������¢��ע�����ƭƶ��������碣������ຨ��������������"
"���в��������Ѣ��۾�����Т��墣�ꢣ����������̥�ޢ��ɢ��������������Ȣ�������į"
"��ʽ������������Ң�������������Ǧ�ڢ��Ƣ������������������䢣�����������̴���"
"�����ö򢣢�������������Ρ�������Ԣ�����̨ø��γ�����������̢����좣�����Ԣ���"
"�����޿�ȭ��������̡�ˢ��������Ӣ���ϭ�������������Ч������η�좣�����Ƣ�ˤ��"
"�����������ࢣ���͢�������������ͫ��˻��̯���������񢣾��������¢���������������"
"���γ����һ鳸��������Ͷ��Ž�ɢ����Ң�£�����袣�����¢���������������῱ϣ����"
"��������̲�碣�������Ң�������ݨ���������������ü��碣���Ϣ�����Ǣ�¯�ɢ�������"
"��������ȳŦ��̷�����������ۢ��Ը밮˶��۰΢����������Ѣ��ŷ��⽥��Ǣ�袣������"
"�����ڸ���ϰ���ܢ����Ϣ������Ǣ�������������������������������֢��Ƣ������"
"��������������������ƿ�󢣢�������ĳ�ϧš�δ�å�͢���á�����������Ϥ����˧��"
"�����ע�ǭ���ɵ��绤�͢����Ѣ�ݵ�������������碣���������ꢣ������ȼ�����ᢣ��ɤ"
"�٢�����ʮ���ߢ���ɺ���������ꢣ����������ͱ˥���������ɢ������������͢��������"
"���⢣��ʾ���귡�Т���������İ�躶���Ƣ��Ӣ�����������������������������ˢ��ͪ��"
"���ע����ޢ������⢣�ֿ�����Ķ̸������ͣ������ۣ�������֢��Ÿ�������ν�������ٸ�"
"����ϼ��������碣����ı��˸�͢����Ϣ���͡������β�ܱ�������ȱ���������͸鶸����"
"�ɢ����������紪ű���������Ѽ����â����͢����梣�٢��������Ţ������ƺ��󢣢�����"
"�������������񺭶ע������ϼ��â�����ũ��������˵۩��¥���������п��ķ�����׷���"
"���������⢣��Ǩ��������ĩ���ۢ���䢣�����Ǣ���˷���زע����������������ڢ���"
"�����ӳ뢣�����������ۢ��墣����������˫���֢������´����������⢣����±��������"
"��ɱ�ܼ������բ����������Ң�����������Ʃ�����ƥ�Ӣ�����˰�������������䢣����"
"�������򢣿�������������������鬢���������˹���Ϣ������ۢ����ƾ͢��բ�ǥ�����ݢ�"
"�������������Ţ��ӵ��Ӿ��ݢ��������Ȣ���̻��͵�����Ţ���˦�㢣���䢣ȶ��ͩ���ޢ�"
"��������ϳ���������ࢣǫ�������颣�ʢ�Ъ�����ݢ�ö���ʢ�·����Ĩ������ʷ���Ģ���"
"����鮽��������������ݢ����������㢣�������������ע����������բ�����ϲ�����ſ��"
"������Ǻ�����������������Ϣ������������ۺ̢����������Ѣ�����˳���â��������ؿ���"
"����Ħ��Ǣ���½�����������������Ģ������������������������������뢣�ɲ���������"
"�����Ԣ����������������������ʤ���������ۢ����Ȣ���ļ����ƹ���͢���������������"
"��ųǴê��������ʶ������������âδ�����ʷ����������������Ģ��ҽ�������������"
])

(setq tcode-non-2-stroke-char-list
      (mapcar (function
	       (lambda (str)
		 (tcode-string-to-char str)))
	      '("��" "��" "��")))

(setq tcode-special-commands-alist
      '(
	((40) . try-code-space)
	((0 0) . (lambda () (tcode-show-tables nil nil)))
	((0 9) . (lambda () (tcode-show-tables nil t)))
	((9 0) . (lambda () (tcode-show-tables t nil)))
	((9 9) . (lambda () (tcode-show-tables t t)))
	))

(defun try-code-space ()
  (interactive)
  (call-interactively (or (lookup-key tcode-mode-map " ")
			  'self-insert-command)))

;;; try-etbl.el ends here
