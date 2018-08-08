/**
 * @File     security_viid_service.cpp
 * @brief    
 * @DateTime 2018/8/4 11:36:40
 * @Author   Anyz
 */
#include "security_viid_service.h"
#include "simple_xml.h"
#include "http_message.h"
#include "security_rest.h"


int security_viid_service::sys_register(const char* ip, int port, const char* deviceId) {
    std::string suri = addressPrefix(ip, port);
    if (suri.empty()) {
        printf("address incorrect.\n");
        return -1;
    }
    suri.append(SECURITY_URL_PATH_VIID_REGISTER);
    if (!deviceId || strlen(deviceId) < 1) {
        printf("device ID invalid.\n");
        return -1;
    }

    http_message hm;
    std::string sxml = makeRegisterMessage(deviceId);
    int ret = hm.post(suri.c_str(), sxml);
    std::string respData;
    respData = hm.message();
    printf("response: %s\n", respData.c_str());
    if (SECURITY_REST_HTTP_RESPONSE_401 == hm.errorCode()) {
        http_message hm;
        
        printf("server response %d\n", ret);
        hm.appendHeaderItem("username:admin");
        hm.appendHeaderItem("password:13579");
        int ret = hm.post(uri, sxml);
        if (SECURITY_REST_HTTP_RESPONSE_200 != hm.errorCode()) {
            printf("Register failed.\n");
            return -1;
        }
    }
    printf("Register success.");
    return 0;
}
/**
 * @Method   sys_unregister
 * @Brief
 * @DateTime 2018-08-04T12:42:02+0800
 * @Modify   2018-08-04T12:42:02+0800
 * @Author   Anyz
 * @param    ip [description]
 * @param    port [description]
 * @param    deviceId [description]
 * @return   [description]
 */
int security_viid_service::sys_unregister(const char* ip, int port, const char* deviceId) {
    std::string suri = addressPrefix(ip, port);
    if (suri.empty()) {
        printf("address incorrect.\n");
        return -1;
    }
    suri.append(SECURITY_URL_PATH_VIID_UNREGISTER);
    if (!deviceId || strlen(deviceId) < 1) {
        printf("device ID invalid.\n");
        return -1;
    }
    http_message hm;
    std::string sxml = makeUnregisterMessage(deviceId);
    int ret = hm.post(suri.c_str(), sxml);
    std::string respData;
    respData = hm.message();
    printf("response: %s\n", respData.c_str());
    if (SECURITY_REST_HTTP_RESPONSE_200 != hm.errorCode()) {
        printf("Unregister failed.\n");
        return -1;
    }
    printf("Unregister success.");
    return 0;
}
/**
 * @Method   sys_keepalive
 * @Brief
 * @DateTime 2018-08-04T12:54:41+0800
 * @Modify   2018-08-04T12:54:41+0800
 * @Author   Anyz
 * @param    ip [description]
 * @param    port [description]
 * @param    deviceId [description]
 * @return   [description]
 */
int security_viid_service::sys_keepalive(const char* ip, int port, const char* deviceId) {
    std::string suri = addressPrefix(ip, port);
    if (suri.empty()) {
        printf("address incorrect.\n");
        return -1;
    }
    suri.append(SECURITY_URL_PATH_VIID_KEEPALIVE);
    if (!deviceId || strlen(deviceId) < 1) {
        printf("device ID invalid.\n");
        return -1;
    }

    http_message hm;
    std::string sxml = makeKeepaliveMessage(deviceId);
    int ret = hm.post(suri.c_str(), sxml);
    std::string respData;
    respData = hm.message();
    printf("response: %s\n", respData.c_str());
    if (SECURITY_REST_HTTP_RESPONSE_200 != hm.errorCode()) {
        printf("Keep alive failed.\n");
        return -1;
    }
    printf("Keep alive success.");
    return 0;
}
/**
 * @Method   sys_synctime
 * @Brief
 * @DateTime 2018-08-04T12:55:00+0800
 * @Modify   2018-08-04T12:55:00+0800
 * @Author   Anyz
 * @param    ip [description]
 * @param    port [description]
 * @return   [description]
 */
