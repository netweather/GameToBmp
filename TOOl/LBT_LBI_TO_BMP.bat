@echo off
title LBT_LBI�������
echo LBT_LBI��Դ�������
echo ���������ʼ�����ǰĿ¼�µ������ļ�
pause>nul
title ���ڽ���ļ�
for /f "usebackq tokens=*" %%d in (`dir /s /b *.lbt *.lbi`) do (
title ���ڽ���ļ�:"%%d"�����Ժ�
Lbt_LbiToBmp.exe "%%d"
)
mshta vbscript:msgbox("���ļ���������ͼƬ�ز��ѳɹ���ȡ�������˳����˳�����",64,"�ز�����ȡ���")(window.close)
exit
