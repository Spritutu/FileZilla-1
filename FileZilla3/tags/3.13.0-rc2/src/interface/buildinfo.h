#ifndef __BUILDINFO_H__
#define __BUILDINFO_H__

class CBuildInfo
{
protected:
	CBuildInfo() {}

public:

	static wxString GetVersion();
	static int64_t ConvertToVersionNumber(const wxChar* version);
	static wxString GetBuildDateString();
	static wxString GetBuildTimeString();
	static CDateTime GetBuildDate();
	static wxString GetBuildType();
	static wxString GetCompiler();
	static wxString GetCompilerFlags();
	static wxString GetHostname();
	static wxString GetBuildSystem();
	static bool IsUnstable(); // Returns true on beta or rc releases.
	static wxString GetCPUCaps(char separator = ',');
};

#endif //__BUILDINFO_H__
