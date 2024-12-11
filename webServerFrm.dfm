object webServerForm: TwebServerForm
  Left = 237
  Top = 389
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'Web Servers'
  ClientHeight = 408
  ClientWidth = 543
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 543
    Height = 41
    Align = alTop
    TabOrder = 0
    object DBNavigator1: TDBNavigator
      Left = 8
      Top = 8
      Width = 240
      Height = 25
      DataSource = ServerSource
      TabOrder = 0
    end
  end
  object DBGrid1: TDBGrid
    Left = 0
    Top = 41
    Width = 543
    Height = 294
    Align = alClient
    DataSource = ServerSource
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
  end
  object DBMemo1: TDBMemo
    Left = 0
    Top = 335
    Width = 543
    Height = 73
    Align = alBottom
    DataField = 'PATH'
    DataSource = ServerSource
    TabOrder = 2
  end
  object ServerSource: TDataSource
    DataSet = theDataModule.WebServerTable
    Left = 120
    Top = 72
  end
end
