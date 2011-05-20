;;; try-etbl.el --- Try-Code extention table

(setq tcode-tbl [
"¢£¢£¢£¢£¢£¢£¢£¢£¢£¢£¢£¢£¢£¢£²Õ¢£¢£¢£Äå¢£¢£¢£¢£¢£µê¢£·¤±ìÈ©Âá¢£¢£¢£¢£¢£¢£¢£ÀË¢£¢£"
"¢£¢£¢£¢£¢£¢£¢£¢£¢£¢£¢£µÏ¢£¢£¢£¢£¶àÉÍ¹×ÎÄ¢£Å¥¢£¢£´þ°î¢£³À·÷¹²µ§´Ë¢£¢£¸Ý¢£²§¢£ºø·°"
"¢£¢£¢£¢£¢£¢£¢£¢£¢£¢£½¹±³¶´¢£¢£Åï±Ù¢£ÎÍ¢£åº¢£¢£¢£¢£¢£¢£¢£µò¼Ù¢£Ïª¢£¼Ð¼à¢£¢£¢£¢£¶î"
"¢£¢£¢£¢£¢£¢£¢£¢£¢£¢£¸ÌÃÑ¢£ÈÞ¢£ÈÁ¢£À¬¢£´èµà¢£º¦µç¢£¢£Æ§ÈÚÃ²¢£±²´Î¢£¼Û¢£¢£´¥¢£¹Õ³î"
"¢£¢£¢£¢£¢£¢£¢£¢£¢£¢£Êð¢£¢£ËÑ¢£¢£µñÁÆ¢£ÍÞËí¢£·¬³Ì¢£¢£¢£¢£¢£ºïÇÓÆ½¿»¢£ÅÂ¢£´À¢£ÏÎ¢£"
"¢£¢£¢£¢£¢£¢£¢£¢£¢£¢£¢£Îî¢£¢£¢£¢£¢£¢£¢£¢£Çå¢£ÅÜ¢£¢£¼ä¢£¿á²ýÀ¦¢£¢£Äß½Ü¢£Ä¿¾Ó¢£¢£ÅÇ"
"¢£¢£¢£¢£¢£¢£¢£¢£¢£¢£¢£¢£Äþ¢£¢£¢£¢£¢£¢£µ¹¢£áç·æÍåÇí¢£¢£ÃÆ±½¿ÏËúÈä¢£¸Ü¢£»Ý¢£¢£¾ö¢£"
"¢£¢£¢£¢£¢£¢£¢£¢£¢£¢£¢£ÃòÃàÌñÇù¢£¢£¢£¢£ÍÒ¢£¢£¢£»è¢£¢£¢£Éú¢£¢£½Ú¢£Ä½ÃÀ¢£¢£¢£¢£¢£¢£"
"¢£¢£¢£¢£¢£¢£¢£¢£¢£¢£¢£¢£ÊÐËÚ¢£°Ç¢£¢£ÁÎÊíº¿Åþ·«Êº·ßµ³ÍÙ¼¬Ä¤¢£½³ÆÖ¢£¢£´Ú¹¦¢£¿îÊ¯Âî"
"¢£¢£¢£¢£¢£¢£¢£¢£¢£¢£¢£ÄÃ¢£¢£¸¯Íö½±¿¯ÎºÎÝ¢£¢£¢£ÆÚ¢£¢£½ÇÇì¾îÌ¼¢£¢£¢£¹øÉæ¢£ÁÀË¨¢£²í"
"¢£Åé´×Å¯¢£¿Ý¢£¢£ÊæÊ¨²Û¹ó¢£¶ßÇ»¢£½ä¢£¾ÌÂó½·Ëì¢£¢£¼ß¢£¢£Îì¢£Ý¦´Ù²ã¢£À¨¢£ºË¸®¢£¢£Îñ"
"¢£ÁøÅã±Ú¢£¢£¢£¢£Îù¢£³´¹ØÁÂ¢£Ë×¢£¢£¶§Æ­Æ¶±¤´§Êï¢£¢£Èç¢£¢£äµÁñ¢£Äàº¨¿ø¢£Éí¢£¢£¢£ÂÌ"
"¢£ÏÐ²û¢£´÷¢£¼Ñ¢£ËÛ¾¬ÉêµÔÁÐ¢£³å¢£Ãê¢£¾¸¢£¢£¶þÂÆÌ¥½Þ¢£²É¢£¢£¢£¶³¿ñÇö¹àÎÈ¢£¾¢¢£¢£Ä¯"
"¢£Ê½¢£î±ÈêÀûÂÚÌÞÉÒ¢£Íò¢£ÈíÎÑÁ¹¢£ÆÌÇ¦¹Ú¢£ÏÆ¢£·õ¢£¢£¢£¢£¾½ºÄÆõÃä¢£Êø¢£Á¦¿¬À«·Ì´öÃâ"
"¢£ÄâÎÃ¶ò¢£¢£´­¢£Áú¢£¶®¸ÏÎ¡¢£¢£¢£²Ô¢£¢£½ÊÌ¨Ã¸¶ó¢£Î³¢£¢£¢£¢£ÁÔÇÌ¢£°ù¿ì¢£¢£¸°¶Ô¢£ÁÞ"
"¢£ÈùÇÞ¿òÈ­½­¢£¢£À¡Ì¡ÁË¢£¢£¢£¢£°Ó¢£ÌùÏ­¾éÍç±ðÉë·ð½áÎïÀ§Ð§ÅâÁ©¢£Î·³ì¢£¢£¢£½Æ¢£Ë¤Éå"
"¢£·®¸ô½ù¢£Åà¢£¼ôÏÍ¢£¢£ÀÀ¢£¢£¶ù·ÒÍ«»£Ë»¢£Ì¯ÇæÄû¢£¢£Çñ¢£¾ÇÎ÷¢£¢£¹Â¢£¢£Âõ¢£¢£´ý¢£¢£"
"Ìû¹Î³ú¢£ÎÒ»é³¸³í¢£¢£ÁåÍ¶¸¹Å½¿É¢£¶ÇÃÒ¢£Â£¢£¢£Èè¢£¢£¢£ÈÂ¢£¼ì±ú¢£¢£¢£¢£³áÃá¿±Ï£¢£¸Û"
"Êú¢£¢£¼üÌ²»ç¢£¢£¢£¢£ÄÒ¢£¼×ÄñÌÇÝ¨¢£»ø¢£¢£¢£¢£¢£»Ã¼¥Àç¢£²¥¶Ï¢£¹ÊÄç»Ç¢£Â¯ÊÉ¢£¢£³¯ÌÕ"
"¢£¢£¢£¢£È³Å¦³éÌ·º«Àø¢£¢£ÄéÂÛ¢£¿Ô¸ë°®Ë¶Êé¾Û°Î¢£¢£¢£Îô³ÔÇÑ¢£ÃÅ·ýËâ½¥ÈåÇ¢Äè¢£ÆçÄÁ¢£"
"¢£¢£ÇÚ¸¬¢£Ï°¢£·Ü¢£¢£³Ï¢£ÂÁ±ñ½®ÍÇ¢£ÌÔÀð¾ûÅ÷¢£º§´«¿µ»¹¢£Îí¢£¢£¢£¢£³Ö¢£ÇÆ¢£±î¢£¢£¢£"
"¢£µ¶¢£ÈÑÇû¢£¢£¢£¢£ºñÆ¿»ó¢£¢£·ü¢£é¯ÄÄ³¶Ï§Å¡½Î´¾Ã¥ÅÍ¢£¢£Ã¡°í²î¢£¢£¢£¢£¾úÏ¤¢£¢£Ë§¢£"
"¢£ËÅâ×¢£Ç­¢£ÍÉµ©¸ç»¤ÀÍ¢£Åû·Ñ¢£Ýµ¢£¢£½À¢£¢£¾í³ç¢£»´¢£¢£¢£¸ê¢£¢£µ··åÈ¼¢£¢£Ëá¢£»ÌÉ¤"
"ÄÙ¢£¢£¢£Ê®¢£Æß¢£¢£Éºµ½¢£Á¢¢£±ê¢£¢£¢£¾©¢£ÂÅÍ±Ë¥ÇÝÌø¢£¢£ÅÉ¢£¢£¢£¢£¢£º°½Í¢£¢£¿õÍë¹ö"
"¢£°â¢£°ÒÊ¾¢£¾ê·¡ËÐ¢£¢£¢£´²¢£Ä°Éèº¶¢£¹Æ¢£½Ó¢£¢£¢£º»¢£¢£¢£¢£¢£¢£¹µÀ·¢£¢£¢£Ë¢¢£Íª¢£"
"¢£¿×¢£¢£ËÞ¢£¢£»üÉâ¢£±Ö¿ëÎåÊ×Ä¶Ì¸¢£¼¿¢£Í£¢£¢£¢£Û£¢£¢£¢£·Ö¢£ÏÅ¸¼¢£¢£¢£Î½¢£¹¿¢£ÂÙ¸ä"
"¢£¢£Ï¼¢£¢£¶«â²Áç¢£¢£¹±Ä±ºÞË¸³Í¢£¿¡´Ï¢£¿ÂÍ¡¢£¢£¢£Î²ºÜ±ô¢£¢£¢£È±¢£¢£´®²ÂËÍ¸é¶¸Â÷´Ì"
"ÀÉ¢£¢£¾¤¢£¢£¿ç´ªÅ±¢£Áµ¢£¢£ÏÑ¼ÄÃýºÃ¢£¢£²Í¢£¢£Ëæ¢£¾Ù¢£¢£¢£¢£¹Å¢£»··¹ÄÆº²Éó¢£¢£¢£¢£"
"¢£¢£¸¸¢£¢£¢£¼ñº­¶×¢£¢£ÈÒÍÏ¼îÌÃ¢£¢£¢£Å©¶öµÓÁôÃÞËµÛ©³êÂ¥¾²ÝõÀÛËßÉÐ¿ã±ÔÄ·¢£àú¾×·ÀÍï"
"Êö¢£ÆðÆÞÈâ¢£¢£Ç¨Åñ¢£ÂìÁ¼¢£Ä©¢£»Û¢£Îð¹ä¢£²ÇÃÃÏÇ¢£¢£Ë·¢£ºØ²×¢£±¾¢£¢£¢£¢£Á²¹ÙÄÚ¢£µ±"
"¢£¢£ÉÓ³ë¢£¢£¢£¢£¢£ÀàæÛ¢£½å¢£¢£¢£·ø¢£¢£Ë«¢£ÌÖ¢£¢£¢£ÀÂ´½Æú¢£¢£¢£¸â¢£¢£¢£Â±µ°¢£·ª¢£"
"¢£É±±Ü¼´¢£¢£ºÕ¢£¹£¢£²ü¢£¿Ò¢£»±³§¢£¢£µ¾Æ©Äî¢£¢£¢£Æ¥´Ó¢£¢£½ÃË°¢£¢£´¸¢£¢£³ºËä¢£¢£¢£"
"¢£¢£±¬Áò¢£¿ßËÂßõ¾ü¢£Äù¢£¢£¢£ÂÑé¬¢£¢£°ÞÌö¢£Ë¹¢£ËÏ¢£¢£¢£ÌÛ¢£ËÄÀÆ¾Í¢£ÇÕ¢£Ç¥¾£ÌËÀÝ¢£"
"¢£¢£¢£Éõ¢£¢£¶Å¢£¶Óµ÷±Ó¾âÉÝ¢£¢£²ù¢£ÍÈ¢£ÃÜÌ»ÐíÍµ¿£¢£¿Å¢£¢£Ë¦¸ã¢£¢£Éä¢£È¶»ðÍ©¢£ÎÞ¢£"
"¢£¢£¢£ÃÕÏ³¢£¢£¢£¢£Ëà¢£Ç«¢£¢£¢£¹é¢£ÊÊ¢£ÐªÎö¿«ËÝ¢£Ã¶¢£ÈÊ¢£Â·Áº·ÆÄ¨¢£»ãÉîÊ·´òÂÄ¢£¶Ý"
"¢£¢£é®½ö¢£¢£¢£¢£¢£¢£ÁÝ¢£º¾Þú¢£¾ôÍã¢£¢£Áû²±¾¶³ÅÌÑÌ×¢£¢£¢£¾´¶º´Õ¢£ËÁ¢£Ï²¢£ÃïÁÅ¿ï¶ã"
"¢£¢£ÁþÇº¢£¼í²ø¹´¢£ÇïÍô¢£ºÏ¢£´¢¢£¢£¢£Íù½ÛºÌ¢£¢£¢£¢£Á­ÉÑ¢£¢£¢£Ë³ËõËÃ¢£¢£¢£¢£¼Ø¿°ÂÕ"
"¢£ÎõÄ¦°ò¿Ç¢£¢£Â½Åí¢£ºû¢£¢£¢£ÁÓÇÁ¶Ä¢£Âú¢£¢£µ¼ºéÍÀ¢£¢£¢£¢£¢£¢£¢£¢£Åë¢£¾É²ô¢£¢£µ²Áï"
"¢£¢£ÃÔ¢£¢£¢£¢£¢£¿æ½Á¢£Á¶¢£¢£ÉÞÊ¤¢£¢£¢£¢£ÅÛ¢£¢£ÏÈ¢£¢£Ä¼¢£¢£Æ¹¢£µÍ¢£¢£µºÀÒÈõ¢£¢£Ìã"
"¢£Å³Ç´Ãª¼À¢£¢£»òÊ¶¼ÏÆÆÀòÇõ¢£¢£Ã¢Î´·þ¢£ÍÊ·ÔÌæ°ï¢£¢£¢£¢£¢£¢£ÌþÉÄ¢£²Ò½ïÌèÄú¢£¢£¢£¢£"
])

(setq tcode-non-2-stroke-char-list
      (mapcar (function
	       (lambda (str)
		 (tcode-string-to-char str)))
	      '("¢£" "¢¡" "¡þ")))

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
