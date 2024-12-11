object httpAutoCheckForm: ThttpAutoCheckForm
  Left = 1049
  Top = 397
  Width = 192
  Height = 199
  Caption = 'Automatic Checks'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 76
    Height = 13
    Caption = 'Min. User Count'
  end
  object Label2: TLabel
    Left = 8
    Top = 40
    Width = 79
    Height = 13
    Caption = 'Max. User Count'
  end
  object Label3: TLabel
    Left = 8
    Top = 72
    Width = 72
    Height = 13
    Caption = 'User Increment'
  end
  object Label4: TLabel
    Left = 8
    Top = 104
    Width = 74
    Height = 13
    Caption = 'Max. Avg. Time'
  end
  object MinUserEdit: TEdit
    Left = 96
    Top = 8
    Width = 49
    Height = 21
    TabOrder = 0
    Text = '1'
  end
  object MaxUserEdit: TEdit
    Left = 96
    Top = 40
    Width = 49
    Height = 21
    TabOrder = 2
    Text = '1'
  end
  object UserIncementEdit: TEdit
    Left = 96
    Top = 72
    Width = 49
    Height = 21
    TabOrder = 4
    Text = '1'
  end
  object MaxAvgTimeEdit: TEdit
    Left = 96
    Top = 104
    Width = 49
    Height = 21
    TabOrder = 6
    Text = '0'
  end
  object StartButton: TButton
    Left = 8
    Top = 136
    Width = 75
    Height = 25
    Caption = 'Start'
    Default = True
    ModalResult = 1
    TabOrder = 7
  end
  object CancelButton: TButton
    Left = 88
    Top = 136
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 8
  end
  object MinUserUpDown: TUpDown
    Left = 145
    Top = 8
    Width = 21
    Height = 21
    Associate = MinUserEdit
    Min = 1
    Position = 1
    TabOrder = 1
    Wrap = False
  end
  object MaxUserUpDown: TUpDown
    Left = 145
    Top = 40
    Width = 21
    Height = 21
    Associate = MaxUserEdit
    Min = 1
    Max = 1000
    Position = 1
    TabOrder = 3
    Wrap = False
  end
  object UserIncrementUpDown: TUpDown
    Left = 145
    Top = 72
    Width = 21
    Height = 21
    Associate = UserIncementEdit
    Min = 1
    Position = 1
    TabOrder = 5
    Wrap = False
  end
  object MaxAvgTimeUpDown: TUpDown
    Left = 145
    Top = 104
    Width = 21
    Height = 21
    Associate = MaxAvgTimeEdit
    Min = 0
    Position = 0
    TabOrder = 9
    Wrap = False
  end
end
