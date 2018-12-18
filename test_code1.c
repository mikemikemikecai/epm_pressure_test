Action()
{
    int nHttpRetCode;

    web_set_max_html_param_len("44662");

    //web_reg_save_param("X-ORACLE-BPMUI-CSRF", "LB=X-ORACLE-BPMUI-CSRF=", "RB=", "Search=Headers", LAST);
	web_reg_save_param_regexp(
		"ParamName=X-ORACLE-BPMUI-CSRF",
		"RegExp=X-ORACLE-BPMUI-CSRF:\\ (.*?)\\\r\\\n",
		SEARCH_FILTERS,
		"Scope=Headers",
		"IgnoreRedirections=No",
		LAST);
   
	
	web_reg_save_param("sso_token","LB=CDATA[","RB=]]></token>", "Search=Body", LAST);
	web_reg_save_param("ora_epm_ctg","LB=<assertertoken><![CDATA[","RB=]]></assertertoken>", "Search=Body", LAST);

    lr_start_transaction("login");
    web_add_cookie("ORA_EPMWS_User=admin; DOMAIN=192.168.60.125");

    web_add_cookie("ORA_EPMWS_Locale=zh_CN; DOMAIN=192.168.60.125");

    web_add_cookie("ORA_EPMWS_AccessibilityMode=false; DOMAIN=192.168.60.125");

    web_add_cookie("ORA_EPMWS_ThemeSelection=Skyros; DOMAIN=192.168.60.125");

    //web_add_header("Cookie","usrsvr=-2102138882.D94E71BF3E5738294DE4B56266B044CA; ORA_EPMWS_session=c52f739b0eefaaa8664c4a461e794b16ef12d8d3960dec31163d9ee9230037835a8f74896422e6c7f1f05a810b77dd44907147cc5ca7da0948ecb9f9b11242d93828b2c83713e62b21dc573639b3cf9c067d5b2e3b6f8e714370816cd04c760ddf5f7a211e4bd5eee1105e61ad22e32a4bb28546ac0e9afffd030bba9c32a1ff83430e1c2aba17d23e5a2864cd514a62d2391a71806767f05fe66b395dda3e74b75ffa16e80c7814c47657dbc5d652dadba869691bf05fbe306091f3397ec916ad71a4d2b534da7055391aa75efee749f48443370cae430895ac596bdcaafb5a2cbad75e83c7c8454f93177992f9166721331db1e11e48a113a51b3ebc2a79f1d74199127183d7708c47a3ff71663d9d; JSESSIONID=wZDBcGMXYhnXV01NtgT624H6hV24nLMK9SsZTrbwlhphTLJRPvH2!-602621212; ORA_EPMWS_User=admin; ORA_EPMWS_Locale=en_US; ORA_EPMWS_AccessibilityMode=false; ORA_EPMWS_ThemeSelection=Skyros; ORA_EPMWS_timeZone=-480");

	
	//=======登陆(logon)操作

    web_reg_save_param("JSESSIONID", "LB=JSESSIONID=", "RB=; path=/workspace; HttpOnly", "Search=Headers", LAST);
	web_save_header(REQUEST, "RequestHeader");
	web_save_header(RESPONSE,"ResponseHeader");
    web_reg_save_param("ResponseBody", "LB=", "RB=", "Search=Body", LAST);
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
		
    web_add_cookie("JSESSIONID={\"path\": \"/workspace\",\"HttpOnly\": \"true\",\"value\": \"{JSESSIONID}\"}; DOMAIN=192.168.60.125");

    lr_end_transaction("login", LR_AUTO);


    //打印返回信息



    //lr_output_message("# 响应原始内容体：\n %s", lr_eval_string("{ResponseBody}"));
    lr_convert_string_encoding(lr_eval_string("{RequestHeader}"),LR_ENC_UTF8,LR_ENC_SYSTEM_LOCALE,"RequestHeaderUTF8");
    lr_convert_string_encoding(lr_eval_string("{ResponseBody}"),LR_ENC_UTF8 ,LR_ENC_SYSTEM_LOCALE,"ResponseBodyUTF8");
	
    lr_output_message("# 1. 登陆(logon)操作获得的 RequestHeader 响应头信息：\n %s", lr_eval_string("{RequestHeaderUTF8}"));
    lr_output_message("# 1. 登陆(logon)操作获得的 ResponseHeader 响应头信息：\n %s", lr_eval_string("{ResponseHeader}"));
    lr_output_message("# 1. 登陆(logon)操作获得的 ResponseBodyUTF8 响应解码后内容体：\n %s", lr_eval_string("{ResponseBodyUTF8}"));
    lr_output_message("# 1. 登陆(logon)操作获得的 JSESSIONID\n %s", lr_eval_string("{JSESSIONID}"));
    lr_output_message("# 1. 登陆(logon)操作获得的 X-ORACLE-BPMUI-CSRF\n %s", lr_eval_string("{X-ORACLE-BPMUI-CSRF}"));

        //获取服务器http响应码

    nHttpRetCode = web_get_int_property(HTTP_INFO_RETURN_CODE);

    if(nHttpRetCode == 200){
        lr_output_message("#    1.1. 登陆成功Success!");
    }else{
        lr_output_message("#    1.1. 登陆失败Failed!");
    }

        // 打印token值，此时token值存在了loginToken变量中，在后续的操作中你可以随意使用

    lr_log_message("#    1.2. 登陆(logon)获得的 SSO_TOKEN user token is:%s",lr_eval_string("{sso_token}"));
	//=======================dyn
	web_reg_save_param("ResponseBody", "LB=", "RB=", "Search=Body", LAST);
	web_save_header(REQUEST, "RequestHeader");
    web_save_header(RESPONSE,"ResponseHeader");
	//web_reg_save_param("ORA_EPMWS_session", "LB=ORA_EPMWS_session=", "RB=; path=/raframework", "Search=Headers", LAST);
	web_add_header("ora_epm_ctg","{ora_epm_ctg}");
	web_custom_request("dyn", 
		"URL=http://192.168.60.125:19000/raframework/browse/dyn", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=text/xml;charset=UTF-8", 
		"Referer=http://192.168.60.125:19000/workspace/index.jsp?framed=true", 
		"Snapshot=t86.inf", 
		"Mode=HTML", 
		"EncType=application/x-www-form-urlencoded;charset=UTF-8", 
		"Body=page=/conf/CDSConfig.jsp&amp&action=returnXML&LOCALE_LANGUAGE=en_US&rightToLeft=false&accessibilityMode=false&themeSelection=Skyros&sso_token={sso_token}", 
		LAST);

    lr_convert_string_encoding(lr_eval_string("{RequestHeader}"),LR_ENC_UTF8,LR_ENC_SYSTEM_LOCALE,"RequestHeaderUTF8");
    lr_output_message("# 2. 登陆后dyn操作获得的 RequestHeader 响应头信息：\n %s", lr_eval_string("{RequestHeaderUTF8}"));
	lr_output_message("# 2. 登陆后dyn操作获得的 ORA_EPMWS_session: \n %s",lr_eval_string("{ORA_EPMWS_session}"));
	lr_output_message("# 2. 登陆后dyn操作获得的 ResponseBody ，响应包体: \n %s",lr_eval_string("{ResponseBody}"));
	lr_output_message("# 2. 登陆后dyn操作获得的 ResponseHeader ，响应头部: \n %s",lr_eval_string("{ResponseHeader}"));
	

		
    return 0;
}




