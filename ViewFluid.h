// generated by Fast Light User Interface Designer (fluid) version 1.0305

#ifndef ViewFluid_h
#define ViewFluid_h
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Table_Row.H>
#include <string>
#include <vector>

class SimpleTable : public Fl_Table_Row {
public:
  void draw_cell(TableContext context, int R=0, int C=0, int X=0, int Y=0, int W=0, int H=0);
  SimpleTable(int x, int y, int w, int h, const char *l = 0) ;
  void SetTableData(std::string data, unsigned int x = 0, unsigned int y = 0, Fl_Color color = FL_WHITE);
  void SetCellColor(Fl_Color color, unsigned int x = 0, unsigned int y = 0);
  std::vector<std::vector<std::string>> GetTableData();
  void Resize(unsigned int x = 0, unsigned int y = 0);
using TableData = std::vector<std::vector<std::string>>;
using TableCellColors = std::vector<std::vector<Fl_Color>>;
private:
  void DrawData(const char *s, Fl_Color cell_color, int X, int Y, int W, int H);
  void DrawHeader(const char *s, int X, int Y, int W, int H);
  TableData m_TableData; 
  TableCellColors m_CellColors; 
};
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_File_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Box.H>

class ViewFluid {
protected:
  ViewFluid();
  Fl_Double_Window *win_main;
  Fl_Input *ti_http_addr;
  Fl_Value_Input *vi_http_port;
  Fl_File_Input *ti_http_folder;
  Fl_Button *btn_http_folder;
  Fl_Value_Input *vi_http_threads;
  Fl_Check_Button *chb_http_ssl;
  Fl_File_Input *ti_http_certificate;
  Fl_Button *btn_http_certificate;
  Fl_File_Input *ti_http_certkey;
  Fl_Button *btn_http_certkey;
  Fl_Return_Button *btn_http_start;
  Fl_Text_Editor *te_http_rcv;
  Fl_Input *ti_wss_addr;
  Fl_Value_Input *vi_wss_port;
  Fl_Value_Input *vi_wss_threads;
  Fl_Check_Button *chb_wss_ssl;
  Fl_File_Input *ti_wss_certificate;
  Fl_Button *btn_wss_certificate;
  Fl_File_Input *ti_wss_certkey;
  Fl_Button *btn_wss_certkey;
  Fl_Button *btn_wss_start;
  Fl_Text_Editor *te_wss_rcv;
  Fl_Text_Editor *te_wss_snd;
  Fl_Return_Button *btn_wss_send;
  Fl_Input *ti_wsc_addr;
  Fl_Value_Input *vi_wsc_port;
  Fl_Value_Input *vi_wsc_threads;
  Fl_Check_Button *chb_wsc_ssl;
  Fl_Button *btn_wsc_start;
  Fl_Text_Editor *te_wsc_snd;
  Fl_Text_Editor *te_wsc_rcv;
  Fl_Return_Button *btn_wsc_send;
  Fl_Box *box_about;
};
#endif
