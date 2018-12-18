#! py -3
# -*- coding: utf-8 -*-

import requests
from urllib.parse import quote
import logging
from urllib.parse import urlparse

logger = logging.getLogger(__name__)

logger = logging.getLogger()
# 配置日志级别，如果不显示配置，默认为Warning，表示所有warning级别已下的其他level直接被省略，
# 内部绑定的handler对象也只能接收到warning级别以上的level，你可以理解为总开关
logger.setLevel(logging.INFO)

formatter = logging.Formatter(fmt="%(asctime)s %(filename)s[line:%(lineno)d]%(levelname)s - %(message)s",
                              datefmt="%m/%d/%Y %I:%M:%S %p")  # 创建一个格式化对象

console = logging.StreamHandler() # 配置日志输出到控制台
console.setLevel(logging.INFO) # 设置输出到控制台的最低日志级别
console.setFormatter(formatter)  # 设置格式
logger.addHandler(console)


#  后续这些配置项都会移动到一个单独的配置文件
userAgent = "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36"
# serverUrl = "http://192.168.60.125:19000/"
serverUrl = "http://epm.huaxinglu72hao.com/"
host = "epm.huaxinglu72hao.com"
#  定义当前会话
# 会话使用统一的header 和 cookie
# 下面代码更新header 和 cookie 的使用后续的所有请求都会使用更新后的header 和 cookie
# 所以下面的函数没有返回值
s = requests.Session()
s.headers.update({"User-Agent": userAgent})
s.headers.update({"Referer": serverUrl})
s.headers.update({"Host": host})






def workspaceLogon(account, password):
    #  登录
    logger.info("logon: 开始模拟登录workspace")

    postUrl = "%sworkspace/logon" % serverUrl
    postData = {
        "sso_username": account,
        "sso_password": password,
    }
    try:
        responseRes = s.post(postUrl, data = postData)
    except Exception as e:
        logger.error(e)
        raise RuntimeError("登录失败: 网络异常, 请检查服务器地址配置")



    logger.info("登录返回: " + responseRes.text)

    # 无论是否登录成功，状态码一般都是 statusCode = 200
    sso_token = responseRes.text.split('[')[2].split(']')[0]
    assertertoken = responseRes.text.split('[')[6].split(']')[0]

    assertertoken_ = {"ora_epm_ctg": assertertoken}

    updateHeaders(assertertoken_)

    token = {"_sso_token": sso_token}
    updateHeaders(token)


    CSRF = responseRes.headers.get("X-ORACLE-BPMUI-CSRF")
    csrf_ = {"X-ORACLE-BPMUI-CSRF": CSRF}
    updateHeaders(csrf_)

    ECID = responseRes.headers.get("X-ORACLE-DMS-ECID")
    h = {"X-ORACLE-DMS-ECID": ECID}

    updateHeaders(h)


def updateHeaders(h):
    logger.info(f"更新请求头: {h}")
    s.headers.update(h)


def request_dyn():

    logger.info ("dyn: 开始测试请求")
    postUrl = "%s/raframework/browse/dyn" % serverUrl
    postData={
        "page": "/conf/CDSConfig.jsp",
        "amp":"",
        "action": "returnXML",
        "LOCALE_LANGUAGE": "en_US",
        "rightToLeft": "false",
        "accessibilityMode": "false",
        "themeSelection": "Skyros",
        "sso_token": s.headers.get("_sso_token")
    }
    responseRes = s.post(postUrl, data=postData)
    # logger.info(f"dyn: 响应text：{responseRes.text}")
    logger.info(f"dyn: 响应header：{responseRes.headers}")