/*

Virtual User Script started at : 2018/12/5 15:04:09
Starting action vuser_init.
Web Turbo Replay of LoadRunner 12.0.0 for Windows 2012 R2; build 2739 (Nov 30 2014 23:13:05)  	[MsgId: MMSG-27143]
Run mode: HTML  	[MsgId: MMSG-26993]
Run-Time Settings file: "C:\Users\Administrator\Documents\VuGen\Scripts\WebHttpHtml3\\default.cfg"  	[MsgId: MMSG-27141]
Ending action vuser_init.
Running Vuser...
Starting iteration 1.
Maximum number of concurrent connections per server: 6  	[MsgId: MMSG-26989]
Starting action Action.
Action.c(5): web_set_max_html_param_len started  	[MsgId: MMSG-26355]
Action.c(5): web_set_max_html_param_len was successful  	[MsgId: MMSG-26392]
Action.c(8): web_reg_save_param_regexp started  	[MsgId: MMSG-26355]
Action.c(8): Registering web_reg_save_param_regexp was successful  	[MsgId: MMSG-26390]
Action.c(17): web_reg_save_param started  	[MsgId: MMSG-26355]
Action.c(17): Registering web_reg_save_param was successful  	[MsgId: MMSG-26390]
Action.c(18): web_reg_save_param started  	[MsgId: MMSG-26355]
Action.c(18): Registering web_reg_save_param was successful  	[MsgId: MMSG-26390]
Action.c(20): Notify: Transaction "login" started.
Action.c(21): web_add_cookie started  	[MsgId: MMSG-26355]
Action.c(21): web_add_cookie was successful  	[MsgId: MMSG-26392]
Action.c(23): web_add_cookie started  	[MsgId: MMSG-26355]
Action.c(23): web_add_cookie was successful  	[MsgId: MMSG-26392]
Action.c(25): web_add_cookie started  	[MsgId: MMSG-26355]
Action.c(25): web_add_cookie was successful  	[MsgId: MMSG-26392]
Action.c(27): web_add_cookie started  	[MsgId: MMSG-26355]
Action.c(27): web_add_cookie was successful  	[MsgId: MMSG-26392]
Action.c(34): web_reg_save_param started  	[MsgId: MMSG-26355]
Action.c(34): Registering web_reg_save_param was successful  	[MsgId: MMSG-26390]
Action.c(35): web_save_header started  	[MsgId: MMSG-26355]
Action.c(35): web_save_header was successful  	[MsgId: MMSG-26392]
Action.c(36): web_save_header started  	[MsgId: MMSG-26355]
Action.c(36): web_save_header was successful  	[MsgId: MMSG-26392]
Action.c(37): web_reg_save_param started  	[MsgId: MMSG-26355]
Action.c(37): Registering web_reg_save_param was successful  	[MsgId: MMSG-26390]
Action.c(38): web_custom_request("logon") started  	[MsgId: MMSG-26355]
Action.c(38): web_custom_request("logon") was successful, 567 body bytes, 1160 header bytes, 17 chunking overhead bytes  	[MsgId: MMSG-26385]
Action.c(50): web_add_cookie started  	[MsgId: MMSG-26355]
Action.c(50): web_add_cookie was successful  	[MsgId: MMSG-26392]
Action.c(62): # 1. 登陆(logon)操作获得的 RequestHeader 响应头信息：
 POST /workspace/logon HTTP/1.1
Content-Type: application/x-www-form-urlencoded;charset=UTF-8
Referer: http://192.168.60.125:19000/workspace/index.jsp?framed=true
User-Agent: Mozilla/5.0 (Windows NT 6.3; Win64; x64; Trident/7.0; rv:11.0) like Gecko
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN
Accept: */*
Connection: Keep-Alive
Host: 192.168.60.125:19000
Cookie: ORA_EPMWS_User=admin; ORA_EPMWS_Locale=zh_CN; ORA_EPMWS_AccessibilityMode=false; ORA_EPMWS_ThemeSelection=Skyros
Content-Length: 117
Action.c(63): # 1. 登陆(logon)操作获得的 ResponseHeader 响应头信息：
 HTTP/1.1 200 OK
