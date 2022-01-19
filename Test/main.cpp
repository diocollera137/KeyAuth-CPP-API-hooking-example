#include <iostream>
#include <windows.h>
#include <random>
#include "auth.hpp"
#include <string>
#include <wininet.h>
#include <fstream>
#include <cstdio>
#include <stdlib.h>  
#include <gdiplus.h>
#include <Winternl.h>
#include <Iphlpapi.h>
#include <winnt.h>
#include <tlhelp32.h>
#include <time.h>
#include <vector>
#include <debugapi.h>
#include <shlwapi.h>
#include <conio.h>
#include <CommCtrl.h>
#include <mmsystem.h>
#include <tchar.h>
#include <comdef.h>
#include "FileUtils.h"
#include "../HookLib/HookLib.h"
#pragma comment(lib, "urlmon.lib")
#pragma warning(disable : 2001)
using namespace std;
using namespace KeyAuth;

std::string name = ""; // application name. right above the blurred text aka the secret on the licenses tab among other tabs
std::string ownerid = ""; // ownerid, found in account settings. click your profile picture on top right of dashboard and then account settings.
std::string secret = ""; // app secret, the blurred text on licenses tab and other tabs
std::string version = ""; // leave alone unless you've changed version on website



api KeyAuthApp(name, ownerid, secret, version);
int wmain() {
	wstring moduleFileName;
	Hydr10n::FileUtils::GetModuleFileNameW(moduleFileName);
	//ShellExecuteW(NULL, NULL, L"taskmgr", NULL, NULL, SW_SHOWNORMAL); // debugging purposes
	SetGlobalWindowsHook(); // we are calling here the hook " HookLib.dll "
	std::cout << "\n\n Connecting..";
	SetConsoleTitleA("Loader");
	KeyAuthApp.init();
	if (!KeyAuthApp.data.success)
	{
		std::cout << "\n Status: " + KeyAuthApp.data.message;
		Sleep(1500);
		exit(0);
	}

	std::cout << "\n\n App data:";
	std::cout << "\n Number of users: " + KeyAuthApp.data.numUsers;
	std::cout << "\n Number of online users: " + KeyAuthApp.data.numOnlineUsers;
	std::cout << "\n Number of keys: " + KeyAuthApp.data.numKeys;
	std::cout << "\n Application Version: " + KeyAuthApp.data.version;
	std::cout << "\n Customer panel link: " + KeyAuthApp.data.customerPanelLink;

	std::cout << "\n\n [1] Login\n [2] Register\n [3] Upgrade\n [4] License key only\n\n Choose option: ";

	int option;
	std::string username;
	std::string password;
	std::string key;

	std::cin >> option;
	switch (option)
	{
	case 1:
		std::cout << "\n\n Enter username: ";
		std::cin >> username;
		std::cout << "\n Enter password: ";
		std::cin >> password;
		KeyAuthApp.login(username, password);
		break;
	case 2:
		std::cout << "\n\n Enter username: ";
		std::cin >> username;
		std::cout << "\n Enter password: ";
		std::cin >> password;
		std::cout << "\n Enter license: ";
		std::cin >> key;
		KeyAuthApp.regstr(username, password, key);
		break;
	case 3:
		std::cout << "\n\n Enter username: ";
		std::cin >> username;
		std::cout << "\n Enter license: ";
		std::cin >> key;
		KeyAuthApp.upgrade(username, key);
		break;
	case 4:
		std::cout << "\n Enter license: ";
		std::cin >> key;
		KeyAuthApp.license(key);
		break;
	default:
		std::cout << "\n\n Status: Failure: Invalid Selection";
		Sleep(3000);
		exit(0);
	}

	if (!KeyAuthApp.data.success)
	{
		std::cout << "\n Status: " + KeyAuthApp.data.message;
		Sleep(1500);
		exit(0);
	}

	std::cout << "\n User data:";
	std::cout << "\n Username: " + KeyAuthApp.data.username;
	std::cout << "\n IP address: " + KeyAuthApp.data.ip;
	std::cout << "\n Hardware-Id: " + KeyAuthApp.data.hwid;
	
}