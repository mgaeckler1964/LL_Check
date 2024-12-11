object llFuncSelForm: TllFuncSelForm
  Left = 172
  Top = 238
  BorderStyle = bsDialog
  Caption = 'Select LL Request'
  ClientHeight = 377
  ClientWidth = 592
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  ShowHint = True
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 136
    Top = 8
    Width = 44
    Height = 13
    Caption = 'Function:'
  end
  object Label2: TLabel
    Left = 328
    Top = 8
    Width = 14
    Height = 13
    Caption = 'ID:'
  end
  object SpeedButton1: TSpeedButton
    Left = 560
    Top = 8
    Width = 23
    Height = 22
    Hint = 'Refresh'
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      04000000000000010000130B0000130B00001000000000000000000000000000
      800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
      333333333333333FF3FF3333333333CC30003333333333773777333333333C33
      3000333FF33337F33777339933333C3333333377F33337F3333F339933333C33
      33003377333337F33377333333333C333300333F333337F33377339333333C33
      3333337FF3333733333F33993333C33333003377FF33733333773339933C3333
      330033377FF73F33337733339933C33333333FF377F373F3333F993399333C33
      330077F377F337F33377993399333C33330077FF773337F33377399993333C33
      33333777733337F333FF333333333C33300033333333373FF7773333333333CC
      3000333333333377377733333333333333333333333333333333}
    NumGlyphs = 2
    OnClick = SpeedButton1Click
  end
  object DBNavigator1: TDBNavigator
    Left = 8
    Top = 8
    Width = 120
    Height = 25
    DataSource = LLChartForm.funcSource
    VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast]
    TabOrder = 0
  end
  object functionDBGrid: TDBGrid
    Left = 8
    Top = 40
    Width = 577
    Height = 297
    TabOrder = 4
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
  end
  object Button1: TButton
    Left = 8
    Top = 344
    Width = 75
    Height = 25
    Caption = 'Close'
    Default = True
    ModalResult = 1
    TabOrder = 5
  end
  object FuncFilter: TEdit
    Left = 184
    Top = 8
    Width = 137
    Height = 21
    TabOrder = 1
  end
  object ID_Filter: TEdit
    Left = 344
    Top = 8
    Width = 97
    Height = 21
    TabOrder = 2
  end
  object CheckBoxIgnoreObjId: TCheckBox
    Left = 448
    Top = 8
    Width = 97
    Height = 17
    Caption = 'Ignore Object ID'
    TabOrder = 3
  end
end