Date: Wed, 05 Dec 2018 07:03:50 GMT
Server: Oracle-Application-Server-11g
Cache-Control: no-store, no-cache, must-revalidate
Pragma: no-cache
Expires: Thu, 01 Jan 1970 00:00:00 GMT
X-Content-Type-Options: nosniff
X-ORACLE-BPMUI-CSRF: 524FA4F955FC7394AF6AFC0C382F7E41B8A1C4E69BFB699D0A714BC4FB2217F8E495F9066BD66091CFB3CAE4B34FFAF51D1520580D1544CABA0367E26EE31BE5
X-ORACLE-DMS-ECID: 00iqhT4UmDw2nJWjLxATOA00015W0037FK
X-Powered-By: Servlet/2.5 JSP/2.1
X-SSO-Login-Status: 1
Set-Cookie: JSESSIONID=qDSRcH4WQq782yvpnCWPVnp0gTJTxXWSw2xRTg2dldH3GcS8CyLB!-602621212; path=/workspace; HttpOnly
Set-Cookie: ORA_EPMWS_User=admin; expires=Fri, 04-Jan-2019 07:03:50 GMT; path=/
Set-Cookie: ORA_EPMWS_Locale=zh_CN; expires=Thu, 05-Dec-2019 07:03:50 GMT; path=/
Set-Cookie: ORA_EPMWS_AccessibilityMode=false; expires=Thu, 05-Dec-2019 07:03:50 GMT; path=/
Set-Cookie: ORA_EPMWS_ThemeSelection=Skyros; expires=Thu, 05-Dec-2019 07:03:50 GMT; path=/
Vary: Accept-Encoding
Content-Encoding: gzip
Keep-Alive: timeout=180, max=100
Connection: Keep-Alive
Transfer-Encoding: chunked
Content-Type: text/xml;charset=UTF-8
Content-Language: en
Action.c(64): # 1. 登陆(logon)操作获得的 ResponseBodyUTF8 响应解码后内容体：
 <?xml version="1.0" encoding="UTF-8"?><BpmResponse type="success"><token><![CDATA[buLcGQQQOwUF344Cz/uBaYnkzJqc2xzXXcrc9VsLLbGUfgPuBLKUx0kKQ4acEzmjsym1GQJ74oYmqvDWYjkmaGsAdBZ3EBZzfncd95GT+/dF5MmKXOCp9MXYfNCqadYB9bPyx7xd4QeWUUYwV2x36zjK0xXM98HFw/vWFeKT5d8RsxUXXM22d9XwjO9cPtW3xeP77XtZSKK8euixzJ5RzMxahEkeXeQYFSoAMNRhTaBFbckwb9Oqz+qdhRYh1y8pj95UZC8WeKTEqT86mGLHL9X8omWApYLEup3Sdr5j77xoEHhSVpipByOeMgtITp2SgKqOB+YCsO95aqtIjixqtwtT8F9h6Y9DQM6BYwxtmvUaoLo2Ji3yIAS4pcaXE6oN0tVHX9BCMcln247yz49q65n7fBie/wAEAlWHZ/68D5FD5ioN4v/RsVyedYcSOhY7]]></token><user><![CDATA[admin]]></user><assertertoken><![CDATA[qyXvqIgII872oxf1jYUTQmZSticKNAHhLAPXotLUFeOWsTNK92z%2Fm2JpZFL9fst6]]></assertertoken></BpmResponse>
