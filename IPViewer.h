// IPViewer.h : CIPViewer 的声明

#pragma once
#include "resource.h"       // 主符号
#include <shlobj.h>
#include <WinSock2.h>
#include <string>
#include <vector>
#include <stdlib.h>

#include "ShellViewIP_i.h"
typedef std::wstring STRING;
typedef std::vector<STRING> STRINGVector;


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "??????????????"
#endif

/*"Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"*/

using namespace ATL;

#define SZ_MENUTEXT TEXT("本机IP : ")
#define SZ_HELPTEXTA "显示本机IP地址"
#define SZ_HELPTEXTW L"显示本机IP地址"
#define SZ_GETIPFAILED _T("没有查询结果")
extern HINSTANCE         _hInstance;

// CIPViewer

class ATL_NO_VTABLE CIPViewer :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CIPViewer, &CLSID_IPViewer>,
	public IDispatchImpl<IIPViewer, &IID_IIPViewer, &LIBID_ShellViewIPLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
    public IShellExtInit,
    public IContextMenu
{
public:
	CIPViewer()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_IPVIEWER)


BEGIN_COM_MAP(CIPViewer)
	COM_INTERFACE_ENTRY(IIPViewer)
	COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(IShellExtInit)
    COM_INTERFACE_ENTRY(IContextMenu)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
        m_hBitmap = LoadBitmap(_hInstance, MAKEINTRESOURCE(IDB_MENU_ICON));
		return S_OK;
	}

	void FinalRelease()
	{
        if (m_hBitmap)
        {
            DeleteObject(m_hBitmap);
        }
	}

public:
    enum 
    {
        IDM_CTXMENU = 0,
    };

public:

    HRESULT STDMETHODCALLTYPE Initialize( 
        /* [in] */ LPCITEMIDLIST pidlFolder,
        /* [in] */ IDataObject *pdtobj,
        /* [in] */ HKEY hkeyProgID)
    {
        return S_OK;
    }

    STDMETHOD(QueryContextMenu)(THIS_
        HMENU hmenu,
        UINT indexMenu,
        UINT idCmdFirst,
        UINT idCmdLast,
        UINT uFlags)
    {
        if (uFlags & CMF_DEFAULTONLY)
        {
            return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, 0);
        }
        int nID =  idCmdFirst;
        STRING ip;
        STRINGVector vectorIP;
        GetIpAddress(vectorIP);

#pragma region 创建子菜单
        HMENU hSubMenu = CreateMenu();

        for (int i = 1; i < vectorIP.size(); i++)
        {
            ip = _T("IP: ");
            ip += vectorIP[i];
            InsertMenu(hSubMenu, i-1, MF_STRING  | MF_BYPOSITION, nID++, ip.c_str());
        }
