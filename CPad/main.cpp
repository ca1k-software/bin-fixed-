/*
 * File: main.cpp
 * Author: CA1K
 *
 * Created on November 1, 2015, 9:58 PM
 */
#include <iostream>
#include <fstream>
#include <windows.h>
#include <commdlg.h>
#include <stdio.h>
#include <string>

using namespace std;

// [ PROGRAM PROCEDURES ]
//=========================================================
/*Really what these are used for is to address conditions to
 *the WS_COMMAND case, these are registered as integers
 */
#define BUFFER_LEN 1024//buffer length
#define IDC_MAIN_EDIT 0//edit ID
#define EXIT_PROC 1//the exit procedure
#define ABOUT_PROC 2//the trigger for the "about" window
#define SAVE_PROC 3//save procedure
#define OPEN_PROC 4//copy procedure
#define NEW_PROC 5//create a new document procedure
#define SAVE_CUR 6//current save procedure
#define HTML_LAY 7//layout HTML
#define EMU 8//html emulator(IE API)
//=========================================================

// [ DEVELOPER FRIENDLY VARIABLES ]
//=========================================================
const char g_szClassName[] = "CPadx1"; //window class name
const char g_Title[] = "Untitled - CPad"; //window title
const char g_About[] = "->CPad Version 1.0<-\nAuthor: CA1K [via ca1k.xkotto.com]\nSource Code Language: C++\nAPI: Win32\nDescription: CPad is a program developed by CA1K. It is entirely made from the win32 API. Ideally, in the future, CPad will become a code editor.\nFor more programs, go to ca1k.xkotto.com.";
int dim = 600;//window dimensions(square)
//=========================================================

// [ OBJECT BUILDING ]
//=========================================================
void makeMenu(HWND hwnd){
    HMENU hMenubar;
    HMENU hMenu;
    HMENU hMenu2;
    hMenubar = CreateMenu();
    hMenu = CreateMenu();
    hMenu2 = CreateMenu();
    AppendMenuW(hMenu, MF_STRING, NEW_PROC, L"&New file");
    AppendMenuW(hMenu, MF_STRING, SAVE_CUR, L"&Save");
    AppendMenuW(hMenu, MF_STRING, SAVE_PROC, L"&Save as");
    AppendMenuW(hMenu, MF_STRING, OPEN_PROC, L"&Open file");
    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenu, MF_STRING, HTML_LAY, L"&Load HTML Layout");
    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenu, MF_STRING, ABOUT_PROC, L"&About");
    AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu, L"&File");
    AppendMenuW(hMenu2, MF_STRING, EXIT_PROC, L"&Exit");
    AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu2, L"&Config");
    SetMenu(hwnd, hMenubar);
}

HWND makeEdit(HWND hwnd, HWND hEdit){//this function creates the edit
HINSTANCE hInstance;
HFONT font = CreateFont(18,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,
OUT_OUTLINE_PRECIS,CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY,VARIABLE_PITCH,TEXT("Arial"));
RECT rect;
int pwidth;
int pheight;
if(GetWindowRect(hwnd, &rect))
{
    pwidth = rect.right - rect.left;
    pheight = rect.bottom - rect.top;
}
    hEdit = CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT","",
    WS_CHILD|WS_VISIBLE|ES_AUTOVSCROLL|ES_AUTOHSCROLL|ES_MULTILINE,
    0,0,pwidth,pheight,hwnd,(HMENU)IDC_MAIN_EDIT,
    hInstance,NULL);
    SendMessage(hEdit,WM_SETFONT,(WPARAM)font,MAKELPARAM(TRUE, 0));
    return hEdit;
}

void saveTextFile(HWND hwnd){
    char buffer[BUFFER_LEN];//buffer
    GetWindowText(GetDlgItem(hwnd,IDC_MAIN_EDIT), buffer, sizeof(buffer));
    TCHAR szFilters[] = "HTML Page (.html)\0*.html\0All (.*)\0*.*";
    TCHAR szFilePathName[sizeof(buffer)] = "";
    OPENFILENAME ofn;
    HANDLE hf;
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFileTitle = NULL;
    ofn.nFilterIndex = 1;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrFilter = szFilters;
    ofn.lpstrFile = szFilePathName;
    ofn.nMaxFile = sizeof(buffer);
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = "place_holder";
    ofn.nMaxFileTitle = 0;
    if(GetSaveFileName(&ofn)==TRUE){
        hf = CreateFile(ofn.lpstrFile, GENERIC_WRITE, FILE_SHARE_WRITE,
        NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL|FILE_ATTRIBUTE_ARCHIVE|SECURITY_IMPERSONATION,
        NULL);
        fstream file;
        file.open(ofn.lpstrFile,ios::out);
        file.write(buffer,sizeof(buffer));
        file.close();
        SetWindowText(hwnd, ofn.lpstrFile);
        CloseHandle(hf);
    }
}

