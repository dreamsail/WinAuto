#include<stdio.h>
#include "WinAuto.h"

int main() {
	auto app=WinAuto::start(TEXT("C:\\Users\\61373\\xwechat_files\\wxid_9864orskiak012_f0d9\\msg\\file\\2025-10\\���ͻ��ˡ��ѳ�1.0\\�ѳ�1.0\\res\\Pdg2Pic\\Pdg2Pic.exe"));
	Sleep(500);

	auto windowsList = app.windowsList().filterByTitle(TEXT("Pdg2Pic")).filterByStyle(0x94CF0044);
	if (windowsList.size()==0){
		return 0;
	}
	auto windows = windowsList.at(0);
	auto buttonList = windows.windowsList().filterByClassName(TEXT("Button")).filterByTitle(TEXT(""));
	buttonList.at(0).click();

	Sleep(1000);
	auto selectFileWindowsList=app.windowsList().filterByTitle(TEXT("ѡ����PDG�ļ����ļ���"));
	if (selectFileWindowsList.size() == 0) {
		return 0;
	}
	auto selectFileWindows = selectFileWindowsList.at(0);

	auto editList = selectFileWindows.windowsList().filterByClassName( TEXT("Edit"));
	editList.at(0).setTitle(TEXT("D:\\Desktop\\�ѳɵ��Ӱ��ѹ\\����ѧȫ��  ���²ᣩ_10165980"));

	buttonList = selectFileWindows.windowsList().filterByClassName(TEXT("Button")).filterByTitle(TEXT("ȷ��"));
	buttonList.at(0).click();

	buttonList = windows.windowsList().filterByClassName(TEXT("Button")).filterByTitle(TEXT("&4����ʼת��"));
	buttonList.at(0).click();

	Sleep(1000);
	windowsList = app.windowsList().filterByTitle(TEXT("Pdg2Pic")).filterByStyle(0x94C801C5);
	if (windowsList.size()==0){
		return 0;
	}
	buttonList = windowsList.at(0).windowsList().filterByClassName(TEXT("Button")).filterByTitle(TEXT("ȷ��"));
	buttonList.at(0).click();
}