def request_planning_session(plan_name):
    """
    "accessibilityMode":	"false",
    "bpm.contentheight":	"621",
    "bpm.contentwidth":	"1314",
    "bpm.objectpaletteheight":	"648",
    "bpm.objectpalettewidth":	"207",
    "cluster":	"PLANNING_LWA",
    "instance":	"7",
    "LOCALE_LANGUAGE":	"zh_CN",
    "mru_id":	"PLANNING_LWA_JSTI1:application",
    "repository_token":	"59d9b714b22a35fb616dd3c05c5850d56b12522a9561499e9ea22afd918b6d36ea703f19668538504f86305c84f95441a1daf4cac09725703738d5073524871af0489411df16d2bb8f5d4726acdcc389b45e9e6ff00482249c53c1886ca68bfc090fcfbd365243996436f5bbe3affd9c87f6d5e8b7626e59adaeebcc4a89a66ef9725d8d4218c8b0c15912455a2690fcd2391a71806767f05fe66b395dda3e74b75ffa16e80c7814c47657dbc5d652da1044edc74ff20d6e604bdd733542457c3befca52c0700d758445b00ad519d0e8dee43e40cb78e070caca6b7c7a56008b2cbad75e83c7c8454f93177992f9166721331db1e11e48a113a51b3ebc2a79f1d74199127183d7708c47a3ff71663d9d",
    "rightToLeft":	"false",
    "sourceApp":	"JSTI1",
    "sso_token":	"sJIsuVcoOMtHD5CgUaVLmuo4SfCatQy4dowOxaTF0cj1CDqPrPW8YYKvn4nU5rsBYG1yLUChBU/ndO+3pDhwFcRbHJZmaiUOnyFhEh97A5xDXatOpkhIPx4CW+ygHNQlmKrbgUZEmJBgwNT4lcBuDPCZiodPZBo3zCkrSMLQcq0R8qoX6nHvfSVW3ep86WHDyJ859v9OCxcbo4FD4tSv4fTdHGdkGtQaRpdMtuSGtvY2hB+Z7MPEHqkhkIVAt0WWVplND5rUdF5yrLVsywYLWq7I2GH3/UVnwSgsmQy/psjChbnHkzqAcxNg837XRFI1EZBVxaGvdJw6U2mu3qlD29oYi2C/UqwODIjXGtj/st29j6fvd3lJHpsneutkVoG0E/mohFU+JzQaCnopeA+L3A8pORvkfwSyqhURqiLLHS0=",
    "themeSelection":	"Skyros",


    """




    logger.info ("planning_session: 开始测试请求")
    postUrl = "%s/HyperionPlanning/modules/com/hyperion/planning/Adf.jsp" % serverUrl
    postData={
        "accessibilityMode": "false",
        "bpm.contentheight": "621",
        "bpm.contentwidth": "1314",
        "bpm.objectpaletteheight": "648",
        "bpm.objectpalettewidth": "207",
        "cluster": "PLANNING_LWA",
        "instance": "7",
        "LOCALE_LANGUAGE": "zh_CN",
        "mru_id": f"PLANNING_LWA_{plan_name}:application",
        "repository_token": s.cookies.get("ORA_EPMWS_session"),
        "rightToLeft": "false",
        "sourceApp": plan_name,
        "sso_token": s.headers.get("_sso_token"),
        "themeSelection": "Skyros",
    }
    responseRes = s.post(postUrl, data=postData)
    # logger.info(f"dyn: 响应text：{responseRes.text}")
    logger.info(f"planning_session: 响应cookie：{responseRes.cookies}")

    #     手动添加两个cookie
    s.cookies.set("ORA_HP_MRUApplication", plan_name, path="/HyperionPlanning/", domain=host)
    s.cookies.set("ORA_HP_MRUUsername", s.cookies.get("ORA_EPMWS_User"), path="/HyperionPlanning/", domain=host)

    logger.info("当前的header为: " + str(s.headers))
    logger.info("当前的cookie为: " + str(s.cookies))
    # logger.info(f"planning_session: 响应：{responseRes.text}")