void saveCurrentTextFile(HWND hwnd){
    char path[BUFFER_LEN];
    char fileText[BUFFER_LEN];
    GetWindowText(hwnd,path,sizeof(path));
    GetWindowText(GetDlgItem(hwnd,IDC_MAIN_EDIT),fileText,sizeof(fileText));
    fstream outfile(path,ios::out);
    outfile << fileText;
    outfile.close();
    MessageBox(NULL, path, "File Saved", MB_ICONINFORMATION);
}

void loadHTMLLayout(HWND hwnd){
    char buffer[BUFFER_LEN];
    ifstream file("html_lay.html",ios::in);;
    file.read(buffer,sizeof(buffer));
    file.close();
    SetWindowText(GetDlgItem(hwnd,IDC_MAIN_EDIT), buffer);
}

void openTextFile(HWND hwnd){
    char buffer[BUFFER_LEN];
    string app;
    string target;
    TCHAR szFilters[] = "HTML Page (.html)\0*.html\0All (.*)\0*.*";
    TCHAR szFilePathName[sizeof(buffer)] = "";
    OPENFILENAME ofn;
    DWORD dwWritten = 0;
    HANDLE hf;
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFileTitle = NULL;
    ofn.nFilterIndex = 1;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrFilter = szFilters;
    ofn.lpstrFile = szFilePathName;
    ofn.nMaxFile = sizeof(buffer);
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = "place_holder";
    ofn.nMaxFileTitle = 0;
    if(GetOpenFileName(&ofn)==TRUE){
        hf = CreateFile(ofn.lpstrFile, GENERIC_READ, FILE_SHARE_READ,
        NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL|FILE_ATTRIBUTE_ARCHIVE|SECURITY_IMPERSONATION,
        NULL);
        ifstream file;
        file.open(ofn.lpstrFile,ios::in);
        while(file.good()){//build together a string to convert into a char array
            file >> app;
            string add = " " + app;
            target += add;
        }
        char superBuffer[target.length()];
        strcpy(superBuffer,target.c_str());
        file.close();
        SetWindowText(hwnd, ofn.lpstrFile);
        SetWindowText(GetDlgItem(hwnd,IDC_MAIN_EDIT), superBuffer);
        CloseHandle(hf);
    }
}

void createNewDoc(HWND hwnd){
    const char zilch[] = "";
    SetWindowText(GetDlgItem(hwnd,IDC_MAIN_EDIT), zilch);
    SetWindowText(hwnd, g_Title);
}

//=========================================================

// [ SOFTWARE PROCESSING ]
//=========================================================
// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HWND winEdit;
    switch(msg)
    {
        /*WINDOW ACTIONS*/
        case WM_CREATE:{//on window creation
            makeMenu(hwnd);
            makeEdit(hwnd,winEdit);
        }
        break;
        case WM_SIZE:
            makeEdit(hwnd,winEdit);
        break;
        case WM_COMMAND://WINDOW COMMANDS
            switch(LOWORD(wParam))
            {
                case ABOUT_PROC:
                    MessageBox(NULL, g_About, "About CPad", MB_ICONINFORMATION);
                break;
                case EXIT_PROC:
                    PostQuitMessage(0);//exit program
                break;
                case SAVE_PROC:
                    saveTextFile(hwnd);
                break;
                case OPEN_PROC:
                    openTextFile(hwnd);//caching the text, so it can be used later by the current save method
                break;
                case NEW_PROC:
                    createNewDoc(hwnd);
                break;
                case SAVE_CUR:
                    saveCurrentTextFile(hwnd);
                break;
                case HTML_LAY:
                    loadHTMLLayout(hwnd);
                break;
                case EMU:
                break;
            }
        break;
        case WM_CLOSE://on window close
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY://on window destroy
            PostQuitMessage(0);
        break;
        case WM_CTLCOLOREDIT:
            {//edit colors
                HDC hdcStatic = (HDC)wParam;
                SetTextColor(hdcStatic, RGB(255,255,255));
                SetBkColor(hdcStatic, RGB(55,55,55));
                return (INT_PTR)CreateSolidBrush(RGB(55,55,55));
            }
        break;
        default://default method
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    //Step 1: Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = (HICON)LoadImage(NULL,"logo2icon.ico",IMAGE_ICON,0,0,LR_DEFAULTCOLOR|LR_LOADFROMFILE);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = (HICON)LoadImage(NULL,"logo2icon.ico",IMAGE_ICON,0,0,LR_DEFAULTCOLOR|LR_LOADFROMFILE);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        g_Title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, dim, dim,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Step 3: The Message Loop
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;

}
//=========================================================
