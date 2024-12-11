object llImportForm: TllImportForm
  Left = 322
  Top = 383
  BorderStyle = bsDialog
  Caption = 'Livelink Import'
  ClientHeight = 218
  ClientWidth = 500
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
    Top = 32
    Width = 56
    Height = 13
    Caption = 'Current File:'
  end
  object FileLabel: TLabel
    Left = 72
    Top = 32
    Width = 400
    Height = 13
    AutoSize = False
    Caption = '-'
  end
  object Label3: TLabel
    Left = 8
    Top = 56
    Width = 48
    Height = 13
    Caption = 'Requests:'
  end
  object RequestsLabel: TLabel
    Left = 72
    Top = 56
    Width = 400
    Height = 13
    AutoSize = False
    Caption = '-'
  end
  object Label5: TLabel
    Left = 8
    Top = 8
    Width = 34
    Height = 13
    Caption = 'Server:'
  end
  object ServerLabel: TLabel
    Left = 72
    Top = 8
    Width = 400
    Height = 13
    AutoSize = False
    Caption = '-'
  end
  object Label2: TLabel
    Left = 8
    Top = 80
    Width = 30
    Height = 13
    Caption = 'Errors:'
  end
  object errorLabel: TLabel
    Left = 72
    Top = 80
    Width = 400
    Height = 13
    AutoSize = False
    Caption = '-'
  end
  object StatusLabel: TLabel
    Left = 72
    Top = 104
    Width = 400
    Height = 13
    AutoSize = False
    Caption = '-'
  end
  object Label7: TLabel
    Left = 8
    Top = 104
    Width = 33
    Height = 13
    Caption = 'Status:'
  end
  object Label4: TLabel
    Left = 8
    Top = 128
    Width = 26
    Height = 13
    Caption = 'Time:'
  end
  object TimeLabel: TLabel
    Left = 72
    Top = 128
    Width = 400
    Height = 13
    AutoSize = False
    Caption = '-'
  end
  object Label6: TLabel
    Left = 208
    Top = 156
    Width = 71
    Height = 13
    Caption = 'Days To Keep:'
  end
  object CancelCloseButton: TButton
    Left = 88
    Top = 184
    Width = 75
    Height = 25
    Caption = 'Cancel'
    TabOrder = 1
    OnClick = CancelCloseButtonClick
  end
  object StartStopButton: TButton
    Left = 8
    Top = 184
    Width = 75
    Height = 25
    Caption = 'Start'
    TabOrder = 0
    OnClick = StartStopButtonClick
  end
  object summarizeCheckBox: TCheckBox
    Left = 104
    Top = 155
    Width = 97
    Height = 17
    Caption = 'incl. Summarize'
    TabOrder = 2
  end
  object DaysToKeepEdit: TEdit
    Left = 278
    Top = 155
    Width = 33
    Height = 21
    TabOrder = 3
    Text = '31'
  end
  object DaysToKeep: TUpDown
    Left = 311
    Top = 155
    Width = 42
    Height = 21
    Associate = DaysToKeepEdit
    Min = 1
    Max = 366
    Orientation = udHorizontal
    Position = 31
    TabOrder = 4
    Wrap = False
  end
  object CheckBoxIgnoreErrors: TCheckBox
    Left = 8
    Top = 155
    Width = 81
    Height = 17
    Caption = 'Ignore Errors'
    TabOrder = 5
  end
  object threadTimer: TTimer
    Enabled = False
    OnTimer = threadTimerTimer
    Left = 448
    Top = 152
  end
end
