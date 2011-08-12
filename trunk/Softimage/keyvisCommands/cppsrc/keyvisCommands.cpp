// keyvisCommands
// Initial code generated by XSI SDK Wizard
// Executed Tue Dec 1 21:37:11 UTC+0100 2009 by Administrator
// 
// Tip: You need to compile the generated code before you can load the plug-in.
// After you compile the plug-in, you can load it by clicking Update All in the Plugin Manager.
#include <xsi_application.h>
#include <xsi_context.h>
#include <xsi_pluginregistrar.h>
#include <xsi_status.h>
#include <xsi_argument.h>
#include <xsi_command.h>
using namespace XSI; 

XSIPLUGINCALLBACK CStatus XSILoadPlugin( PluginRegistrar& in_reg )
{
	in_reg.PutAuthor(L"Stefan Kubicek");
	in_reg.PutName(L"keyvisCompiledCommands");
	in_reg.PutEmail(L"");
	in_reg.PutURL(L"");
	in_reg.PutVersion(1,0);
	in_reg.RegisterCommand(L"GetCommandByUID",L"GetCommandByUID");
	//RegistrationInsertionPoint - do not remove this line

	return CStatus::OK;
}

XSIPLUGINCALLBACK CStatus XSIUnloadPlugin( const PluginRegistrar& in_reg )
{
	CString strPluginName;
	strPluginName = in_reg.GetName();
	Application().LogMessage(strPluginName + L" has been unloaded.",siVerboseMsg);
	return CStatus::OK;
}

XSIPLUGINCALLBACK CStatus GetCommandByUID_Init( CRef& in_ctxt )
{
	Context ctxt( in_ctxt );
	Command oCmd;
	oCmd = ctxt.GetSource();
	oCmd.PutDescription(L"Returns Command with the given UID");
	oCmd.PutTooltip(L"Returns Command with the given UID");
	oCmd.SetFlag(siSupportsKeyAssignment,false);
	oCmd.SetFlag(siNoLogging,true);
	oCmd.EnableReturnValue(true);

	ArgumentArray oArgs;
	oArgs = oCmd.GetArguments();
	oArgs.Add(L"UID");
	return CStatus::OK;
}

XSIPLUGINCALLBACK CStatus GetCommandByUID_Execute( CRef& in_ctxt )
{
	Context ctxt( in_ctxt );
	CValueArray args = ctxt.GetAttribute(L"Arguments");
	CValue UID = args[0];
	// CString UID = args[0];

	//Application().LogMessage(L"GetCommandByUID_Execute called",siVerboseMsg);
	
	XSI::CommandArray cmds;
	XSI::Application appxsi;
	cmds = appxsi.GetCommands();
	for(int i = 0; i < cmds.GetCount(); i++)
		{
		Command cmd = cmds.GetItem(i);
		CValue cmdUID = cmd.GetUID();
		if(cmdUID == UID)
			{
				CValue retval = CValue(cmd);
				ctxt.PutAttribute( L"ReturnValue", retval );
				return CStatus::OK;
			}
		}

 // Return a value by setting this attribute:
 ctxt.PutAttribute( L"ReturnValue", false );

 // Return CStatus::Fail if you want to raise a script error
 return CStatus::OK;
}
