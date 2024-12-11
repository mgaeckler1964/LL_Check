object DeleteDateForm: TDeleteDateForm
  Left = 672
  Top = 303
  BorderStyle = bsDialog
  Caption = 'Delete old Entries'
  ClientHeight = 95
  ClientWidth = 342
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 16
    Width = 105
    Height = 13
    Caption = 'Min. Date to preserve:'
  end
  object DateTimePicker: TDateTimePicker
    Left = 136
    Top = 16
    Width = 186
    Height = 21
    CalAlignment = dtaLeft
    Date = 41758
    Time = 41758
    DateFormat = dfLong
    DateMode = dmComboBox
    Kind = dtkDate
    ParseInput = False
    TabOrder = 0
  end
  object ButtonOK: TButton
    Left = 8
    Top = 56
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 1
  end
  object ButtonCancel: TButton
    Left = 88
    Top = 56
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 2
  end
end
