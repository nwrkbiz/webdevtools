/**
 * @file View.cpp
 * @brief Implementation of the View.
 * @author Daniel Giritzer
 * @copyright "THE BEER-WARE LICENSE" (Revision 42):
 * <giri@nwrk.biz> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Daniel Giritzer
 */
#include "View.h"
#include <FL/fl_ask.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_PNG_Image.H>
#include <Blob.h>
#include <ostream>

using namespace giri;

void View::showErrorMsg(const std::string& message)
{
    std::cerr << message << std::endl;
    std::string printMsg = message;
    fl_message_title("Error!");
    printMsg.append("\n\nExit application?");
    switch ( fl_choice(printMsg.c_str(), "Yes", "No", 0) ) {
      case 0: exit(EXIT_FAILURE); break;
    }
}
View::~View(){

}
View::View(){

    Fl::scheme("gtk+");

#ifdef _WIN32
    win_main->icon((char*)LoadIcon(fl_display, MAKEINTRESOURCE(101)));
#else
    Blob b;
    b.loadBase64(m_Icon);
    Fl_PNG_Image win_icon("Icon.png", (unsigned char*)b.data(), b.size());
    win_main->icon(&win_icon);
#endif /*_WIN32*/

    ti_http_addr->value("0.0.0.0");
    ti_http_certificate->value("cert.pem");
    ti_http_certkey->value("key.pem");
    vi_http_port->value(8080);
    vi_http_threads->value(1);

    ti_wss_addr->value("0.0.0.0");
    ti_wss_certificate->value("cert.pem");
    ti_wss_certkey->value("key.pem");
    vi_wss_port->value(8080);
    vi_wss_threads->value(1);

    ti_wsc_addr->value("echo.websocket.org");
    vi_wsc_port->value(80);
    vi_wsc_threads->value(1);

    box_about->label("(c) Daniel Giritzer, 2020\nhttps://page.nwrk.biz/giri");

    btn_http_start->callback((Fl_Callback*)btn_http_start_cb, (void*)(this) );
    btn_wss_start->callback((Fl_Callback*)btn_wss_start_cb, (void*)(this) );
    btn_wsc_start->callback((Fl_Callback*)btn_wsc_start_cb, (void*)(this) );
    btn_wss_send->callback((Fl_Callback*)btn_wss_send_cb, (void*)(this) );
    btn_wsc_send->callback((Fl_Callback*)btn_wsc_send_cb, (void*)(this) );
    btn_http_folder->callback((Fl_Callback*)btn_http_folder_cb, (void*)(this) );
    btn_http_certkey->callback((Fl_Callback*)btn_http_certkey_cb, (void*)(this) );
    btn_http_certificate->callback((Fl_Callback*)btn_http_certificate_cb, (void*)(this) );
    btn_wss_certkey->callback((Fl_Callback*)btn_wss_certkey_cb, (void*)(this) );
    btn_wss_certificate->callback((Fl_Callback*)btn_wss_certificate_cb, (void*)(this) );

    chb_http_ssl->callback((Fl_Callback*)chb_http_ssl_cb, (void*)(this) );
    chb_wss_ssl->callback((Fl_Callback*)chb_wss_ssl_cb, (void*)(this) );

    m_WSC_RCV = new Fl_Text_Buffer();
    te_wsc_rcv->buffer(m_WSC_RCV);

    m_WSC_SND = new Fl_Text_Buffer();
    te_wsc_snd->buffer(m_WSC_SND);

    m_WSS_RCV = new Fl_Text_Buffer();
    te_wss_rcv->buffer(m_WSS_RCV);

    m_WSS_SND = new Fl_Text_Buffer();
    te_wss_snd->buffer(m_WSS_SND);

    m_HTTP_RCV = new Fl_Text_Buffer();
    te_http_rcv->buffer(m_HTTP_RCV);

    win_main->show();
}
void View::update(giri::WebSocketServer::SPtr srv){
    srv->getSession()->subscribe(this->shared_from_this());
}
void View::update(giri::WebSocketSession::SPtr sess){
    std::unique_lock<std::mutex> lck(m_SendMtx);
    m_WSS_RCV->text(sess->getMessage().c_str());
    win_main->redraw();
    Fl::check();
    m_Send.wait(lck);
    std::string msg(m_WSS_SND->text());
    sess->send(msg);
}
void View::update(giri::WebSocketClient::SPtr clnt){
    m_WSC_RCV->text(clnt->getMessage().c_str());
    win_main->redraw();
    Fl::check();
}
void View::update(giri::HTTPServer::SPtr serv){
    serv->getSession()->subscribe(this->shared_from_this());
}
void View::update(giri::HTTPSession::SPtr sess){
    std::ostringstream ostr;
    ostr <<  sess->getRequest();
    m_HTTP_RCV->text(ostr.str().c_str());
    win_main->redraw();
    Fl::check();
}
std::string View::getFolder(){
    Fl_File_Chooser chooser(".",
                            "*",
                            Fl_File_Chooser::DIRECTORY,
                            "Select directory...");
    chooser.newButton->activate();
    chooser.show();
    while(chooser.shown())
        Fl::wait();
    if ( chooser.value() == nullptr )
        return "";
    return chooser.value();
}
std::string View::getFile(){
        Fl_File_Chooser chooser(".",
                                "Certificate Files (*.pem)",
                                Fl_File_Chooser::SINGLE,
                                "Select File...");
        chooser.show();
        while(chooser.shown())
            Fl::wait();
        if ( chooser.value() == nullptr )
            return "";
        return chooser.value();
}
void View::btn_http_start_cb(Fl_Button* btn, void* view)
{
    try
    {
        View* me = static_cast<View*>(view);
        std::string addr = me->ti_http_addr->value();
        std::string port = std::to_string((int)me->vi_http_port->value());
        std::string rootdir = me->ti_http_folder->value();
        size_t threads = me->vi_http_threads->value();
        bool ssl = me->chb_http_ssl->value();
        std::string cert = me->ti_http_certificate->value();
        std::string key = me->ti_http_certkey->value();
        me->m_HTTPS = std::make_shared<HTTPServer>(addr, port, rootdir, threads, ssl, cert, key);
        me->m_HTTPS->subscribe(me->shared_from_this());
        me->m_HTTPS->run();

        me->te_http_rcv->activate();
        me->ti_http_certificate->deactivate();
        me->ti_http_certkey->deactivate();
        me->btn_http_certificate->deactivate();
        me->btn_http_certkey->deactivate();
        me->chb_http_ssl->deactivate();
        me->ti_http_addr->deactivate();
        me->vi_http_port->deactivate();
        me->vi_http_threads->deactivate();
        me->btn_http_start->deactivate();
        me->btn_http_folder->deactivate();
        me->ti_http_folder->deactivate();
    }
    catch(const ExceptionBase &e)
    {
        showErrorMsg(e.getMessage().c_str());
    }
    catch(...)
    {
        showErrorMsg("Unknown error occured!");
    }
}
void View::btn_http_folder_cb(Fl_Button* btn, void* view)
{
    try
    {
        View* me = static_cast<View*>(view);
        me->ti_http_folder->value(me->getFolder().c_str());
    }
    catch(...)
    {
        showErrorMsg("Unknown error occured!");
    }
}
void View::btn_http_certificate_cb(Fl_Button* btn, void* view)
{
    try
    {
        View* me = static_cast<View*>(view);
        me->ti_http_certificate->value(me->getFile().c_str());
    }
    catch(...)
    {
        showErrorMsg("Unknown error occured!");
    }
}
void View::btn_http_certkey_cb(Fl_Button* btn, void* view)
{
    try
    {
        View* me = static_cast<View*>(view);
        me->ti_http_certkey->value(me->getFile().c_str());
    }
    catch(...)
    {
        showErrorMsg("Unknown error occured!");
    }
}
void View::btn_wss_certificate_cb(Fl_Button* btn, void* view)
{
    try
    {
        View* me = static_cast<View*>(view);
        me->ti_wss_certificate->value(me->getFile().c_str());
    }
    catch(...)
    {
        showErrorMsg("Unknown error occured!");
    }
}
void View::btn_wss_certkey_cb(Fl_Button* btn, void* view)
{
    try
    {
        View* me = static_cast<View*>(view);
        me->ti_wss_certkey->value(me->getFile().c_str());
    }
    catch(...)
    {
        showErrorMsg("Unknown error occured!");
    }
}
void View::chb_http_ssl_cb(Fl_Button* btn, void* view)
{
    try
    {
        View* me = static_cast<View*>(view);
        if(me->chb_http_ssl->value()) 
        {
            me->ti_http_certificate->activate();
            me->ti_http_certkey->activate();
            me->btn_http_certificate->activate();
            me->btn_http_certkey->activate();
        }
        else
        {
            me->ti_http_certificate->deactivate();
            me->ti_http_certkey->deactivate();
            me->btn_http_certificate->deactivate();
            me->btn_http_certkey->deactivate();
        }
    }
    catch(...)
    {
        showErrorMsg("Unknown error occured!");
    }
}
void View::chb_wss_ssl_cb(Fl_Button* btn, void* view)
{
    try
    {
        View* me = static_cast<View*>(view);
        if(me->chb_wss_ssl->value()) 
        {
            me->ti_wss_certificate->activate();
            me->ti_wss_certkey->activate();
            me->btn_wss_certificate->activate();
            me->btn_wss_certkey->activate();
        }
        else
        {
            me->ti_wss_certificate->deactivate();
            me->ti_wss_certkey->deactivate();
            me->btn_wss_certificate->deactivate();
            me->btn_wss_certkey->deactivate();
        }
    }
    catch(...)
    {
        showErrorMsg("Unknown error occured!");
    }
}

