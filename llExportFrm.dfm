object llExportForm: TllExportForm
  Left = 606
  Top = 349
  BorderStyle = bsDialog
  Caption = 'Export Timings'
  ClientHeight = 214
  ClientWidth = 523
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 112
    Width = 25
    Height = 13
    Caption = 'Path:'
  end
  object Label2: TLabel
    Left = 8
    Top = 8
    Width = 39
    Height = 13
    Caption = 'Servers:'
  end
  object StatusLabel: TLabel
    Left = 8
    Top = 144
    Width = 30
    Height = 13
    Caption = 'Status'
  end
  object PathEdit: TEdit
    Left = 56
    Top = 112
    Width = 457
    Height = 21
    TabOrder = 1
    OnChange = EnableDisableOK
  end
  object ServerListBox: TListBox
    Left = 56
    Top = 8
    Width = 457
    Height = 97
    ExtendedSelect = False
    ItemHeight = 13
    MultiSelect = True
    Sorted = True
    TabOrder = 0
    OnClick = EnableDisableOK
  end
  object StartStopButton: TButton
    Left = 8
    Top = 184
    Width = 75
    Height = 25
    Caption = 'Start'
    Default = True
    TabOrder = 3
    OnClick = StartStopButtonClick
  end
  object CancelCloseButton: TButton
    Left = 88
    Top = 184
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    TabOrder = 4
    OnClick = CancelCloseButtonClick
  end
  object ProgressBar: TProgressBar
    Left = 8
    Top = 160
    Width = 505
    Height = 16
    Min = 0
    Max = 100
    TabOrder = 2
  end
  object ServerQuery: TQuery
    DatabaseName = 'llCheck_DB'
    SQL.Strings = (
      'select distinct server_name'
      'from server')
    Left = 120
    Top = 32
  end
  object TimingsQuery: TQuery
    DatabaseName = 'llCheck_DB'
    SQL.Strings = (
      'select * '
      'from llthread, server'
      'where llthread.server = server.id')
    UniDirectional = True
    Left = 200
    Top = 32
    object TimingsQueryREQUEST_DATE_TIME: TDateTimeField
      FieldName = 'REQUEST_DATE_TIME'
      Origin = 'LLCHECK_DB.LLTHREAD.REQUEST_DATE_TIME'
    end
    object TimingsQuerySTART_TICK: TFloatField
      FieldName = 'START_TICK'
      Origin = 'LLCHECK_DB.LLTHREAD.START_TICK'
    end
    object TimingsQueryTHREAD: TFloatField
      FieldName = 'THREAD'
      Origin = 'LLCHECK_DB.LLTHREAD.THREAD'
    end
    object TimingsQueryFUNC: TStringField
      FieldName = 'FUNC'
      Origin = 'LLCHECK_DB.LLTHREAD.FUNC'
      Size = 255
    end
    object TimingsQueryEXEC_TIME: TFloatField
      FieldName = 'EXEC_TIME'
      Origin = 'LLCHECK_DB.LLTHREAD.EXEC_TIME'
    end
    object TimingsQuerySQL_TIME: TFloatField
      FieldName = 'SQL_TIME'
      Origin = 'LLCHECK_DB.LLTHREAD.SQL_TIME'
    end
    object TimingsQuerySQL_COUNT: TFloatField
      FieldName = 'SQL_COUNT'
      Origin = 'LLCHECK_DB.LLTHREAD.SQL_COUNT'
    end
    object TimingsQueryGENERATE_TIME: TFloatField
      FieldName = 'GENERATE_TIME'
      Origin = 'LLCHECK_DB.LLTHREAD.GENERATE_TIME'
    end
    object TimingsQueryOBJECT_ID: TFloatField
      FieldName = 'OBJECT_ID'
      Origin = 'LLCHECK_DB.LLTHREAD.OBJECT_ID'
    end
    object TimingsQueryPARENT_ID: TFloatField
      FieldName = 'PARENT_ID'
      Origin = 'LLCHECK_DB.LLTHREAD.PARENT_ID'
    end
    object TimingsQueryMISRC_ARGS: TStringField
      FieldName = 'MISRC_ARGS'
      Origin = 'LLCHECK_DB.LLTHREAD.MISRC_ARGS'
      Size = 255
    end
    object TimingsQueryERROR: TStringField
      FieldName = 'ERROR'
      Origin = 'LLCHECK_DB.LLTHREAD.ERROR'
      Size = 255
    end
    object TimingsQuerySERVER_NAME: TStringField
      FieldName = 'SERVER_NAME'
      Origin = 'LLCHECK_DB.LLTHREAD.ID'
      Size = 255
    end
  end
  object CountQuery: TQuery
    DatabaseName = 'llCheck_DB'
    SQL.Strings = (
      'select count(*) as counter'
      'from llthread, server'
      'where llthread.server = server.id')
    UniDirectional = True
    Left = 280
    Top = 32
    object CountQueryCOUNTER: TFloatField
      FieldName = 'COUNTER'
    end
  end
  object threadTimer: TTimer
    Enabled = False
    OnTimer = threadTimerTimer
    Left = 184
    Top = 184
  end
end
