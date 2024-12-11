object WebThreadForm: TWebThreadForm
  Left = 444
  Top = 373
  Width = 964
  Height = 473
  Caption = 'Web Requests'
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
    Width = 948
    Height = 41
    Align = alTop
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 16
      Width = 22
      Height = 13
      Caption = 'Sort:'
    end
    object SortComboBox: TComboBox
      Left = 48
      Top = 8
      Width = 145
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 0
      OnChange = SortComboBoxChange
      Items.Strings = (
        'Date'
        'Function'
        'Time')
    end
    object DBNavigator1: TDBNavigator
      Left = 208
      Top = 8
      Width = 135
      Height = 25
      DataSource = theDataSource
      VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbRefresh]
      TabOrder = 1
    end
    object ButtonImport: TButton
      Left = 352
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Import...'
      TabOrder = 2
      OnClick = ButtonImportClick
    end
    object ComboBoxBrowser: TComboBox
      Left = 440
      Top = 8
      Width = 353
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 3
      OnChange = ComboBoxFilterChange
    end
    object ComboBoxStatus: TComboBox
      Left = 800
      Top = 8
      Width = 145
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 4
      OnChange = ComboBoxFilterChange
    end
  end
  object DBGrid1: TDBGrid
    Left = 0
    Top = 41
    Width = 948
    Height = 393
    Align = alClient
    DataSource = theDataSource
    ReadOnly = True
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
  end
  object theDataSource: TDataSource
    AutoEdit = False
    DataSet = theDataModule.webThreadTable
    Left = 24
    Top = 40
  end
  object QueryBrowser: TQuery
    DatabaseName = 'llCheck_DB'
    SQL.Strings = (
      'select distinct HTTP_AGENT'
      'from WEB_LOGS'
      'order by HTTP_AGENT')
    Left = 120
    Top = 48
    object QueryBrowserHTTP_AGENT: TStringField
      FieldName = 'HTTP_AGENT'
      Origin = 'LLCHECK_DB.WEB_LOGS.HTTP_AGENT'
      Size = 255
    end
  end
  object QueryStatus: TQuery
    DatabaseName = 'llCheck_DB'
    SQL.Strings = (
      'select distinct HTTP_STATUS'
      'from WEB_LOGS'
      'order by HTTP_STATUS')
    Left = 216
    Top = 48
    object QueryStatusHTTP_STATUS: TFloatField
      FieldName = 'HTTP_STATUS'
      Origin = 'LLCHECK_DB.WEB_LOGS.HTTP_STATUS'
    end
  end
end