Action.c(65): # 1. 登陆(logon)操作获得的 JSESSIONID
 qDSRcH4WQq782yvpnCWPVnp0gTJTxXWSw2xRTg2dldH3GcS8CyLB!-602621212
Action.c(66): # 1. 登陆(logon)操作获得的 X-ORACLE-BPMUI-CSRF
 524FA4F955FC7394AF6AFC0C382F7E41B8A1C4E69BFB699D0A714BC4FB2217F8E495F9066BD66091CFB3CAE4B34FFAF51D1520580D1544CABA0367E26EE31BE5
Action.c(70): web_get_int_property started  	[MsgId: MMSG-26355]
Action.c(70): web_get_int_property was successful  	[MsgId: MMSG-26392]
Action.c(73): #    1.1. 登陆成功Success!
#    1.2. 登陆(logon)获得的 SSO_TOKEN user token is:buLcGQQQOwUF344Cz/uBaYnkzJqc2xzXXcrc9VsLLbGUfgPuBLKUx0kKQ4acEzmjsym1GQJ74oYmqvDWYjkmaGsAdBZ3EBZzfncd95GT+/dF5MmKXOCp9MXYfNCqadYB9bPyx7xd4QeWUUYwV2x36zjK0xXM98HFw/vWFeKT5d8RsxUXXM22d9XwjO9cPtW3xeP77XtZSKK8euixzJ5RzMxahEkeXeQYFSoAMNRhTaBFbckwb9Oqz+qdhRYh1y8pj95UZC8WeKTEqT86mGLHL9X8omWApYLEup3Sdr5j77xoEHhSVpipByOeMgtITp2SgKqOB+YCsO95aqtIjixqtwtT8F9h6Y9DQM6BYwxtmvUaoLo2Ji3yIAS4pcaXE6oN0tVHX9BCMcln247yz49q65n7fBie/wAEAlWHZ/68D5FD5ioN4v/RsVyedYcSOhY7
Action.c(82): web_reg_save_param started  	[MsgId: MMSG-26355]
Action.c(82): Registering web_reg_save_param was successful  	[MsgId: MMSG-26390]
Action.c(83): web_save_header started  	[MsgId: MMSG-26355]
Action.c(83): web_save_header was successful  	[MsgId: MMSG-26392]
Action.c(84): web_save_header started  	[MsgId: MMSG-26355]
Action.c(84): web_save_header was successful  	[MsgId: MMSG-26392]
Action.c(86): web_add_header("ora_epm_ctg") started  	[MsgId: MMSG-26355]
Action.c(86): web_add_header("ora_epm_ctg") was successful  	[MsgId: MMSG-26392]
Action.c(87): web_custom_request("dyn") started  	[MsgId: MMSG-26355]
Action.c(87): web_custom_request("dyn") was successful, 166 body bytes, 459 header bytes, 16 chunking overhead bytes  	[MsgId: MMSG-26385]
Action.c(100): # 2. 登陆(logon)操作获得的 RequestHeader 响应头信息：
 POST /raframework/browse/dyn HTTP/1.1
