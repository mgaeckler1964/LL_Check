object httpTimesForm: ThttpTimesForm
  Left = 553
  Top = 367
  Width = 548
  Height = 253
  Caption = 'HTTP Times'
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
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 532
    Height = 41
    Align = alTop
    TabOrder = 0
    object DBNavigator1: TDBNavigator
      Left = 8
      Top = 8
      Width = 125
      Height = 25
      DataSource = DataSource
      VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbDelete]
      TabOrder = 0
    end
    object RefreshButton: TButton
      Left = 136
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Refresh'
      TabOrder = 1
      OnClick = RefreshButtonClick
    end
    object ButtonDelUrl: TButton
      Left = 216
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Del. Url'
      TabOrder = 2
      OnClick = ButtonDelUrlClick
    end
    object RadioButtonSortURL: TRadioButton
      Left = 304
      Top = 8
      Width = 81
      Height = 17
      Caption = 'Sort URL'
      Checked = True
      TabOrder = 3
      TabStop = True
      OnClick = ChangeSort
    end
    object RadioButtonSortDate: TRadioButton
      Left = 384
      Top = 8
      Width = 113
      Height = 17
      Caption = 'Sort Date'
      TabOrder = 4
      OnClick = ChangeSort
    end
  end
  object DBGridTimes: TDBGrid
    Left = 0
    Top = 41
    Width = 532
    Height = 173
    Align = alClient
    DataSource = DataSource
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    OnDblClick = DBGridTimesDblClick
  end
  object DataSource: TDataSource
    DataSet = httpTimesQuery
    Left = 48
    Top = 136
  end
  object httpTimesQuery: TQuery
    CachedUpdates = True
    DatabaseName = 'llCheck_DB'
    SQL.Strings = (
      'select'#9'id,'
      #9#9'request_date_time,'
      #9#9'substr( http_url, 1, 255 ) as url,'
      #9#9'http_url,'
      #9#9'substr( http_cookies, 1, 255 ) as cookies,'
      #9#9'loop_count,'
      #9#9'user_count,'
      #9#9'avg_time,'
      #9#9'proxy_server,'
      #9#9'proxy_port,'
      #9#9'COMPLETE_FLAG,'
      #9#9'TOTAL_SIZE,'
      #9#9'NUM_FILES'
      'from'#9'http_thread'
      'order by 3, user_count, request_date_time desc')
    Left = 160
    Top = 136
    object httpTimesQueryID: TFloatField
      FieldName = 'ID'
      Visible = False
    end
    object httpTimesQueryREQUEST_DATE_TIME: TDateTimeField
      DisplayLabel = 'Date'
      FieldName = 'REQUEST_DATE_TIME'
    end
    object httpTimesQueryURL: TStringField
      DisplayLabel = 'Url'
      DisplayWidth = 80
      FieldName = 'URL'
      Size = 255
    end
    object httpTimesQueryHTTP_URL: TMemoField
      FieldName = 'HTTP_URL'
      Visible = False
      BlobType = ftMemo
      Size = 1995
    end
    object httpTimesQueryCOOKIES: TStringField
      DisplayLabel = 'Cookies'
      DisplayWidth = 20
      FieldName = 'COOKIES'
      Size = 255
    end
    object httpTimesQueryLOOP_COUNT: TFloatField
      DisplayLabel = 'Loops'
      FieldName = 'LOOP_COUNT'
    end
    object httpTimesQueryUSER_COUNT: TFloatField
      DisplayLabel = 'Users'
      FieldName = 'USER_COUNT'
    end
    object httpTimesQueryAVG_TIME: TFloatField
      DisplayLabel = 'Avg. Time'
      FieldName = 'AVG_TIME'
    end
    object httpTimesQueryPROXY_SERVER: TStringField
      DisplayLabel = 'Proxy'
      DisplayWidth = 32
      FieldName = 'PROXY_SERVER'
      Size = 255
    end
    object httpTimesQueryPROXY_PORT: TFloatField
      DisplayLabel = 'Porxy Port'
      FieldName = 'PROXY_PORT'
    end
    object httpTimesQueryCOMPLETE_FLAG: TStringField
      DisplayLabel = 'Complete'
      FieldName = 'COMPLETE_FLAG'
      Size = 1
    end
    object httpTimesQueryTOTAL_SIZE: TFloatField
      DisplayLabel = 'Size'
      FieldName = 'TOTAL_SIZE'
    end
    object httpTimesQueryNUM_FILES: TFloatField
      DisplayLabel = '# Files'
      FieldName = 'NUM_FILES'
    end
  end
  object delUrlQuery: TQuery
    DatabaseName = 'llCheck_DB'
    SQL.Strings = (
      'delete from http_thread'
      'where lower(http_url) = lower(:http_url)')
    Left = 376
    Top = 128
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'http_url'
        ParamType = ptUnknown
      end>
  end
end
