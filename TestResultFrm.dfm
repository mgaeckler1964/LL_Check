object TestResultForm: TTestResultForm
  Left = 572
  Top = 418
  Width = 525
  Height = 257
  Caption = 'Test Result'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object StringGridResult: TStringGrid
    Left = 0
    Top = 0
    Width = 517
    Height = 230
    Align = alClient
    ColCount = 3
    FixedCols = 0
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing]
    TabOrder = 0
    ColWidths = (
      64
      64
      64)
  end
end
