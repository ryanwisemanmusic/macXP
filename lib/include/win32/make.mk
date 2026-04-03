# macOS/Linux make equivalent of make.bat for generating windows.h

OUT := windows.h

HEADER_PARTS := \
	accctrl.h \
	aclapi.h \
	aclui.h \
	adsprop.h \
	af_irda.h \
	afxres.h \
	amaudio.h \
	amvideo.h \
	atomic.h \
	audevcod.h \
	aviriff.h \
	aygshell.h \
	basetsd.h \
	basetyps.h \
	bdatypes.h \
	cderr.h \
	ceconfig.h \
	cguid.h \
	cmnquery.h \
	comcat.h \
	commctrl.h \
	commdlg.h \
	connmgr.h \
	control.h \
	cpl.h \
	cplext.h \
	custcntl.h \
	dbgapi.h \
	dbghelp.h \
	dbt.h \
	dde.h \
	ddeml.h \
	ddraw.h \
	dds.h \
	devguid.h \
	devload.h \
	dhcpcsdk.h \
	dlgs.h \
	docobj.h \
	dsadmin.h \
	dsclient.h \
	dsgetdc.h \
	dshow.h \
	dsound.h \
	dsquery.h \
	dsrole.h \
	dvdevcod.h \
	dvdmedia.h \
	edevdefs.h \
	errorrep.h \
	errors.h \
	evcode.h \
	excpt.h \
	exdisp.h \
	exdispid.h \
	fiber.h \
	file.h \
	fltdefs.h \
	gdi.h \
	gdiplus.h \
	httpext.h \
	icm.h \
	icmpapi.h \
	idispids.h \
	il21dec.h \
	imagehlp.h \
	imm.h \
	initguid.h \
	intrin.h \
	intshcut.h \
	io.h \
	ipexport.h \
	iphlpapi.h \
	ipifcons.h \
	ipinfoid.h \
	iprtrmib.h \
	iptypes.h \
	ipxconst.h \
	ipxrtdef.h \
	ipxtfflt.h \
	isguids.h \
	kfuncs.h \
	ks.h \
	ksmedia.h \
	largeint.h \
	lm.h \
	lmaccess.h \
	lmalert.h \
	lmapibuf.h \
	lmat.h \
	lmaudit.h \
	lmbrowsr.h \
	lmchdev.h \
	lmconfig.h \
	lmcons.h \
	lmerr.h \
	lmerrlog.h \
	lmmsg.h \
	lmremutl.h \
	lmrepl.h \
	lmserver.h \
	lmshare.h \
	lmsname.h \
	lmstats.h \
	lmsvc.h \
	lmuse.h \
	lmuseflg.h \
	lmwksta.h \
	lzexpand.h \
	mapi.h \
	mapidefs.h \
	mciavi.h \
	mcx.h \
	mgm.h \
	mgmtapi.h \
	misc.h \
	mlang.h \
	mmreg.h \
	mmsystem.h \
	mpegtype.h \
	mprapi.h \
	mq.h \
	msacm.h \
	msgqueue.h \
	mshtml.h \
	mswsock.h \
	nb30.h \
	nddeapi.h \
	notify.h \
	nspapi.h \
	ntdef.h \
	ntdll.h \
	ntdsapi.h \
	ntdsbcli.h \
	ntldap.h \
	ntsecapi.h \
	ntsecpkg.h \
	oaidl.h \
	objbase.h \
	objfwd.h \
	objidl.h \
	objsafe.h \
	objsel.h \
	ocidl.h \
	odbcinst.h \
	ole.h \
	ole2.h \
	ole2ver.h \
	oleacc.h \
	oleauto.h \
	olectl.h \
	olectlid.h \
	oledlg.h \
	oleidl.h \
	pbt.h \
	phone.h \
	pimstore.h \
	pm.h \
	poppack.h \
	powrprof.h \
	process.h \
	projects.h \
	prsht.h \
	psapi.h \
	pshpack1.h \
	pshpack2.h \
	pshpack4.h \
	pshpack8.h \
	qedit.h \
	rapi.h \
	ras.h \
	rasdlg.h \
	raserror.h \
	rassapi.h \
	reason.h \
	regstr.h \
	richedit.h \
	richole.h \
	routprot.h \
	rpc.h \
	rpcdce.h \
	rpcdce2.h \
	rpcdcep.h \
	rpcndr.h \
	rpcnsi.h \
	rpcnsip.h \
	rpcnterr.h \
	rpcproxy.h \
	rtutils.h \
	schannel.h \
	schnlsp.h \
	scrnsave.h \
	sddl.h \
	secext.h \
	security.h \
	service.h \
	servprov.h \
	setupapi.h \
	shellapi.h \
	shldisp.h \
	shlguid.h \
	shlobj.h \
	shlwapi.h \
	simmgr.h \
	sipapi.h \
	sms.h \
	snmp.h \
	specstrings.h \
	sql.h \
	sqlext.h \
	sqltypes.h \
	sqlucode.h \
	sspi.h \
	stm.h \
	strmif.h \
	strsafe.h \
	subauth.h \
	svcguid.h \
	sysinfo.h \
	threads.h \
	tlhelp32.h \
	tmschema.h \
	todaycmn.h \
	unknwn.h \
	userenv.h \
	usp10.h \
	uxtheme.h \
	vfw.h \
	vidcap.h \
	vmr9.h \
	vptype.h \
	w32api.h \
	webvw.h \
	win32defs.h \
	win32functions.h \
	winable.h \
	winbase.h \
	winber.h \
	wincon.h \
	wincrypt.h \
	windef.h \
	windns.h \
	window.h \
	windows_base.h \
	windows_modular.h \
	windowsx.h \
	winerror.h \
	wingdi.h \
	wininet.h \
	winioctl.h \
	winldap.h \
	winnetwk.h \
	winnls.h \
	winnt.h \
	winperf.h \
	winreg.h \
	winresrc.h \
	winsnmp.h \
	winsock.h \
	winsock2.h \
	winspool.h \
	winsvc.h \
	winuser.h \
	winver.h \
	ws2spi.h \
	ws2tcpip.h \
	wsahelp.h \
	wsipx.h \
	wsnetbs.h \
	wtsapi32.h \
	wtypes.h \
	xprtdefs.h \
	zmouse.h

.PHONY: all clean regen

all: $(OUT)

regen: clean all

$(OUT): $(HEADER_PARTS)
	@rm -f "$(OUT)"
	@printf '%s\n' '#if defined(__APPLE__) && (defined(__aarch64__) || defined(__arm64__))' > "$(OUT)"
	@printf '%s\n' '#pragma once' >> "$(OUT)"
	@printf '%s\n' '#ifndef _INC_WINDOWS' >> "$(OUT)"
	@printf '%s\n' '#define _INC_WINDOWS' >> "$(OUT)"
	@printf '%s\n' '#ifndef WINDOWS_H' >> "$(OUT)"
	@printf '%s\n' '#define WINDOWS_H' >> "$(OUT)"
	@printf '\n' >> "$(OUT)"
	@for f in $(HEADER_PARTS); do \
		printf '\n' >> "$(OUT)"; \
		cat "$$f" >> "$(OUT)"; \
	done
	@printf '\n' >> "$(OUT)"
	@printf '%s\n' '#endif' >> "$(OUT)"
	@printf '%s\n' '#endif' >> "$(OUT)"
	@printf '%s\n' '#define _WINDOWS_' >> "$(OUT)"
	@printf '%s\n' '#endif' >> "$(OUT)"

clean:
	@rm -f "$(OUT)"
