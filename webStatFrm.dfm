object webStatForm: TwebStatForm
  Left = 576
  Top = 327
  Width = 961
  Height = 410
  Caption = 'Web Statistics'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object DBGrid1: TDBGrid
    Left = 0
    Top = 73
    Width = 945
    Height = 298
    Align = alClient
    DataSource = theDataSource
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 945
    Height = 73
    Align = alTop
    TabOrder = 0
    object Label1: TLabel
      Left = 432
      Top = 8
      Width = 22
      Height = 13
      Caption = 'Sort:'
    end
    object DateTimePicker: TDateTimePicker
      Left = 232
      Top = 8
      Width = 186
      Height = 21
      CalAlignment = dtaLeft
      Date = 37382
      Time = 37382
      DateFormat = dfShort
      DateMode = dmComboBox
      Kind = dtkDate
      ParseInput = False
      TabOrder = 2
    end
    object OneDay: TCheckBox
      Left = 128
      Top = 8
      Width = 97
      Height = 17
      Caption = 'One Day'
      TabOrder = 1
    end
    object Calc: TButton
      Left = 8
      Top = 32
      Width = 75
      Height = 25
      Caption = 'Calc'
      TabOrder = 4
      OnClick = CalcClick
    end
    object CheckIgnoreQuery: TCheckBox
      Left = 8
      Top = 8
      Width = 121
      Height = 17
      Caption = 'Ignore Query String'
      TabOrder = 0
    end
    object ChartButton: TButton
      Left = 88
      Top = 32
      Width = 75
      Height = 25
      Caption = 'Chart'
      TabOrder = 5
      OnClick = ChartButtonClick
    end
    object SortComboBox: TComboBox
      Left = 464
      Top = 8
      Width = 145
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 3
      Items.Strings = (
        'Count'
        'Average Time'
        'Max. Time'
        'Total Time')
    end
  end
  object theQuery: TQuery
    DatabaseName = 'llCheck_DB'
    SQL.Strings = (
      
        'select'#9'substr( lower(func) || '#39'('#39' || to_char( object_id ) || '#39')'#39 +
        ', 1, 255 ) as request,'
      #9#9'count(*) as counter,'
      #9#9'min( exec_time ) as mini,'
      #9#9'round( avg( exec_time ), 3 ) as average,'
      #9#9'max( exec_time ) as maxi,'
      #9#9'sum( exec_time ) as total_time,'
      #9#9'min( request_date_time ) as first_call,'
      #9#9'max( request_date_time ) as last_call'
      'from'#9'llthread'
      
        'where'#9'request_date_time >= :startDate and request_date_time < :e' +
        'ndDate'
      
        'group by substr( lower(func) || '#39'('#39' || to_char( object_id ) || '#39 +
        ')'#39', 1, 255 )'
      'order by counter desc'
      ''
      ' '
      ' ')
    Left = 128
    Top = 104
    ParamData = <
      item
        DataType = ftDateTime
        Name = 'startDate'
        ParamType = ptInput
        Value = 0d
      end
      item
        DataType = ftDateTime
        Name = 'endDate'
        ParamType = ptInput
        Value = 0d
      end>
    object theQueryREQUEST: TStringField
      DisplayLabel = 'Request'
      DisplayWidth = 40
      FieldName = 'REQUEST'
      Size = 255
    end
    object theQueryCOUNTER: TFloatField
      DisplayLabel = 'Count'
      FieldName = 'COUNTER'
    end
    object theQueryMINI: TFloatField
      DisplayLabel = 'Min. Time'
      DisplayWidth = 10
      FieldName = 'MINI'
    end
    object theQueryAVERAGE: TFloatField
      DisplayLabel = 'Avg. Time'
      FieldName = 'AVERAGE'
    end
    object theQueryMAXI: TFloatField
      DisplayLabel = 'Max. Time'
      FieldName = 'MAXI'
    end
    object theQueryTOTAL_TIME: TFloatField
      DisplayLabel = 'Total Time'
      FieldName = 'TOTAL_TIME'
    end
    object theQueryFIRST_CALL: TDateTimeField
      DisplayLabel = 'First Call'
      FieldName = 'FIRST_CALL'
    end
    object theQueryLAST_CALL: TDateTimeField
      DisplayLabel = 'Last Call'
      FieldName = 'LAST_CALL'
    end
  end
  object theDataSource: TDataSource
    DataSet = theQuery
    Left = 24
    Top = 104
  end
end
