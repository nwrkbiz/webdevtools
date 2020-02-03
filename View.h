/**
 * @file View.h
 * @brief Implementation of the View.
 * @author Daniel Giritzer
 * @copyright "THE BEER-WARE LICENSE" (Revision 42):
 * <giri@nwrk.biz> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Daniel Giritzer
 */
#ifndef WEBTOOLS_VIEW_H
#define WEBTOOLS_VIEW_H
#include <WebSocketServer.h>
#include <WebSocketClient.h>
#include <HTTPServer.h>
#include <mutex>
#include <condition_variable>
#include "ViewFluid.h"

class View : public ViewFluid, 
             public giri::Observer<giri::WebSocketServer>, 
             public giri::Observer<giri::WebSocketClient>,
             public giri::Observer<giri::WebSocketSession>,
             public std::enable_shared_from_this<View>
{
public:
    View();
    ~View();
    static void showErrorMsg(const std::string& message);

    using SPtr = std::shared_ptr<View>;
    using UPtr = std::weak_ptr<View>;
    using WPtr = std::unique_ptr<View>;
private:

    void update(giri::WebSocketServer::SPtr srv);
    void update(giri::WebSocketSession::SPtr sess);
    void update(giri::WebSocketClient::SPtr clnt);

    std::string getFolder();
    std::string getFile();

    // -------------------------------------------------
    // ------------ FLTK Callback Functions ------------
    // -------------------------------------------------
    static void btn_wsc_start_cb(Fl_Button* btn, void* view);
    static void btn_wss_start_cb(Fl_Button* btn, void* view);
    static void btn_wsc_send_cb(Fl_Button* btn, void* view);
    static void btn_wss_send_cb(Fl_Button* btn, void* view);
    static void btn_http_start_cb(Fl_Button* btn, void* view);
    static void btn_http_folder_cb(Fl_Button* btn, void* view);
    static void btn_http_certificate_cb(Fl_Button* btn, void* view);
    static void btn_http_certkey_cb(Fl_Button* btn, void* view);
    static void btn_wss_certificate_cb(Fl_Button* btn, void* view);
    static void btn_wss_certkey_cb(Fl_Button* btn, void* view);
    static void chb_http_ssl_cb(Fl_Button* btn, void* view);
    static void chb_wss_ssl_cb(Fl_Button* btn, void* view);


    giri::WebSocketClient::SPtr m_WSC;
    giri::WebSocketServer::SPtr m_WSS;
    giri::HTTPServer::SPtr m_HTTPS;

    Fl_Text_Buffer* m_WSS_SND;
    Fl_Text_Buffer* m_WSS_RCV;
    Fl_Text_Buffer* m_WSC_SND;
    Fl_Text_Buffer* m_WSC_RCV;

    std::mutex m_SendMtx;
    std::condition_variable m_Send;
};
#endif //WEBTOOLS_VIEW_H