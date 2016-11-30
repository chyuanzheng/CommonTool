#include "StdAfx.h"
#include "AfxFuc.h"
#include "AfxModule.h"


 CE_CONTROL_API CWinApp*  AfxGetApp(){
	return AfxModule::GetModuleState()->GetApp();
 }

 CE_CONTROL_API void AfxShowPopupWnd( bool b )
 {
	AfxModule::GetModuleState()->GetApp()->ShowPopupWnd(b);
 }

 CE_CONTROL_API void AfxSetApp(CWinApp* app)
 {
	return AfxModule::GetModuleState()->SetApp(app);
 }
 CE_CONTROL_API HINSTANCE AfxGetInstanceHandle( ){
	 return AfxModule::GetModuleState()->GetInstanceHandle();
 }

 CE_CONTROL_API BOOL  AfxWinInit(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	 LPTSTR lpCmdLine, int nCmdShow){
		 return AfxModule::GetModuleState()->WinInit(hInstance,  hPrevInstance,lpCmdLine, nCmdShow);
 }


 CE_CONTROL_API BOOL AfxInvalidateRect(LPCRECT  rc){
	return AfxModule::GetModuleState()->InvalidateRect(rc);
 }


 CE_CONTROL_API BOOL AfxInvalidatePopupRect( LPCRECT rc )
 {
	return AfxModule::GetModuleState()->InvalidatePopupRect(rc);
 }


 CE_CONTROL_API void AfxValidate(){
	 AfxModule::GetModuleState()->Validate();
 }

 CE_CONTROL_API BOOL  AfxGetWorkPathW(wstring &path){
	 return AfxModule::GetModuleState()->GetWorkPathW(path);
 }
 CE_CONTROL_API BOOL  AfxGetWorkPathA(string &path){
	 return AfxModule::GetModuleState()->GetWorkPathA(path);
 }
//工作目录 加上 addstr
 CE_CONTROL_API const char * AfxAddWorkPathA( const char * addstr )
 {
	 return AfxModule::GetModuleState()->AddWorkPathA(addstr);
 }

 CE_CONTROL_API BOOL  AfxShowTaskBar(BOOL Show){
	 return AfxModule::GetModuleState()->ShowTaskBar(Show);
 }




 //CE_CONTROL_API void  AfxFinishActiviy( Activity* const act){
	//return AfxModule::GetModuleState()->FinishActiviy(act);
 //}


 CE_CONTROL_API void AfxSetPopupHWND( HWND hwnd )
 {
	AfxModule::GetModuleState()->SetPopupHWND( hwnd);
 }

 CE_CONTROL_API HWND AfxGetPopupHWND()
 {
	return AfxModule::GetModuleState()->GetPopupHWND();
 }

 CE_CONTROL_API void  AfxSetHWND(HWND  hwnd){
	AfxModule::GetModuleState()->SetHWND( hwnd);
 }
 CE_CONTROL_API HWND  AfxGetHWND(){
	return AfxModule::GetModuleState()->GetHWND();
 }
 CE_CONTROL_API BOOL  AfxPostMessage( UINT nMsg, WPARAM wParam, LPARAM lParam ){
	return AfxModule::GetModuleState()->PostMessage(nMsg, wParam, lParam);
 }
 CE_CONTROL_API BOOL  AfxSendMessage( UINT nMsg, WPARAM wParam, LPARAM lParam ){
	return AfxModule::GetModuleState()->SendMessage(nMsg, wParam, lParam);
 }

 CE_CONTROL_API void  AfxSetDcRect(const RECT&  rt){
	AfxModule::GetModuleState()->SetDcRect(rt);
 }
 CE_CONTROL_API const RECT&  AfxGetDcRect(){
	return AfxModule::GetModuleState()->GetDcRect();
 }

 CE_CONTROL_API BOOL AfxGetDeviceBitcount()
 {
	return AfxModule::GetModuleState()->GetDeviceBitcount();
 }
 CE_CONTROL_API int   AfxGetDevWidth()
 {
	return AfxModule::GetModuleState()->GetDevWidth();	
 }
 CE_CONTROL_API int   AfxGetDevHeight()
 {
	return AfxModule::GetModuleState()->GetDevHeight();
 }
 CE_CONTROL_API void AfxSetPopupDcRect( const RECT& rt )
 {
	AfxModule::GetModuleState()->SetPopupDcRect(rt);
 }

 CE_CONTROL_API const RECT& AfxGetPopupDcRect()
 {
	return AfxModule::GetModuleState()->GetPopupDcRect();
 }


 #include "GxxMsgBox.h"
 CE_CONTROL_API void AfxMessageBox( const string &text,UINT time/*=3*/,LPCRECT rc /*= NULL*/,bool bIsTextId /*= true*/ )
 {
	 GxxMsgBox::ShowMsgBox(text, time, rc,bIsTextId);
 }
#include "GxxMsgTypeBox.h"

 // view 是接收消息（OK，Cancel）的控件，type表示弹出对话框的类型
 CE_CONTROL_API void AfxMessageBox( const string& sid, GxxView* view,DWORD param, int type)
 {
	GxxMsgTypeBox::ShowMsgBox(sid, view, param, type);
 }

 CE_CONTROL_API void AfxMessageBox( const wstring& text, GxxView* view,DWORD param, int type )
 {
	GxxMsgTypeBox::ShowMsgBox(text, view, param, type);
 }

