// dllmain.h : 模块类的声明。

class CShellViewIPModule : public ATL::CAtlDllModuleT< CShellViewIPModule >
{
public :
	DECLARE_LIBID(LIBID_ShellViewIPLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_SHELLVIEWIP, "{CE98655E-328A-4260-B1F8-87C449692F72}")
};

extern class CShellViewIPModule _AtlModule;
