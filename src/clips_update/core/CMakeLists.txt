add_library(clips STATIC
	rulebsc.c
	agenda.c    defins.c    factcom.c   globlpsr.c  multifld.c  rulecstr.c
	analysis.c  developr.c  factfile.c  immthpsr.c  multifun.c  ruledef.c
	argacces.c  dffctbin.c  factfun.c   incrrset.c  objbin.c    ruledlt.c
	bload.c     dffctbsc.c  factgen.c   inherpsr.c  objcmp.c    rulelhs.c
	bmathfun.c  dffctcmp.c  facthsh.c   inscom.c    objrtbin.c  rulepsr.c
	bsave.c     dffctdef.c  factlhs.c   insfile.c   objrtbld.c  scanner.c
	classcom.c  dffctpsr.c  factmch.c   insfun.c    objrtcmp.c  sortfun.c
	classexm.c  dffnxbin.c  factmngr.c  insmngr.c   objrtfnx.c  strngfun.c
	classfun.c  dffnxcmp.c  factprt.c   insmoddp.c  objrtgen.c  strngrtr.c
	classinf.c  dffnxexe.c  factqpsr.c  insmult.c   objrtmch.c  symblbin.c
	classini.c  dffnxfun.c  factqury.c  inspsr.c    parsefun.c  symblcmp.c
	classpsr.c  dffnxpsr.c  factrete.c  insquery.c  pattern.c   symbol.c
	clsltpsr.c  dfinsbin.c  factrhs.c   insqypsr.c  pprint.c    sysdep.c
	commline.c  dfinscmp.c  filecom.c   iofun.c     prccode.c   textpro.c
	conscomp.c  drive.c     filertr.c   lgcldpnd.c  prcdrfun.c  tmpltbin.c
	constrct.c  emathfun.c  fileutil.c  main.c      prcdrpsr.c  tmpltbsc.c
	constrnt.c  engine.c    generate.c  memalloc.c  prdctfun.c  tmpltcmp.c
	crstrtgy.c  envrnbld.c  genrcbin.c  miscfun.c   prntutil.c  tmpltdef.c
	cstrcbin.c  envrnmnt.c  genrccmp.c  modulbin.c  proflfun.c  tmpltfun.c
	cstrccom.c  evaluatn.c  genrccom.c  modulbsc.c  reorder.c   tmpltlhs.c
	cstrcpsr.c  expressn.c  genrcexe.c  modulcmp.c  reteutil.c  tmpltpsr.c
	cstrnbin.c  exprnbin.c  genrcfun.c  moduldef.c  retract.c   tmpltrhs.c
	cstrnchk.c  exprnops.c  genrcpsr.c  modulpsr.c  router.c    tmpltutl.c
	cstrncmp.c  exprnpsr.c  globlbin.c  modulutl.c  rulebin.c   userdata.c
	cstrnops.c  extnfunc.c  globlbsc.c  msgcom.c    rulebld.c   userfunctions.c
	cstrnpsr.c  factbin.c   globlcmp.c  msgfun.c    utility.c
	cstrnutl.c  factbld.c   globlcom.c  msgpass.c   rulecmp.c   watch.c
	default.c   factcmp.c   globldef.c  msgpsr.c    rulecom.c
)

#target_link_libraries(clips m)
#set_target_properties(clips PROPERTIES
#	PUBLIC_HEADER clips.h
#)

#install(FILES clips.h DESTINATION include)
#install(TARGETS clips DESTINATION lib)
