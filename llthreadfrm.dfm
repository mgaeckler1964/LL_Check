object LLthreadForm: TLLthreadForm
  Left = 448
  Top = 365
  Width = 840
  Height = 473
  Caption = 'LL Threads'
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
    Width = 824
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
    object ButtonExport: TButton
      Left = 432
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Export...'
      TabOrder = 3
      OnClick = ButtonExportClick
    end
  end
  object DBGrid1: TDBGrid
    Left = 0
    Top = 41
    Width = 824
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
    DataSet = theDataModule.llThreadTable
    Left = 24
    Top = 40
  end
end
