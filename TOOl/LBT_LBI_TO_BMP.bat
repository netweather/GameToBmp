@echo off
title LBT_LBI解包工具
echo LBT_LBI资源解包程序
echo 按任意键开始解包当前目录下的所有文件
pause>nul
title 正在解包文件
for /f "usebackq tokens=*" %%d in (`dir /s /b *.lbt *.lbi`) do (
title 正在解包文件:"%%d"。请稍候
Lbt_LbiToBmp.exe "%%d"
)
mshta vbscript:msgbox("此文件夹内所有图片素材已成功提取。单击退出以退出程序。",64,"素材已提取完成")(window.close)
exit
