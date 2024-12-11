object HttpRecurringForm: THttpRecurringForm
  Left = 527
  Top = 381
  Width = 540
  Height = 553
  Caption = 'HTTP Autochecks'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDefaultPosOnly
  Visible = True
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 524
    Height = 249
    Align = alTop
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 40
      Width = 16
      Height = 13
      Caption = 'Url:'
    end
    object Label2: TLabel
      Left = 8
      Top = 64
      Width = 41
      Height = 13
      Caption = 'Cookies:'
    end
    object Label3: TLabel
      Left = 8
      Top = 88
      Width = 29
      Height = 13
      Caption = 'Proxy:'
    end
    object Label4: TLabel
      Left = 440
      Top = 88
      Width = 22
      Height = 13
      Anchors = [akTop, akRight]
      Caption = 'Port:'
    end
    object Label5: TLabel
      Left = 8
      Top = 168
      Width = 32
      Height = 13
      Caption = 'E-Mail:'
    end
    object Label6: TLabel
      Left = 8
      Top = 192
      Width = 33
      Height = 13
      Caption = 'SMTP:'
    end
    object Label7: TLabel
      Left = 440
      Top = 192
      Width = 22
      Height = 13
      Anchors = [akTop, akRight]
      Caption = 'Port:'
    end
    object Label8: TLabel
      Left = 8
      Top = 216
      Width = 49
      Height = 13
      Caption = 'Max Time:'
    end
    object Label9: TLabel
      Left = 240
      Top = 224
      Width = 58
      Height = 13
      Caption = 'SMTP User:'
    end
    object DBNavigator: TDBNavigator
      Left = 8
      Top = 8
      Width = 240
      Height = 25
      DataSource = DataSourceHttpRecurring
      TabOrder = 0
    end
    object DBEditProxy: TDBEdit
      Left = 64
      Top = 88
      Width = 369
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      DataField = 'PROXY_SERVER'
      DataSource = DataSourceHttpRecurring
      TabOrder = 3
    end
    object DBEditProxyPort: TDBEdit
      Left = 469
      Top = 88
      Width = 50
      Height = 21
      Anchors = [akTop, akRight]
      DataField = 'PROXY_PORT'
      DataSource = DataSourceHttpRecurring
      TabOrder = 4
    end
    object DBMemoUrl: TDBMemo
      Left = 64
      Top = 40
      Width = 455
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      DataField = 'HTTP_URL'
      DataSource = DataSourceHttpRecurring
      TabOrder = 1
    end
    object DBMemoCookies: TDBMemo
      Left = 64
      Top = 64
      Width = 455
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      DataField = 'HTTP_COOKIES'
      DataSource = DataSourceHttpRecurring
      TabOrder = 2
    end
    object DBRadioGroupInterval: TDBRadioGroup
      Left = 8
      Top = 120
      Width = 513
      Height = 41
      Anchors = [akLeft, akTop, akRight]
      Caption = 'Interval'
      Columns = 5
      DataField = 'INTERVAL'
      DataSource = DataSourceHttpRecurring
      Items.Strings = (
        'One Minute'
        'Five Minutes'
        'One Hour'
        '12 Hours'
        'One Day')
      TabOrder = 5
      Values.Strings = (
        '60'
        '300'
        '3600'
        '43200'
        '86400')
    end
    object DBEditSmtp: TDBEdit
      Left = 64
      Top = 192
      Width = 369
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      DataField = 'SMTP_SERVER'
      DataSource = DataSourceHttpRecurring
      TabOrder = 7
    end
    object DBEditSmtpPort: TDBEdit
      Left = 469
      Top = 192
      Width = 50
      Height = 21
      Anchors = [akTop, akRight]
      DataField = 'SMTP_PORT'
      DataSource = DataSourceHttpRecurring
      TabOrder = 8
    end
    object DBEditEmail: TDBEdit
      Left = 64
      Top = 168
      Width = 455
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      DataField = 'E_MAIL_ALERT'
      DataSource = DataSourceHttpRecurring
      TabOrder = 6
    end
    object DBEditMaxTime: TDBEdit
      Left = 64
      Top = 216
      Width = 121
      Height = 21
      DataField = 'MAX_TIME'
      DataSource = DataSourceHttpRecurring
      TabOrder = 9
    end
    object DBEditSMTP_USER: TDBEdit
      Left = 304
      Top = 216
      Width = 217
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      DataField = 'SMTP_USER'
      DataSource = DataSourceHttpRecurring
      TabOrder = 10
    end
  end
  object DBGrid: TDBGrid
    Left = 0
    Top = 249
    Width = 524
    Height = 265
    Align = alClient
    DataSource = DataSourceHttpRecurring
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    OnDrawColumnCell = DBGridDrawColumnCell
    Columns = <
      item
        Expanded = False
        FieldName = 'SHORT_URL'
        Width = 369
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'NEXT_START'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'LAST_TIME'
        Title.Caption = 'Last Time'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'LAST_STATUS'
        Title.Caption = 'Last Status'
        Visible = True
      end>
  end
  object TableHttpRecurring: TTable
    OnCalcFields = TableHttpRecurringCalcFields
    AutoRefresh = True
    DatabaseName = 'llCheck_DB'
    IndexName = 'HTTP_RECURRING_IDX'
    TableName = 'HTTP_RECURRING'
    UpdateMode = upWhereKeyOnly
    Left = 64
    Top = 392
    object TableHttpRecurringID: TFloatField
      AutoGenerateValue = arAutoInc
      FieldName = 'ID'
      ReadOnly = True
      Visible = False
    end
    object TableHttpRecurringHTTP_URL: TMemoField
      FieldName = 'HTTP_URL'
      Required = True
      BlobType = ftMemo
      Size = 1995
    end
    object TableHttpRecurringHTTP_COOKIES: TMemoField
      FieldName = 'HTTP_COOKIES'
      BlobType = ftMemo
      Size = 1995
    end
    object TableHttpRecurringPROXY_SERVER: TStringField
      FieldName = 'PROXY_SERVER'
      Size = 255
    end
    object TableHttpRecurringPROXY_PORT: TFloatField
      FieldName = 'PROXY_PORT'
    end
    object TableHttpRecurringINTERVAL: TFloatField
      FieldName = 'INTERVAL'
      Required = True
    end
    object TableHttpRecurringNEXT_START: TDateTimeField
      AutoGenerateValue = arDefault
      DisplayLabel = 'Next Start'
      FieldName = 'NEXT_START'
    end
    object TableHttpRecurringMAX_TIME: TFloatField
      FieldName = 'MAX_TIME'
      Required = True
    end
    object TableHttpRecurringE_MAIL_ALERT: TStringField
      FieldName = 'E_MAIL_ALERT'
      Size = 255
    end
    object TableHttpRecurringSMTP_SERVER: TStringField
      FieldName = 'SMTP_SERVER'
      Size = 255
    end
    object TableHttpRecurringSMTP_PORT: TFloatField
      FieldName = 'SMTP_PORT'
    end
    object TableHttpRecurringSMTP_USER: TStringField
      FieldName = 'SMTP_USER'
      Size = 255
    end
    object TableHttpRecurringSHORT_URL: TStringField
      DisplayLabel = 'Url'
      FieldKind = fkCalculated
      FieldName = 'SHORT_URL'
      Size = 255
      Calculated = True
    end
    object TableHttpRecurringLAST_TIME: TFloatField
      FieldName = 'LAST_TIME'
    end
    object TableHttpRecurringLAST_STATUS: TFloatField
      FieldName = 'LAST_STATUS'
    end
  end
  object DataSourceHttpRecurring: TDataSource
    DataSet = TableHttpRecurring
    Left = 176
    Top = 392
  end
end
