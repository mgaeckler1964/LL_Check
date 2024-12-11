object HtmlBrowseForm: THtmlBrowseForm
  Left = 732
  Top = 271
  Width = 446
  Height = 573
  Caption = 'Html Browse'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object TreeViewHTML: TTreeView
    Left = 0
    Top = 0
    Width = 438
    Height = 457
    Align = alClient
    HideSelection = False
    Indent = 19
    ReadOnly = True
    TabOrder = 0
    OnChange = TreeViewHTMLChange
    OnDblClick = TreeViewHTMLDblClick
  end
  object MemoValue: TMemo
    Left = 0
    Top = 457
    Width = 438
    Height = 89
    Align = alBottom
    ReadOnly = True
    TabOrder = 1
  end
end
