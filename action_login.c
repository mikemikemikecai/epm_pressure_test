Action_login()
{
    ExtendedLog(1);    // 开启扩展日志

	web_reg_save_param_ex(
		"ParamName=sso_param",
		"LB=""",
		"RB=""",
		SEARCH_FILTERS,
		"Scope=Body",
		"RequestUrl=http://192.168.60.125:19000/workspace/logon",
		LAST);
	web_reg_save_param("sso_token","LB=CDATA[","RB=]]></token", SEARCH_FILTERS,"Scope=Body","RequestUrl=http://192.168.60.125:19000/workspace/logon",LAST);
	web_add_cookie("ORA_EPMWS_User=admin; DOMAIN=192.168.60.125");

	web_add_cookie("ORA_EPMWS_Locale=zh_CN; DOMAIN=192.168.60.125");

	web_add_cookie("ORA_EPMWS_AccessibilityMode=false; DOMAIN=192.168.60.125");

	web_add_cookie("ORA_EPMWS_ThemeSelection=Skyros; DOMAIN=192.168.60.125");
	
	web_add_header("Cookie","usrsvr=-2102138882.D94E71BF3E5738294DE4B56266B044CA; ORA_EPMWS_session=c52f739b0eefaaa8664c4a461e794b16ef12d8d3960dec31163d9ee9230037835a8f74896422e6c7f1f05a810b77dd44907147cc5ca7da0948ecb9f9b11242d93828b2c83713e62b21dc573639b3cf9c067d5b2e3b6f8e714370816cd04c760ddf5f7a211e4bd5eee1105e61ad22e32a4bb28546ac0e9afffd030bba9c32a1ff83430e1c2aba17d23e5a2864cd514a62d2391a71806767f05fe66b395dda3e74b75ffa16e80c7814c47657dbc5d652dadba869691bf05fbe306091f3397ec916ad71a4d2b534da7055391aa75efee749f48443370cae430895ac596bdcaafb5a2cbad75e83c7c8454f93177992f9166721331db1e11e48a113a51b3ebc2a79f1d74199127183d7708c47a3ff71663d9d; JSESSIONID=wZDBcGMXYhnXV01NtgT624H6hV24nLMK9SsZTrbwlhphTLJRPvH2!-602621212; ORA_EPMWS_User=admin; ORA_EPMWS_Locale=en_US; ORA_EPMWS_AccessibilityMode=false; ORA_EPMWS_ThemeSelection=Skyros; ORA_EPMWS_timeZone=-480");

	web_custom_request("logon", 
		"URL=http://192.168.60.125:19000/workspace/logon", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=text/xml", 
		"Referer=http://192.168.60.125:19000/workspace/index.jsp?framed=true", 
		"Snapshot=t47.inf", 
		"Mode=HTML", 
		"EncType=application/x-www-form-urlencoded;charset=UTF-8", 
		"Body=sso_username=admin&sso_password=Passw0rd&LOCALE_LANGUAGE=%20&rightToLeft=%20&accessibilityMode=%20&themeSelection=%20", 
		LAST);
	web_reg_save_param("sso_token","LB=CDATA[","RB=]]></token", LAST);
    ExtendedLog(0);    // 关闭扩展日志

	web_submit_data("Adf.jsp_5", 
		"Action=http://192.168.60.125:19000/workspace/modules/com/oracle/workspace/mode/Adf.jsp", 
		"Method=POST", 
		"RecContentType=text/xml", 
		"Referer=http://192.168.60.125:19000/workspace/index.jsp?framed=true", 
		"Snapshot=t17.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=instance", "Value=2", ENDITEM, 
		"Name=serverName", "Value=Workspace", ENDITEM, 
		"Name=resizeContentInterval", "Value=2000", ENDITEM, 
		"Name=LOCALE_LANGUAGE", "Value=zh_CN", ENDITEM, 
		"Name=rightToLeft", "Value=false", ENDITEM, 
		"Name=accessibilityMode", "Value=false", ENDITEM, 
		"Name=themeSelection", "Value=Skyros", ENDITEM, 
		"Name=sso_token", "Value={sso_token}", ENDITEM, 
		EXTRARES, 
		"Url=/workspace/cache/2018-11-26_17-29-45/static/js/com/oracle/workspace/roles/Roles.js", "Referer=http://192.168.60.125:19000/workspace/index.jsp?framed=true", ENDITEM, 
		"Url=/workspace/static/resources/wksp_zh-CN.js", "Referer=http://192.168.60.125:19000/workspace/index.jsp?framed=true", ENDITEM, 
		"Url=/workspace/cache/2018-11-26_17-29-45/static/js/com/oracle/workspace/services/Services.js", "Referer=http://192.168.60.125:19000/workspace/index.jsp?framed=true", ENDITEM, 
		"Url=/epmstatic/raframework/resources/cds_global_zh-CN.js", "Referer=http://192.168.60.125:19000/workspace/index.jsp?framed=true", ENDITEM, 
		LAST);


	web_custom_request("dyn", 
		"URL=http://192.168.60.125:19000/raframework/browse/dyn", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=text/xml", 
		"Referer=http://192.168.60.125:19000/workspace/index.jsp?framed=true", 
		"Snapshot=t18.inf", 
		"Mode=HTML", 
		"EncType=application/x-www-form-urlencoded;charset=UTF-8", 
		"Body=page=%2Fconf%2FCDSConfig.jsp&amp&action=returnXML&LOCALE_LANGUAGE=zh_CN&rightToLeft=false&accessibilityMode=false&themeSelection=Skyros&sso_token="
		"{sso_token}", 
		EXTRARES, 
		"Url=../js/com/hyperion/wsearch/util/launchRepositoryDocument.js", "Referer=http://192.168.60.125:19000/workspace/index.jsp?framed=true", ENDITEM, 
		"Url=../js/com/hyperion/tools/cds/lang/Lang.js", "Referer=http://192.168.60.125:19000/workspace/index.jsp?framed=true", ENDITEM, 
		"Url=../js/com/hyperion/tools/cds/util/Util.js", "Referer=http://192.168.60.125:19000/workspace/index.jsp?framed=true", ENDITEM, 
		"Url=../js/com/hyperion/tools/cds/data/Data.js", "Referer=http://192.168.60.125:19000/workspace/index.jsp?framed=true", ENDITEM, 
		"Url=../js/com/hyperion/tools/cds/bindows/Bindows.js", "Referer=http://192.168.60.125:19000/workspace/index.jsp?framed=true", ENDITEM, 
		"Url=../js/com/hyperion/tools/cds/repository/Repository.js", "Referer=http://192.168.60.125:19000/workspace/index.jsp?framed=true", ENDITEM, 
		"Url=../resources/cds_zh-CN.js", "Referer=http://192.168.60.125:19000/workspace/index.jsp?framed=true", ENDITEM, 
		"Url=../js/com/hyperion/tools/cds/Cds.js", "Referer=http://192.168.60.125:19000/workspace/index.jsp?framed=true", ENDITEM, 
		LAST);
	web_reg_save_param_ex("ParamName=usrsvr",
		"LB=usrsvr=",
		"RB=; expires=",
		SEARCH_FILTERS,
		"Scope=All",
		LAST);
	web_reg_save_param_ex("ParamName=ORA_EPMWS_session",
		"LB=ORA_EPMWS_session=",
		"RB=; JSESSIONID=",
		SEARCH_FILTERS,
		"Scope=All",
		LAST);
	web_reg_save_param_ex("ParamName=c_dtCookie",
		"LB=JSESSIONID=",
		"RB=; ORA_EPMWS_User=admin",
		SEARCH_FILTERS,
		"Scope=All",
		LAST);
	web_add_header("Cookie","usrsvr={usrsvr}; ORA_EPMWS_session={ORA_EPMWS_session} JSESSIONID={c_dtCookie}; ORA_EPMWS_User=admin; ORA_EPMWS_Locale=en_US; ORA_EPMWS_AccessibilityMode=false; ORA_EPMWS_ThemeSelection=Skyros; ORA_EPMWS_timeZone=-480");
	
	web_add_cookie("usrsvr={usrsvr}; DOMAIN=192.168.60.125");
	web_add_cookie("ORA_EPMWS_session={ORA_EPMWS_session}; path=/raframework");

		
	
	
/*Correlation comment - Do not change!  Original value='0A5B4D5E9BFC5ABF43A2B45B7E38B3BAEE778FE9B7ED731E227F4679A04CB1B520C29B009DC1B9339535E2679C0756604D2262D327B2D9BA1BD28EB2CF3B5CF1' Name ='X-ORACLE-BPMUI-CSRF' Type ='ResponseBased'*/
	web_reg_save_param_regexp(
		"ParamName=X-ORACLE-BPMUI-CSRF",
		"RegExp=X-ORACLE-BPMUI-CSRF:\\ (.*?)\\\r\\\n",
		SEARCH_FILTERS,
		"Scope=Headers",
		"IgnoreRedirections=No",
		LAST);	
		
	web_reg_save_param_regexp(
		"ParamName=X-ORACLE-DMS-ECID",
		"RegExp=X-ORACLE-DMS-ECID:\\ (.*?)\\\r\\\n",
		SEARCH_FILTERS,
		"Scope=Headers",
		"IgnoreRedirections=No",
		LAST);

	web_reg_save_param_regexp(
		"ParamName=X-SSO-Token",
		"RegExp=X-SSO-Token:\\ (.*?)\\\r\\\n",
		SEARCH_FILTERS,
		"Scope=Headers",
		"IgnoreRedirections=No",
		LAST);



	web_add_header("Cookie","JSESSIONID={c_dtCookie}");
	

	web_add_cookie("X-ORACLE-DMS-ECID: {X-ORACLE-DMS-ECID}");
	web_add_cookie("X-ORACLE-BPMUI-CSRF: {X-ORACLE-BPMUI-CSRF}");
	
	// web_add_cookie("X-ORACLE-BPMUI-CSRF: {X-ORACLE-BPMUI-CSRF}");
	
	return 0;
}