int security_viid_service::sys_synctime(const char* ip, int port) {
    std::string suri = addressPrefix(ip, port);
    if (suri.empty()) {
        printf("address incorrect.\n");
        return -1;
    }
    suri.append(SECURITY_URL_PATH_VIID_TIME);
    if (!deviceId || strlen(deviceId) < 1) {
        printf("device ID invalid.\n");
        return -1;
    }
    http_message hm;
    int ret = hm.post(suri.c_str());
    std::string respData;
    respData = hm.message();
    if (SECURITY_REST_HTTP_RESPONSE_200 != hm.errorCode()) {
        printf("Keep alive failed.\n");
        return -1;
    }

    printf("Keep alive success.\n");
    printf("response: %s\n", respData.c_str());
    // synchorize your system time
    return 0;
}
/**
 * @Method   query_apes
 * @Brief
 * @DateTime 2018-08-04T14:15:03+0800
 * @Modify   2018-08-04T14:15:03+0800
 * @Author   Anyz
 * @param    ip [description]
 * @param    port [description]
 * @param    key [description]
 * @param    value [description]
 * @return   [description]
 */
int security_viid_service::query_apes(const char* ip, int port, const char* key, const char* value) {
    std::string suri = addressPrefix(ip, port);
    if (suri.empty()) {
        printf("address incorrect.\n");
        return -1;
    }
    suri.append(SECURITY_URL_PATH_VIID_APES);
    if (!key || strlen(key) < 5) {
        printf("IP address invalid.\n");
        return -1;
    }
    http_message hm;
    int ret = hm.post(suri.c_str());
    std::string respData;
    respData = hm.message();
    if (SECURITY_REST_HTTP_RESPONSE_200 != hm.errorCode()) {
        printf("get APE list failed.\n");
        return -1;
    }
    printf("get APE list success.\n");
    printf("response: %s\n", respData.c_str());
    // pase APE list
    return 0;
}
/**
 * @Method   update_apes
 * @Brief
 * @DateTime 2018-08-04T14:21:52+0800
 * @Modify   2018-08-04T14:21:52+0800
 * @Author   Anyz
 * @return   [description]
 */
int security_viid_service::update_apes(const char* ) {
    std::string suri = addressPrefix(ip, port);
    if (suri.empty()) {
        printf("address incorrect.\n");
        return -1;
    }
    suri.append(SECURITY_URL_PATH_VIID_APES);
    if (!key || strlen(key) < 5) {
        printf("IP address invalid.\n");
        return -1;
    }
    std::string sxml = makeAPEListMessage(deviceId);
    http_message hm;
    int ret = hm.put(suri.c_str(), sxml);
    std::string respData;
    respData = hm.message();
    if (SECURITY_REST_HTTP_RESPONSE_200 != hm.errorCode()) {
        printf("get APE list failed.\n");
        return -1;
    }
    printf("get APE list success.\n");
    printf("response: %s\n", respData.c_str());
    // pase APE list
    return 0;
}

int security_viid_service::query_apss() {

}

int security_viid_service::query_tollgates() {

}

int security_viid_service::query_lanes() {

}

int security_viid_service::query_video_slices() {

}

int security_viid_service::add_video_slices() {

}

int security_viid_service::query_video_slice() {

}

int security_viid_service::update_video_slice() {

}

int security_viid_service::delete_video_slice() {

}

int security_viid_service::query_videoinfo() {

}

int security_viid_service::add_videoinfo() {

}

int security_viid_service::delete_videoinfo() {

}
/**
 * @Method   addressPrefix
 * @Brief
 * @DateTime 2018-08-04T14:15:16+0800
 * @Modify   2018-08-04T14:15:16+0800
 * @Author   Anyz
 * @param    ip [description]
 * @param    port [description]
 * @return   [description]
 */
std::string security_viid_service::addressPrefix(const char* ip, int port) {
    if (!ip || strlen(ip) < 5) {
        printf("IP address invalid.\n");
        return SECURITY_STRING_EMPTY;
    }
    if (port < 1024 || port > 65536) {
        printf("port invalid.\n");
        return SECURITY_STRING_EMPTY;
    }
    std::string suri("http://");
    suri.append(ip);
    suri.append(":");
    suri.append(port2String(port));
    return suri;
}







