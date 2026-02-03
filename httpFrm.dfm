object httpForm: ThttpForm
  Left = 310
  Top = 390
  Width = 900
  Height = 469
  Caption = 'HTTP'
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
  object CommandPanel: TPanel
    Left = 0
    Top = 0
    Width = 884
    Height = 169
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    object Label5: TLabel
      Left = 8
      Top = 12
      Width = 16
      Height = 13
      Caption = 'Url:'
    end
    object Label6: TLabel
      Left = 8
      Top = 108
      Width = 32
      Height = 13
      Caption = 'Loops:'
    end
    object Label7: TLabel
      Left = 104
      Top = 108
      Width = 25
      Height = 13
      Caption = 'User:'
    end
    object Label8: TLabel
      Left = 587
      Top = 108
      Width = 117
      Height = 13
      Anchors = [akTop, akRight]
      Caption = 'Avg. Gets/Size/Time (s):'
    end
    object Label9: TLabel
      Left = 8
      Top = 36
      Width = 41
      Height = 13
      Caption = 'Cookies:'
    end
    object Label1: TLabel
      Left = 8
      Top = 60
      Width = 53
      Height = 13
      Caption = 'Proxy/Port:'
    end
    object Label2: TLabel
      Left = 200
      Top = 108
      Width = 30
      Height = 13
      Caption = 'Delay:'
    end
    object Label3: TLabel
      Left = 8
      Top = 84
      Width = 61
      Height = 13
      Caption = 'User/Passw:'
    end
    object GetButton: TButton
      Left = 88
      Top = 136
      Width = 75
      Height = 25
      Caption = 'Get'
      TabOrder = 17
      OnClick = GetButtonClick
    end
    object LoginButton: TButton
      Left = 328
      Top = 136
      Width = 75
      Height = 25
      Caption = 'LL Login'
      TabOrder = 20
      OnClick = LoginButtonClick
    end
    object LoopsEdit: TEdit
      Left = 40
      Top = 104
      Width = 33
      Height = 21
      Hint = 'Number of requests per user'
      TabOrder = 6
      Text = '1'
      OnChange = enableDisableAnchors
    end
    object LoopCount: TUpDown
      Left = 73
      Top = 104
      Width = 21
      Height = 21
      Associate = LoopsEdit
      Min = 1
      Max = 9999
      Position = 1
      TabOrder = 7
      Wrap = False
    end
    object UserCountEdit: TEdit
      Left = 136
      Top = 104
      Width = 33
      Height = 21
      Hint = 'Number of users to simulate'
      TabOrder = 8
      Text = '1'
      OnChange = enableDisableAnchors
    end
    object UserCount: TUpDown
      Left = 169
      Top = 104
      Width = 21
      Height = 21
      Associate = UserCountEdit
      Min = 1
      Max = 10000
      Position = 1
      TabOrder = 9
      Wrap = False
    end
    object TimeEdit: TEdit
      Left = 706
      Top = 104
      Width = 171
      Height = 21
      Anchors = [akTop, akRight]
      TabOrder = 15
    end
    object CookieEdit: TEdit
      Left = 80
      Top = 32
      Width = 797
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 1
    end
    object GetLocationButton: TButton
      Left = 248
      Top = 136
      Width = 75
      Height = 25
      Caption = 'Get Location'
      Enabled = False
      TabOrder = 19
      OnClick = GetLocationButtonClick
    end
    object Complete: TCheckBox
      Left = 288
      Top = 106
      Width = 65
      Height = 17
      Caption = 'Complete'
      TabOrder = 12
      OnClick = enableDisableAnchors
    end
    object ProxyServer: TEdit
      Left = 80
      Top = 56
      Width = 672
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 2
    end
    object ProxyPort: TEdit
      Left = 756
      Top = 56
      Width = 121
      Height = 21
      Anchors = [akTop, akRight]
      TabOrder = 3
    end
    object CheckBoxAnchors: TCheckBox
      Left = 360
      Top = 106
      Width = 57
      Height = 17
      Caption = 'Anchors'
      TabOrder = 13
      OnClick = enableDisableAnchors
    end
    object DelayEdit: TEdit
      Left = 232
      Top = 104
      Width = 33
      Height = 21
      Hint = 'Number of seconds between the start of new users'
      TabOrder = 10
      Text = '0'
      OnChange = enableDisableAnchors
    end
    object Delay: TUpDown
      Left = 265
      Top = 104
      Width = 15
      Height = 21
      Associate = DelayEdit
      Min = 0
      Position = 0
      TabOrder = 11
      Wrap = False
    end
    object UrlEdit: TComboBox
      Left = 80
      Top = 8
      Width = 797
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      ItemHeight = 13
      Sorted = True
      TabOrder = 0
    end
    object HeadButton: TButton
      Left = 8
      Top = 136
      Width = 75
      Height = 25
      Caption = 'Head'
      TabOrder = 16
      OnClick = GetButtonClick
    end
    object AutoCheckButton: TButton
      Left = 168
      Top = 136
      Width = 75
      Height = 25
      Caption = 'Auto Check...'
      TabOrder = 18
      OnClick = AutoCheckButtonClick
    end
    object CheckBoxCache: TCheckBox
      Left = 432
      Top = 136
      Width = 97
      Height = 17
      Caption = 'Cache'
      TabOrder = 21
    end
    object EditUserName: TEdit
      Left = 80
      Top = 80
      Width = 476
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 4
    end
    object EditPassword: TEdit
      Left = 563
      Top = 80
      Width = 314
      Height = 21
      Anchors = [akTop, akRight]
      TabOrder = 5
    end
    object CheckBoxExternal: TCheckBox
      Left = 424
      Top = 106
      Width = 73
      Height = 17
      Caption = 'External'
      TabOrder = 14
    end
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 169
    Width = 884
    Height = 261
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 1
    object TabSheet1: TTabSheet
      Caption = 'Head'
      object HeadMemo: TMemo
        Left = 0
        Top = 0
        Width = 876
        Height = 233
        Align = alClient
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 0
        WordWrap = False
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Status'
      ImageIndex = 1
      object MemoStatus: TMemo
        Left = 0
        Top = 0
        Width = 737
        Height = 245
        Align = alClient
        ReadOnly = True
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
    object TabSheetError: TTabSheet
      Caption = 'Errors'
      ImageIndex = 3
      object MemoErrors: TMemo
        Left = 0
        Top = 0
        Width = 737
        Height = 245
        Align = alClient
        ScrollBars = ssBoth
        TabOrder = 0
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Body'
      ImageIndex = 2
      object BodyMemo: TMemo
        Left = 0
        Top = 0
        Width = 884
        Height = 245
        Align = alClient
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 0
        WantReturns = False
        WordWrap = False
      end
    end
  end
end
