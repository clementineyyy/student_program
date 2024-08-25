#pragma once
#include "BasicWidget.h"
#include "PushButton.h"
#include <vector>

class Table :
    public BasicWidget
{
public:
    Table(int row = 0, int col = 0);
    ~Table();
    void setRowCount(int row);
    int rowCount()const { return m_datas.size(); }
    int colCount()const { return m_cols; }
    void setColCount(int col);
    void setHeader(const std::string& header);
    void insertData(const std::string& data);
    void show();
    void drawTableGrid();
    void drawButton();
    void drawTableData();
    void drawHeader();
    static std::vector<std::string> split(std::string str, char seperator = '\t');
    void updatePage();
    void event()override;
    void clear() { m_datas.clear(); }

private:
    int m_rows;
    int m_cols;
    //格子的宽度和高度
    int m_gridW;
    int m_gridH;
    //文字的宽度和高度
    int m_tw;
    int m_th;
    std::string m_header;
    std::vector<std::string> m_datas;

private:
    //分页处理
    //当前页
    int m_curPage;
    //最大页数
    int m_maxPage;
    //最后一页剩余多少数据
    int m_extraData;

    PushButton* m_prevBtn;
    PushButton* m_nextBtn;
    PushButton* m_firstBtn;
    PushButton* m_lastBtn;
};