void View::btn_wsc_start_cb(Fl_Button* btn, void* view){
    try
    {
        View* me = static_cast<View*>(view);
        std::string addr = me->ti_wsc_addr->value();
        std::string port = std::to_string((int)me->vi_wsc_port->value());
        size_t threads = me->vi_wsc_threads->value();
        bool ssl = me->chb_wsc_ssl->value();

        me->m_WSC = std::make_shared<WebSocketClient>(addr, port, ssl, threads);
        me->m_WSC->subscribe(me->shared_from_this());

        me->chb_wsc_ssl->deactivate();
        me->ti_wsc_addr->deactivate();
        me->vi_wsc_port->deactivate();
        me->vi_wsc_threads->deactivate();
        me->btn_wsc_start->deactivate();
        me->btn_wsc_send->activate();
        me->te_wsc_rcv->activate();
        me->te_wsc_snd->activate();

        me->m_WSC->run();
    }
    catch(const ExceptionBase &e)
    {
        showErrorMsg(e.getMessage().c_str());
    }
    catch(...)
    {
        showErrorMsg("Unknown error occured!");
    }
}
void View::btn_wss_start_cb(Fl_Button* btn, void* view){
    try
    {
        View* me = static_cast<View*>(view);
        std::string addr = me->ti_wss_addr->value();
        std::string port = std::to_string((int)me->vi_wss_port->value());
        size_t threads = me->vi_wss_threads->value();
        bool ssl = me->chb_wss_ssl->value();
        std::string cert = me->ti_wss_certificate->value();
        std::string key = me->ti_wss_certkey->value();

        me->m_WSS = std::make_shared<WebSocketServer>(addr, port, ssl, threads, cert, key);
        me->m_WSS->subscribe(me->shared_from_this());

        me->chb_wss_ssl->deactivate();
        me->ti_wss_certificate->deactivate();
        me->ti_wss_certkey->deactivate();
        me->ti_wss_addr->deactivate();
        me->vi_wss_port->deactivate();
        me->vi_wss_threads->deactivate();
        me->btn_wss_start->deactivate();
        me->btn_wss_send->activate();
        me->te_wss_rcv->activate();
        me->te_wss_snd->activate();

        me->m_WSS->run();
    }
    catch(const ExceptionBase &e)
    {
        showErrorMsg(e.getMessage().c_str());
    }
    catch(...)
    {
        showErrorMsg("Unknown error occured!");
    }
}
void View::btn_wsc_send_cb(Fl_Button* btn, void* view){
    try
    {
        View* me = static_cast<View*>(view);
        std::string msg(me->m_WSC_SND->text());
        me->m_WSC->send(msg);
    }
    catch(const ExceptionBase &e)
    {
        showErrorMsg(e.getMessage().c_str());
    }
    catch(...)
    {
        showErrorMsg("Unknown error occured!");
    }
}
void View::btn_wss_send_cb(Fl_Button* btn, void* view){
    try
    {
        View* me = static_cast<View*>(view);
        std::unique_lock<std::mutex> lck(me->m_SendMtx);
        me->m_Send.notify_one();
    }
    catch(...)
    {
        showErrorMsg("Unknown error occured!");
    }
}