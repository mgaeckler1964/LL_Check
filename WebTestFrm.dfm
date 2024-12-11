object WebTestForm: TWebTestForm
  Left = 391
  Top = 381
  Width = 873
  Height = 658
  Caption = 'Automatic Web Tests'
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
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 185
    Top = 25
    Width = 5
    Height = 594
    Cursor = crHSplit
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 857
    Height = 25
    Align = alTop
    TabOrder = 0
    object SpeedButtonNew: TSpeedButton
      Left = 0
      Top = 0
      Width = 23
      Height = 22
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000130B0000130B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF0033333333B333
        333B33FF33337F3333F73BB3777BB7777BB3377FFFF77FFFF77333B000000000
        0B3333777777777777333330FFFFFFFF07333337F33333337F333330FFFFFFFF
        07333337F33333337F333330FFFFFFFF07333337F33333337F333330FFFFFFFF
        07333FF7F33333337FFFBBB0FFFFFFFF0BB37777F3333333777F3BB0FFFFFFFF
        0BBB3777F3333FFF77773330FFFF000003333337F333777773333330FFFF0FF0
        33333337F3337F37F3333330FFFF0F0B33333337F3337F77FF333330FFFF003B
        B3333337FFFF77377FF333B000000333BB33337777777F3377FF3BB3333BB333
        3BB33773333773333773B333333B3333333B7333333733333337}
      NumGlyphs = 2
      OnClick = SpeedButtonNewClick
    end
    object SpeedButtonOpen: TSpeedButton
      Left = 24
      Top = 0
      Width = 23
      Height = 22
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000120B0000120B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00555555555555
        55555555FFFFFFFFFF55555000000000055555577777777775F55500B8B8B8B8
        B05555775F555555575F550F0B8B8B8B8B05557F75F555555575550BF0B8B8B8
        B8B0557F575FFFFFFFF7550FBF0000000000557F557777777777500BFBFBFBFB
        0555577F555555557F550B0FBFBFBFBF05557F7F555555FF75550F0BFBFBF000
        55557F75F555577755550BF0BFBF0B0555557F575FFF757F55550FB700007F05
        55557F557777557F55550BFBFBFBFB0555557F555555557F55550FBFBFBFBF05
        55557FFFFFFFFF7555550000000000555555777777777755555550FBFB055555
        5555575FFF755555555557000075555555555577775555555555}
      NumGlyphs = 2
      OnClick = SpeedButtonOpenClick
    end
    object SpeedButtonSave: TSpeedButton
      Left = 48
      Top = 0
      Width = 23
      Height = 22
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000120B0000120B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        333333FFFFFFFFFFFFF33000077777770033377777777777773F000007888888
        00037F3337F3FF37F37F00000780088800037F3337F77F37F37F000007800888
        00037F3337F77FF7F37F00000788888800037F3337777777337F000000000000
        00037F3FFFFFFFFFFF7F00000000000000037F77777777777F7F000FFFFFFFFF
        00037F7F333333337F7F000FFFFFFFFF00037F7F333333337F7F000FFFFFFFFF
        00037F7F333333337F7F000FFFFFFFFF00037F7F333333337F7F000FFFFFFFFF
        00037F7F333333337F7F000FFFFFFFFF07037F7F33333333777F000FFFFFFFFF
        0003737FFFFFFFFF7F7330099999999900333777777777777733}
      NumGlyphs = 2
      OnClick = SpeedButtonSaveClick
    end
    object SpeedButtonRunTests: TSpeedButton
      Left = 72
      Top = 0
      Width = 23
      Height = 22
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000130B0000130B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        33333333333333333333EEEEEEEEEEEEEEE333FFFFFFFFFFFFF3E00000000000
        00E337777777777777F3E0F77777777770E337F33333333337F3E0F333333333
        70E337F3333F333337F3E0F33303333370E337F3337FF33337F3E0F333003333
        70E337F33377FF3337F3E0F33300033370E337F333777FF337F3E0F333000033
        70E337F33377773337F3E0F33300033370E337F33377733337F3E0F333003333
        70E337F33377333337F3E0F33303333370E337F33373333337F3E0F333333333
        70E337F33333333337F3E0FFFFFFFFFFF0E337FFFFFFFFFFF7F3E00000000000
        00E33777777777777733EEEEEEEEEEEEEEE33333333333333333}
      NumGlyphs = 2
      OnClick = SpeedButtonRunTestsClick
    end
  end
  object TreeView: TTreeView
    Left = 0
    Top = 25
    Width = 185
    Height = 594
    Align = alLeft
    HideSelection = False
    Indent = 19
    TabOrder = 1
    OnChange = TreeViewChange
    OnEdited = TreeViewEdited
  end
  object Panel2: TPanel
    Left = 190
    Top = 25
    Width = 667
    Height = 594
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 2
    object Splitter2: TSplitter
      Left = 0
      Top = 305
      Width = 667
      Height = 5
      Cursor = crVSplit
      Align = alTop
    end
    object Panel3: TPanel
      Left = 0
      Top = 0
      Width = 667
      Height = 48
      Align = alTop
      TabOrder = 0
      object Label1: TLabel
        Left = 8
        Top = 12
        Width = 52
        Height = 13
        Caption = 'Base URL:'
      end
      object ComboBoxBaseURL: TComboBox
        Left = 88
        Top = 12
        Width = 580
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        ItemHeight = 13
        TabOrder = 0
        OnChange = ComboBoxBaseURLChange
      end
    end
    object Panel4: TPanel
      Left = 0
      Top = 48
      Width = 667
      Height = 41
      Align = alTop
      TabOrder = 1
      object LabelStatus: TLabel
        Left = 256
        Top = 8
        Width = 33
        Height = 13
        Caption = 'Status:'
      end
      object ButtonNewCase: TButton
        Left = 8
        Top = 8
        Width = 75
        Height = 25
        Caption = 'New Case'
        TabOrder = 0
        OnClick = ButtonNewCaseClick
      end
      object ButtonNewStep: TButton
        Left = 88
        Top = 8
        Width = 75
        Height = 25
        Caption = 'New Step'
        TabOrder = 1
        OnClick = ButtonNewStepClick
      end
      object ButtonRunStep: TButton
        Left = 168
        Top = 8
        Width = 75
        Height = 25
        Caption = 'Run Step'
        TabOrder = 2
        OnClick = ButtonRunStepClick
      end
    end
    object GroupBoxRequest: TGroupBox
      Left = 0
      Top = 89
      Width = 667
      Height = 216
      Align = alTop
      Caption = 'Request'
      TabOrder = 2
      object Label2: TLabel
        Left = 8
        Top = 24
        Width = 25
        Height = 13
        Caption = 'URL:'
      end
      object Label3: TLabel
        Left = 8
        Top = 56
        Width = 39
        Height = 13
        Caption = 'Method:'
      end
      object Label4: TLabel
        Left = 8
        Top = 88
        Width = 51
        Height = 13
        Caption = 'Parameter:'
      end
      object ComboBoxStepURL: TComboBox
        Left = 88
        Top = 24
        Width = 578
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        ItemHeight = 13
        TabOrder = 0
        OnChange = ComboBoxStepURLChange
      end
      object RadioButtonGet: TRadioButton
        Left = 88
        Top = 56
        Width = 49
        Height = 17
        Caption = 'Get'
        TabOrder = 1
        OnClick = ChangeRequestMethod
      end
      object RadioButtonPost: TRadioButton
        Left = 144
        Top = 56
        Width = 113
        Height = 17
        Caption = 'Post'
        TabOrder = 2
        OnClick = ChangeRequestMethod
      end
      object StringGridParameter: TStringGrid
        Left = 88
        Top = 88
        Width = 578
        Height = 121
        Anchors = [akLeft, akTop, akRight, akBottom]
        ColCount = 2
        FixedCols = 0
        RowCount = 2
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goEditing, goAlwaysShowEditor]
        TabOrder = 3
        OnKeyUp = StringGridParameterKeyUp
        OnSetEditText = StringGridParameterSetEditText
        ColWidths = (
          64
          64)
      end
    end
    object GroupBoxResult: TGroupBox
      Left = 0
      Top = 310
      Width = 667
      Height = 284
      Align = alClient
      Caption = 'Expected Result'
      TabOrder = 3
      object Label5: TLabel
        Left = 8
        Top = 24
        Width = 33
        Height = 13
        Caption = 'Status:'
      end
      object Label6: TLabel
        Left = 8
        Top = 56
        Width = 67
        Height = 13
        Caption = 'Content Type:'
      end
      object Label7: TLabel
        Left = 8
        Top = 96
        Width = 35
        Height = 13
        Caption = 'Values:'
      end
      object CheckBoxStatus: TCheckBox
        Left = 88
        Top = 24
        Width = 145
        Height = 17
        Caption = 'Check HTTP Status OK'
        TabOrder = 0
        OnClick = CheckBoxStatusClick
      end
      object ComboBoxContentType: TComboBox
        Left = 88
        Top = 56
        Width = 578
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        ItemHeight = 13
        TabOrder = 1
        OnChange = ComboBoxContentTypeChange
        Items.Strings = (
          'text/html'
          'text/xml'
          'text/xhtml'
          'text/css'
          'text/javascript'
          'text/plain'
          'image/jpreg'
          'image/gif'
          'image/png')
      end
      object StringGridValues: TStringGrid
        Left = 88
        Top = 96
        Width = 578
        Height = 193
        Anchors = [akLeft, akTop, akRight, akBottom]
        ColCount = 3
        FixedCols = 0
        RowCount = 2
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goEditing, goAlwaysShowEditor]
        TabOrder = 2
        OnKeyUp = StringGridValuesKeyUp
        OnSetEditText = StringGridValuesSetEditText
      end
      object ButtonBrowseHtml: TButton
        Left = 8
        Top = 128
        Width = 75
        Height = 25
        Caption = 'BrowseHtml'
        Enabled = False
        TabOrder = 3
        OnClick = ButtonBrowseHtmlClick
      end
    end
  end
  object OpenDialog: TOpenDialog
    DefaultExt = 'cwt'
    Filter = 'CRESD Web Tests (*.cwt)|*.cwt'
    Title = 'Open Web Test'
    Left = 30
    Top = 113
  end
  object SaveDialog: TSaveDialog
    DefaultExt = 'cwt'
    Filter = 'CRESD Web Tests (*.cwt)|*.cwt'
    Title = 'Save Web Test'
    Left = 30
    Top = 49
  end
end
