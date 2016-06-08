/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is itstructures.com code.
 *
 * The Initial Developer of the Original Code is IT Structures.
 * Portions created by the Initial Developer are Copyright (C) 2008
 * the Initial Developer. All Rights Reserved.
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */
#pragma once

#include "Host.h"
namespace ATL
{
	template <typename T>
	class CComObject;
}
class CControlEventSink;
class CControlSite;
class PropertyList;

class CAxHost : public CHost{
private:
	CAxHost(const CAxHost &);

	bool isValidClsID;
	bool isKnown;
	bool noWindow;
protected:
	// The window handle to our plugin area in the browser
	HWND Window;
	WNDPROC OldProc;

	// The class/prog id of the control
	CLSID ClsID;
	LPCWSTR CodeBaseUrl;

	CComObject<CControlEventSink> *Sink;
	RECT lastRect;
	
	PropertyList *Props_;
public:
	CAxHost(NPP inst);
	~CAxHost();

	static CLSID ParseCLSIDFromSetting(LPCSTR clsid, int length);
	
	virtual NPP ResetNPP(NPP npp);
	CComObject<CControlSite> *Site;
	void SetNPWindow(NPWindow *window);
	void ResetWindow();

	PropertyList *Props() {
		return Props_;
	}
	void Clear();
	void setWindow(HWND win);
	HWND getWinfow();
	void UpdateRect(RECT rcPos);

	bool verifyClsID(LPOLESTR oleClsID);
	bool setClsID(const char *clsid);
	bool setClsID(const CLSID& clsid);
	CLSID getClsID() {
		return this->ClsID;
	}

	void setNoWindow(bool value);

	bool setClsIDFromProgID(const char *progid);
	void setCodeBaseUrl(LPCWSTR clsid);
	bool hasValidClsID();
	bool CreateControl(bool subscribeToEvents);
	void UpdateRectSize(LPRECT origRect);
	void SetRectSize(LPSIZEL size);
	bool AddEventHandler(wchar_t *name, wchar_t *handler);
	
	HRESULT GetControlUnknown(IUnknown **pObj);

	short HandleEvent(void *event);
	ScriptBase *CreateScriptableObject();
};
