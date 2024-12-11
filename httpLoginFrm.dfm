object httpLoginForm: ThttpLoginForm
  Left = 680
  Top = 347
  BorderStyle = bsDialog
  Caption = 'Login'
  ClientHeight = 105
  ClientWidth = 465
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 51
    Height = 13
    Caption = 'Username:'
  end
  object Label2: TLabel
    Left = 8
    Top = 40
    Width = 49
    Height = 13
    Caption = 'Password:'
  end
  object UsernameEdit: TEdit
    Left = 72
    Top = 8
    Width = 377
    Height = 21
    TabOrder = 0
  end
  object PasswordEdit: TEdit
    Left = 72
    Top = 40
    Width = 377
    Height = 21
    PasswordChar = '*'
    TabOrder = 1
  end
  object LoginButton: TButton
    Left = 8
    Top = 72
    Width = 75
    Height = 25
    Caption = 'Login'
    Default = True
    ModalResult = 1
    TabOrder = 2
  end
  object CancelButton: TButton
    Left = 88
    Top = 72
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 3
  end
end