#pragma endregion 

        if (vectorIP.size() <= 1)
        {
            ip = SZ_GETIPFAILED;
        }
        else
        {
            ip = _T("Name:");
            ip += vectorIP[0];
        }

        
        MENUITEMINFO mii;
        
        CreateMainMenuItem(mii);
        mii.hSubMenu = hSubMenu;
        mii.dwTypeData = (wchar_t *)ip.c_str();
        mii.cch = ip.size();
        mii.wID = nID + indexMenu;
        InsertMenuItem(hmenu, indexMenu, TRUE, &mii);
        int nCount = vectorIP.size();
        if(nCount <= 0)
            nCount = 1;
        return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, nCount);
    }

    STDMETHOD(InvokeCommand)(THIS_
        LPCMINVOKECOMMANDINFO lpici)
    {
        BOOL fEx = FALSE;
        BOOL fUnicode = FALSE;

        if(lpici->cbSize == sizeof(CMINVOKECOMMANDINFOEX))
        {
            fEx = TRUE;
            if((lpici->fMask & CMIC_MASK_UNICODE))
            {
                fUnicode = TRUE;
            }
        }

        if( !fUnicode && HIWORD(lpici->lpVerb))
        {
            if(StrCmpIA(lpici->lpVerb, m_pszVerb))
            {
                return E_FAIL;
            }
        }

        else if( fUnicode && HIWORD(((CMINVOKECOMMANDINFOEX *) lpici)->lpVerbW))
        {
            if(StrCmpIW(((CMINVOKECOMMANDINFOEX *)lpici)->lpVerbW, m_pwszVerb))
            {
                return E_FAIL;
            }
        }

        else if(LOWORD(lpici->lpVerb) != IDM_CTXMENU)
        {
            return E_FAIL;
        }

        else
        {
            //在此处理点击事件.
            return S_OK;
            
        }

        return E_FAIL;

    }

    STDMETHOD(GetCommandString)(THIS_
        UINT_PTR    idCmd,
        UINT        uType,
        UINT      * pwReserved,
        LPSTR       pszName,
        UINT        cchMax)
    {
        HRESULT  hr = E_INVALIDARG;
        static CHAR szHelpTextA[] = SZ_HELPTEXTA;
        static WCHAR szHelpTextW[] = SZ_HELPTEXTW;

        if(idCmd != IDM_CTXMENU)
        {
            return hr;
        }

        switch(uType)
        {
        case GCS_HELPTEXTA:
            lstrcpynA((CHAR*)pszName, szHelpTextA, cchMax);
            break; 

        case GCS_HELPTEXTW: 
            lstrcpynW((WCHAR*)pszName, szHelpTextW, cchMax);;
            break; 

        case GCS_VERBA:
            lstrcpynA((CHAR*)pszName, m_pszVerb, cchMax);
            break; 

        case GCS_VERBW:
            lstrcpynW((WCHAR*)pszName, m_pwszVerb, cchMax);
            break;

        default:
            hr = S_OK;
            break; 
        }
        return hr;
    }
    
    void GetIpAddress(STRINGVector& ipList)
    {
        WORD  wVersionRequested = 0;  
        WSADATA  wsaData;  
        char hostname[255] = {0};  
        wchar_t * unicodeHostName = NULL;
        int err;

        wVersionRequested  =  MAKEWORD( 1, 1 );//版本号1.1

        //1.加载套接字库 
        err = WSAStartup( wVersionRequested, &wsaData );
        if ( err != 0 ) {

            return;
        }

        //判断是否我们请求的winsocket版本，如果不是
        //则调用WSACleanup终止winsocket的使用并返回            

        if ( LOBYTE( wsaData.wVersion ) != 1 ||
            HIBYTE( wsaData.wVersion ) != 1 ) {

                WSACleanup( );
                return; 
        }///...if

        if  ( err  ==  0  )  
        {  

            if(  gethostname  (  hostname,  sizeof(hostname))  ==  0)  
            {  
                C2W(hostname,unicodeHostName);
                ipList.push_back(unicodeHostName);
                delete[] unicodeHostName;
                hostent* host = gethostbyname(hostname);
                sockaddr_in addre;
                for (int i = 0;host->h_addr_list[i];i++)
                {
                    STRING ip;
                    wchar_t* wstr = NULL;
                    memcpy_s(&addre.sin_addr.s_addr,host->h_length,host->h_addr_list[i],host->h_length);
                    C2W(inet_ntoa(addre.sin_addr), wstr);

                    ip = wstr;
                    delete[] wstr;
                    ipList.push_back(ip);
                }
            }  

            WSACleanup(  );  
        }    
    }
    void C2W(const char* cstr, wchar_t*& wstr )
    {
        size_t len = strlen(cstr) + 1;
        size_t converted = 0;
        wstr=(wchar_t*)malloc(len * sizeof(wchar_t));
        mbstowcs_s(&converted, wstr, len, cstr, _TRUNCATE);
    }
    void W2C(const wchar_t* wstr, char*& cstr)
    {
        size_t len = wcslen(wstr) + 1;
        size_t converted = 0;

        cstr=(char*)malloc(len*sizeof(char));
        wcstombs_s(&converted, cstr, len, wstr, _TRUNCATE);
    }
    void CreateMainMenuItem(MENUITEMINFO& mii)
    {
        memset((void*)&mii, 0, sizeof(mii));
        mii.cbSize = sizeof(mii);
        mii.fMask = MIIM_STRING | MIIM_CHECKMARKS | MIIM_ID | MIIM_STATE | MIIM_SUBMENU;
        mii.hbmpItem = m_hBitmap;
        mii.hbmpChecked = m_hBitmap;
        mii.hbmpUnchecked = m_hBitmap;
        mii.fState = MFS_ENABLED;
    }
private:
    HBITMAP m_hBitmap;
    CHAR    m_pszVerb[32];
    WCHAR   m_pwszVerb[32];

};

OBJECT_ENTRY_AUTO(__uuidof(IPViewer), CIPViewer)