Content-Type: application/x-www-form-urlencoded;charset=UTF-8
Referer: http://192.168.60.125:19000/workspace/index.jsp?framed=true
ora_epm_ctg: qyXvqIgII872oxf1jYUTQmZSticKNAHhLAPXotLUFeOWsTNK92z%2Fm2JpZFL9fst6
User-Agent: Mozilla/5.0 (Windows NT 6.3; Win64; x64; Trident/7.0; rv:11.0) like Gecko
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN
Accept: */*
Connection: Keep-Alive
Host: 192.168.60.125:19000
Cookie: ORA_EPMWS_User=admin; ORA_EPMWS_Locale=zh_CN; ORA_EPMWS_AccessibilityMode=false; ORA_EPMWS_ThemeSelection=Skyros; JSESSIONID={"path": "/workspace","HttpOnly": "true","value": "qDSRcH4WQq782yvpnCWPVnp0gTJTxXWSw2xRTg2dldH3GcS8CyLB!-602621212"}
Content-Length: 590
Action.c(101): # 2. 登陆后dyn操作获得的 ORA_EPMWS_session: 
 {ORA_EPMWS_session}
Action.c(102): # 2. 登陆后dyn操作获得的 ResponseBody ，响应包体: 
 <?xml version="1.0"?><BpmResponse type='error'><code>-3</code><desc><![CDATA[You must supply a valid User Name and Password to log onto the system.]]></desc></BpmResponse>
Action.c(103): # 2. 登陆后dyn操作获得的 ResponseHeader ，响应头部: 
 HTTP/1.1 200 OK
Date: Wed, 05 Dec 2018 07:03:50 GMT
Server: Oracle-Application-Server-11g
Cache-Control: private
Expires: 0
Last-Modified: Wed, 05 Dec 2018 07:03:50 GMT
X-ORACLE-DMS-ECID: 00iqhT4WbQK2nJWjLxATOA00015W0037FL
X-Powered-By: Servlet/2.5 JSP/2.1
Vary: Accept-Encoding
Content-Encoding: gzip
Keep-Alive: timeout=180, max=99
Connection: Keep-Alive
Transfer-Encoding: chunked
Content-Type: text/xml;charset=UTF-8
Content-Language: en
Action.c(105): Notify: Transaction "login" ended with a "Pass" status (Duration: 0.5572 Wasted Time: 0.1603).
Ending action Action.
Ending iteration 1.
Ending Vuser...
Starting action vuser_end.
Ending action vuser_end.
Vuser Terminated.






*/