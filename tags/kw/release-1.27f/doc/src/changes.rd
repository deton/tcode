=begin

== �u����Win 1.26�v����̕ύX�_

�u����Win�v�o�[�W���� 1.27 �ł́A�ݒ�t�@�C���̏������ύX����Ă��܂��B

�u����Win�v�o�[�W���� 1.26eb (kw126eb-20020505.zip) �₻��ȑO�̔�
(�ȉ��A�u1.26 �Łv�Ƒ���) �ŁA
�ݒ�t�@�C�������J�X�^�}�C�Y���Ďg�p����Ă������́A
�ȉ��̋L�q���Q�l�ɁA�ăJ�X�^�}�C�Y���Ă��������B

�ݒ�t�@�C���̕ύX�_

* �y�����z
  1.26 �łł͓Ǝ��`���ł������A1.27 �łł� INI �`���ɂȂ�܂����B
  ���ɁA�t�@�C���̐擪�ɁA�Z�N�V������ (({[kanchoku]})) �̋L�q���K�v�ł��B
  �܂��A�R�����g�� (({#})) �ł͂Ȃ��A (({;})) �ŋL�q���Ă��������B
* �y�I�v�V�����z
  * �y(({USEWMCHAR}))�z
    1.26 �łł́AWM_IME_CHAR �̂����� WM_CHAR ���w�肷��I�v�V�����ł������A
    ���̃I�v�V�����͔p�~����܂����B
    ���o���b�Z�[�W�́A�f�t�H���g�� WM_CHAR ���p�����܂��B
    WM_IME_CHAR ���g�p����ꍇ�ɂ́A
    (({useWMIMECHAR=1})) �܂��� (({outputMethod=1})) �Ǝw�肵�Ă��������B
  * �y(({SHOWHELP}))�z
    1.26 �łł́A�����w���v��\������I�v�V�����ł������A
    ���̃I�v�V�����͔p�~����܂����B
    �����w���v�͏�ɕ\������A��\���ɂ��邱�Ƃ͂ł��Ȃ��Ȃ�܂����B
  * �y(({FORCEBS}))�z
    (({hardBS})) �Ƀ��l�[������܂����B

  �ڂ����� ((<�����ݒ�t�@�C��>)) ���Q�Ƃ��Ă��������B



�e�[�u���t�@�C���̕ύX�_

* �y���[�h�u���b�N�z
  1.26 �łł́A
  (TUT-Code �̂������ȃ��[�h�ɑΉ����邽��)
  �e�[�u���t�@�C������AA ���[�h�EB ���[�h�� 
  2 �̃��[�h�u���b�N��ǂ݂��ގd�l�ɂȂ��Ă��܂����B
  1.27 �łł́A
  �������ȃ��[�h������̕ϊ����[�`���ŏ�������悤�ɂȂ������ƁA
  �S�p���[�h���Ǔ_�؂�ւ��@�\��V�݂������Ƃɔ����A
  ���[�h�u���b�N�� 1 �����ǂ݂��ގd�l�ɕύX����܂����B
  �e�[�u���t�@�C���ɁA���[�h�u���b�N�̒�`�� 2 ����ꍇ�A
  �ŏ��̂��̂�����ǂ݂��݁A2 �Ԗڂ̂��͖̂������܂��B

* �y�V�݂��ꂽ�����`�z
  * (({@Z})) (((|F_HANZEN|)))
  * (({@K})) (((|F_HIRAKATA|)))
  * (({@p})) (((|F_PUNCT|)))
  * (({@!})) (((|F_HIST|)))
  * (({@q})) (((|F_QUIT|)))
  * (({@D})) (((|F_DAKUTEN|)))
  * (({@P})) (((|F_HANDAKUTEN|)))
* �y���O���ύX���ꂽ�����`�z
  * (({@b})): ((|F_BUSHU_PRE|)) �� ((|F_BUSHU|))
  * (({@m})): ((|F_MAZE_PRE|)) �� ((|F_MAZEGAKI_START|))
  * (({@B})): ((|F_BUSHU_POST|)) �� ((|F_KOUCHIBUSHU|))
  * (({@1})) �` (({@9})): ((|F_MAZE_POSTn|)) �� ((|F_KOUCHIn|))
  * (({@h})): ((|F_HELP_BACKW|)) �� ((|F_HELP|))
  * (({@H})): ((|F_HELP_FORW|)) �� ((|F_HELP_NEXT|))
  * (({@v})): ((|F_VERB_FIRST|)) �� ((|F_VERTATIM|))
* �y�d�l���ύX���ꂽ�����`�z
  * (({@s})):
    1.26 �łł̓��[�h�u���b�N�̐؂�ւ��ł������A
    1.27 �łł͂������ȃ��[�h�̐؂�ւ� (({@K})) �Ɠ����ɂȂ�܂��B
  * (({@h})), (({@H})):
    1.26 �łł́A(({@h})) ���u�ŏ��̕����v�̃w���v�A
    (({@H})) ���u���̕����v�̃w���v�ł����B
    1.27 �łł́A(({@h})) �𑱂��Ď��s���邱�Ƃ�
    �u���̕����v�̃w���v��\�����A
    �܂� (({@H})) �� (({@h})) �Ƌt�����ɕ\�����܂��B
  * (({@v}))
    1.26 �łł́A��ɁA�Ή�����L�[�̓��͂ł����B
    �o�[�W���� 1.27 �ł́A�� 2 �Ō��ȍ~�Ŏw�肳�ꂽ�ꍇ�́A
    �� 1 �Ō��̃L�[�̓��͂ɂȂ�܂��B

=end