#  访问一个具体的表单
import re
def request_planning_table():
    # 下面的数据都是写死的, 只适用于JSTI->A0000主要指标表
    s.headers["Adf-Ads-Page-Id"] = "2"
    s.headers["Adf-Rich-Message"] = "true"
    url = serverUrl + "/HyperionPlanning/faces/PlanningCentral?_adf.ctrl-state=9gxaes0ha_55?_adf.ctrl-state="
    response = s.post(url + "14hssan6gi_4",
                      data="p:r:0:pc1:searchName=&org.apache.myfaces.trinidad.faces.FORM=f1&javax.faces.ViewState=!-9xx6pbfv3&oracle.adf.view.rich.DELTAS=%7Bp%3Ar%3A0%3Apc1%3AformTbl%3D%7BviewportSize%3D27%2Crows%3D33%2CscrollTopRowKey%7Cp%3D0%7D%2Cp%3AformTbl%3D%7BselectedRowKeys%3D0%7D%7D&event=p%3AloadBtn&event.p:loadBtn=%3Cm+xmlns%3D%22http%3A%2F%2Foracle.com%2FrichClient%2Fcomm%22%3E%3Ck+v%3D%22_custom%22%3E%3Cb%3E1%3C%2Fb%3E%3C%2Fk%3E%3Ck+v%3D%22module%22%3E%3Cs%3Eenterdata%3C%2Fs%3E%3C%2Fk%3E%3Ck+v%3D%22folderId%22%3E%3Cs%3E%3C%2Fs%3E%3C%2Fk%3E%3Ck+v%3D%22formId%22%3E%3Cn%3E55532%3C%2Fn%3E%3C%2Fk%3E%3Ck+v%3D%22searchFormName%22%3E%3Cs%3EA0000%E4%B8%BB%E8%A6%81%E6%8C%87%E6%A0%87%E8%A1%A8%3C%2Fs%3E%3C%2Fk%3E%3Ck+v%3D%22adhocSessionIdForForm%22%3E%3Cs%3E%3C%2Fs%3E%3C%2Fk%3E%3Ck+v%3D%22artifactType%22%3E%3Cs%3E%3C%2Fs%3E%3C%2Fk%3E%3Ck+v%3D%22tlArtifactType%22%2F%3E%3Ck+v%3D%22tlArtifactId%22%2F%3E%3Ck+v%3D%22immediate%22%3E%3Cb%3E1%3C%2Fb%3E%3C%2Fk%3E%3Ck+v%3D%22type%22%3E%3Cs%3EloadModule%3C%2Fs%3E%3C%2Fk%3E%3C%2Fm%3E&oracle.adf.view.rich.PROCESS=p%3AloadBtn")


    # 从输出的结果看被重定向了
    logger.info(response.content)

    # m = re.search(r"_adf\.ctrl-state=.+?&", response.text)
    # current = m.group(0).split("=")[1].replace("&", "")
    #
    # response = s.post(url + current,
    #                   data="p:r:0:pc1:searchName=&org.apache.myfaces.trinidad.faces.FORM=f1&javax.faces.ViewState=!-9xx6pbfv3&oracle.adf.view.rich.DELTAS=%7Bp%3Ar%3A0%3Apc1%3AformTbl%3D%7BviewportSize%3D27%2Crows%3D33%2CscrollTopRowKey%7Cp%3D0%7D%2Cp%3AformTbl%3D%7BselectedRowKeys%3D0%7D%7D&event=p%3AloadBtn&event.p:loadBtn=%3Cm+xmlns%3D%22http%3A%2F%2Foracle.com%2FrichClient%2Fcomm%22%3E%3Ck+v%3D%22_custom%22%3E%3Cb%3E1%3C%2Fb%3E%3C%2Fk%3E%3Ck+v%3D%22module%22%3E%3Cs%3Eenterdata%3C%2Fs%3E%3C%2Fk%3E%3Ck+v%3D%22folderId%22%3E%3Cs%3E%3C%2Fs%3E%3C%2Fk%3E%3Ck+v%3D%22formId%22%3E%3Cn%3E55532%3C%2Fn%3E%3C%2Fk%3E%3Ck+v%3D%22searchFormName%22%3E%3Cs%3EA0000%E4%B8%BB%E8%A6%81%E6%8C%87%E6%A0%87%E8%A1%A8%3C%2Fs%3E%3C%2Fk%3E%3Ck+v%3D%22adhocSessionIdForForm%22%3E%3Cs%3E%3C%2Fs%3E%3C%2Fk%3E%3Ck+v%3D%22artifactType%22%3E%3Cs%3E%3C%2Fs%3E%3C%2Fk%3E%3Ck+v%3D%22tlArtifactType%22%2F%3E%3Ck+v%3D%22tlArtifactId%22%2F%3E%3Ck+v%3D%22immediate%22%3E%3Cb%3E1%3C%2Fb%3E%3C%2Fk%3E%3Ck+v%3D%22type%22%3E%3Cs%3EloadModule%3C%2Fs%3E%3C%2Fk%3E%3C%2Fm%3E&oracle.adf.view.rich.PROCESS=p%3AloadBtn")
    #
    # logger.info(response.content)
if __name__ == "__main__":
    # 从返回结果来看，有登录成功
    workspaceLogon("admin", "welcome1")
    request_dyn()
    request_planning_session("JSTI")
    request_planning_table()
    # logger.info("sso_token = %s" % sso_token)
    # logger.info("sso_token = %s" % sso_token)
    # logger.info("assertertoken = %s" % assertertoken)
    # request_dyn(sso_token,assertertoken)
    # requestHSS("tYy6FOvH4ZhJR1CUTy83Q9ZJxiNnYbnAt8fjWcMBII4rEmQlYjth+/M4MLIXVuXp7Hi3xQS4+QRySoxvNuFibcGbxbIYRVLFVKogwyhtIAcvtIXMvfhxd8svcLZgIXyTklurCsTarP9KtRgc26B3XRWlDG/QAzVLWyGH26ROffQpUj+bW6yRrj7A0udq1PbqGFXjDZ9iNW0ALbg0Z5NC7g3pBgjtetBohXRmpV32DCw4tI1Y7j7tLnHtSFk/NtdNri5AAFCTqTPd6HYdBzbCDqfP7ZEdfeXJFsfatRE5Pcgqm36hV1U7HeDENhTvNBtZiiQ9OfMdopyHQQvPnBQsyfKzSKTq1O5bSHH9HzQfCJdvq/nkSbalctY2SxIb0vtefJ9fUZ2y4bMAm/g95EZLiKZ5aouVrzOKjt8sl1zVctk+Ivg141wUPqtTULOYdBoi")


